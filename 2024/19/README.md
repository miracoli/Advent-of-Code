## First Part:

Uses recursive backtracking with memoization (`std::unordered_map memo`) to cache results of substring checks, optimizing repeated computations.

## Second Part:

Extends Part 1's logic by tracking combinatorial counts (via `uint64_t` memoization) instead of boolean validity, summing all valid decompositions recursively.
