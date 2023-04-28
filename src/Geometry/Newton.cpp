#include "Newton.h"
#include <optional>
#include <cstdint>
#include <cmath>
#include <iostream>

template<typename F, typename DF>
std::optional<double> newton(F f, DF df, double &guess) {
    constexpr double EPSILON = 1e-5;
    constexpr uint64_t N_MAX_ITERATIONS = 256;
    
    double prevU = firstGuess;
    for(uint64_t i = 0; i < N_MAX_ITERATIONS; ++i) {
        const double fu = f(prevU);
        const double dfu = df(prevU);
        guess = prevU - fu / dfu;
        if (std::fabs(guess - prevU) <= EPSILON)
            return guess;
        prevU = guess;
    }
    return std::nullopt;
}
