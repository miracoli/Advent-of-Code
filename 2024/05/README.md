## First Part:

1. Rules are read from `input.txt` into an `unordered_map`.
2. Sequences are processed:
   - Numbers are read into a vector (`seq`) and checked against existing rules using an `unordered_set` (`pos`).
   - If valid, the middle element of the sequence is added to the result.
3. The sum of all valid middle elements is printed.

## Second Part:

1. Rules are read from `input.txt` into an `unordered_map`.
2. Sequences are processed:
   - Numbers are read into a vector (`seq`) and tracked in an `unordered_set` (`pos`).
   - Invalid sequences are sorted, and the middle element is added to the result.
3. The sum of all middle elements from sorted sequences is printed.
