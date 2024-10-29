#pragma once

#include <cstdint>
#include <span>


struct SrcImpl {
    static SrcImpl* create();

    void doSomething(std::span<int> s);
    int64_t doSomething();

    int64_t data = 0;
};
