## First Part:

1. Reads grid data from `input.txt`.
2. Uses BFS to traverse from every `'0'` position.
3. Moves to adjacent cells with the next sequential character (e.g., `'0'` → `'1'`).
4. Increments `totalScore` when `'9'` is reached and finally outputs total number of valid paths.


## Second Part:

1. Uses a DP table (`ways`) to track the number of paths reaching each cell.
2. Initializes paths starting at `'0'` with a count of 1.
3. Propagates path counts via BFS, accumulating valid transitions (e.g., `'0'` → `'1'`).
4. Sums all paths reaching `'9'` into `totalWays`.
