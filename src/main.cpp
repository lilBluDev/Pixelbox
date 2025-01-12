#include "pixelbox.h"
#include <iostream>



int main(int argc, char* argv[]) {
    (void)argc;
    (void)argv;
    
    PixelBoxEngine& engine = PixelBoxEngine::getInstance();
    if (!engine.init()) {
        std::cerr << "Failed to initialize engine!" << std::endl;
        return -1;
    }

    engine.run();
    engine.cleanup();

    return 0;
}
