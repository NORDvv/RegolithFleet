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

        void Initialize();
        void Run(int max_ticks = 1000000);
        bool IsFinished() const;

        const RunSummary& GetSummary() const;

    private:
        void Step();
        void UpdateMetrics();
        std::vector<RobotState> BuildRobotStateSnapshot() const;
        void RosolveConflicts(std::vector<PlannedAction>& actions);
        void ApplyActions(const std::vector<PlannedAction>& actions);
        void UpdateTaskCompletion();
        void UpdateMetrics();

        Robot* FindRobotById(int robot_id);
        const Robot* FindRobotById(int robot_id) const;

        Map map_;
        std::vector<Robot> robots_;
        std::vector<Task> tasks_;
        std::unique_ptr<Coordinator> coordinator_;
        MetricsCollector metrics_;
        RunSummary summary_;
        int current_tick_ {0};
        bool initialized_ {false};
    };
}  // namespace rf

#endif