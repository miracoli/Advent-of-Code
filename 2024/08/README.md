### First Part:
- **Input**: Grid with antennas (non-`.` characters).  
- **Logic**:  
  - For each pair of antennas with the same frequency:  
    1. Compute the vector `(dx, dy)` between them.  
    2. Calculate **two mirrored points** using offsets `-1×` and `2×` the vector.  
    3. Add valid grid points to `antinodes` set.  
- **Output**: Total unique mirrored points within grid bounds.  

### Second Part:
- **Input**: Same as Program 1.  
- **Logic**:  
  - For each antenna pair:  
    1. Extend in **both directions** (`dir = ±1`) along their line.  
    2. Add **all collinear points** via scalar multiples (`a`) until out of bounds.  
- **Output**: Total unique grid points along infinite antenna-pair lines.  
