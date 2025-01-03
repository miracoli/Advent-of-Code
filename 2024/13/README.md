## First Part

1. Read the entire input as a single string.
2. Use a regular expression to extract button positions (A, B) and the prize coordinates.
3. Instead of brute-forcing values for A and B solve a system of linear equations for each match:
   - `a * ax + b * bx = X`
   - `a * ay + b * by = Y`

   These equations describe how the prize coordinates `(X, Y)` are a linear combination of the button positions. The coefficients `a` and `b` are calculated as:

   - `b = (Y * ax - X * ay) / (by * ax - bx * ay)`
   - `a = (X - b * bx) / ax`

   The code verifies that these values satisfy both equations before proceeding.

4. For valid solutions, compute the result as `3 * a + b` and add it to the total.

## Second Part

Same as Part One, but with `10000000000000` added to `X` and `Y`.
