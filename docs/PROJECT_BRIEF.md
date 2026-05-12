# RegolithFleet — Project Brief

## Project Name
RegolithFleet

## Problem Statement
A team of robots must excavate a predefined set of target cells in a grid-based dig site and transport the removed regolith to a shared depot. The robots must coordinate their movement and task execution while avoiding interference, congestion, and inefficient travel.

## Research Question
How do uncoordinated, centralized, and decentralized coordination strategies affect the efficiency of multi-robot regolith excavation and haulage in a constrained grid-based environment?

## Objectives
- Build a simulation of a multi-robot excavation and haulage task.
- Implement and compare three coordination strategies:
  - Greedy uncoordinated baseline
  - Centralized coordinated strategy
  - Decentralized coordinated strategy
- Measure the effect of these strategies on mission efficiency.

## Primary Metric
- Makespan: total time required to complete the excavation blueprint

## Secondary Metrics
- Total robot travel distance
- Loaded travel distance / time
- Unloaded travel distance / time
- Congestion events
- Replans / reroutes
- Idle / waiting time
- Robot utilization

## Environment
- Grid-based map
- Shared depot
- Excavation targets
- Obstacles / blocked cells
- Traversable free cells

## Robot Capabilities
- Move
- Dig
- Carry one unit of regolith
- Dump at depot
- Wait

## Algorithms to Compare
1. GreedyCoordinator
2. CentralCoordinator
3. DecentralizedCoordinator

## Non-Goals for Version 1
- Full physics simulation
- Detailed soil mechanics
- SLAM / perception
- Sensor simulation
- Gazebo integration
- Continuous planning

## Deliverables
- Working simulator
- RViz-based visualization
- Logged experiment results
- Figures and notes for a conference abstract / paper