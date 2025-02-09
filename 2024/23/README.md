## First Part:

This one is pretty simple, so here are just a few key features:

- Uses an adjacency list (`unordered_map<string, unordered_set<string>>`) to store connections.  
- Avoids duplicate edges by enforcing alphabetical order (`a < b`).  
- Iterates through node triplets to check for triangular connections with the `'t'` constraint.

## Second Part:

This one utilizes the well-defined Bron–Kerbosch algorithm with backtracking to efficiently find the largest clique in an undirected graph.

- Uses recursive backtracking with sets `R` (current clique), `P` (potential candidates), and `X` (excluded nodes).  
- Converts the final clique into a sorted vector for ordered output.  
- Optimizes pruning by discarding branches early if they cannot exceed the current largest clique size.
