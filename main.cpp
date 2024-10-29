#include <benchmark/benchmark.h>

#include <array>

#include <sources/interface.h>
#include <pimpl/interface.h>
#include <fast-pimpl/interface.h>
#include <virtual/interface.h>

int64_t sum(std::span<int> vec) {
    int64_t sum = 0;
    for (int i = 0; i < vec.size(); i++) {
        sum += vec[i];
    }
    return sum;
}

template <typename Impl, std::size_t Size>
static void BM_ArrayLoadLibraryExposure(benchmark::State& state) {
    auto* impl = Impl::create();

    std::array<int, Size> vec;
    int64_t sum = 0;

    for (auto _ : state) {
        impl->doSomething(vec);
        benchmark::DoNotOptimize(sum += ::sum(vec));
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(2 * sizeof(int) * Size * state.iterations());

    delete impl;
}

#define BENCHMARK_ARR_EXPOSURE(Impl)                              \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 1);     \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 4);     \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 16);    \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 64);    \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 512);   \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 2048);  \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 8192);  \
    BENCHMARK_TEMPLATE(BM_ArrayLoadLibraryExposure, Impl, 32768)

BENCHMARK_ARR_EXPOSURE(VirtualImpl);
BENCHMARK_ARR_EXPOSURE(PimplImpl);
BENCHMARK_ARR_EXPOSURE(FastPimplImpl);
BENCHMARK_ARR_EXPOSURE(SrcImpl);

template <typename Impl>
static void BM_VecLoadLibraryExposure(benchmark::State& state) {
    auto* impl = Impl::create();

    std::vector<int> vec;
    vec.resize(state.range(0));
    int64_t sum = 0;

    for (auto _ : state) {
        impl->doSomething(vec);
        benchmark::DoNotOptimize(sum += ::sum(vec));
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(2 * sizeof(int) * state.range(0) * state.iterations());

    delete impl;
}

#define BENCHMARK_VEC_EXPOSURE(Impl)                    \
    BENCHMARK_TEMPLATE(BM_VecLoadLibraryExposure, Impl) \
        ->Arg(1)                                        \
        ->Arg(4)                                        \
        ->Arg(16)                                       \
        ->Arg(64)                                       \
        ->Arg(512)                                      \
        ->Arg(2048)                                     \
        ->Arg(8192)                                     \
        ->Arg(32768)

BENCHMARK_VEC_EXPOSURE(VirtualImpl);
BENCHMARK_VEC_EXPOSURE(PimplImpl);
BENCHMARK_VEC_EXPOSURE(FastPimplImpl);
BENCHMARK_VEC_EXPOSURE(SrcImpl);

template <typename Impl>
static void BM_NoLoadLibraryExposure(benchmark::State& state) {
    auto* impl = Impl::create();

    for (auto _ : state) {
        benchmark::DoNotOptimize(impl->doSomething());
        benchmark::ClobberMemory();
    }

    state.SetBytesProcessed(sizeof(int) * state.iterations());

    delete impl;
}

BENCHMARK_TEMPLATE(BM_NoLoadLibraryExposure, VirtualImpl);
BENCHMARK_TEMPLATE(BM_NoLoadLibraryExposure, PimplImpl);
BENCHMARK_TEMPLATE(BM_NoLoadLibraryExposure, FastPimplImpl);
BENCHMARK_TEMPLATE(BM_NoLoadLibraryExposure, SrcImpl);

BENCHMARK_MAIN();
