## First Part:

1. Reads robot positions (`p`) and velocities (`v`) from `input.txt`.
2. Advances each robot's position by **100 time steps** (via `100 * vx` and `100 * vy`), with positions wrapping modulo `101x103` grid dimensions.
3. Excludes robots on central axes (`x=50`, `y=51`) and counts robots in the four quadrants
4. Multiplies the counts of all quadrants and prints the result.

## Second Part:

The trick used is: If most of the robots arrange themselves into a picture of a Christmas tree, we assume that no two robots will be on the same grid cell.

1. Stores robots' initial positions and velocities in a vector.
2. Simulates each time step starting from **t=1**, updating robot positions as `initial + velocity * t`, with wrapping on `101x103` grid.
3. Uses a boolean grid to detect collisions (two robots in the same position). Stops at the first time step with **no collisions**.
4. Prints the earliest collision-free time step.
