#ifndef SIMULATOR_HPP
#define SIMULATOR_HPP

#include <memory>
#include <vector>

#include "core/Map.hpp"
#include "core/MetricsCollector.hpp"
#include "core/Robot.hpp"
#include "coordinators/Coordinator.hpp"
#include "types/Task.hpp"

namespace rf
{
    class Simulator
    {
    public:
        explicit Simulator(std::unique_ptr<Coordinator> coordinator);

        void SetMap(Map map);
        void SetRobots(std::vector<Robot> robots);
        void SetTasks(std::vector<Task> tasks);

        void Run();
        bool IsFinished() const;

        const RunSummary& GetSummary() const;

    private:
        void Step();
        void ResolveActions();
        void UpdateMetrics();

    private:
        Map map_;
        std::vector<Robot> robots_;
        std::vector<Task> tasks_;
        std::unique_ptr<Coordinator> coordinator_;
        MetricsCollector metrics_;
        RunSummary summary_;
        int current_tick_ {0};
    };
}  // namespace rf

#endif