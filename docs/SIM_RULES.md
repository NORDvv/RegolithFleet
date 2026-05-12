# RegolithFleet — Simulation Rules

## 1. Map Cell Types
- `Obstacle`: impassable terrain
- `Free`: traversable terrain
- `Target`: cell containing regolith that must be excavated
- `Depot`: starting location and dump location
- `Excavated`: previously excavated target cell

## 2. Robot State
Each robot has:
- Unique ID
- Position
- Current mode
- Whether it is carrying regolith
- Current assigned task (optional)
- Statistics counters

## 3. Robot Modes
- `Idle`
- `MovingToTarget`
- `Digging`
- `ReturningToDepot`
- `Dumping`
- `Waiting`

## 4. Robot Actions
### Move
A robot moves by one grid cell per simulation tick.

### Dig
A robot excavates one target cell.
- Default cost: 1 tick
- Result:
  - target cell becomes excavated
  - robot becomes loaded

### Carry
The robot may carry exactly one unit of regolith.

### Dump
At the depot, the robot dumps the carried regolith.
- Default cost: 1 tick
- Result:
  - robot becomes unloaded

### Wait
Robot does nothing for one tick.

## 5. Conflict Rules
- Two robots may not occupy the same cell in the same tick.
- Two robots may not swap positions in the same tick.
- If movement fails due to another robot, this counts as a congestion event.
- If an algorithm changes a route because of blockage, this counts as a reroute / replan.

## 6. Excavation Rules
- A target cell is considered complete only after a robot reaches it and performs the dig action.
- Once excavated, the cell changes state from `Target` to `Excavated`.
- Excavated cells are traversable.

## 7. Depot Rules
- All robots start at the depot or predefined cells adjacent to the depot.
- Regolith must be returned to the depot to count as successfully removed.
- A task is fully complete only after excavation and successful dump.

## 8. Completion Condition
The simulation ends when:
- all target cells have been excavated, and
- all excavated regolith has been delivered to the depot

## 9. Tick Model
The simulator advances in discrete ticks.
At each tick:
1. Coordinator updates assignments / intentions
2. Robots attempt actions
3. Conflicts are resolved
4. Metrics are updated
5. Simulation state is logged