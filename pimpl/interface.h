#pragma once

#include <cstdint>
#include <memory>
#include <span>


struct PimplImpl {
    static PimplImpl* create();
    ~PimplImpl();               // Required for PIMPL to work. Destructor implementation should not be exposed in .h file explicitly or implicitly.

    void doSomething(std::span<int> s);

    int64_t doSomething();

private:
    struct Impl;

    std::unique_ptr<Impl> impl = nullptr;
};
