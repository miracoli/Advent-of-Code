### First Part:

1. Reads lock and key schematics from `input.txt`, ignoring the first line as it duplicates the last line's information.  
2. Encodes schematics into `uint32_t` using bitwise operations. Grids with the last line's bit set are categorized as locks; others as keys.  
3. Compares locks and keys using bitwise AND. A pair is valid if the result is `0`, indicating no overlap.  

### Second Part:

No code needed here. Once all other stars are completed, simply click a button to unlock the final star.
