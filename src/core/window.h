#pragma once

#include <glad/glad.h>
#include <SDL2/SDL.h>
#include <string>
#include <unordered_map>
#include "core/scene.h"
#include "utility/Timer.h"

struct Window {
    SDL_Window* sdlWindow;
    SDL_GLContext glContext;
    bool isRunning;
    SceneManager sceneManager;

    Window() : sdlWindow(nullptr), glContext(nullptr), isRunning(true) {}
    ~Window() = default;
};

class WindowManager {
public:
    WindowManager();
    ~WindowManager() = default;

    bool createWindow(const std::string& name, int width, int height);
    void setCurrentScene(const std::string& windowName, const std::string& sceneName, Scene* scene);
    Scene* getCurrentScene(const std::string& windowName) const;
    void handleEvents(const std::string& windowName, bool& quit, Timer timer);
    void clearScreen() const;
    void updateScreen(const std::string& windowName) const;
    void cleanup();
    
private:
    std::unordered_map<std::string, Window> windows;
};
