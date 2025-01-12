#include "Timer.h"

Timer::Timer()
    : deltaTime(0.0f), fps(0.0f), frameCount(0), fpsTimeAccumulator(0.0f), isRunning(false) {}

void Timer::start() {
    startTime = std::chrono::high_resolution_clock::now();
    lastTime = startTime;
    isRunning = true;
}

void Timer::stop() {
    stopTime = std::chrono::high_resolution_clock::now();
    isRunning = false;
}

long long Timer::currentUnixTime() const {
    using namespace std::chrono;
    auto now = system_clock::now();
    auto unixTime = time_point_cast<seconds>(now).time_since_epoch();
    return unixTime.count();
}

float Timer::totalRuntime() const {
    if (isRunning) {
        auto now = std::chrono::high_resolution_clock::now();
        auto elapsed = std::chrono::duration<float>(now - startTime).count();
        return elapsed;
    }
    return std::chrono::duration<float>(stopTime - startTime).count();
}

void Timer::update() {
    if (!isRunning) return;

    auto currentTime = std::chrono::high_resolution_clock::now();
    elapsedTime = std::chrono::duration<float>(currentTime - lastTime);
    lastTime = currentTime;

    deltaTime = elapsedTime.count();
    frameCount++;

    // Accumulate time for FPS calculation
    fpsTimeAccumulator += deltaTime;
    if (fpsTimeAccumulator >= 1.0f) {
        fps = frameCount;
        frameCount = 0;
        fpsTimeAccumulator = 0.0f;
    }
}

float Timer::getDeltaTime() const {
    return deltaTime;
}

float Timer::getFPS() const {
    return fps;
}
