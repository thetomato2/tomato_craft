#ifndef TOMATO_COMMON_HPP_
#define TOMATO_COMMON_HPP_

#include <cassert>
#include <cmath>
#include <cstdint>
#include <cstdio>

#include <imgui.h>
#include <imgui_impl_win32.h>
#include <imgui_impl_opengl3.h>

// NOTE: for grep purposes
#define scast(t, v) static_cast<t>(v)
#define rcast(t, v) reinterpret_cast<t>(v)
#define ccast(t, v) const_cast<t>(v)
#define cast(t, v)  ((t)(v))

#ifdef _MSVC
    #define MSVC 1
#endif

#ifdef _LLVM
    #define LLVM 1
#endif

#if MSVC
    /* #include <intrin.h> */
    #pragma intrinsic(_BitScanForward)
#endif

typedef int8_t s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float f32;
typedef double f64;

typedef size_t szt;
typedef size_t mem_ind;
typedef u8 byt;

#ifdef _WIN32
typedef wchar_t wchar;
typedef unsigned long ul;
typedef unsigned long long ull;
#endif

typedef int32_t b32;

#ifdef __cplusplus
static_assert(sizeof(s8) == 1, "s8 isn't 1 byte!");
static_assert(sizeof(s16) == 2, "s16 isn't 2 byte!s");
static_assert(sizeof(s32) == 4, "s32 isn't 4 byte!s");
static_assert(sizeof(s64) == 8, "s64 isn't 8 byte!s");
static_assert(sizeof(u8) == 1, "u8 isn't 1 byte!");
static_assert(sizeof(u16) == 2, "u16 isn't 2 byte!s");
static_assert(sizeof(u32) == 4, "u32 isn't 4 byte!s");
static_assert(sizeof(u64) == 8, "u64 isn't 8 byte!s");
static_assert(sizeof(f32) == 4, "f32 isn't 4 byte!s");
static_assert(sizeof(f64) == 8, "f64 isn't 8 byte!s");
static_assert(sizeof(b32) == 4, "b32 isn't 4 byte!s");
#endif

#define U8_MIN 0u
#define U8_MAX 0xffu
#define S8_MIN (-0x7f - 1)
#define S8_MAX 0x7f

#define U16_MIN 0u
#define U16_MAX 0xffffu
#define S16_MIN (-0x7fff - 1)
#define S16_MAX 0x7fff

#define U32_MIN 0u
#define U32_MAX 0xffffffffu
#define S32_MIN (-0x7fffffff - 1)
#define S32_MAX 0x7fffffff

#define U64_MIN 0ull
#define U64_MAX 0xffffffffffffffffull
#define S64_MIN (-0x7fffffffffffffffll - 1)
#define S64_MAX 0x7fffffffffffffffll

#define BIT(x) (1 << x)

#define KILOBYTES(val) ((val)*1024)
#define MEGABYTES(val) (KILOBYTES(val) * 1024)
#define GIGABYTES(val) (MEGABYTES(val) * 1024)
#define TERABYTES(val) (GIGABYTES(val) * 1024)

#define ARRAY_COUNT(array) (sizeof((array)) / sizeof((array)[0]))

// NOTE: this breaks tree-sitter >:|
#define internal      static
#define local_persist static
#define global_var    static

// NOTE: only win32 is supported currently
#ifdef _WIN32
    #define TOM_WIN32
#endif

#ifdef TOM_WIN32
    #define TOM_DLL_EXPORT __declspec(dllexport)
#else
    #define TOM_DLL_EXPORT
#endif

#ifdef TOM_INTERNAL
    #define TOM_ASSERT(x)                                                    \
        if (!(x)) {                                                          \
            printf("FAILED ASSERT -> %s at :%d\n", __FILE__, __LINE__); \
            __debugbreak();                                                  \
        }                                                                    \
        assert(x)

    #define TOM_ASSERT_MSG(x, msg)                                                \
        if (!(x)) {                                                               \
            printf("FAILED ASSERT -> %s at :%d - %s\n", __FILE__, __LINE__, msg); \
            __debugbreak();                                                       \
        }                                                                         \
        assert(x)

    #define DEBUG_BREAK(x)  \
        if (x) {            \
            __debugbreak(); \
        }
#else
    #define TOM_ASSERT(x)
    #define TOM_ASSERT_MSG(x, msg)
    #define DEBUG_BREAK(x)
#endif

#define INVALID_CODE_PATH TOM_ASSERT(!"Invalid code path!")

#include "math.hpp"

namespace tom
{

struct thread_context
{
    s32 place_holder;
};

struct memory_arena
{
    mem_ind size;
    u8 *base;
    mem_ind used;
};

inline void init_arena(memory_arena *arena, const mem_ind size, void *base)
{
    arena->size = size;
    arena->base = scast(byt *, base);
    arena->used = 0;
}

inline void *push_size(memory_arena *arena, mem_ind size)
{
    TOM_ASSERT((arena->used + size) <= arena->size);
    void *result = arena->base + arena->used;
    arena->used += size;

    return result;
}

inline void zero_size(mem_ind size, void *ptr)
{
    // TODO: profile this for performance
    byt *byte = scast(byt *, ptr);
    while (size--) {
        *byte++ = 0;
    }
}

#define PUSH_STRUCT(arena, type)       (type *)push_size(arena, sizeof(type))
#define PUSH_ARRAY(arena, count, type) (type *)push_size(arena, (count * sizeof(type)))
#define ZERO_STRUCT(inst)              zero_size(sizeof(inst), &(inst))

// Generic flag stuff

inline bool is_flag_set(s32 flags, s32 flag)
{
    return flags & flag;
}

inline void set_flag(s32 &flags, s32 flag)
{
    flags |= flag;
}

inline void clear_flag(s32 &flags, s32 flag)
{
    flags &= ~flag;
}

inline u32 safe_truncate_u32_to_u64(u64 value)
{
    TOM_ASSERT(value <= U32_MAX);
    u32 result = scast(u32, value);
    return result;
}

}  // namespace tom
#endif  // TOMATO_COMMON_HPP_
