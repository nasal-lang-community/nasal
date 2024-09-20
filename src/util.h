#ifndef _UTIL_H
#define _UTIL_H


/**
 * @brief Computes 2 raised to the power of n using bit shifting.
 *
 * This function performs the equivalent of 2^n by using the bitwise left-shift operation.
 * It shifts the value 1 by `n` bits to the left, which is equivalent to calculating 2^n.
 *
 * @param n The exponent to which 2 is raised. Should be a non-negative integer.
 *
 * @return The value of 2 raised to the power of `n`.
 *         If `n` is negative or too large, the behavior is undefined.
 *
 * @note This function provides the same functionality as the old POW2() macro (1 << n) but with better
 *       type safety and debugging.
 *
 * @warning Be cautious of large values of `n` which may cause overflow if the return value
 *          exceeds the limits of an `int`. For example, `pow2(31)` on a 32-bit system would
 *          return 0 due to overflow.
 */

inline static int pow2(int n) {
    return 1 << n;
}

#endif
