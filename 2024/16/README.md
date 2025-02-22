## First Part:

- Uses Dijkstra's algorithm with a priority queue to explore minimal-cost paths.
- Tracks state as (cost, x, y, direction), where direction determines movement (4 possible directions).
- Avoids revisiting nodes with higher costs using a visited array.

## Second Part:

- Extends Part 1 to identify all unique grid tiles that lie on any optimal path from start to end.
- After finding the minimal cost, it backtracks using a predecessors structure to trace all optimal paths.
- Uses a BFS to explore all valid predecessors of the end node (E), capturing every tile involved in optimal paths.

