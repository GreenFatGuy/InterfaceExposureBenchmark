#pragma once

#include <span>

namespace utils {

inline void doSomething(std::span<int> s) {
    for (int i = 0; i < s.size(); i++) {
        s[i] = i;
    }
}

} // namespace utils
