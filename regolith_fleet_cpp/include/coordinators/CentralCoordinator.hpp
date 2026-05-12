#ifndef CENTRAL_COORDINATOR_HPP
#define CENTRAL_COORDINATOR_HPP

#include "coordinators/Coordinator.hpp"

namespace rf
{
    class CentralCoordinator : public Coordinator
    {
    public:
        std::string Name() const override;

        void Initialize(const Map& map,
                        const std::vector<RobotState>& initial_robot_states,
                        const std::vector<Task>& tasks) override;

        void UpdateAssignments(const Map& map,
                            std::vector<RobotState>& robot_states,
                            std::vector<Task>& tasks,
                            int current_tick) override;

    private:
        // Future place for reservation tables, global assignment logic, etc.
    };
}  // namespace rf

#endif