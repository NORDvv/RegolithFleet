# RegolithFleet — Experiment Plan

## Goal
Compare three coordination algorithms for a multi-robot excavation and haulage task under identical map and task conditions.

## Algorithms
1. GreedyCoordinator
2. CentralCoordinator
3. DecentralizedCoordinator

## Maps
### Map A — Open Site
- Few obstacles
- Wide movement space
- Low congestion risk

### Map B — Constrained Site
- Moderate number of obstacles
- Several narrow passages
- Medium congestion risk

### Map C — Bottleneck Site
- Strong choke points near frontier or depot
- High congestion risk

## Fleet Sizes
- 2 robots
- 4 robots
- 6 robots

## Fixed Conditions
- Same excavation blueprint for all algorithms
- Same robot starting positions
- Same movement and action timing rules
- Same carrying capacity
- Same map geometry

## Primary Metric
- Makespan

## Secondary Metrics
- Total travel distance
- Loaded travel time
- Unloaded travel time
- Congestion events
- Reroutes / replans
- Idle time
- Utilization per robot

## First Experiment Set
For each map:
- run GreedyCoordinator with 2, 4, and 6 robots
- run CentralCoordinator with 2, 4, and 6 robots
- run DecentralizedCoordinator with 2, 4, and 6 robots

## Output
- Per-run summary table
- CSV logs
- Plots for:
  - makespan vs fleet size
  - congestion vs fleet size
  - travel distance vs fleet size

## Hypotheses
- GreedyCoordinator will perform worst in congested environments.
- CentralCoordinator will achieve the best makespan in most cases.
- DecentralizedCoordinator may approach centralized performance while being more scalable or robust.