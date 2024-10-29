#include "interface.h"

#include <utils/utils.h>

struct PimplImpl::Impl {
    void doSomething(std::span<int> s) {
        utils::doSomething(s);
    }

    int64_t doSomething() {
        return ++data;
    }

    int64_t data = 0;
};

PimplImpl* PimplImpl::create() {
    auto* ptr =  new PimplImpl();
    ptr->impl = std::make_unique<Impl>();
    return ptr;
}

void PimplImpl::doSomething(std::span<int> s) {
    return impl->doSomething(s);
}

int64_t PimplImpl::doSomething() {
    return impl->doSomething();
}

PimplImpl::~PimplImpl() {}
