#ifndef GRID_TYPERS_HPP
#define GRID_TYPERS_HPP

namespace rf
{
    enum class CellType
    {
        Obstacle,
        Free,
        Target,
        Depot,
        Excavated
    };

    enum class RobotMode
    {
        Idle,
        MovingToTarget,
        Digging,
        ReturningToDepot,
        Dumping,
        Waiting
    };
}  // namespace rf

#endif