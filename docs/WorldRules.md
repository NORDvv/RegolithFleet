Cells

obstacle
free
target excavation
depot
excavated

Robot state

position
carrying or not
current task
mode: to_target / digging / returning / dumping / waiting

Timing

move = 1 tick
dig = 1 or N ticks
dump = 1 tick

Conflict rules

no two robots in one cell
no head-on swaps in one tick
blocked move counts as congestion
reroute counts separately

Excavation rule
A target cell becomes excavated only after a robot reaches it and performs dig action.