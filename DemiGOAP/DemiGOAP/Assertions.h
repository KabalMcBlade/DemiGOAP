// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\Assertions.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#pragma once

#include <cstdio>

#ifdef _DEBUG

#define Assert( condition, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
    }
#define AssertVoid( condition, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		return; \
    }
#define AssertValue( condition, return_value, format, ... ) \
    if( !(condition) ) { \
        fprintf (stderr, "%s(%u): " format "\n", __FILE__, __LINE__, __VA_ARGS__); \
		return return_value; \
    }

#else

#define Assert( condition, format, ... )
#define AssertVoid( condition, format, ... )
#define AssertValue( condition, return_value, format, ... )

#endif 


#define AssertReturnVoid( condition, format, ... )					AssertVoid( condition, format, __VA_ARGS__ )
#define AssertReturnValue( condition, return_value, format, ...  )	AssertValue( condition, return_value, format, __VA_ARGS__ )