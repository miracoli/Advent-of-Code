## First Part:

### Key Variables:
- **currentDirection**: Tracks the direction, encoded as an integer (0 = up, 1 = right, 2 = down, 3 = left).
- **directionOffsets**: An array that stores the changes in the x and y coordinates for each direction.

### Steps:
1. **Input Parsing**: The map is read from a file, and the starting position (indicated by '^') is identified.
2. **Movement Simulation**: Moves based on the direction. If the next position is blocked (represented by `#`), turns 90 degrees clockwise. Otherwise, continues moving to the next position until it eventually leaves the map.
3. **Tracking Visited Locations**: A set is used to track all the unique coordinates visited.
4. The size of the set is the answer we are looking for.

## Second Part:

1. Does the same as the first part to get the set of all the unique coordinates visited.
2. To get the count of endless loops:
   - An obstacle is temporarily placed.
   - The navigation logic checks if it results in an endless loop (repeated states of position **AND** direction).
   - To improve performance, obstacles are only placed on the coordinates visited in the first part.
   - To improve performance even further, tracking the state of positions and direction for endless loop detection is only done when the direction changes.
