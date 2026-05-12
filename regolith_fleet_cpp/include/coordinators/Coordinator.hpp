#ifndef COORDINATOR_HPP
#define COORDINATOR_HPP

#include <string>
#include <vector>

#include "types/RobotState.hpp"
#include "types/Task.hpp"

namespace rf
{
    class Map;

    class Coordinator
    {
    public:
        virtual ~Coordinator() = default;

        virtual std::string Name() const = 0;

        virtual void Initialize(const Map& map,
                                const std::vector<RobotState>& initial_robot_states,
                                const std::vector<Task>& tasks) = 0;

        virtual void UpdateAssignments(const Map& map,
                                    std::vector<RobotState>& robot_states,
                                    std::vector<Task>& tasks,
                                    int current_tick) = 0;
    };
}  // namespace rf

#endif