### First Part:

Nothing to mention here. Implementation is straight forward.

### Second Part:

- Maps sequences of 4 price deltas to a compact 19⁴-sized state space (each delta ∈ [-9, 9] → 19 options after +9 offset).
- Computes state index via `(((Δ1+9)*19 + (Δ2+9))*19 + (Δ3+9))*19 + (Δ4+9)` to avoid collisions.
- Checks `sequenceLastBuyer[stateIndex]` to prevent duplicate updates per buyer.