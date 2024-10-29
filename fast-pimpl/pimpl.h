#pragma once

#include <cstddef>
#include <new>
#include <utility>

template <typename T, std::size_t Size, std::size_t Align>
class FastPimpl {
public:
    template <typename... Args>
    explicit FastPimpl(Args&&... args) {
        new (ptr()) T(std::forward<Args>(args)...);
    }

    ~FastPimpl() {
        static_assert(alignof(T) == Align, "Alignment mismatch"); // this allows to get right alignment for the object in one compilation cycle
        static_assert(sizeof(T) <= Size, "Size mismatch");        // this allows to get right size for the object in one compilation cycle
        ptr()->~T();
    }
    FastPimpl(const FastPimpl& other) { new (ptr()) T(*other); }
    FastPimpl(FastPimpl&& other) { new (ptr()) T(std::move(*other)); }
    FastPimpl& operator=(const FastPimpl& other) {
        *ptr() = *other.ptr();
        return *this;
    }
    FastPimpl& operator=(FastPimpl&& other) {
        *ptr() = std::move(*other.ptr());
        return *this;
    }
    T* operator->() { return ptr(); }
    T& operator*() { return *ptr(); }
    const T* operator->() const { return ptr(); }
    const T& operator*() const { return *ptr();}

private:
    T* ptr() { return std::launder(reinterpret_cast<T*>(data)); }
    const T* ptr() const { return std::launder(reinterpret_cast<const T*>(data)); }

    alignas(Align) std::byte data[Size];
};
