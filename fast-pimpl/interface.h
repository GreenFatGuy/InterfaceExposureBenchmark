#pragma once

#include <cstdint>
#include <span>

#include "pimpl.h"

struct FastPimplImpl {
    static FastPimplImpl* create();
    ~FastPimplImpl();               // Required for Pimpl to work. Destructor implementation should not be exposed in .h file explicitly or implicitly.

    void doSomething(std::span<int> s);
    int64_t doSomething();

private:
    struct Impl;

    FastPimpl<Impl, sizeof(int64_t), alignof(int64_t)> pimpl;
};
