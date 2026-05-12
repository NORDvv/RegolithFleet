#ifndef ROBOT_HPP
#define ROBOT_HPP

#include "types/RobotState.hpp"

namespace rf
{
    class Robot
    {
    public:
        explicit Robot(RobotState initial_state);

        const RobotState& GetState() const;
        RobotState& GetState();

    private:
        RobotState state_;
    };
}  // namespace rf

#endif