#ifndef __MY_DEBUG_H__
#define __MY_DEBUG_H__

#ifdef __cplusplus
extern "C"
{
#endif

#include "xprintf.h"

#ifndef	_DEBUG
#define _DEBUG
#endif

#ifdef _DEBUG
	#define debug_info(...) \
		{\
			xprintf(__VA_ARGS__); \
		}
	#else
		#define debug_info(...)
	#endif


#ifdef __cplusplus
}
#endif

#endif // __MY_DEBUG_H__
