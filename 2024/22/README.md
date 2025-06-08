### First Part:

We pre-compute at compile time the 24-bit “jump-ahead” mask that represents the effect of 2 000 hash_once steps; then, at run-time, each value is processed with just 24 hash_once calls and at most 24 XORs—eliminating the 1 999 extra iterations per input while giving identical results.

Code to compute it at compile time:


#include <fstream>
#include <iostream>

constexpr uint_fast32_t MOD_MASK = (1u << 24) - 1u;

constexpr uint_fast32_t hash_once(uint_fast32_t x) noexcept {
    x ^= (x << 6) & MOD_MASK;
    x ^= (x >> 5);
    x ^= (x << 11) & MOD_MASK;
    return x & MOD_MASK;
}

constexpr uint_fast32_t jump_masked(uint_fast32_t n, uint_fast32_t mask) {
    uint_fast32_t acc = 0;
    for (uint_fast8_t b = 0; b < 24; ++b) {
        if (mask & 1u) {
            acc ^= n;
        }
        n = hash_once(n);
        mask >>= 1u;
    }
    return acc;
}

constexpr auto build_T_matrix() {
    std::array<uint_fast32_t, 24> T_col{};
    for (int j = 0; j < 24; ++j) {
        T_col[j] = hash_once(1u << j);
    }
    return T_col;
}

constexpr auto compute_sequence() {
    constexpr auto T_col = build_T_matrix();
    std::array<uint_fast32_t, 25> v{};
    v[0] = 1;
    for (int i = 1; i <= 24; ++i) {
        v[i] = 0;
        for (int j = 0; j < 24; ++j) {
            if (v[i-1] & (1u << j)) {
                v[i] ^= T_col[j];
            }
        }
    }
    return v;
}

constexpr uint_fast32_t compute_g() {
    constexpr auto v = compute_sequence();
    std::array<uint_fast32_t, 24> mat{};

    for (int i = 0; i < 24; ++i) {
        uint_fast32_t row = 0;
        for (int j = 0; j < 24; ++j) {
            if (v[j] & (1u << i)) {
                row |= (1u << j);
            }
        }
        if (v[24] & (1u << i)) {
            row |= (1u << 24);
        }
        mat[i] = row;
    }

    for (int col = 0; col < 24; ++col) {
        int pivot = -1;
        for (int r = col; r < 24; ++r) {
            if (mat[r] & (1u << col)) {
                pivot = r;
                break;
            }
        }
        if (pivot == -1) continue;
        if (pivot != col) {
            std::swap(mat[col], mat[pivot]);
        }
        for (int r = col + 1; r < 24; ++r) {
            if (mat[r] & (1u << col)) {
                mat[r] ^= mat[col];
            }
        }
    }

    for (int col = 23; col >= 0; --col) {
        for (int r = 0; r < col; ++r) {
            if (mat[r] & (1u << col)) {
                mat[r] ^= mat[col];
            }
        }
    }

    uint_fast32_t x = 0;
    for (int i = 0; i < 24; ++i) {
        if (mat[i] & (1u << 24)) {
            x |= (1u << i);
        }
    }
    return x;
}

constexpr uint_fast32_t poly_mul(uint_fast32_t a, uint_fast32_t b, uint_fast32_t g) {
    a &= MOD_MASK;
    b &= MOD_MASK;
    uint_fast32_t res = 0;
    for (int i = 0; i < 24; ++i) {
        if (b & (1u << i)) {
            res ^= a;
        }
        a <<= 1;
        if (a & (1u << 24)) {
            a ^= (1u << 24) ^ g;
            a &= MOD_MASK;
        }
    }
    return res;
}

constexpr uint_fast32_t poly_pow(uint_fast32_t base, uint_fast32_t exponent, uint_fast32_t g) {
    uint_fast32_t res = 1;
    while (exponent) {
        if (exponent & 1) {
            res = poly_mul(res, base, g);
        }
        base = poly_mul(base, base, g);
        exponent >>= 1;
    }
    return res;
}

consteval uint_fast32_t derive_poly() {
    constexpr uint_fast32_t g = compute_g();
    constexpr uint_fast32_t base = 2;
    constexpr uint_fast32_t r = poly_pow(base, 2000, g);
    return r;
}

static_assert(0x00F33FA2u == derive_poly(), "computed mask does not match expected POLY");

int main() {
    std::ifstream in("input.txt");
    uint_fast64_t sum = 0;
    uint_fast32_t secret;
    while (in >> secret) {
        sum += jump_masked(secret, derive_poly());
    }
    std::cout << sum << '\n';
}

### Second Part:

- Maps sequences of 4 price deltas to a compact 19⁴-sized state space (each delta ∈ [-9, 9] → 19 options after +9 offset).
- Computes state index via `(((Δ1+9)*19 + (Δ2+9))*19 + (Δ3+9))*19 + (Δ4+9)` to avoid collisions.
- Checks `sequenceLastBuyer[stateIndex]` to prevent duplicate updates per buyer.