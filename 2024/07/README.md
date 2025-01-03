## First Part:

1. Read the input line by line.
2. Instead of brute-forcing all combinations of '+' and '*', we recursively work our way from back to front through the list (nums) and check if the remaining target is divisible or larger so we can subtract.
3. Finally, nums[0] and the (changed) target need to be equal to make it a valid line.
4. If valid, the (original) target is added to the total.

## Second Part:

Same as Part One, with additional handling of multi-digit combinations ('||' operator):
   - In addition to dividing or subtracting, the program now checks if the current number (curr) matches the last digits of the target. If true, it reduces the target by dividing it by a power of 10 corresponding to the length of curr, which effectively means cutting off the digits from the back.
