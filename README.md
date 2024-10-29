# InterfaceExposureBenchmark

Test of performance of different aproaches to exposure of interface of some library class.

Imaginary task is to implement some library with some class and prepare for external usage: give out some headers to include and library to link with. There is a trade off between two goals measured:

1. Do not expose internals of this class implementation. Keep them inside the binary part of library as much as possible, not in the header.
2. Given that user will use link time optimizations (and any other optimizations possible), provide the best performance of API calls.

4 different aproaches are measured:

- Give out sources: header with definition of real class which will be used. All members of the class are exposed, the actual class name is exposed as well.
- Use PIMPL with some trick to place implementation on stack without inderection. Name of implementation, size and alignment are exposed. Members are hidden.
- Use PIMPL with `std::unique_ptr`. Only name of the implementation is exposed.
- Use abstract interface. Nothing is exposed.

Each implementation is compiled into library, which is linked with final executable (the benchmark in our case). Build was made for `clang` toolchain and uses `-flto=thin`. No guarantees with `gcc`.

This project has some CMake variables, which can be turned on or off with `-D{VAR_NAME}=ON|OFF`:

- `BUILD_SHARED_LIBS`. If `ON` - build and link implementations as shared libraries, otherwise as static. With static linking LTO will give some benefits. Default is `OFF`
- `DERIVE_FINAL`. Affects only approach with abstract interface. Overriden method will be marked as `final` if this option is `ON`, or `override` otherwise. Default is `ON`.

Script `./do_benches.sh` will run all 4 combinations of options of benchmarks. Skript uses `ninja` and `clang-18`.

Benchmarks require `cmake >= 3.20`, `google benchmark`. Uses `c++20`.
