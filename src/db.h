#pragma once

// asci art font : rubi_font https://patorjk.com/software/taag

#include <stdint.h>
#include <stdio.h>
#include <string.h>
#ifdef _WIN32
#include <io.h>
#include <process.h>
#else
#include <unistd.h>
#endif

#if defined(__win32_) || defined(__WIN32) || defined(_WIN32)

#define DB_PLATFORM_WINDOWS
#define NOGDI
#define NOUSER
#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#elif __linux__

#define DB_PLATFORM_LINUX
#include <sanitizer/asan_interface.h>
#include <sys/mman.h>

#elif __APPLE__

#define DB_PLATFORM_MACOS
#include <sanitizer/asan_interface.h>
#include <sys/mman.h>

#endif

/*
   ▗▖  ▗▖▗▖  ▗▖    ▗▄▄▄▖▗▖  ▗▖▗▄▄▖ ▗▄▄▄▖ ▗▄▄▖
   ▐▛▚▞▜▌ ▝▚▞▘       █   ▝▚▞▘ ▐▌ ▐▌▐▌   ▐▌
   ▐▌  ▐▌  ▐▌        █    ▐▌  ▐▛▀▘ ▐▛▀▀▘ ▝▀▚▖
   ▐▌  ▐▌  ▐▌        █    ▐▌  ▐▌   ▐▙▄▄▖▗▄▄▞▘
   */
// types typedef
typedef int8_t  s8;
typedef int16_t s16;
typedef int32_t s32;
typedef int64_t s64;

typedef uint8_t  u8;
typedef uint16_t u16;
typedef uint32_t u32;
typedef uint64_t u64;

typedef float  f32;
typedef double f64;

typedef s8 b8;

/*
   ▗▖ ▗▖ ▗▄▄▖▗▄▄▄▖▗▄▄▄▖▗▖ ▗▖▗▖       ▗▖  ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▖  ▗▄▖  ▗▄▄▖
   ▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▌       ▐▛▚▞▜▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌
   ▐▌ ▐▌ ▝▀▚▖▐▛▀▀▘▐▛▀▀▘▐▌ ▐▌▐▌       ▐▌  ▐▌▐▛▀▜▌▐▌   ▐▛▀▚▖▐▌ ▐▌ ▝▀▚▖
   ▝▚▄▞▘▗▄▄▞▘▐▙▄▄▖▐▌   ▝▚▄▞▘▐▙▄▄▖    ▐▌  ▐▌▐▌ ▐▌▝▚▄▄▖▐▌ ▐▌▝▚▄▞▘▗▄▄▞▘
*/
#define DEBUG_BREAK __builtin_trap()

#define ASSERT(expr)                                                                                                   \
    {                                                                                                                  \
        do                                                                                                             \
        {                                                                                                              \
            if (!(expr))                                                                                               \
            {                                                                                                          \
                printf("ASSERTion failure: %s:%d on %s\n", __FILE__, __LINE__, #expr);                                 \
                DEBUG_BREAK;                                                                                           \
            }                                                                                                          \
        } while (0);                                                                                                   \
    }

#define ASSERT_WITH_MSG(expr, msg)                                                                                     \
    {                                                                                                                  \
        do                                                                                                             \
        {                                                                                                              \
            if (!(expr))                                                                                               \
            {                                                                                                          \
                printf("%s\n.", msg);                                                                                  \
                printf("ASSERTion failure: %str:%d on %s\n", __FILE__, __LINE__, #expr);                               \
                DEBUG_BREAK;                                                                                           \
            }                                                                                                          \
        } while (0);                                                                                                   \
    }

#define false 0
#define true 1

#define s32_min -2147483648
#define s32_max 2147483647

// hmmmm we need a floating point max too ?
#define db_max(n, m) (s64) n >= (s64)m ? (s64)n : (s64)m
#define db_min(n, m) (s64) n <= (s64)m ? (s64)n : (s64)m

#define KB(n) ((s32)n * 1024)
#define MB(n) ((s32)n * 1024 * 1024)
#define GB(n) ((s32)n * 1024 * 1024 * 1024)

#define pi32 3.1415926535897f
#define machine_epsilon64 4.94065645841247e-324

#define max_u64 0xffffffffffffffffull
#define max_u32 0xffffffff
#define max_u16 0xffff
#define max_u8 0xff

#define max_s64 ((s64)0x7fffffffffffffffll)
#define max_s32 ((s32)0x7fffffff)
#define max_s16 ((s16)0x7fff)
#define max_s8 ((s8)0x7f)

#define min_s64 ((s64)0x8000000000000000ll)
#define min_s32 ((s32)0x80000000)
#define min_s16 ((s16)0x8000)
#define min_s8 ((s8)0x80)

#define db_clamp_integer(min, val_to_clamp, max) val_to_clamp >= min ? (val_to_clamp >= max ? max : val_to_clamp) : min

#define defer_loop(a, b) for (b8 i = 0, res = a; i != 1 && res; i++, b)

#define bitmask1 0x00000001
#define bitmask2 0x00000003
#define bitmask3 0x00000007
#define bitmask4 0x0000000f
#define bitmask5 0x0000001f
#define bitmask6 0x0000003f
#define bitmask7 0x0000007f
#define bitmask8 0x000000ff
#define bitmask9 0x000001ff
#define bitmask10 0x000003ff
#define bitmask11 0x000007ff
#define bitmask12 0x00000fff
#define bitmask13 0x00001fff
#define bitmask14 0x00003fff
#define bitmask15 0x00007fff
#define bitmask16 0x0000ffff
#define bitmask17 0x0001ffff
#define bitmask18 0x0003ffff
#define bitmask19 0x0007ffff
#define bitmask20 0x000fffff
#define bitmask21 0x001fffff
#define bitmask22 0x003fffff
#define bitmask23 0x007fffff
#define bitmask24 0x00ffffff
#define bitmask25 0x01ffffff
#define bitmask26 0x03ffffff
#define bitmask27 0x07ffffff
#define bitmask28 0x0fffffff
#define bitmask29 0x1fffffff
#define bitmask30 0x3fffffff
#define bitmask31 0x7fffffff
#define bitmask32 0xffffffff

#define bitmask33 0x00000001ffffffffull
#define bitmask34 0x00000003ffffffffull
#define bitmask35 0x00000007ffffffffull
#define bitmask36 0x0000000fffffffffull
#define bitmask37 0x0000001fffffffffull
#define bitmask38 0x0000003fffffffffull
#define bitmask39 0x0000007fffffffffull
#define bitmask40 0x000000ffffffffffull
#define bitmask41 0x000001ffffffffffull
#define bitmask42 0x000003ffffffffffull
#define bitmask43 0x000007ffffffffffull
#define bitmask44 0x00000fffffffffffull
#define bitmask45 0x00001fffffffffffull
#define bitmask46 0x00003fffffffffffull
#define bitmask47 0x00007fffffffffffull
#define bitmask48 0x0000ffffffffffffull
#define bitmask49 0x0001ffffffffffffull
#define bitmask50 0x0003ffffffffffffull
#define bitmask51 0x0007ffffffffffffull
#define bitmask52 0x000fffffffffffffull
#define bitmask53 0x001fffffffffffffull
#define bitmask54 0x003fffffffffffffull
#define bitmask55 0x007fffffffffffffull
#define bitmask56 0x00ffffffffffffffull
#define bitmask57 0x01ffffffffffffffull
#define bitmask58 0x03ffffffffffffffull
#define bitmask59 0x07ffffffffffffffull
#define bitmask60 0x0fffffffffffffffull
#define bitmask61 0x1fffffffffffffffull
#define bitmask62 0x3fffffffffffffffull
#define bitmask63 0x7fffffffffffffffull
#define bitmask64 0xffffffffffffffffull

#define bit0 0
#define bit1 (1u << 0)
#define bit2 (1u << 1)
#define bit3 (1u << 2)
#define bit4 (1u << 3)
#define bit5 (1u << 4)
#define bit6 (1u << 5)
#define bit7 (1u << 6)
#define bit8 (1u << 7)
#define bit9 (1u << 8)
#define bit10 (1u << 9)
#define bit11 (1u << 10)
#define bit12 (1u << 11)
#define bit13 (1u << 12)
#define bit14 (1u << 13)
#define bit15 (1u << 14)
#define bit16 (1u << 15)
#define bit17 (1u << 16)
#define bit18 (1u << 17)
#define bit19 (1u << 18)
#define bit20 (1u << 19)
#define bit21 (1u << 20)
#define bit22 (1u << 21)
#define bit23 (1u << 22)
#define bit24 (1u << 23)
#define bit25 (1u << 24)
#define bit26 (1u << 25)
#define bit27 (1u << 26)
#define bit28 (1u << 27)
#define bit29 (1u << 28)
#define bit30 (1u << 29)
#define bit31 (1u << 30)
#define bit32 (1u << 31)

#define bit33 (1ull << 32)
#define bit34 (1ull << 33)
#define bit35 (1ull << 34)
#define bit36 (1ull << 35)
#define bit37 (1ull << 36)
#define bit38 (1ull << 37)
#define bit39 (1ull << 38)
#define bit40 (1ull << 39)
#define bit41 (1ull << 40)
#define bit42 (1ull << 41)
#define bit43 (1ull << 42)
#define bit44 (1ull << 43)
#define bit45 (1ull << 44)
#define bit46 (1ull << 45)
#define bit47 (1ull << 46)
#define bit48 (1ull << 47)
#define bit49 (1ull << 48)
#define bit50 (1ull << 49)
#define bit51 (1ull << 50)
#define bit52 (1ull << 51)
#define bit53 (1ull << 52)
#define bit54 (1ull << 53)
#define bit55 (1ull << 54)
#define bit56 (1ull << 55)
#define bit57 (1ull << 56)
#define bit58 (1ull << 57)
#define bit59 (1ull << 58)
#define bit60 (1ull << 59)
#define bit61 (1ull << 60)
#define bit62 (1ull << 61)
#define bit63 (1ull << 62)
#define bit64 (1ull << 63)

// thanks google https://github.com/google/sanitizers/wiki/addresssanitizermanualpoisoning
// user code should use macros instead of functions.
#if __has_feature(address_sanitizer) || defined(__sanitize_address__)
#define asan_poison_memory_region(addr, size) __asan_poison_memory_region((addr), (size))
#define asan_unpoison_memory_region(addr, size) __asan_unpoison_memory_region((addr), (size))
#else
#define asan_poison_memory_region(addr, size) ((void)(addr), (void)(size))
#define asan_unpoison_memory_region(addr, size) ((void)(addr), (void)(size))
#endif

typedef enum db_return_code
{
    DB_ERROR   = 0,
    DB_SUCCESS = 1,
} db_return_code;

/*
▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖ ▗▄▖ ▗▄▄▖▗▖  ▗▖
▐▛▚▞▜▌▐▌   ▐▛▚▞▜▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘
▐▌  ▐▌▐▛▀▀▘▐▌  ▐▌▐▌ ▐▌▐▛▀▚▖ ▐▌
▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌▝▚▄▞▘▐▌ ▐▌ ▐▌
*/

void          *__db_reserve_virtual_memory(size_t reserve_memory_size);
db_return_code __db_commit_virtual_memory(void *memory, s32 page_offset, s32 num_pages);
db_return_code __db_decommit_virtual_memory(void *memory, size_t size);
db_return_code __db_release_virtual_memory(void *memory, size_t size);

#if defined(DB_PLATFORM_LINUX) || defined(DB_PLATFORM_WINDOWS)
#define DB_PAGE_SIZE KB(4)
#elif defined(DB_PLATFORM_MACOS) // if the mac is an apple silicon which has an default page size of 16kb
// kind of a hack, what if the macos is apple intel ?
#define DB_PAGE_SIZE KB(16)
#endif
/*
 ▗▄▖ ▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▖  ▗▄▄▖
▐▌ ▐▌▐▌ ▐▌▐▌   ▐▛▚▖▐▌▐▌ ▐▌▐▌
▐▛▀▜▌▐▛▀▚▖▐▛▀▀▘▐▌ ▝▜▌▐▛▀▜▌ ▝▀▚▖
▐▌ ▐▌▐▌ ▐▌▐▙▄▄▖▐▌  ▐▌▐▌ ▐▌▗▄▄▞▘
*/
typedef enum
{
    TYPE_ARENA_LINEAR  = 0,
    TYPE_ARENA_CHUNKED = 1, // free list arena
} db_arena_type;

typedef struct db_arena_params
{
    db_arena_type type;
    u32           chunk_size;
} db_arena_params;

typedef struct db_arena_chunk_header
{
    struct db_arena_chunk_header *next_chunk;
} db_arena_chunk_header;

typedef struct db_arena
{
    db_arena_type type;
    // how many pages has the arena commited till now.
    // we need this because if we need the arena to grow it will use the page offset to find out how many pages to
    // commit.
    s64    curr_page_offset;
    size_t allocated_till_now;
    size_t total_size;
    //  @ = memory in use/ already allocated
    //  @@@@@@@@@@@@--------------------
    //              ^-- starting ptr for the next allocation
    uintptr_t curr_mem_pos;
    // original or the first ptr, this is also the starting page'str memory ptr. we will need to pass this ptr if we
    // want to unmap the memory.
    void *memory; // this will also be the first chunk in the list

    // if its type arena chunked
    size_t                 allocated_chunk_count;
    u32                    chunk_size;
    db_arena_chunk_header *free_list_head;
} db_arena;

#define DB_ARENA_DEFAULT_RESERVED_MEMORY MB(64)
#define DB_ARENA_DEFAULT_COMMITED_MEMORY DB_PAGE_SIZE
#define db_arena_init(...)                                                                                             \
    db_arena_init_with_size(&(db_arena_params){__VA_ARGS__}, (size_t)DB_ARENA_DEFAULT_COMMITED_MEMORY)
db_arena       db_arena_init_with_size(db_arena_params *params, size_t memory_size);
void          *db_arena_alloc(db_arena *arena, size_t size);
db_return_code db_arena_reset(db_arena *arena);
db_return_code db_arena_free(db_arena *arena);
db_return_code db_arena_free_node(db_arena *arena, void *ptr);
/*

▗▄▄▄▗▖  ▗▖▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖     ▗▄▖ ▗▄▄▖ ▗▄▄▖  ▗▄▖▗▖  ▗▖▗▄▄▖
▐▌  █▝▚▞▘ ▐▛▚▖▐▌▐▌ ▐▌▐▛▚▞▜▌  █  ▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘▐▌
▐▌  █ ▐▌  ▐▌ ▝▜▌▐▛▀▜▌▐▌  ▐▌  █  ▐▌       ▐▛▀▜▌▐▛▀▚▖▐▛▀▚▖▐▛▀▜▌ ▐▌  ▝▀▚▖
▐▙▄▄▀ ▐▌  ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▗▄█▄▖▝▚▄▄▖    ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ ▐▌ ▗▄▄▞▘
dynamic arrays
*/
// inspo :
// @note: thanks ginger bill :) he is the inspiration for this whole single header file
//  https://github.com/gingerBill/gb/blob/master/gb.h
// https://iafisher.com/blog/2020/06/type-safe-generics-in-c

typedef struct db_array_skeleton
{
    s64       total_length;
    s64       length;
    s64       type_size;
    db_arena *arena;
    void     *data;
} db_array_skeleton;

#define DB_ARRAY_DEFAULT_RESIZE_FACTOR 2
#define DB_ARRAY_DEFAULT_ALLOCATION_BUCKETS 512

#define db_array_decl(name, Type)                                                                                      \
    typedef struct db_array_##name                                                                                     \
    {                                                                                                                  \
        s64       total_length;                                                                                        \
        s64       length;                                                                                              \
        s64       type_size;                                                                                           \
        db_arena *arena;                                                                                               \
        Type     *data;                                                                                                \
    } db_array_##name;                                                                                                 \
    static inline db_array_##name db_array_##name##_init(db_arena *db_arena_ptr)                                       \
    {                                                                                                                  \
        ASSERT_WITH_MSG(db_arena_ptr, "Passed Arena is Null.");                                                        \
        ASSERT_WITH_MSG(db_arena_ptr->type == TYPE_ARENA_LINEAR,                                                       \
                        "Arena has to be a linear, we dont support chunked arenas yet:)");                             \
        db_array_##name _array = {};                                                                                   \
        __db_array_init(db_arena_ptr, (db_array_skeleton *)&_array, sizeof(Type));                                     \
        return _array;                                                                                                 \
    }                                                                                                                  \
    static inline s64 db_array_##name##_length(db_array_##name *a)                                                     \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        return a->length;                                                                                              \
    }                                                                                                                  \
    static inline void db_array_##name##_set_length(db_array_##name *a, s64 n)                                         \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        a->length = n;                                                                                                 \
    }                                                                                                                  \
    static inline s64 db_array_##name##_capacity(db_array_##name *a)                                                   \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        return a->total_length / a->type_size;                                                                         \
    }                                                                                                                  \
    static inline void db_array##name##_free(db_array_##name *a)                                                       \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        __db_array_free((db_array_skeleton *)a);                                                                       \
    }                                                                                                                  \
    static inline Type db_array_##name##_get_index(db_array_##name *a, s64 index)                                      \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        ASSERT_WITH_MSG(index < a->length, "Index out of bounds.");                                                    \
        return a->data[index];                                                                                         \
    }                                                                                                                  \
    static inline Type *db_array_##name##_get_index_ptr(db_array_##name *a, s64 index)                                 \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        ASSERT_WITH_MSG(index < a->length, "Index out of bounds.");                                                    \
        return &a->data[index];                                                                                        \
    }                                                                                                                  \
    static inline void db_array_##name##_append(db_array_##name *a, Type element)                                      \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        if (a->length + 1 >= a->total_length)                                                                          \
        {                                                                                                              \
            __db_array_resize((db_array_skeleton *)a);                                                                 \
        }                                                                                                              \
        a->data[a->length++] = element;                                                                                \
    }                                                                                                                  \
    static inline void db_array_##name##__pop(db_array_##name *a)                                                      \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        ASSERT_WITH_MSG(a->length != 0, "array has no elements yet.");                                                 \
        a->length--;                                                                                                   \
    }                                                                                                                  \
    static inline void db_array_##name##_remove_range(db_array_##name *a, s64 start, s64 num_elems)                    \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        /*get the remaining length of the array after start + num_elems                                                \
         *  for example: start = 2, num_elems = 3, v = n0 n1 n2 n3 n4 n5 n6 ... n                                      \
         *     v = n0 n1 n2 n3 n4 n5 n6 ...    we want to remove elmems n2, n3, n4                                     \
         * to get the length of the n5+ array. we have to do v.count -   len(n0,n1,...n4)                              \
         * length of the whole array - the length from the starting of array up to the last element we want to remove  \
         * */                                                                                                          \
        ASSERT(start < a->length);                                                                                     \
        s64 rem_length = a->length - ((start) + (num_elems));                                                          \
        ASSERT(rem_length >= 0);                                                                                       \
        memmove(&a->data[(start)], &a->data[(start) + (num_elems)], rem_length * a->type_size);                        \
        a->length -= num_elems;                                                                                        \
        memset(&a->data[a->length], 0, num_elems * a->type_size);                                                      \
    }                                                                                                                  \
    static inline void db_array_##name##_insert(db_array_##name *a, s64 index, s64 element)                            \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        if (a->length + 1 >= a->total_length)                                                                          \
        {                                                                                                              \
            __db_array_resize((db_array_skeleton *)&a);                                                                \
        }                                                                                                              \
        s64 move_length = a->length - index;                                                                           \
        memmove(&a->data[index + 1], &a->data[index], move_length * a->type_size);                                     \
        a->data[index] = element;                                                                                      \
        a->length++;                                                                                                   \
    }                                                                                                                  \
    static inline Type db_array_##name##_get_last(db_array_##name *a)                                                  \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        return a->data[a->length - 1];                                                                                 \
    }                                                                                                                  \
    static inline Type *db_array_##name##_get_last_ptr(db_array_##name *a)                                             \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        return &a->data[a->length - 1];                                                                                \
    }                                                                                                                  \
    static inline Type *db_array_##name##_find(db_array_##name *a, Type *elem,                                         \
                                               b8 (*db_array_##name##_cmp)(Type * a, Type * b))                        \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        s64 length = a->length;                                                                                        \
        for (s64 i = 0; i < length; i++)                                                                               \
        {                                                                                                              \
            if (db_array_##name##_cmp(elem, &a->data[i]))                                                              \
            {                                                                                                          \
                return &a->data[i];                                                                                    \
            }                                                                                                          \
        }                                                                                                              \
        return NULL;                                                                                                   \
    }                                                                                                                  \
    static inline db_array_##name db_array_##name##_duplicate(db_array_##name *a)                                      \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        db_array_##name _res   = db_array_##name##_init(a->arena);                                                     \
        s64             length = a->length;                                                                            \
        for (s64 i = 0; i < length; i++)                                                                               \
        {                                                                                                              \
            db_array_##name##_append(&_res, a->data[i]);                                                               \
        }                                                                                                              \
        return _res;                                                                                                   \
    }                                                                                                                  \
    static inline void db_array_##name##_clear(db_array_##name *a)                                                     \
    {                                                                                                                  \
        ASSERT(a);                                                                                                     \
        memset(a->data, 0, a->length * a->type_size);                                                                  \
        a->length = 0;                                                                                                 \
    }                                                                                                                  \
    static inline void db_array_copy(db_array_##name *arr_dest, db_array_##name *arr_src)                              \
    {                                                                                                                  \
        ASSERT(arr_dest);                                                                                              \
        ASSERT(arr_src);                                                                                               \
        db_array_##name##_clear(arr_dest);                                                                             \
        s64 length = db_array_##name##_length(arr_src);                                                                \
        for (s64 i = 0; i < length; i++)                                                                               \
        {                                                                                                              \
            db_array_##name##_append(arr_dest, arr_src->data[i]);                                                      \
        }                                                                                                              \
    }

// removes from the starting index + num_elems elements
#define db_array_for_each(array, i, iter) for (i = 0, iter = array.data[i]; i < array.length; i++, iter = array.data[i])
#define db_array_for_each_ptr(array, i, iter)                                                                          \
    for (i = 0, iter = &array.data[i]; i < array.length; i++, iter = &array.data[i])

db_return_code __db_array_init(db_arena *shared_arena, db_array_skeleton *array, size_t type_size);
void           __db_array_free(db_array_skeleton *array);

// /*
//   ▗▄▄▖▗▄▄▄▖▗▄▖  ▗▄▄▖▗▖ ▗▖
//  ▐▌     █ ▐▌ ▐▌▐▌   ▐▌▗▞▘
//   ▝▀▚▖  █ ▐▛▀▜▌▐▌   ▐▛▚▖
//  ▗▄▄▞▘  █ ▐▌ ▐▌▝▚▄▄▖▐▌ ▐▌
//
// // */
// //@info: this will make it so each stack has its own backing arena. idk if this is the way I should do it
// // @warn: each stack has its own arena.  which can allocate physical mem behind your back
// // @info : only use this when you know that you need an stack that is bigger than 4kb
// #define db_stack(type) db_array(type)
// #define db_stack_init(arena, stack) db_array_init(arena, stack)
// #define db_stack_push(stack, elem) db_array_append(stack, elem)
// #define db_stack_pop(stack) db_array_pop(stack)
// #define db_stack_peek(stack) db_array_get_last(stack)
// #define db_stack_peek_ptr(stack) db_array_get_last_ptr(stack)
// #define db_stack_free(stack) db_array_free(stack)
// #define db_stack_get_count(stack) db_array_length(stack)
// #define db_stack_clear(stack) db_array_clear(stack)
//
// /*
//  ▗▄▄▖▗▖ ▗▖ ▗▄▖ ▗▄▄▖  ▗▄▄▖
// ▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌
// ▐▌   ▐▛▀▜▌▐▛▀▜▌▐▛▀▚▖ ▝▀▚▖
// ▝▚▄▄▖▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▗▄▄▞▘
//
// */
//
// char db_char_to_lower(char c);
// char db_char_to_upper(char c);
// b8   db_char_is_space(char c);
// b8   db_char_is_digit(char c);
// b8   db_char_is_hex_digit(char c);
// b8   db_char_is_alphabet(char c);
// b8   db_char_is_alphanumeric(char c);
// s32  db_digit_to_int(char c);
// s32  db_hex_digit_to_int(char c);
//
// void db_str_to_lower(char *str);
// void db_str_to_upper(char *str);
//
// char const *db_char_first_occurence(char const *str, char c);
// char const *db_char_last_occurence(char const *str, char c);
//
// /*
//      ▗▄▄▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▄▖ ▗▄▄▖
//     ▐▌     █  ▐▌ ▐▌  █  ▐▛▚▖▐▌▐▌   ▐▌
//      ▝▀▚▖  █  ▐▛▀▚▖  █  ▐▌ ▝▜▌▐▌▝▜▌ ▝▀▚▖
//     ▗▄▄▞▘  █  ▐▌ ▐▌▗▄█▄▖▐▌  ▐▌▝▚▄▞▘▗▄▄▞▘
//
// */
// // https://graphics.stanford.edu/~seander/bithacks.html#ZeroInWord
// // all the tricks that I use for the following funcs are defined in this above page
// // Still have to implement it
// // size_t db_strlen(char const *str);
// // size_t db_strnlen(char const *str, size_t max_len);
// // s32    db_strcmp(char const *s1, char const *s2);
// // s32    db_strncmp(char const *s1, char const *s2, size_t len);
// // char  *db_strcpy(char *dest, char const *source);
// // char  *db_strncpy(char *dest, char const *source, size_t len);
// // size_t db_strlcpy(char *dest, char const *source, size_t len);
// // char  *db_strrev(char *str); // NOTE(bill): ASCII only
// //
// // char const *db_strtok(char *output, char const *src, char const *delimit);
// //
// // b8 db_str_has_prefix(char const *str, char const *prefix);
// // b8 db_str_has_suffix(char const *str, char const *suffix);
// //
// //
// // void gb_str_concat(char *dest, size_t dest_len, char const *src_a, size_t src_a_len, char const *src_b,
// //                   size_t src_b_len);
// //
// // u64  db_str_to_u64(char const *str, char **end_ptr,
// //                   s32 base); // TODO: Support more than just decimal and hexadecimal
// // s64  db_str_to_i64(char const *str, char **end_ptr,
// //                   s32 base); // TODO: Support more than just decimal and hexadecimal
// // f32  db_str_to_f32(char const *str, char **end_ptr);
// // f64  db_str_to_f64(char const *str, char **end_ptr);
// // void db_i64_to_str(s64 value, char *string, s32 base);
// // void db_u64_to_str(u64 value, char *string, s32 base);
//
// // my string
// typedef db_array(char) db_string;
//
// char *db_string_get_first_occurence(const char *str, const char *sub);
// void  db_string_make_reserve(db_string str, s64 capacity);
//
// //@info: this will make it so each string has its own backing arena. idk if I should do it
// // @warn: each string has its own arena.  which can allocate physical mem behind your back
// // @info : only use this when you know that you need a string that is bigger than 4kb
//
// db_string db_string_make(db_arena *arena, char const *a);
// db_string db_string_duplicate(db_arena *arena, db_string const str);
// // does not do anything except if its a pool allocator
// void      db_string_free(db_string str);
// s64       db_string_length(db_string const str);
// s64       db_string_capacity(db_string const str);
// s64       db_string_available_space(db_string const str);
// void      db_string_clear(db_string str);
// void      db_string_append(db_string str, const char *other);
// void      db_string_append_char(db_string str, const char c);
// b8        db_strings_are_equal(db_string const lhs, db_string const rhs);
// db_string db_string_trim(db_string str, char const *cut_set);
// db_string db_string_trim_space(db_string str); // Whitespace ` \t\r\n\v\f`
//
// // well this looks like for utf8 strings. Well Let me figure that out later
// // db_string db_string_append_rune(db_string str, Rune r);
// // I have to have my own fmt parser so this is disabled for now
// // db_string db_string_append_fmt(db_string str, char const *fmt, ...);
// void db_string_set(db_string str, char const *cstr);
// // hmmmmm I dont think we need this because our arena will automatically scale based on appending
// // db_string db_string_make_length(db_string str, void const *a, s64 num_bytes);
// // void       db_string_make_space_for(db_string str, s64 add_len);
// // s64        db_string_allocation_size(db_string const str);
// /*
// ▗▖ ▗▖ ▗▄▖  ▗▄▄▖▗▖ ▗▖▗▖  ▗▖ ▗▄▖ ▗▄▄▖
// ▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌ ▐▌▐▌ ▐▌
// ▐▛▀▜▌▐▛▀▜▌ ▝▀▚▖▐▛▀▜▌▐▌  ▐▌▐▛▀▜▌▐▛▀▘
// ▐▌ ▐▌▐▌ ▐▌▗▄▄▞▘▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▐▌
// */
//
// #define DB_HASH_SEED 0x31415926
// #define db_hash_string(data) db_murmur64A_seed(data, strlen(data), DB_HASH_SEED)
// u64 db_murmur64A_seed(void const *const key, u64 len, u64 seed);

/*
▗▄▄▄▖▗▖  ▗▖▗▄▄▖ ▗▖   ▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖▗▄▄▄▖▗▄▖▗▄▄▄▖▗▄▄▄▖ ▗▄▖ ▗▖  ▗▖
  █  ▐▛▚▞▜▌▐▌ ▐▌▐▌   ▐▌   ▐▛▚▞▜▌▐▌   ▐▛▚▖▐▌  █ ▐▌ ▐▌ █    █  ▐▌ ▐▌▐▛▚▖▐▌
  █  ▐▌  ▐▌▐▛▀▘ ▐▌   ▐▛▀▀▘▐▌  ▐▌▐▛▀▀▘▐▌ ▝▜▌  █ ▐▛▀▜▌ █    █  ▐▌ ▐▌▐▌ ▝▜▌
▗▄█▄▖▐▌  ▐▌▐▌   ▐▙▄▄▖▐▙▄▄▖▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌  █ ▐▌ ▐▌ █  ▗▄█▄▖▝▚▄▞▘▐▌  ▐▌

*/

#ifdef DB_IMPLEMENTATION
#undef DB_IMPLEMENTATION
// verify later on though if i could have huge pages or not

void *__db_reserve_virtual_memory(size_t reserve_memory_size)
{
    void *ptr = NULL;
#if defined(DB_PLATFORM_LINUX) || defined(DB_PLATFORM_MACOS)
    // thanks @tsoding (mista zozin) for the mmap explanation https://youtu.be/sfyfubzu9ow
    ptr = mmap(NULL, reserve_memory_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    ASSERT(ptr != MAP_FAILED);

    return ptr;
#elif defined(DB_PLATFORM_WINDOWS)
    ptr = VirtualAlloc(0, reserve_memory_size, MEM_RESERVE, PAGE_READWRITE);
#endif
    ASSERT(ptr != NULL);
    return (void *)ptr;
}

db_return_code __db_commit_virtual_memory(void *memory, s32 page_offset, s32 num_pages)
{
    uintptr_t next_page_base_ptr = (uintptr_t)memory + (page_offset * DB_PAGE_SIZE);
    s64       new_allocated_size = num_pages * DB_PAGE_SIZE;

#if defined(DB_PLATFORM_LINUX) || defined(DB_PLATFORM_MACOS)
    s32 ret_code = mprotect((void *)next_page_base_ptr, new_allocated_size, PROT_READ | PROT_WRITE);
    if (ret_code == -1)
    {
        printf("cannot commit: %d pages, arleady commited %d pages. increase the reserved virtual alloc size.\n",
               num_pages, page_offset);
        ASSERT(ret_code != -1);
    }

    // poison the memory
    asan_poison_memory_region((void *)next_page_base_ptr, new_allocated_size);

    return DB_SUCCESS;
#elif defined(DB_PLATFORM_WINDOWS)
    b8 result = (VirtualAlloc((void *)next_page_base_ptr, new_allocated_size, MEM_COMMIT, PAGE_READWRITE) != NULL);

    if (result == false)
    {
        printf("cannot commit: %d pages, arleady commited %d pages. increase the reserved virtual alloc size.\n",
               num_pages, page_offset);
        ASSERT(result);
    }
    return DB_SUCCESS;
#endif
}

// i dont think i will decomit individual pages, for example for an dynamic array i am pretty sure i will not decommit
// the last page or last 2 pages and so on. so decommit the whole allocated memory size of it.
// decommiting means letting the os reclaim the pages while retaining the virtual address space.
// idk when i will call this though, i think i will just unmap it but oh well :)

db_return_code __db_decommit_virtual_memory(void *memory, size_t size)
{
#if defined(DB_PLATFORM_LINUX) || defined(DB_PLATFORM_MACOS)
    madvise(memory, size, MADV_DONTNEED);
    s32 ret_code = mprotect(memory, size, PROT_NONE);
    ASSERT(ret_code != -1);
    return DB_SUCCESS;
#elif defined(DB_PLATFORM_WINDOWS)
    // size not needed for windows
    VirtualFree(memory, 0, MEM_DECOMMIT);
#endif
    return DB_ERROR;
}
// unmaping the memory
db_return_code __db_release_virtual_memory(void *memory, size_t size)
{
#if defined(DB_PLATFORM_LINUX) || defined(DB_PLATFORM_MACOS)
    s32 ret_code = munmap(memory, size);
    ASSERT(ret_code != -1);
    return DB_SUCCESS;
#elif defined(DB_PLATFORM_WINDOWS)
    VirtualFree(memory, 0, MEM_RELEASE);
    return DB_SUCCESS;
#endif
}

// the easy and the understandable way of doing this is to take an example:
// m = 13 and n = 8, the problem is that we need to align 13 to an multiple of 8.
// or in other words how much do i have to add to 13 in order to make it a multiple of 8.
// really naive solution:
// 1st) find out the interval in which m exists. (k - 1)n <= m <= kn, in our case 8 < 13 < 16
// 2nd) find out how much do we have to add. kn - m. 16 - 13 = 3
// 3rd) add it and then you have the next multiple of n from m.
// there is a problem with this solution. its really inefficeint because first we have to find the largest multiple
// of n
// which is bigger than m. and for large values we might have to do multiple multiplication and then check if that
// number is greater than n. psudo code
//             k = 1
//             while(n * k < m)k++;
//             how_much_to_add = n * k - m
//             m + how_much_to_add == n * k
// so to simplyfy it we do a neat math trick
// we take the mod of the divisor and the quotient for example: m (mod) n
// when we do the mod we get the remainder. the remainder will help us find how much do we have to add to make it an
// multiple of n. for example: 13 mod 8
//       8|13|1
//        - 8      the remainder is the remaning part when an integer cannot divide another interger.
//          5      we can use this fact to find out which integer will divide it.
//    lets visualize this
//       if we wanted to find out the lowest multiple we cound just minus the remainder and be done with it.
//       to find out the next largest integer which can be divided we can do (8 - remainder) + 13
//                          8____13__16
// so this simplifies our solution
//  pseudo code:
//      remainder = m % n
//      padding   = (n - remainder)
//      next_multiple = m + padding
// there is a one small caviat with this solution. lets say m = 8
// we dont want to find the next multiple if m mod n == 0
// so before we add the padding we just mod it my n so that if the remainder was 0 the padding will also be 0
// for example:
// m = 16, n = 8
// remainder = 16 % 8 = 0
// padding = (8 - remainder) = 8 - 0;
// // if we just add the padding we would get 24 which we dont want. so
// aligned_padding = padding % n
// next_multiple = m + aligned_padding
// one liner : ((n - (m % n)) % n) + m
//
// another faster way is to do a bitwise operation if and only if n is a multiple of 2
// this one is a little confusing. i sill dont understand it compeletly
// this works because of the 2'str complement so for example :
//  8: 0000000 00000000 00000000 00001000
//  to get -8 from 8 we do  the following
//  first we have 8'str binary 0000000 00000000 00000000 00001000
//  then we inverse all the bits 0'str map to 1 and 1 maps to 0
//  1111111 11111111 11111111 11110111 then we add  1 to it.
//
//   1111111 11111111 11111111 11110111
// + 0000000 00000000 00000000 00000001
//   1111111 11111111 11111111 11111000  which is -8
//
// -8: 1111111 11111111 11111111 11111000 .this is the 2'str complemenent representation
// which i didnt know even though i have been programming for about 4 years with c :(. damn wtf.....
//
// so how does the following work?
// for example mem = 13 and align to = 8
// 13 in binary      : 00000000 00000000 00000000 00001101
//  8 in binary      : 00000000 00000000 00000000 00001000
// (8 - 1) in binary : 00000000 00000000 00000000 00000111
// 13 + (8 - 1)      : 00000000 00000000 00000000 00010100
// (13 + (8 - 1)) & (-8)
//
// 13 + (8 - 1)      : 00000000 00000000 00000000 00010100
// -8                : 11111111 11111111 11111111 11111000 -> which we derived from the above example
//(13 +(8 - 1)) & -8 : 00000000 00000000 00000000 00010000 -> which would be 16
#define DB_ALIGN_TO_MULTIPLE(mem, align_to) (((uintptr_t)mem + (align_to - 1)) & (-align_to))
#define DB_DEFAULT_MEMORY_ALIGNEMENT 8

// use the macro if its a align_to is the power of 2
uintptr_t __db_align_to_multiple(uintptr_t mem, s32 align_to)
{
    /*
       https://en.wikipedia.org/wiki/data_structure_alignment
      padding = (align - (offset mod align)) mod align
     aligned = offset + padding
     = offset + ((align - (offset mod align)) mod align)
    */
    size_t    padding     = (align_to - (mem % align_to)) % align_to;
    uintptr_t aligned_mem = mem + padding;
    return aligned_mem;
}

//
// args:
// memory_size -> in bytes
db_arena db_arena_init_with_size(db_arena_params *params, size_t memory_size)
{
    db_arena_params def_params = {.type = TYPE_ARENA_LINEAR, .chunk_size = 0};

    if (params)
    {
        def_params.type = params->type;
        if (def_params.type == TYPE_ARENA_CHUNKED)
        {
            ASSERT_WITH_MSG(params->chunk_size, "Chunked Arena specified but Chunk size is 0.");
            def_params.chunk_size = params->chunk_size;
        }
    }

    size_t mem_size = memory_size;
    if (mem_size < DB_ARENA_DEFAULT_COMMITED_MEMORY)
    {
        mem_size = DB_ARENA_DEFAULT_COMMITED_MEMORY;
    }
    else if (mem_size > DB_ARENA_DEFAULT_COMMITED_MEMORY)
    {
        mem_size = DB_ALIGN_TO_MULTIPLE(mem_size, DB_ARENA_DEFAULT_COMMITED_MEMORY);
    }
    // well if you are allocating an arena which has a size greater than db_ARENA_DEFAULT_RESERVED_MEMORY usally
    // 64mb.
    // then why are you allocating it? i cant think of a reason for that :).
    ASSERT(mem_size < DB_ARENA_DEFAULT_RESERVED_MEMORY);

    s32   num_pages_to_commit = mem_size / DB_PAGE_SIZE;
    void *memory              = __db_reserve_virtual_memory(DB_ARENA_DEFAULT_RESERVED_MEMORY);
    ASSERT(memory != NULL);

    db_return_code code = __db_commit_virtual_memory(memory, 0, num_pages_to_commit);
    ASSERT(code != DB_ERROR);

    db_arena arena           = {0};
    arena.curr_page_offset   = num_pages_to_commit;
    arena.allocated_till_now = 0;
    arena.total_size         = mem_size;
    arena.memory             = memory;
    arena.type               = def_params.type;
    arena.curr_mem_pos       = (uintptr_t)arena.memory;

    if (def_params.type == TYPE_ARENA_CHUNKED)
    {
        ASSERT_WITH_MSG(def_params.chunk_size % 8 == 0, "Chunk size must be a multiple of 8 bytes.");
        ASSERT_WITH_MSG(def_params.chunk_size > sizeof(db_arena_chunk_header), "Chunk Size is too small.");
        arena.chunk_size         = def_params.chunk_size;
        arena.allocated_till_now = mem_size; // cause we allocated all of it right
        u64 chunk_count          = mem_size / def_params.chunk_size;

        uintptr_t mem = arena.curr_mem_pos;
        for (u64 i = 0; i < chunk_count; i++)
        {

            /*
               ┌───┐
               │   │ <- previous linked list head
               └───┘

               ┌───┐   ┌───┐
               │   ├<──┤   │ <- new node which was created
               └───┘   └───┘       which will be our new linked list head
                ^
                prev head will be the next node in our linked list;

            */
            db_arena_chunk_header *header = (db_arena_chunk_header *)mem;
            header->next_chunk            = arena.free_list_head;
            arena.free_list_head          = header;

            mem += arena.chunk_size;
            // i think this is unnecessary cause chunk size is supposed to be multiple of 8
            DB_ALIGN_TO_MULTIPLE(mem, DB_DEFAULT_MEMORY_ALIGNEMENT);
        }
    }
    return arena;
}

void db_arena_chunked_init(db_arena *arena, size_t chunk_count, void *mem)
{
    ASSERT((uintptr_t)mem % 8 == 0);
    for (u64 i = 0; i < chunk_count; i++)
    {

        /*
           ┌───┐
           │   │ <- previous linked list head
           └───┘

           ┌───┐   ┌───┐
           │   ├<──┤   │ <- new node which was created
           └───┘   └───┘       which will be our new linked list head
           ^
           prev head will be the next node in our linked list;

*/
        db_arena_chunk_header *header  = (db_arena_chunk_header *)mem;
        header->next_chunk             = arena->free_list_head;
        arena->free_list_head          = header;
        mem                           += arena->chunk_size;
        // i think this is unnecessary cause chunk size is supposed to be multiple of 8
        DB_ALIGN_TO_MULTIPLE(mem, DB_DEFAULT_MEMORY_ALIGNEMENT);
    }
}

void db_arena_resize(db_arena *arena, size_t size)
{
    size_t new_size = 0;
    if (size < DB_PAGE_SIZE)
    {
        new_size = DB_PAGE_SIZE;
    }
    else
    {
        new_size = DB_ALIGN_TO_MULTIPLE(size, DB_PAGE_SIZE);
    }

    s32 num_pages = new_size / DB_PAGE_SIZE;

    // lets say we have commited n - 1 pages of total reserved memory and now we want to allocate n + k number
    // of pages. i am pretty sure that the os will not let us and its going to crash the application.
    db_return_code code = __db_commit_virtual_memory(arena->memory, arena->curr_page_offset, num_pages);

    arena->total_size       += num_pages * DB_PAGE_SIZE;
    arena->curr_page_offset += num_pages;
    ASSERT(code != DB_ERROR);

    if (arena->type == TYPE_ARENA_CHUNKED)
    {
        arena->allocated_till_now = arena->total_size;
        u64 chunk_count           = num_pages / arena->chunk_size;

        //@todo: is this real chat??
        uintptr_t new_page_start_ptr = (uintptr_t)arena->memory + (num_pages * DB_PAGE_SIZE);
        db_arena_chunked_init(arena, chunk_count, (void *)new_page_start_ptr);
        arena->free_list_head = (db_arena_chunk_header *)new_page_start_ptr;
    }
}

// args:
//  arena -> ptr to the db_arena form which you would like to allocate.
//  size ->  memory block size to allocate from the arena.
void *db_arena_alloc(db_arena *arena, size_t size)
{
    ASSERT(arena != NULL);
    ASSERT(size != 0);
    // if the size passed on is bigger than the toal size of the arena then increase the size of the arena to
    // accodomate the allocation.
    size_t aligned_size = DB_ALIGN_TO_MULTIPLE(size, DB_DEFAULT_MEMORY_ALIGNEMENT);
    if (arena->type == TYPE_ARENA_LINEAR)
    {
        if (arena->allocated_till_now + aligned_size > (size_t)arena->total_size)
        {
            db_arena_resize(arena, aligned_size);
        }
    }
    else if (arena->type == TYPE_ARENA_CHUNKED)
    {
        if (arena->free_list_head == NULL) // this means all the free list nodes are occupied
        {
            db_arena_resize(arena, DB_PAGE_SIZE); // @todo: think of a better growth factor for the arena
        }
    }

    void *ret_mem = NULL;
    if (arena->type == TYPE_ARENA_LINEAR)
    {
        // unpoison the memory;
        ret_mem = (void *)arena->curr_mem_pos;
        asan_unpoison_memory_region(ret_mem, aligned_size);

        // align the mem ptr to a multiple of 8 for better cpu/read writes
        uintptr_t temp = arena->curr_mem_pos;

        arena->curr_mem_pos += aligned_size;
        arena->curr_mem_pos  = DB_ALIGN_TO_MULTIPLE(arena->curr_mem_pos, DB_DEFAULT_MEMORY_ALIGNEMENT);

        // sanity check
        // if this triggers then i need to fix the aligned_size logic.
        ASSERT((temp + aligned_size) == arena->curr_mem_pos);

        arena->allocated_till_now += aligned_size;
    }
    else if (arena->type == TYPE_ARENA_CHUNKED)
    {
        db_arena_chunk_header *header = arena->free_list_head;
        ret_mem                       = (void *)((uintptr_t)header + sizeof(db_arena_chunk_header));
        asan_unpoison_memory_region(ret_mem, DB_PAGE_SIZE);
        DB_ALIGN_TO_MULTIPLE((uintptr_t)ret_mem, DB_DEFAULT_MEMORY_ALIGNEMENT);

        arena->free_list_head = header->next_chunk;
        header->next_chunk    = NULL; // invalidate the pointer

        // sanity check
        ASSERT((uintptr_t)header + sizeof(db_arena_chunk_header) == (uintptr_t)ret_mem);

        arena->allocated_chunk_count++;
    }
    ASSERT_WITH_MSG(ret_mem, "ARENA ALLOCATION FAILEDD!!!! WHYYY");
    return ret_mem;
}

// hmmmmmmmmmmmmmmmmmmmmmm
/*
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⡠⠞⠉⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠲⡑⢄⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⢮⣣⡀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⠞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠁⠱⡀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢣⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⡞⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⡆⠀
⠀⠀⠀⠀⠀⠀⠀⠀⡼⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⡤⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢸⣹⠀
⠀⠀⠀⠀⢀⣀⣀⣸⢧⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠞⣩⡤⠶⠶⠶⠦⠤⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠘⡇⡇
⠀⠀⠀⣰⣫⡏⠳⣏⣿⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠚⠁⠀⠀⠀⠀⠀⠀⠙⢿⣿⣶⣄⡀⠀⠀⢀⡀⠀⠀⠀⠀⠀⡀⡅⡇
⠀⠀⢰⡇⣾⡇⠀⠙⣟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣀⣠⣴⣶⠿⠛⠻⢿⣶⣤⣍⡙⢿⣿⣷⣤⣾⡇⣼⣆⣴⣷⣿⣿⡇⡇
⠀⠀⢸⡀⡿⠁⠀⡇⠈⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⣿⣯⠴⢲⣶⣶⣶⣾⣿⣿⣿⣷⠹⣿⣿⠟⢰⣿⣿⣿⠿⣿⣿⣿⠁
⠀⠀⠈⡇⢷⣾⣿⡿⢱⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠉⠉⠹⣌⠳⣼⣿⣿⣿⣻⣿⣿⣿⣿⡇⠈⠁⢰⣿⣿⣿⣿⣶⣾⣿⣿⠀
⠀⠀⠀⣷⠘⠿⣿⡥⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠈⠃⠌⠉⣿⣿⣿⣿⣿⣿⠟⠃⠀⢀⡿⣿⣿⣿⣿⣿⣿⣿⡞⠀
⠀⠀⠀⢸⡇⠀⠹⠗⡀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣸⣿⡿⠟⠉⠉⠀⠀⠀⠈⢃⣿⣿⣿⣿⣿⣿⡻⠀⠀
⠀⠀⠀⠈⢧⠀⠀⠏⣇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠙⠋⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⣿⣿⣿⣿⣿⣿⠁⠀⠀
⠀⠀⠀⠀⠈⢳⠶⠞⠃⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⣴⠆⠀⠀⠊⠁⠀⠀⠀⠀⠸⣿⣿⣿⣿⣿⣿⠀⠀⠀
⠀⠀⠀⠀⠀⢸⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠂⠀⣼⣿⣀⡰⠀⠀⣤⣄⠀⠀⠀⠀⢹⣿⣿⣿⣿⢻⠀⠀⠀
⠀⠀⠀⠀⠀⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠉⠹⣿⠀⠀⠀⠀⠉⠀⠀⠀⠀⠀⠙⣿⣿⣿⡏⠀⠀⠀
⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢻⣄⢠⣤⣶⣤⣀⠀⢀⣶⣶⣶⣿⣿⠟⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⠖⠁⠀⠀⠀⠀⠀⠻⣿⣿⣥⣤⣯⣥⣾⣿⣿⣿⣿⠋⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣰⠇⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⢀⡼⠁⠀⠀⠀⠠⠀⠀⠀⠀⠈⣿⣿⣼⣿⣿⣿⣿⣿⣿⠇⠀⠀⠀⠀⠀⠀
⠀⠀⠀⡰⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠊⠀⠀⠀⣠⣰⣄⡀⠀⢀⣀⣀⣛⣟⣿⣿⣿⣿⣿⣿⡿⠀⠀⠀⠀⠀⠀⠀
⠀⣠⠜⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣠⣼⠾⠛⠛⠻⠿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⣿⠃⠀⠀⠀⠀⠀⠀⠀
⠾⠁⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣼⡟⠀⠀⠀⠀⠠⣄⣉⣉⣻⣿⣿⣿⣿⣿⣿⡟⠧⢄⡀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠻⠅⠀⠀⠀⠀⠘⠉⠹⣿⣿⣿⣿⣿⣿⣿⣿⣧⡀⠀⠉⠓⠢⣄⠀⠀⠀
⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⣉⣿⣿⣿⣿⣿⣿⣿⣿⣷⣻⡄⠀⠀⢀⡑⠢⠄
*/
db_return_code db_arena_free_node(db_arena *arena, void *ptr)
{
    ASSERT(ptr);
    ASSERT(arena);
    ASSERT(arena->type == TYPE_ARENA_CHUNKED);

    db_arena_chunk_header *header = (db_arena_chunk_header *)((uintptr_t)ptr - sizeof(db_arena_chunk_header));
    // check for ptr validity
    // kinda useless??
    {

        u64 chunk_count = arena->total_size / arena->chunk_size;

        db_arena_chunk_header *check = arena->memory;
        b8                     found = false;
        for (u64 i = 0; i < chunk_count && !found; i++)
        {
            if (check == header)
            {
                found = true;
            }
            check = (db_arena_chunk_header *)((uintptr_t)check + arena->chunk_size);
        }
        ASSERT_WITH_MSG(found, "This ptr is not valid.");
    }
    header->next_chunk    = arena->free_list_head;
    arena->free_list_head = header;

    return DB_SUCCESS;
}

db_return_code db_arena_reset(db_arena *arena)
{
    ASSERT(arena != NULL);

    memset(arena->memory, 0, arena->allocated_till_now);
    arena->allocated_till_now = 0;
    arena->curr_mem_pos       = (uintptr_t)arena->memory;
    arena->free_list_head     = NULL;

    return DB_SUCCESS;
}

db_return_code db_arena_free(db_arena *arena)
{
    ASSERT(arena != NULL);

    // there might be the case that we allocated/commited more than db_ARENA_DEFAULT_RESERVED_MEMORY.
    size_t total_reserved_size = db_max(arena->total_size, DB_ARENA_DEFAULT_RESERVED_MEMORY);

    db_return_code res = __db_release_virtual_memory(arena->memory, total_reserved_size);
    ASSERT(res != DB_ERROR);

    return DB_SUCCESS;
}

db_return_code __db_array_resize(db_array_skeleton *array)
{
    ASSERT(array != NULL);

    size_t new_size = array->total_length * DB_ARRAY_DEFAULT_RESIZE_FACTOR;
    void  *new_mem  = db_arena_alloc(array->arena, new_size * array->type_size);
    memcpy(new_mem, array->data, array->length * array->type_size);
    array->data          = new_mem;
    array->total_length += new_size;
    return DB_SUCCESS;
}

db_return_code __db_array_init(db_arena *shared_arena, db_array_skeleton *array, size_t type_size)
{

    // maybe a bit wasteful but we've already commited this much isnt it?
    size_t array_size = DB_ARRAY_DEFAULT_ALLOCATION_BUCKETS * type_size;
    if (array_size >= DB_PAGE_SIZE)
    {
        printf("The array you are initializing is already bigger than the page size on your os. You might consider "
               "using the big array for this one cheif.\n");
    }
    array_size = DB_ALIGN_TO_MULTIPLE(array_size, DB_DEFAULT_MEMORY_ALIGNEMENT);

    void *memory = db_arena_alloc(shared_arena, array_size);

    array->total_length = array_size / type_size;
    array->length       = 0;
    array->type_size    = type_size;
    array->arena        = shared_arena;
    array->data         = memory;
    return DB_SUCCESS;
}

void __db_array_free(db_array_skeleton *array)
{
    ASSERT(array != NULL);
    array->total_length = 0;
    array->length       = 0;
    array->type_size    = 0;
    array->data         = NULL;
    // does absolutely nothing actually
    // print warning
    printf("WHY ARE YOU MANNUALLY FREEING UP MEMORY???????\n");
    ASSERT_WITH_MSG(false, "I DID THIS JUST TO PISS YOU OFFF");
}
//
// #define DB_SIZE_T_BITS ((sizeof(size_t)) * 8)
//
// #define DB_rotate_left(val, n) (((val) << (n)) | ((val) >> (db_SIZE_T_BITS - (n))))
// #define DB_rotate_right(val, n) (((val) >> (n)) | ((val) << (db_SIZE_T_BITS - (n))))
//
// u64 db_murmur64A_seed(void const *const key, u64 len, u64 seed)
// {
//     const u64 m = 0xc6a4a7935bd1e995LLU;
//     const int r = 47;
//
//     u64 h = seed ^ (len * m);
//
//     const u64 *data = (const u64 *)key;
//     const u64 *end  = (len >> 3) + data;
//
//     while (data != end)
//     {
//         u64 k = *data++;
//
//         k *= m;
//         k ^= k >> r;
//         k *= m;
//
//         h ^= k;
//         h *= m;
//     }
//
//     const unsigned char *data2 = (const unsigned char *)data;
//
//     switch (len & 7)
//     {
//         case 7:
//             h ^= (u64)(data2[6]) << 48;
//         case 6:
//             h ^= (u64)(data2[5]) << 40;
//         case 5:
//             h ^= (u64)(data2[4]) << 32;
//         case 4:
//             h ^= (u64)(data2[3]) << 24;
//         case 3:
//             h ^= (u64)(data2[2]) << 16;
//         case 2:
//             h ^= (u64)(data2[1]) << 8;
//         case 1:
//             h ^= (u64)(data2[0]);
//             h *= m;
//     };
//
//     h ^= h >> r;
//     h *= m;
//     h ^= h >> r;
//
//     return h;
// }
//
// char db_char_to_lower(char c)
// {
//     if (c >= 'A' && c <= 'Z')
//     {
//         char ret = 'a' + (c - 'A');
//         return ret;
//     }
//     return c;
// }
// char db_char_to_upper(char c)
// {
//     if (c >= 'a' && c <= 'z')
//     {
//         char ret = 'A' + (c - 'a');
//         return ret;
//     }
//     return c;
// }
// b8 db_char_is_space(char c)
// {
//     if (c == ' ' || c == '\t' || c == '\n' || c == '\r' || c == '\f' || c == '\v')
//     {
//         return true;
//     }
//     return false;
// }
// b8 db_char_is_digit(char c)
// {
//     if (c >= '0' && c <= '9')
//     {
//         return true;
//     }
//     return false;
// }
// b8 db_char_is_hex_digit(char c)
// {
//     if (db_char_is_digit(c) || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F'))
//     {
//         return true;
//     }
//     return false;
// }
// b8 db_char_is_alphabet(char c)
// {
//     if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
//     {
//         return true;
//     }
//     return false;
// }
// b8 db_char_is_alphanumeric(char c)
// {
//     if (db_char_is_alphabet(c) || db_char_is_digit(c))
//     {
//         return true;
//     }
//     return false;
// }
// // hex digit
// // IF YOU ARE TURNING A HEX INTO A DIGIT THEN:
// // if its a it will return 10 and so on till f == 15 but if the value is anything plus f, so g,h... it will return
// // an incorecct value so always call is db_char_is_hex_digit() before calling this.
// s32 db_digit_to_int(char c)
// {
//     if (db_char_is_digit(c))
//     {
//         return (c - '0');
//     }
//     return (c - 'W');
// }
// s32 db_hex_digit_to_int(char c)
// {
//     if (db_char_is_digit(c))
//     {
//         return db_digit_to_int(c);
//     }
//     else if (c <= 'a' && c <= 'f')
//     {
//         return 10 + c;
//     }
//     else if (c <= 'A' && c <= 'F')
//     {
//         return 10 + c;
//     }
//     return -1;
// }
//
// void db_str_to_lower(char *str)
// {
//     // well if you forget the null terminator then we're kind of fucked
//     while (*str)
//     {
//         *str = db_char_to_lower(*str);
//         str++;
//     }
// }
// void db_str_to_upper(char *str)
// {
//     // well if you forget the null terminator then we're kind of fucked
//     while (*str)
//     {
//         *str = db_char_to_upper(*str);
//         str++;
//     }
// }
//
// char const *db_char_first_occurence(char const *str, char c)
// {
//     char ch = c;
//     for (; *str != ch; str++)
//     {
//         if (*str == '\0')
//         {
//             return NULL;
//         }
//     }
//     return str;
// }
// char const *db_char_last_occurence(char const *str, char c)
// {
//     char const *result = NULL;
//     do
//     {
//         if (*str == c)
//         {
//             result = str;
//         }
//     } while (*str++);
//
//     return result;
// }
//
// db_string db_string_make(db_arena *arena, char const *a)
// {
//     db_string str;
//     db_array_init(arena, str);
//     while (*a)
//     {
//         db_array_append(str, *a);
//         a++;
//     }
//     s64 count  = db_array_length(str);
//     // hmmm it will be zero there too but lets just me more explicit
//     str[count] = '\0';
//     return str;
// }
// void db_string_make_reserve(db_string str, s64 capacity)
// {
//     if (db_array_capacity(str) > capacity)
//     {
//         return;
//     }
//     else
//     {
//         // hmmm what if even after this the capacity is smaller?
//         // FIXME:
//         __db_array_resize((void **)&str);
//     }
// }
// void db_string_free(db_string str)
// {
//     db_array_free(str);
// }
// db_string db_string_duplicate(db_arena *arena, db_string const str)
// {
//     db_string new_str = db_array_duplicate(str);
//     s64       count   = db_array_length(new_str);
//     // hmmm it will be zero there too but lets just me more explicit
//     new_str[count]    = '\0';
//     return new_str;
// }
// s64 db_string_length(db_string const str)
// {
//     db_array_header *header = db_array_get_header(str);
//     ASSERT_WITH_MSG(header != NULL, "String header is NULL");
//     return header->count;
// }
// s64 db_string_capacity(db_string const str)
// {
//     db_array_header *header = db_array_get_header(str);
//     ASSERT_WITH_MSG(header != NULL, "String header is NULL");
//     u64 capacity = header->total_length / header->type_size;
//     return capacity;
// }
// s64 db_string_available_space(db_string const str)
// {
//     db_array_header *header = db_array_get_header(str);
//     ASSERT_WITH_MSG(header != NULL, "String header is NULL");
//     u64 capacity        = db_string_capacity(str);
//     u64 available_space = capacity - header->count;
//     return available_space;
// }
// void db_string_clear(db_string str)
// {
//     db_array_clear(str);
// }
//
// void db_string_append(db_string str, const char *other)
// {
//     s32 len = strlen(other);
//     for (s32 i = 0; i < len; i++)
//     {
//         db_array_append(str, other[i])
//     }
//     u64 count  = db_array_length(str);
//     // hmmm it will be zero there too but lets just me more explicit
//     str[count] = '\0';
// }
//
// void db_string_append_char(db_string str, const char c)
// {
//     u64 count = db_array_length(str);
//     db_array_append(str, c);
//     // hmmm it will be zero there too but lets just me more explicit
//     str[count] = '\0';
// }
//
// // well this looks like for utf8 strings. Well Let me figure that out later
// // db_string db_string_append_rune(db_string str, Rune r);
// // db_string db_string_append_fmt(db_string str, char const *fmt, ...)
// //{
// //    // hmm this is gonna take a bit of time.  I have to make my own (va args) format parser
// //    return 0;
// //}
// void db_string_set(db_string str, char const *cstr)
// {
//     db_string_clear(str);
//     // maybe this is very very bad :)
//     char *c = (char *)cstr;
//     while (*c)
//     {
//         db_array_append(str, *c);
//         c++;
//     }
//     u64 count  = db_array_length(str);
//     // hmmm it will be zero there too but lets just me more explicit
//     str[count] = '\0';
// }
// // hmmmmm I dont think we need this because our arena will automatically scale based on appending
// // void db_string_make_space_for(db_string str, s64 add_len)
// //{
// //}
//
// // s64 db_string_allocation_size(db_string const str)
// //{
// // }
//
// b8 db_strings_are_equal(db_string const lhs, db_string const rhs)
// {
//     u64 lhs_count = db_array_length(lhs);
//     u64 rhs_count = db_array_length(rhs);
//
//     if (lhs_count != rhs_count)
//         return false;
//
//     for (u64 i = 0; i < lhs_count; i++)
//     {
//         if (lhs[i] != rhs[i])
//             return false;
//     }
//
//     return true;
// }
// db_string db_string_trim(db_string str, char const *cut_set)
// {
//     u64 length = db_array_length(str);
//
//     char *start_pos = &str[0];
//     char *end_pos   = &str[length - 1];
//
//     while (start_pos <= end_pos && db_char_first_occurence(cut_set, *start_pos))
//     {
//         start_pos++;
//     }
//
//     while (end_pos >= start_pos && db_char_first_occurence(cut_set, *end_pos))
//     {
//         end_pos--;
//     }
//     //@fix: what if the arena is a pool allocator
//     db_string        new_str    = NULL;
//     db_array_header *str_header = db_array_get_header(str);
//     db_array_init(str_header->shared_arena, new_str);
//     while (start_pos <= end_pos)
//     {
//         db_array_append(new_str, *start_pos);
//         start_pos++;
//     }
//     length          = db_array_length(new_str);
//     new_str[length] = '\0';
//     return new_str;
// }
// /**
//  * WHITESPACE REFERENCE:
//  * ' ' Space
//  * \t  Horizontal Tab
//  * \r  Carriage Return (Line start)
//  * \n  Line Feed (New line)
//  * \v  Vertical Tab
//  * \f  Form Feed (Page break) for printers
//  */
// db_string db_string_trim_space(db_string str)
// {
//     return db_string_trim(str, " \t\r\n\v\f");
// } // Whitespace ` \t\r\n\v\f`
#endif
