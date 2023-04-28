#pragma once
#include <optional>


template<typename F, typename DF>
std::optional<double> newton(F f, DF df, double &guess);