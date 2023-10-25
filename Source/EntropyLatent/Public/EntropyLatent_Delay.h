#pragma once

#include "EntropyLatent_Base.h"

namespace EntropyLatent
{
	/**
	 * Types possible for Delay
	 */
	enum class EDelayTimeType
	{
		/** Game time influenced by time dilation and pausing */
		GameTime,
		
		/** Game time influenced by time dilation but not by pausing */
		UnpausedGameTime,

		/** Real time unaffected by pausing and time dilation */
		RealTime,

		/** Time that passes for the audio system */
		AudioTime
	};

	/**
	 * Wait for a specified time and execute a callback afterwards.
	 * The type of time waited can be customized with the template parameter.
	 * @tparam DelayType The typ e of time to wait
	 * @tparam T Should always be derived automatically
	 * @param Duration Time to wait in seconds
	 * @param Callback Callback to execute after the delay
	 * @return Handle of the started coroutine
	 */
	template<EDelayTimeType DelayType = EDelayTimeType::GameTime, callable T>
	UE5Coro::TCoroutine<> Delay(const T Callback, const float Duration)
	{
		ensure(Duration > 0);
		if constexpr (DelayType == EDelayTimeType::GameTime)
		{
			co_await UE5Coro::Latent::Seconds(Duration);
		}
		else if constexpr (DelayType == EDelayTimeType::UnpausedGameTime)
		{
			co_await UE5Coro::Latent::UnpausedSeconds(Duration);
		}
		else if constexpr (DelayType == EDelayTimeType::RealTime)
		{
			co_await UE5Coro::Latent::RealSeconds(Duration);
		}
		else
		{
			co_await UE5Coro::Latent::AudioSeconds(Duration);
		}
		Callback();
	}

	/**
	 * Wait until a specified time and execute a callback afterwards.
	 * The type of time waited can be customized with the template parameter.
	 * Usually you will want to use Delay instead!
	 * @tparam DelayType The typ e of time to wait
	 * @tparam T Should always be derived automatically
	 * @param Time Point in time until to wait (in seconds)
	 * @param Callback Callback to execute after the delay
	 * @return Handle of the started coroutine
	 */
	template<EDelayTimeType DelayType = EDelayTimeType::GameTime, callable T>
	UE5Coro::TCoroutine<> DelayUntil(const T& Callback, const float Time)
	{
		if constexpr (DelayType == EDelayTimeType::GameTime)
		{
			co_await UE5Coro::Latent::UntilTime(Time);
		}
		else if constexpr (DelayType == EDelayTimeType::UnpausedGameTime)
		{
			co_await UE5Coro::Latent::UntilUnpausedTime(Time);
		}
		else if constexpr (DelayType == EDelayTimeType::RealTime)
		{
			co_await UE5Coro::Latent::UntilRealTime(Time);
		}
		else
		{
			co_await UE5Coro::Latent::UntilAudioTime(Time);
		}
		Callback();
	}
}
