#include "core/window.h"
#include "SDL2/SDL.h"
#include <iostream>
#include "core/scene.h"

WindowManager::WindowManager() : windows() {}

bool WindowManager::createWindow(const std::string& name, int width, int height) {
    if (windows.find(name) != windows.end()) {
        std::cerr << "Window with name \"" << name << "\" already exists!" << std::endl;
        return false;
    }

    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        std::cerr << "SDL could not initialize! SDL_Error: " << SDL_GetError() << std::endl;
        return false;
    }

    // Set OpenGL ES version
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 0);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_ES);

    Window newWindow;
    newWindow.sdlWindow = SDL_CreateWindow(
        name.c_str(),
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
        width, height,
        SDL_WINDOW_OPENGL | SDL_WINDOW_SHOWN | SDL_WINDOW_RESIZABLE
    );

    if (!newWindow.sdlWindow) {
        std::cerr << "Window could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_Quit();
        return false;
    }

    newWindow.glContext = SDL_GL_CreateContext(newWindow.sdlWindow);
    if (!newWindow.glContext) {
        std::cerr << "OpenGL context could not be created! SDL_Error: " << SDL_GetError() << std::endl;
        SDL_DestroyWindow(newWindow.sdlWindow);
        SDL_Quit();
        return false;
    }

    if (!gladLoadGLES2Loader((GLADloadproc)SDL_GL_GetProcAddress)) {
        std::cerr << "Failed to initialize GLAD!" << std::endl;
        SDL_GL_DeleteContext(newWindow.glContext);
        SDL_DestroyWindow(newWindow.sdlWindow);
        SDL_Quit();
        return false;
    }

    newWindow.sceneManager = SceneManager();

    windows[name] = newWindow;
    return true;
}

void WindowManager::setCurrentScene(const std::string& windowName, const std::string& sceneName, Scene* scene) {
    if (windows[windowName].sceneManager.getScene(sceneName) == nullptr && scene != nullptr)
        windows[windowName].sceneManager.addScene(sceneName, scene);
    windows[windowName].sceneManager.setCurrentScene(sceneName);
}

Scene* WindowManager::getCurrentScene(const std::string& windowName) const {
    return windows.at(windowName).sceneManager.getCurrentScene();
}

void WindowManager::handleEvents(const std::string& windowName, bool& quit, Timer timer) {
    SDL_Event e;
    while (SDL_PollEvent(&e) != 0) {
        if (e.type == SDL_QUIT) {
            quit = true;
            windows[windowName].isRunning = false;
        }

        Window& window = windows[windowName];
        auto* currentScene = window.sceneManager.getCurrentScene();

        if (!currentScene) {
            continue;
        }

        // Handle keyboard events
        if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP) {
            bool isPressed = (e.type == SDL_KEYDOWN);
            KeyInputEvent keyEvent(e.key.keysym.sym, isPressed);
            currentScene->handleInputEvent(keyEvent, timer);
        }

        // Handle mouse button events
        if (e.type == SDL_MOUSEBUTTONDOWN || e.type == SDL_MOUSEBUTTONUP) {
            bool isPressed = (e.type == SDL_MOUSEBUTTONDOWN);
            MouseInputEvent mouseEvent(e.button.x, e.button.y, e.button.button, isPressed);
            currentScene->handleInputEvent(mouseEvent, timer);
        }

        // if (e.type == SDL_KEYDOWN) {
        //     Window& window = windows[windowName];
        //     switch (e.key.keysym.sym) {
        //     case SDLK_w:
        //         window.sceneManager.getCurrentScene()->getCamera()->position.y += 0.1f;
        //         break;
            
        //     case SDLK_s:
        //         window.sceneManager.getCurrentScene()->getCamera()->position.y -= 0.1f;
        //         break;
            
        //     case SDLK_a:
        //         window.sceneManager.getCurrentScene()->getCamera()->position.x -= 0.1f;
        //         break;

        //     case SDLK_d:
        //         window.sceneManager.getCurrentScene()->getCamera()->position.x += 0.1f;
        //         break;
            
        //     default:
        //         break;
        //     }
        // }
    }
}

void WindowManager::clearScreen() const {
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f); // Black background
    glClear(GL_COLOR_BUFFER_BIT);
}

void WindowManager::updateScreen(const std::string& windowName) const {
    SDL_GL_SwapWindow(windows.at(windowName).sdlWindow);
    SDL_Delay(16); // Limit to 60 FPS
}

void WindowManager::cleanup() {
    for (auto& [name, window] : windows) {
        if (window.sceneManager.getCurrentScene()) {
            window.sceneManager.getCurrentScene()->cleanup();
        }
        if (window.glContext) {
            SDL_GL_DeleteContext(window.glContext);
        }
        if (window.sdlWindow) {
            SDL_DestroyWindow(window.sdlWindow);
        }
    }
    SDL_Quit();
}
