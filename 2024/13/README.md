## First Part:

1. Read the whole input as one big string.
2. Extract movements for buttons (A, B) and the prize using a regex over multiple lines.
3. Instead of brute-forcing values we can do equation solving:

    For each match, it solves the system of linear equations:

    - \( a \cdot ax + b \cdot bx = X \)
    - \( a \cdot ay + b \cdot by = Y \)

    These equations represent how the prize coordinates \( (X, Y) \) are derived as linear combinations of the button coordinates. The coefficients \( a \) and \( b \) are unknowns solved using algebraic manipulation:

    - \( b = \frac{(Y \cdot ax - X \cdot ay)}{(by \cdot ax - bx \cdot ay)} \)
    - \( a = \frac{(X - b \cdot bx)}{ax} \)
   
    The code verifies that the calculated \( a \) and \( b \) satisfy both equations before proceeding.

4. For valid solutions, the result \( 3 \cdot a + b \) is computed and added to the total.

## Second Part:

Same as Part One, with 10000000000000 added to X and Y.
