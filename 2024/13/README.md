GitHub does not natively support MathJax or LaTeX for rendering equations, so formulas must be written using plain text and simple Markdown. Here's an adjusted version that works better with GitHub's limitations:

---

## First Part

1. Read the entire input as a single string.
2. Use a regular expression to extract button positions (A, B) and the prize coordinates.
3. Solve a system of linear equations for each match:
   - `a * ax + b * bx = X`
   - `a * ay + b * by = Y`

   These equations describe how the prize coordinates `(X, Y)` are a linear combination of the button positions. The coefficients `a` and `b` are calculated as:

   - `b = (Y * ax - X * ay) / (by * ax - bx * ay)`
   - `a = (X - b * bx) / ax`

   The code verifies that these values satisfy both equations before proceeding.

4. For valid solutions, compute the result as `3 * a + b` and add it to the total.

## Second Part

Same as Part One, but with `10000000000000` added to `X` and `Y`.

---

This format avoids special characters that GitHub cannot render and ensures the formulas are displayed in a readable format.
