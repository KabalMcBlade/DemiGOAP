// Copyright (c) 2020-2025 Michele Condo'
// File: C:\Projects\DemiGOAP\DemiGOAP\DemiGOAP\Core.h
// Licensed under the MIT License. See LICENSE file in the project root for full license information.
#pragma once

#include <stdint.h>

#include <functional>
#include <string>
#include <unordered_map>
#include <map>
#include <algorithm>

#define DEMIGOAP_INLINE    __forceinline

#define DEMIGOAP_STRINGYFY_HELPER(token)      #token
#define DEMIGOAP_STRINGYFY(str)               DEMIGOAP_STRINGYFY_HELPER(str)

/// concatenates two strings, even when the strings are macros themselves
#define DEMIGOAP_JOIN(x, y)                   DEMIGOAP_JOIN_HELPER(x, y)
#define DEMIGOAP_JOIN_HELPER(x, y)            DEMIGOAP_JOIN_HELPER_HELPER(x, y)
#define DEMIGOAP_JOIN_HELPER_HELPER(x, y)     x##y



#define DEMIGOAP_NAMESPACE_BEGIN namespace DemiGOAP {
#define DEMIGOAP_NAMESPACE_END };  