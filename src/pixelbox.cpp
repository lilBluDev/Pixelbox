#include "pixelbox.h"
#include <iostream>

#include "scenes/default_scene.h"

GLuint shaderProgram = 0;

bool PixelBoxEngine::init() {
    timer.start();

    shaderLoader = ShaderLoader(&fileSystem);

    if (!windowManager.createWindow("PixelBox", 800, 600)) {
        std::cerr << "Failed to create window!" << std::endl;
        return -1;
    }

    std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << std::endl;
    fileSystem.addPrefix("shdr", "assets/shaders/");
    shaderProgram = shaderLoader.loadShader("shdr://default.glsl");
    renderer.setShaderProgram(shaderProgram);

    windowManager.setCurrentScene("PixelBox", "DefaultScene", new DefaultScene());

    return true;
}

void PixelBoxEngine::run() {
    // Main game loop
    bool quit = false;
    while (!quit) {
        timer.update();
        windowManager.handleEvents("PixelBox", quit, timer);
        windowManager.clearScreen();
        shaderLoader.useShader(shaderProgram);
        windowManager.getCurrentScene("PixelBox")->update(timer);
        renderer.renderView(*windowManager.getCurrentScene("PixelBox")->getCamera());
        windowManager.getCurrentScene("PixelBox")->render(&renderer);
        windowManager.updateScreen("PixelBox");
    }
}

void PixelBoxEngine::cleanup() {
    shaderLoader.deleteShader(shaderProgram);
    windowManager.cleanup();
    timer.stop();
    std::cout << "Total runtime: " << timer.totalRuntime() << " seconds" << std::endl;
}

WindowManager& PixelBoxEngine::getWindowManager() {
    return windowManager;
}

FileSystem& PixelBoxEngine::getFileSystem() {
    return fileSystem;
}

Timer& PixelBoxEngine::getTimer() {
    return timer;
}