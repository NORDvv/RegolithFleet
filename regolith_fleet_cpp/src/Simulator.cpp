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

    ResolveConflicts(actions);

    ApplyActions(actions);

    UpdateTaskCompletion();

    UpdateMetrics();

    ++current_tick_;
}

void rf::Simulator::ResolveConflicts(std::vector<PlannedAction>& actions) {
    // Map desired target cell -> indices of actions trying to move there
    std::unordered_map<long long, std::vector<std::size_t>> move_targets;

    auto encode = [](const Position& p) -> long long {
        return (static_cast<long long>(p.row) << 32) | static_cast<unsigned int>(p.col);
    };

    // First pass: invalidate obviously bad moves
    for (auto& action : actions) {
        if (action.type != ActionType::Move) {
            continue;
        }

        if (!map_.IsInside(action.target_position) || !map_.IsTraversable(action.target_position)) {
            action.type = ActionType::Wait;
            continue;
        }

        move_targets[encode(action.target_position)].push_back(&action - actions.data());
    }

    // Second pass: if multiple robots want same cell, all wait
    for (const auto& [_, indices] : move_targets) {
        if (indices.size() > 1) {
            for (const auto idx : indices) {
                actions[idx].type = ActionType::Wait;
            }
        }
    }

    // Third pass: prevent head-on swaps
    for (std::size_t i = 0; i < actions.size(); ++i) {
        if (actions[i].type != ActionType::Move) {
            continue;
        }

        const Robot* robot_a = FindRobotById(actions[i].robot_id);
        if (robot_a == nullptr) {
            actions[i].type = ActionType::Wait;
            continue;
        }

        for (std::size_t j = i + 1; j < actions.size(); ++j) {
            if (actions[j].type != ActionType::Move) {
                continue;
            }

            const Robot* robot_b = FindRobotById(actions[j].robot_id);
            if (robot_b == nullptr) {
                actions[j].type = ActionType::Wait;
                continue;
            }

            const Position pos_a = robot_a->GetState().position;
            const Position pos_b = robot_b->GetState().position;

            if (actions[i].target_position == pos_b && actions[j].target_position == pos_a) {
                actions[i].type = ActionType::Wait;
                actions[j].type = ActionType::Wait;
            }
        }
    }
}

void rf::Simulator::ApplyActions(const std::vector<PlannedAction>& actions) {
    for (const auto& action : actions) {
        Robot* robot = FindRobotById(action.robot_id);
        if (robot == nullptr) {
            continue;
        }

        RobotState& state = robot->GetState();

        switch (action.type) {
        case ActionType::Move: {
            const bool loaded_before_move = state.carrying_regolith;
            state.position = action.target_position;
            state.total_steps += 1;

            if (loaded_before_move) {
                state.loaded_steps += 1;
                state.mode = RobotMode::ReturningToDepot;
            } else {
                state.unloaded_steps += 1;
                state.mode = RobotMode::MovingToTarget;
            }
            break;
        }

        case ActionType::Dig: {
            const Position& pos = state.position;
            if (map_.GetCell(pos) == CellType::Target && !state.carrying_regolith) {
                map_.SetCell(pos, CellType::Excavated);
                state.carrying_regolith = true;
                state.mode = RobotMode::Digging;
            } else {
                state.mode = RobotMode::Waiting;
                state.waiting_ticks += 1;
            }
            break;
        }

        case ActionType::Dump: {
            const Position& pos = state.position;
            if (map_.GetCell(pos) == CellType::Depot && state.carrying_regolith) {
                state.carrying_regolith = false;
                state.mode = RobotMode::Dumping;

                if (state.current_task_id != -1) {
                    for (auto& task : tasks_) {
                        if (task.id == state.current_task_id) {
                            task.completed = true;
                            task.assigned = false;
                            state.current_task_id = -1;
                            break;
                        }
                    }
                }
            } else {
                state.mode = RobotMode::Waiting;
                state.waiting_ticks += 1;
            }
            break;
        }

        case ActionType::Wait:
        default: {
            state.mode = RobotMode::Waiting;
            state.waiting_ticks += 1;
            break;
        }
        }
    }
}

void rf::Simulator::UpdateTaskCompletion() {
    // TODO: Placeholder for later consistency checks if needed.
}

bool rf::Simulator::IsFinished() const {
    for (const auto& task : tasks_) {
        if (!task.completed) {
            return false;
        }
    }

    return true;
}

const rf::Robot* rf::Simulator::FindRobotById(int robot_id) const {
    for (const auto& robot : robots_) {
        if (robot.GetState().id == robot_id) {
            return &robot;
        }
    }

    return nullptr;
}