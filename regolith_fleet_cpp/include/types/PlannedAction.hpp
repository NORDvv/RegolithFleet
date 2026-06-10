#ifndef PLANNED_ACTION_HPP
#define PLANNED_ACTION_HPP

#include "Position.hpp"

namespace rf
{
    enum class ActionType {
        Move,
        Dig,
        Dump,
        Wait,
    };

    struct PlannedAction {
        int robot_id {-1};
        ActionType type {ActionType::Wait};

        // Used to move
        Position target_position {};

        // For debug
        int task_id {-1};
    };
}

#endif