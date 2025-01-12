#pragma once

#include <iostream>
#include <memory>
#include "core/window.h"
#include "utility/Timer.h"
#include "utility/FS.h"
#include "scenes/default_scene.h"
#include "renderer/shaderLoader.h"

class PixelBoxEngine {
public:
    static PixelBoxEngine& getInstance() {
        static PixelBoxEngine instance;
        return instance;
    }

    bool init();
    void run();
    void cleanup();

    WindowManager& getWindowManager();
    FileSystem& getFileSystem();
    Timer& getTimer();
private:
    PixelBoxEngine()
        : shaderLoader(&fileSystem)
    {}
    
    PixelBoxEngine(const PixelBoxEngine&) = delete;
    PixelBoxEngine& operator=(const PixelBoxEngine&) = delete;

    WindowManager windowManager;
    FileSystem fileSystem;
    ShaderLoader shaderLoader;
    Timer timer;
};
