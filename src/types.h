/* -*- coding: utf-8; tab-width: 8; indent-tabs-mode: t; -*- */

/*
 * x-engine
 * Copyright (C) 2024, The Authors. All rights reserved.
 */

/*
 * This header handles non-C89 and/or compiler-specific features.
 *
 * - The compilers we support as of April 2024 are:
 *   - GCC 13 or later
 *   - LLVM/Clang 15 or later
 *   - MSVC 14 or later
 */

#ifndef XENGINE_TYPES_H
#define XENGINE_TYPES_H

/*
 * Define macros that indicate a target platform we are compiling to.
 *  - XENGINE_TARGET_WIN32   for Win32 (x86/x64/Arm64)
 *  - XENGINE_TARGET_MACOS   for macOS (Arm64/x86_64)
 *  - XENGINE_TARGET_IOS     for iOS (Arm64)
 *  - XENGINE_TARGET_ANDROID for Android (armv8/armv7/x86_64)
 *  - XENGINE_TARGET_WASM    for Wasm with Emscripten
 *  - XENGINE_TARGET_POSIX   for Linux and *BSD
 *  - XENGINE_TARGET_SDL2    for SDL2
 */
#if defined(__APPLE__) && __has_include(<TargetConditionals.h>)
#include <TargetConditionals.h>
#if TARGET_OS_IPHONE
#define XENGINE_TARGET_IOS
#else
#define XENGINE_TARGET_MACOS
#endif
#elif defined(_WIN32)
#define XENGINE_TARGET_WIN32
#elif defined(__ANDROID__)
#define XENGINE_TARGET_ANDROID
#elif defined(__EMSCRIPTEN__)
#define XENGINE_TARGET_WASM
#elif !defined(XENGINE_TARGET_UNITY) && !defined(XENGINE_TARGET_SDL2)
#define XENGINE_TARGET_POSIX
#endif

#if defined(XENGINE_TARGET_ANDROID) || defined(XENGINE_TARGET_UNITY)
#define XENGINE_DLL
#endif

/*
 * For GCC and LLVM/Clang
 */
#if defined(__GNUC__) || defined(__llvm__)

 /*
  * Define a macro that indicates a target architecture.
  *  - XENGINE_ARCH_X86 for ia32 (x86)
  *  - XENGINE_ARCH_X86_64 for amd64 (x86_64)
  *  - XENGINE_ARCH_ARM32 for armv7
  *  - XENGINE_ARCH_ARM64 for armv8
  */
#if defined(__i386__) && !defined(__x86_64__)
#define XENGINE_ARCH_X86
#elif defined(__x86_64__)
#define XENGINE_ARCH_X86_64
#elif defined(__arm__)
#define XENGINE_ARCH_ARM32
#elif defined(__aarch64__)
#define XENGINE_ARCH_ARM64
#endif

/*
 * Struct member definition with 512-bit memory alignment.
 */
#define SIMD_ALIGNED_MEMBER(cdecl) cdecl __attribute__((aligned(64)))

#endif /* End of the GCC/Clang section*/

/*
 * For MSVC
 */
#ifdef _MSC_VER

 /*
  * Define a macro that indicates a target architecture.
  *  - XENGINE_ARCH_X86    for ia32 (x86)
  *  - XENGINE_ARCH_X86_64 for amd64 (x86_64)
  *  - XENGINE_ARCH_ARM64  for armv8
  */
#if defined(_M_IX86)
#define XENGINE_ARCH_X86
#elif defined(_M_X64)
#define XENGINE_ARCH_X86_64
#elif defined(_M_ARM64)
#define XENGINE_ARCH_ARM64
#endif

/*
 * Struct member definition with 512-bit memory alignment.
 */
#define SIMD_ALIGNED_MEMBER(cdecl) __declspec(align(64)) cdecl

/*
 * Do not get warnings for usages of string.h functions.
 */
#define _CRT_SECURE_NO_WARNINGS

/*
 * POSIX libc to MSVCRT mapping
 */
#define strdup _strdup

#endif /* End of MSVC */

/*
 * Use the C99 stdint.h header for the following integer types.
 *  - uint8_t
 *  - uint16_t
 *  - uint32_t
 *  - int8_t
 *  - int16_t
 *  - int32_t
 */
#include <stdint.h>

/*
 * Use the C99 stdbool.h header for the bool type.
 */
#ifndef __cplusplus
#include <stdbool.h>
#endif

/*
 * Common non-C89 keyword wrappers.
 */

/* Inline function. */
#define INLINE				__inline

/* No pointer aliasing. */
#define RESTRICT			__restrict

/* Suppress unused warnings. */
#define UNUSED_PARAMETER(x)		(void)(x)

/* UTF-8 string literal. */
#define U8(s)				u8##s

/* UTF-32 character literal. */
#define U32_C(s)			U##s

#endif
