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
