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

template<typename F, typename DFU, typename DFV> //
bool newtonRalphson(F f, DFU dfu, DFV dfv, Coord& uv, double uvEpsilon, size_t nMaxIteration) {
    for (size_t iIteration = 0; iIteration < nMaxIteration; ++iIteration) {
        const auto evalF  = f(uv);
        const auto evalFu = dfu(uv);
        const auto evalFv = dfv(uv);

        const auto JF = std::array<double, 4>{evalFu.getX(), evalFv.getX(), evalFu.getY(), evalFv.getY()};

        const auto JFInv = inverse(JF);

        const auto previousUV = uv;
        uv[0] -= JFInv[0] * evalF[0] + JFInv[1] * evalF[1];
        uv[1] -= JFInv[2] * evalF[0] + JFInv[3] * evalF[1];

        if (distance(previousUV, uv) <= uvEpsilon)
            return true;
    }

    return false;
}

inline std::array<double, 4> inverse(const std::array<double, 4>& m) {
    const double det = m[0] * m[3] - m[1] * m[2];

    // clang-format off
    return {
        m[3] / det, -m[1] / det,
        -m[2] / det,  m[0] / det
    };
    // clang-format on
}