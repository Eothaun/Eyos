#include <engine/Defines.hpp>

#include <filesystem>
namespace eyos {
class EYOS_API Time{
    public:
        Time() = default;
        Time(const Time & other) = default;
        Time(Time && other) noexcept = default;
        Time& operator=(const Time & other) = default;
        Time& operator=(Time && other) noexcept = default;
    public:
        void Initialize(double maxTimeStep, double maxSteps);
        void Update();
        [[nodiscard]] double GetTime() const { return deltaTime; }
        //Time since application startup.
        [[nodiscard]] double GetTotalTime() const
        {
            return std::chrono::duration_cast<std::chrono::duration<double>>(lastTime - startTime).count();
        }
    public:
        double deltaTime{};
    private:
        std::chrono::high_resolution_clock::time_point startTime{};
        std::chrono::high_resolution_clock::time_point lastTime{};
        double timeLeft{};
        double maxTimeStep{};
        double maxSteps{};
        int steps{};
	};
}