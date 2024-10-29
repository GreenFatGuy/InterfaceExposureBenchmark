#include "interface.h"

#include <utils/utils.h>

#ifdef DERIVE_FINAL
#define OVERRIDE final
#else
#define OVERRIDE override
#endif

struct Impl : public VirtualImpl {
    static Impl* create() {
        return new Impl();
    }

    void doSomething(std::span<int> s) OVERRIDE {
        utils::doSomething(s);
    }

    int64_t doSomething() OVERRIDE {
        return ++data;
    }

    int64_t data = 0;
};

VirtualImpl* VirtualImpl::create() {
    return Impl::create();
}
