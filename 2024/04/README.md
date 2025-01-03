## First Part:

    1. The grid is read from input.txt into a vector of strings, where each string represents a row.
    2. An array directions[8][2] defines 8 possible directions (up, down, left, right, diagonals).
    3. For each cell in the grid, it checks if "XMAS" appears in any direction. The position updates according to the direction array.
    4.  If the word matches, the counter is incremented.

## Second Part:

    1. The grid is read from input.txt into a vector of strings, where each string represents a row.
    2. Iterate through the grid, excluding the edges, and checks each 'A' for a specific pattern in adjacent cells. The pattern requires two diagonal pairs:
        - Top-left and bottom-right: ('M' and 'S' or 'S' and 'M')
        - Top-right and bottom-left: ('M' and 'S' or 'S' and 'M')
    4. If the pattern is found around 'A', the count is incremented.
