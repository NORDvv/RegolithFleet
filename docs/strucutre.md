RegolithFleet/
├── README.md
├── docs/
│   ├── PROJECT_BRIEF.md
│   ├── SIM_RULES.md
│   └── EXPERIMENT_PLAN.md
├── regolith_fleet_cpp/
│   ├── include/
│   │   ├── types/
│   │   │   ├── Position.hpp
│   │   │   ├── GridTypes.hpp
│   │   │   ├── RobotState.hpp
│   │   │   └── Task.hpp
│   │   ├── core/
│   │   │   ├── Map.hpp
│   │   │   ├── Robot.hpp
│   │   │   ├── Simulator.hpp
│   │   │   └── MetricsCollector.hpp
│   │   └── coordinators/
│   │       ├── Coordinator.hpp
│   │       ├── GreedyCoordinator.hpp
│   │       ├── CentralCoordinator.hpp
│   │       └── DecentralizedCoordinator.hpp
│   └── src/
│       ├── Map.cpp
│       ├── Robot.cpp
│       ├── Simulator.cpp
│       ├── MetricsCollector.cpp
│       ├── GreedyCoordinator.cpp
│       ├── CentralCoordinator.cpp
│       └── DecentralizedCoordinator.cpp
└── analysis/
    └── results_placeholder.csv