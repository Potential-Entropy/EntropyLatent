#pragma once

#include "UE5Coro.h"

namespace EntropyLatent {
    
    template<typename T>
    concept callable = requires {
        T();
    };

    constexpr auto Noop = []{};
}