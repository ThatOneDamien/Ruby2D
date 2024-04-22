#pragma once


#ifdef _WIN32

	#define RB_NOVTABLE __declspec(novtable)

	#ifdef _WIN64
		// Windows x64 builds.
		#define RB_PLAT_WIND
		// For now OpenGL is the only Renderering API used.
		#define RB_USE_OPENGL

	#else
		// Windows x86 builds.
		#error "x86/32-bit builds are not supported."
	#endif

#else
	// Other builds. TODO handle more systems specifically.
	#error "Windows is the only platform currently supported by Ruby2D."
	#define RB_NOVTABLE  
#endif

#include <stdint.h>
typedef uint32_t RendererID;

#include "Ruby/Main/Logging.h"

#ifdef RB_EXTERNAL_DEF
#define RB_TRACE(msg, ...)                          ::Ruby::Logger::getClientLogger()->trace(msg, __VA_ARGS__);
#define RB_INFO(msg, ...)                           ::Ruby::Logger::getClientLogger()->info(msg, __VA_ARGS__);
#define RB_WARN(msg, ...)                           ::Ruby::Logger::getClientLogger()->warn(msg, __VA_ARGS__);
#define RB_ERROR(msg, ...)                          ::Ruby::Logger::getClientLogger()->error(msg, __VA_ARGS__);
#define RB_CRITICAL(msg, ...)                       ::Ruby::Logger::getClientLogger()->critical(msg, __VA_ARGS__);
#define RB_LOG_BASIC(msg, ...)                      ::Ruby::Logger::getClientLogger()->basicLog(msg, __VA_ARGS__);
#define RB_LOG_SET_COLOR(textColor, highlightColor) ::Ruby::Logger::getClientLogger()->setLogColor(textColor, highlightColor);
#else							                    
#define RB_TRACE(msg, ...)                          ::Ruby::Logger::getEngineLogger()->trace(msg, __VA_ARGS__)
#define RB_INFO(msg, ...)                           ::Ruby::Logger::getEngineLogger()->info(msg, __VA_ARGS__)
#define RB_WARN(msg, ...)                           ::Ruby::Logger::getEngineLogger()->warn(msg, __VA_ARGS__)
#define RB_ERROR(msg, ...)                          ::Ruby::Logger::getEngineLogger()->error(msg, __VA_ARGS__)
#define RB_CRITICAL(msg, ...)                       ::Ruby::Logger::getEngineLogger()->critical(msg, __VA_ARGS__)
#define RB_LOG_BASIC(msg, ...)                      ::Ruby::Logger::getEngineLogger()->basicLog(msg, __VA_ARGS__)
#define RB_LOG_SET_COLOR(textColor, highlightColor) ::Ruby::Logger::getEngineLogger()->setLogColor(textColor, highlightColor)
#endif

#ifdef RB_PLAT_WIND
	#ifdef RB_DEBUG

		// Prints error message and debug breaks unconditionally.
		// Almost the exact same as doing RB_ASSERT(false, msg, ...) but without branch.
		#define RB_ERROR_DEBUG(msg, ...) { RB_ERROR(msg, __VA_ARGS__); __debugbreak(); }

		// Asserts that condition x is true, if x is false it prints error msg, debug breaks.
		#define RB_ASSERT(x, msg, ...) { if(!(x)) { RB_ERROR_DEBUG(msg, __VA_ARGS__); } }

		// Asserts that condition x is true, if x is false it prints critical msg, debug breaks.
		#define RB_ASSERT_CRITICAL(x, msg, ...) { if(!(x)) { RB_CRITICAL(msg, __VA_ARGS__); __debugbreak(); } }

		// Asserts that condition x is true, if x is false it prints error msg, debug breaks, and returns ret_val.
		#define RB_ASSERT_RET(x, ret_val, msg, ...) { if(!(x)) { RB_ERROR_DEBUG(msg, __VA_ARGS__); return ret_val; } }

		// Asserts that condition x is true, if x is false it prints error msg, debug breaks, and breaks from loop.
		#define RB_ASSERT_BRK(x, msg, ...) { if(!(x)) { RB_ERROR_DEBUG(msg, __VA_ARGS__); break; } }
	#else
		#define RB_ERROR_DEBUG(msg, ...)
		#define RB_ASSERT(x, msg, ...) x
		#define RB_ASSERT_CRITICAL(x, msg, ...) x
		#define RB_ASSERT_RET(x, ret_val, msg, ...) { if(!(x)) { return ret_val; } }
		#define RB_ASSERT_BRK(x, msg, ...) { if(!(x)) { break; } }
	#endif
	// Asserts that condition x is true, if x is false it prints error msg, debug breaks, and returns void.
	// Alias for RB_ASSERT_RET() where ret_val is absent, i.e. return type of function is void.
	#define RB_ASSERT_RET_VOID(x, msg, ...) RB_ASSERT_RET(x, , msg, __VA_ARGS__)

#endif

#include <filesystem>