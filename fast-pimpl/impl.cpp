#include "interface.h"

#include <utils/utils.h>

struct FastPimplImpl::Impl {
    void doSomething(std::span<int> s) {
        utils::doSomething(s);
    }

    int64_t doSomething() {
        return ++data;
    }

    int64_t data = 0;
};

FastPimplImpl* FastPimplImpl::create() {
    return new FastPimplImpl();
}

void FastPimplImpl::doSomething(std::span<int> s) {
    return pimpl->doSomething(s);
}

int64_t FastPimplImpl::doSomething() {
    return pimpl->doSomething();
}

FastPimplImpl::~FastPimplImpl() {}
