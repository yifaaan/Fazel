#pragma once

#include <memory>

#include "Core.h"
#include "spdlog/spdlog.h"

namespace Fazel
{
	class FAZEL_API Log
	{
	public:
		static void Init();

		inline static std::shared_ptr<spdlog::logger>& GetCoreLogger() { return s_CoreLogger; }
		inline static std::shared_ptr<spdlog::logger>& GetClientLogger() { return s_ClientLogger; }


	private:
		static std::shared_ptr<spdlog::logger> s_CoreLogger;
		static std::shared_ptr<spdlog::logger> s_ClientLogger;
	};
}

/// Core log macros
#define FZ_CORE_TRACE(...)	::Fazel::Log::GetCoreLogger()->trace(__VA_ARGS__)
#define FZ_CORE_INFO(...)	::Fazel::Log::GetCoreLogger()->info(__VA_ARGS__)
#define FZ_CORE_WARN(...)	::Fazel::Log::GetCoreLogger()->warn(__VA_ARGS__)
#define FZ_CORE_ERROR(...)	::Fazel::Log::GetCoreLogger()->error(__VA_ARGS__)
#define FZ_CORE_FATAL(...)	::Fazel::Log::GetCoreLogger()->fatal(__VA_ARGS__)

/// Client log macros
#define FZ_TRACE(...)	::Fazel::Log::GetClientLogger()->trace(__VA_ARGS__)
#define FZ_INFO(...)	::Fazel::Log::GetClientLogger()->info(__VA_ARGS__)
#define FZ_WARN(...)	::Fazel::Log::GetClientLogger()->warn(__VA_ARGS__)
#define FZ_ERROR(...)	::Fazel::Log::GetClientLogger()->error(__VA_ARGS__)
#define FZ_FATAL(...)	::Fazel::Log::GetClientLogger()->fatal(__VA_ARGS__)

