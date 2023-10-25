#pragma once

#include "UE5Coro.h"

namespace EntropyLatent {
    
    template<typename T>
    concept callable = requires(T t) {
        t();
    };

    constexpr auto Noop = []{};
}