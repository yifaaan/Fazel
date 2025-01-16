#pragma once

#ifdef FZ_PLATFORM_WINDOWS
	#ifdef FZ_BUILD_DLL
		#define FAZEL_API __declspec(dllexport)
	#else
		#define FAZEL_API __declspec(dllimport)
	#endif
#else
	#error Fazel only supports Windows!
#endif // FZ_BUILD_DLL


#ifdef FZ_ENABLE_ASSERTS
	#define FZ_ASSERT(x, ...) { if (!(x)) { FZ_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
	#define FZ_CORE_ASSERT(x, ...) { if (!(x)) { FZ_CORE_ERROR("Assertion Failed: {0}", __VA_ARGS__); __debugbreak(); } }
#else
	#define FZ_ASSERT(x, ...)
	#define FZ_CORE_ASSERT(x, ...)
#endif


#define BIT(x) (1 << x)