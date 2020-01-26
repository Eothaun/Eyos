#include "engine/Time.hpp"

#include <chrono>

namespace
{
    using ms = std::chrono::duration<float, std::milli>;
    using s = std::chrono::duration<float, std::chrono::seconds>;
}


void eyos::Time::Initialize(double maxTimeStep,double maxSteps)
{
    // *** Delta Time *** //
    this->lastTime = std::chrono::high_resolution_clock::now();
    this->startTime = std::chrono::high_resolution_clock::now();
    this->maxTimeStep = maxTimeStep;
    this->maxSteps = maxSteps;
}


void eyos::Time::Update()
{
    // *** DeltaTime *** //
    auto t = std::chrono::high_resolution_clock::now();
    auto time = std::chrono::duration_cast<ms>(t - lastTime).count() / 1000.0;
    lastTime = t;

    steps = static_cast<int>((time / maxTimeStep) + 1);
    if (steps > maxSteps)
        steps = static_cast<int>(maxSteps);

    if (steps == 1)
    {
        deltaTime = time;
        timeLeft = 0.0;
    }
    else
    {
        deltaTime = time / steps;
        timeLeft = std::remainder(time, steps);
    }

}