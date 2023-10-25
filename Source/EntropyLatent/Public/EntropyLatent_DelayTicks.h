#pragma once

#include "EntropyLatent_Base.h"

namespace EntropyLatent
{
	
	/**
	 * Wait for a specified amount of ticks and execute a callback afterwards.
	 * @tparam T Should always be derived automatically!
	 * @param Callback The callback to execute after the delay
	 * @param NumberOfTicks The amount of ticks to wait. 1 by default. If 0, the callback will be executed immediately.
	 * @return Handle of the started coroutine
	 */
	template<callable T>
	UE5Coro::TCoroutine<> DelayTicks(const T Callback, const int64 NumberOfTicks = 1)
	{
		co_await UE5Coro::Latent::Ticks(NumberOfTicks);
		Callback();
	}
}
