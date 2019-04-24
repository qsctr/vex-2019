#pragma once

template <typename ...Fs>
struct overload : Fs... {
    overload(Fs const&... fs) : Fs {fs}... {}
    using Fs::operator()...;
};
