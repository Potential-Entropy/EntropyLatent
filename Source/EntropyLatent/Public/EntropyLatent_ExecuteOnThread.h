#pragma once

#include "EntropyLatent_Base.h"

namespace EntropyLatent
{
	/**
	 * Executes a specified function on the game thread in the next tick.<br>
	 * If called on the game thread, the function will be called immediately.
	 * @tparam T Should always be derived automatically
	 * @param Function The function/lambda to execute
	 * @return A handle on the started coroutine
	 */
	template <callable T>
	UE5Coro::TCoroutine<> ExecuteOnGameThread(const T Function)
	{
		co_await UE5Coro::Async::MoveToGameThread();
		Function();
	}

	/**
	 * Executes a specified function on an already existing task/worker thread.
	 * @tparam T Should always be derived automatically
	 * @param Function The function/lambda to execute
	 * @return A handle on the started coroutine
	 */
	template <callable T>
	UE5Coro::TCoroutine<> ExecuteOnWorkerThread(const T Function)
	{
		co_await UE5Coro::Tasks::MoveToTask();
		Function();
	}

	/**
	 * The same as ExecuteOnWorkerThread
	 */
	template <callable T>
	UE5Coro::TCoroutine<> ExecuteOnTask(const T Function)
	{
		co_await UE5Coro::Tasks::MoveToTask();
		Function();
	}

	/**
	 * Starts a new thread and executes a specified function on it.<br>
	 * Unless there is a specific reason to use this, prefer to use ExecuteOnWorkerThread instead!
	 * @tparam T Should always be derived automatically
	 * @param Function The function/lambda to execute
	 * @return A handle on the started coroutine
	 */
	template <callable T>
	UE5Coro::TCoroutine<> ExecuteOnNewThread(const T Function)
	{
		co_await UE5Coro::Tasks::MoveToTask();
		Function();
	}
}
