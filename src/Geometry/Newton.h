#pragma once
#include <cmath>
#include <cstdint>
#include <optional>

constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();

struct NewtonOptions
{
    double   epsilon        = 1e-5;
    uint64_t nMaxIterations = 256;
    double   minRange       = -MAX_DOUBLE;
    double   maxRange       = MAX_DOUBLE;
    double   alpha          = 1.0;
};

template<typename F, typename DF>
std::optional<double> newton(F f, DF df, double firstGuess, const NewtonOptions& options = {}) {
    double prevU = firstGuess;
    for (uint64_t i = 0; i < options.nMaxIterations; ++i) {
        const double fu    = f(prevU);
        const double dfu   = df(prevU);
        const double nextU = prevU - options.alpha * (fu / dfu);
        if (std::fabs(nextU - prevU) <= options.epsilon)
            return nextU;
        if (nextU < options.minRange || nextU > options.maxRange)
            return std::nullopt;
        prevU = nextU;
    }
    return std::nullopt;
}