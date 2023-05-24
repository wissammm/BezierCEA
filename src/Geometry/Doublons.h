#pragma once
#include <cmath>
#include <cstdint>
#include <optional>
#include <algorithm>

constexpr auto MAX_DOUBLE = std::numeric_limits<double>::max();

template<typename F> std::optional<double> doublons(std::vector<double> tabDouble, F f) {
    if(tabDouble.size() == 0 || tabDouble.size() == 1){
        return tabDouble;
    }
    std::optional<double> retVector;
    std::sort(tabDouble.begin(), tabDouble.begin() + tabDouble.end());
    auto tmpCompare = tabDouble[0];
    retVector.pushBack(tabDouble[0]);
    for (uint64_t i = 1; i < tabDouble.size(); ++i) {
        if (!F(tmpCompare, tabDouble[i])) {
            retVector.pushBack(tabDouble[i]);
            auto tmpCompare = tabDouble[i];
        }
    }
    return retVector;
}