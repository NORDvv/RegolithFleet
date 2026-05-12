#ifndef METRICS_COLLECTOR_HPP
#define METRICS_COLLECTOR_HPP

#include <vector>

#include "types/RobotState.hpp"

namespace rf
{
    struct RunSummary
    {
        int total_ticks {0};
        int total_steps {0};
        int total_loaded_steps {0};
        int total_unloaded_steps {0};
        int total_waiting_ticks {0};
        int total_congestion_events {0};
        int total_reroute_events {0};
    };

    class MetricsCollector
    {
    public:
        void Reset();

        void RecordTick(const std::vector<RobotState>& robot_states); // TODO consider data race events
        void SetTotalTicks(int ticks);

        RunSummary BuildSummary() const;

    private:
        RunSummary summary_;
    };
}  // namespace rf

#endif