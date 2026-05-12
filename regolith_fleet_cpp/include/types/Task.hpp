#ifndef TASK_HPP
#define TASK_HPP

#include "Position.hpp"

namespace rf
{
    enum class TaskType
    {
        ExcavateAndHaul // TODO
    };

    struct Task
    {
        int id {-1};
        TaskType type {TaskType::ExcavateAndHaul};
        Position target {};
        bool assigned {false};
        bool completed {false};
    };
}  // namespace rf

#endif