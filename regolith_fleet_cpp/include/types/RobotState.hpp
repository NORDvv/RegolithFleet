#ifndef ROBOT_STATE_HPP
#define ROBOT_STATE_HPP

#include <optional>

#include "GridTypes.hpp"
#include "Position.hpp"
#include "Task.hpp"

namespace rf
{
    struct RobotState
    {
        int id {-1};
        Position position {};
        RobotMode mode {RobotMode::Idle};
        bool carrying_regolith {false};
        std::optional<Task> current_task {}; //TODO fix

        int total_steps {0};
        int loaded_steps {0};
        int unloaded_steps {0};
        int waiting_ticks {0};
        int congestion_events {0};
        int reroute_events {0};
    };
}  // namespace rf

#endif