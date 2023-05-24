#pragma once
#include <cmath>
#include <cstdint>
#include <optional>
#include <vector>
#include <algorithm>

template<typename F> std::vector<double> doublons(std::vector<double> tabDouble, F f) {
    if (tabDouble.size() == 0 || tabDouble.size() == 1) {
        return tabDouble;
    }
    std::vector<double> retVector;
    std::sort(tabDouble.begin(), tabDouble.end());
    auto tmpCompare = tabDouble[0];
    retVector.push_back(tabDouble[0]);
    for (uint64_t i = 1; i < tabDouble.size(); ++i) {
        if (!f(tmpCompare, tabDouble[i])) {
            retVector.push_back(tabDouble[i]);
            auto tmpCompare = tabDouble[i];
        }
    }
    return retVector;
}