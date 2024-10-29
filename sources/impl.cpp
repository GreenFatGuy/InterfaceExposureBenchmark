#include "interface.h"

#include <utils/utils.h>

SrcImpl* SrcImpl::create() {
    return new SrcImpl();
}

void SrcImpl::doSomething(std::span<int> s) {
    utils::doSomething(s);
}

int64_t SrcImpl::doSomething() {
    return ++data;
}
