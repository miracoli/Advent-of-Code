## First Part:

1. Read the whole input as one big string.
2. Extract movements for buttons (A, B) and the prize using a regex over multiple lines.
3. Instead of brute-forcing values we can do equation solving:

    For each match, it solves the system of linear equations:

    - $$ \left( a \cdot ax + b \cdot bx = X \right)$$

    - $$ \left( a \cdot ay + b \cdot by = Y \right)$$

    These equations represent how the prize coordinates $ \left( (X, Y) \right)$ are derived as linear combinations of the button coordinates. The coefficients $ \left( a \right)$ and $ \left( b \right)$ are unknowns solved using algebraic manipulation:

    - $$ \left( b = \frac{(Y \cdot ax - X \cdot ay)}{(by \cdot ax - bx \cdot ay)} \right)$$
    - $$ \left( a = \frac{(X - b \cdot bx)}{ax} \right)$$
   
    The code verifies that the calculated $ \left( a \right)$ and $ \left( b \right)$ satisfy both equations before proceeding.

4. For valid solutions, the result $ \left( 3 \cdot a + b \right)$ is computed and added to the total.

## Second Part:

Same as Part One, with 10000000000000 added to X and Y.
