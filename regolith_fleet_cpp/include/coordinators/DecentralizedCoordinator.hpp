#ifndef DECENTRALIZED_COORDINATOR_HPP
#define DECENTRALIZED_COORDINATOR_HPP

#include "coordinators/Coordinator.hpp"

namespace rf
{
    class DecentralizedCoordinator : public Coordinator
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
        // Future place for local utility rules, bidding, neighbor-based logic, etc.
    };
}  // namespace rf

#endif