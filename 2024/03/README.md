## First Part:

    1. Read the whole content of the input.txt file into a string.
    2. A regular expression (mul(\d{1,3},\d{1,3})) identifies all occurrences of mul(a, b), where a and b are numbers with 1-3 digits.
    3. For each match, the numbers a and b are extracted, converted to integers, multiplied and added to the sum.

## Second Part:

    1. Read the whole content of the input.txt file into a string.
    2. A regular expression (do()|don't()|mul(a, b)) identifies commands (do() and don't()) and the mul(a, b) pattern.
    3. The enable flag keeps track of enable status. do() enables summation. don't() disables summation.
    4. When enable is true, the numbers a and b in mul(a, b) are multiplied, and the result is added to the sum. Otherwise, the match is skipped.
