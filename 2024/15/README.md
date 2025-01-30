## First Part:

**Core Mechanics**:  
- **Grid Parsing**:  
  - Tracks robot (`@`), single-cell boxes (`O`), and initial `gpsSum` using `100*y + x` for box coordinates.  
- **Movement Handling**:  
  - Maps direction keys (`<`, `>`, `^`, `v`) to coordinate deltas.  
  - Moves robot/boxes recursively: pushes boxes only if the target cell is empty or another pushable box.  
- **GPS Calculation**:  
  - Updates `gpsSum` by `100*dy + dx` for every valid box push.  
- **Result**: Prints the final accumulated GPS sum.  


## Second Part:

**Enhanced Features**:  
- **Expanded Grid Parsing**:  
  - Converts single-cell boxes (`O`) into **2-cell box segments** (`[]`), doubling grid width.  
  - Tracks robot (`@`), box segments (`[`/`]`), and precomputes `gpsSum` based on leading-edge `[` positions.  
- **Dual-Phase Box Pushing**:  
  1. **Simulation Check**: Validates if a push is possible (`simulate=true`).  
  2. **Execution**: Moves boxes only if the simulation succeeds.  
  - Vertical moves require **both box segments** (`[` and `]`) to clear paths.  
- **Precision GPS Tracking**:  
  - Updates `gpsSum` only when the leading edge (`[`) of a box moves, using `100*dy + dx`.  
- **Grid Swapping**: Maintains box integrity by swapping robot/box segments during valid moves.  
