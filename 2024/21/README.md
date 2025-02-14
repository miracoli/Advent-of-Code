## First Part:

- The keypads (numeric and directional) are both represented as a single map with characters mapped to positions (e.g., `7` to `{0, 0}`).
- Avoids the gaps on the keypads depending on the traversal depth (e.g., avoids `(3,0)` at depth 0 (numeric keypad) and `(0,0)` for higher depths(directional keypad)).
- For each path segment, all permutations of horizontal/vertical moves are evaluated to find the shortest valid path.
- Caches intermediate results (see `cache`) to avoid redundant calculations.

## Second Part:

Same as first part but with a limit of 25.
