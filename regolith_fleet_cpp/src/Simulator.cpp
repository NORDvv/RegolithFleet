#include "Simulator.hpp"

void rf::Simulator::Run(int max_tics) {
    if (!initialized_) {
        Initialize();
    }

    while (!IsFinished() && current_tick_ < max_tics) {
        Step();
    }

    metrics_.SetTotalTicks(current_tick_);
    summary_ = metrics_.BuildSummary();
}

void rf::Simulator::Initialize() {
    coordinator_->Initialize(map_,BuildRobotStateSnapshot(),tasks_);
    metrics_.Reset();
    current_tick_ = 0;
    initialized_ = true;
}

std::vector<rf::RobotState> rf::Simulator::BuildRobotStateSnapshot() const {
    std::vector<RobotState> snapshot;
    snapshot.reserve(robots_.size());

    for (const rf::Robot& robot : robots_) {
        snapshot.push_back(robot.GetState());
    }

    return snapshot;
}

void rf::Simulator::Step() {
    const std::vector<RobotState> robot_states = BuildRobotStateSnapshot();

    std::vector<PlannedAction> actions = coordinator_->PlanActions(map_, robot_states, tasks_, current_tick_);

    RosolveConflicts(actions);

    ApplyActions(actions);

    UpdateTaskCompletion();

    UpdateMetrics();

    ++current_tick_;
}