#pragma once

#include <cstdint>
#include <span>

struct VirtualImpl{
    static VirtualImpl* create();
    virtual ~VirtualImpl() = default;
    virtual void doSomething(std::span<int> s) = 0;
    virtual int64_t doSomething() = 0;
};
