#pragma once
#include <cmath>
#include <cstdint>
#include <optional>

template<typename F, typename DF>
std::optional<double> newton(F        f,
                             DF       df,
                             double   firstGuess,
                             double   epsilon        = 1e-5,
                             uint64_t nMaxIterations = 256,
                             double   minRange       = -1.,
                             double   maxRange       = 2.,
                             double   learningRate   = 1.0) {
    double prevU = firstGuess;
    for (uint64_t i = 0; i < nMaxIterations; ++i) {
        const double fu    = f(prevU);
        const double dfu   = df(prevU);
        const double nextU = prevU - learningRate * (fu / dfu);
        if (std::fabs(nextU - prevU) <= epsilon)
            return nextU;
        if(nextU < minRange || nextU > maxRange) return std::nullopt;
        prevU = nextU;
    }
    return std::nullopt;
}