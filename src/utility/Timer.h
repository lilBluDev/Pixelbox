#pragma once

#include <chrono>
#include <iostream>

class Timer {
public:
    Timer();

    // Start the timer
    void start();

    // Stop the timer
    void stop();

    // Get the current Unix timestamp in seconds
    long long currentUnixTime() const;

    // Get the total app runtime in seconds
    float totalRuntime() const;

    // Update the delta time and FPS
    void update();

    // Get the delta time (time per frame in seconds)
    float getDeltaTime() const;

    // Get the current FPS (frames per second)
    float getFPS() const;

private:
    // Time tracking variables
    std::chrono::high_resolution_clock::time_point startTime;
    std::chrono::high_resolution_clock::time_point stopTime;
    std::chrono::high_resolution_clock::time_point lastTime;
    std::chrono::duration<float> elapsedTime;
    float deltaTime;
    float fps;
    int frameCount;
    float fpsTimeAccumulator;
    bool isRunning;
};
