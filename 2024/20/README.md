## First Part:

- Uses a wall-following algorithm for pathfinding.
- Tracks every position from the start until the exit is reached.
- **Cheat Detection**:  
   - Checks all pairs of positions `(i, j)` in the path.  
   - Valid cheats must:  
     - Have **Manhattan distance ≤ 2** between `i` and `j`.  
     - Save **≥100 picoseconds** (difference between path length `(j - i)` and cheat distance).  

## Second Part:

Same as first part but with a maximumCheatDistance of 20.
