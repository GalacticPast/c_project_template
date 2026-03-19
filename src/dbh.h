#pragma once

// asci art font : rubi_font https://patorjk.com/software/taag

#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>

#ifdef __win32__
#define DBH_PLATFORM_WINDOWS
#elif __linux__
#define DBH_PLATFORM_LINUX
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

#define DEBUG_BREAK asm("int $3")

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
                printf("ASSERTion failure: %s:%d on %s\n", __FILE__, __LINE__, #expr);                                 \
                DEBUG_BREAK;                                                                                           \
            }                                                                                                          \
        } while (0);                                                                                                   \
    }

#define false 0
#define true 1

#define s32_min -2147483648
#define s32_max 2147483647
#define max(n, m) (s64) n >= (s64)m ? (s64)n : (s64)m

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

typedef enum dbh_return_code
{
    DBH_ERROR   = 0,
    DBH_SUCCESS = 1,
} dbh_return_code;

/*
 ▗▄▖ ▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▖  ▗▄▄▖
▐▌ ▐▌▐▌ ▐▌▐▌   ▐▛▚▖▐▌▐▌ ▐▌▐▌
▐▛▀▜▌▐▛▀▚▖▐▛▀▀▘▐▌ ▝▜▌▐▛▀▜▌ ▝▀▚▖
▐▌ ▐▌▐▌ ▐▌▐▙▄▄▖▐▌  ▐▌▐▌ ▐▌▗▄▄▞▘
*/

typedef struct dbh_arena
{
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
    // original or the first ptr, this is also the starting page's memory ptr. we will need to pass this ptr if we want
    // to unmap the memory.
    void *memory;
} dbh_arena;

#define DBH_ARENA_DEFAULT_RESERVED_MEMORY MB(64)
#define DBH_ARENA_DEFAULT_COMMITED_MEMORY KB(4)
#define dbh_arena_init() dbh_arena_init_with_size(DBH_ARENA_DEFAULT_COMMITED_MEMORY)
dbh_arena       dbh_arena_init_with_size(size_t memory_size);
void           *dbh_arena_alloc(dbh_arena *arena, size_t size);
dbh_return_code dbh_arena_clear(dbh_arena *arena);

/*

▗▄▄▄▗▖  ▗▖▗▖  ▗▖ ▗▄▖ ▗▖  ▗▖▗▄▄▄▖ ▗▄▄▖     ▗▄▖ ▗▄▄▖ ▗▄▄▖  ▗▄▖▗▖  ▗▖▗▄▄▖
▐▌  █▝▚▞▘ ▐▛▚▖▐▌▐▌ ▐▌▐▛▚▞▜▌  █  ▐▌       ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘▐▌
▐▌  █ ▐▌  ▐▌ ▝▜▌▐▛▀▜▌▐▌  ▐▌  █  ▐▌       ▐▛▀▜▌▐▛▀▚▖▐▛▀▚▖▐▛▀▜▌ ▐▌  ▝▀▚▖
▐▙▄▄▀ ▐▌  ▐▌  ▐▌▐▌ ▐▌▐▌  ▐▌▗▄█▄▖▝▚▄▄▖    ▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌▐▌ ▐▌ ▐▌ ▗▄▄▞▘

*/

typedef struct dbh_array_header
{
    s64       total_length;
    s64       count;
    s64       type_size;
    dbh_arena arena;
} dbh_array_header;

#define DBH_ARRAY_DEFAULT_RESIZE_FACTOR 2

#define dbh_array(type) type *
#define dbh_array_init(array) __dbh_array_init((void **)&array, sizeof(*array))
#define dbh_array_free(array) __dbh_array_free((void **)&array)
#define dbh_array_get_header(array) (dbh_array_header *)((char *)array - (sizeof(dbh_array_header)))
#define dbh_array_get_count(array) (dbh_array_get_header(array))->count
dbh_return_code __dbh_array_resize(void **array);
dbh_return_code __dbh_array_init(void **array, size_t type_size);
void            __dbh_array_free(void **array);

#define dbh_array_append(array, element)                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        if (header->count + 1 >= header->total_length)                                                                 \
        {                                                                                                              \
            __dbh_array_resize((void **)&array);                                                                       \
        }                                                                                                              \
        array[header->count++] = element;                                                                              \
    } while (0);

#define dbh_array_pop(array)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. ");                                                     \
        ASSERT_WITH_MSG(header->count != 0, "array has no elements yet.");                                             \
        header->count--;                                                                                               \
    } while (0);

// 0 1 2 3 4 5 6
// dbh_array_splice(v, 2, 4)
// removes 2 3 4 5

// removes from the starting index + num_elems elements
#define dbh_array_remove_range(array, start, num_elems)                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        ASSERT_WITH_MSG((start) < header->count, "starting index is greater than array length");                       \
        /*get the remaining length of the array after start + num_elems                                                \
         *  for example: start = 2, num_elems = 3, v = n0 n1 n2 n3 n4 n5 n6 ... n                                      \
         *     v = n0 n1 n2 n3 n4 n5 n6 ...    we want to remove elmems n2, n3, n4                                     \
         * to get the length of the n5+ array. we have to do v.count -   len(n0,n1,...n4)                              \
         * length of the whole array - the length from the starting of array up to the last element we want to remove  \
         * */                                                                                                          \
        s64 rem_length = header->count - ((start) + (num_elems));                                                      \
        ASSERT(rem_length >= 0);                                                                                       \
        memmove(&array[(start)], &array[(start) + (num_elems)], rem_length * header->type_size);                       \
        header->count -= num_elems;                                                                                    \
        memset(&array[header->count], 0, num_elems * header->type_size);                                               \
    } while (0);

#define dbh_array_insert(array, index, element)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        ASSERT_WITH_MSG((index < header->count), "index out of bounds");                                               \
        if (header->count + 1 >= header->total_length)                                                                 \
        {                                                                                                              \
            __dbh_array_resize((void **)&array);                                                                       \
        }                                                                                                              \
        s64 move_length = header->count - index;                                                                       \
        memmove(&array[index + 1], &array[index], move_length * header->type_size);                                    \
        array[index] = element;                                                                                        \
        header->count++;                                                                                               \
    } while (0);

#define dbh_array_get_last(array)                                                                                      \
    ({                                                                                                                 \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        __typeof__(*array) _res;                                                                                       \
        dbh_array_header  *header = dbh_array_get_header(array);                                                       \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        ASSERT_WITH_MSG((header->count > 0), "array has no elements");                                                 \
        _res = array[header->count - 1];                                                                               \
    })

// the function should have a signatrue like this :
//          bool func(type* elem_to_find, type *elem_that_the_array_wants_to_check_with);

#define dbh_array_find(array, elem, func_ptr)                                                                          \
    ({                                                                                                                 \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        __typeof__(array) _res   = NULL;                                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        s64 count = header->count;                                                                                     \
        for (s64 i = 0; i < count; i++)                                                                                \
        {                                                                                                              \
            if (func_ptr(&elem, &array[i]))                                                                            \
            {                                                                                                          \
                _res = &array[i];                                                                                      \
            }                                                                                                          \
        }                                                                                                              \
        _res;                                                                                                          \
    })

// i dont reset the array's length so it might be wasteful.
// for example in the first instance we used 1gb data for the array.
// then we cleared it.  and then we didnt exceed more than a KB of usage for the array.
// well because we had allocated a gb beforehand the array's total length would be a gb. i dont reset that even
// if you call dbh_array_clear() warning: if possible
#define dbh_array_clear(array)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(array != NULL, "array is NULL");                                                               \
        dbh_array_header *header = dbh_array_get_header(array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "array header is NULL. this is a serius bug :(.");                             \
        if (header->count > 0)                                                                                         \
        {                                                                                                              \
            memset((void *)array, 0, header->count * header->type_size);                                               \
        }                                                                                                              \
        header->count = 0;                                                                                             \
    } while (0);

/*
  ▗▄▄▖▗▄▄▄▖▗▄▖  ▗▄▄▖▗▖ ▗▖
 ▐▌     █ ▐▌ ▐▌▐▌   ▐▌▗▞▘
  ▝▀▚▖  █ ▐▛▀▜▌▐▌   ▐▛▚▖
 ▗▄▄▞▘  █ ▐▌ ▐▌▝▚▄▄▖▐▌ ▐▌

*/

#define dbh_stack(type) dbh_array(type)
#define dbh_stack_init(stack) dbh_array_init(stack)
#define dbh_stack_push(stack, elem) dbh_array_append(stack, elem)
#define dbh_stack_pop(stack) dbh_array_pop(stack)
#define dbh_stack_peek(stack) dbh_array_get_last(stack)
#define dbh_stack_free(stack) dbh_array_free(stack)

/*
     ▗▄▄▖▗▄▄▄▖▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▄▖ ▗▄▄▖
    ▐▌     █  ▐▌ ▐▌  █  ▐▛▚▖▐▌▐▌   ▐▌
     ▝▀▚▖  █  ▐▛▀▚▖  █  ▐▌ ▝▜▌▐▌▝▜▌ ▝▀▚▖
    ▗▄▄▞▘  █  ▐▌ ▐▌▗▄█▄▖▐▌  ▐▌▝▚▄▞▘▗▄▄▞▘

*/

typedef dbh_array(char) dbh_string;

dbh_string dbh_string_make_reserve(dbh_string str, s64 capacity);
dbh_string dbh_string_make(dbh_string str, char const *a);
dbh_string dbh_string_make_length(dbh_string str, void const *a, s64 num_bytes);
void       dbh_string_free(dbh_string str);
dbh_string dbh_string_duplicate(dbh_string str, dbh_string const a);
s64        dbh_string_length(dbh_string const str);
s64        dbh_string_capacity(dbh_string const str);
s64        dbh_string_available_space(dbh_string const str);
void       dbh_string_clear(dbh_string str);
dbh_string dbh_string_append(dbh_string str, dbh_string const other);
dbh_string dbh_string_append_length(dbh_string str, void const *other, s64 num_bytes);
dbh_string dbh_string_appendc(dbh_string str, char const *other);
// well this looks like for utf8 strings. Well Let me figure that out later
// dbh_string dbh_string_append_rune(dbh_string str, Rune r);
dbh_string dbh_string_append_fmt(dbh_string str, char const *fmt, ...);
dbh_string dbh_string_set(dbh_string str, char const *cstr);
dbh_string dbh_string_make_space_for(dbh_string str, s64 add_len);
s64        dbh_string_allocation_size(dbh_string const str);
b8         dbh_string_are_equal(dbh_string const lhs, dbh_string const rhs);
dbh_string dbh_string_trim(dbh_string str, char const *cut_set);
dbh_string dbh_string_trim_space(dbh_string str); // Whitespace ` \t\r\n\v\f`

/*
▗▖ ▗▖ ▗▄▖  ▗▄▄▖▗▖ ▗▖▗▖  ▗▖ ▗▄▖ ▗▄▄▖
▐▌ ▐▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▛▚▞▜▌▐▌ ▐▌▐▌ ▐▌
▐▛▀▜▌▐▛▀▜▌ ▝▀▚▖▐▛▀▜▌▐▌  ▐▌▐▛▀▜▌▐▛▀▘
▐▌ ▐▌▐▌ ▐▌▗▄▄▞▘▐▌ ▐▌▐▌  ▐▌▐▌ ▐▌▐▌
*/

#define dbh_hash_seed 0x31415926
#define dbh_hash_string(data) dbh_murmur64A_seed(data, strlen(data), dbh_hash_seed)

/*
▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖ ▗▄▖ ▗▄▄▖▗▖  ▗▖
▐▛▚▞▜▌▐▌   ▐▛▚▞▜▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘
▐▌  ▐▌▐▛▀▀▘▐▌  ▐▌▐▌ ▐▌▐▛▀▚▖ ▐▌
▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌▝▚▄▞▘▐▌ ▐▌ ▐▌
*/

void           *__dbh_reserve_virtual_memory(size_t reserve_memory_size);
dbh_return_code __dbh_commit_virtual_memory(void *memory, s32 page_offset, s32 num_pages);
dbh_return_code __dbh_decommit_virtual_memory(void *memory, size_t size);
dbh_return_code __dbh_release_virtual_memory(void *memory, size_t size);

u64 dbh_murmur64_seed(void const *data_, size_t len, u64 seed);

// private implementation
#ifdef DBH_IMPLEMENTATION
// verify later on though if i could have huge pages or not
#define DBH_PAGE_SIZE KB(4)

void *__dbh_reserve_virtual_memory(size_t reserve_memory_size)
{
    void *ptr = NULL;
#ifdef DBH_PLATFORM_LINUX
    // thanks @tsoding (mista zozin) for the mmap explanation https://youtu.be/sfyfubzu9ow
    ptr = mmap(NULL, reserve_memory_size, PROT_NONE, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
    ASSERT(ptr != MAP_FAILED);

    return ptr;
#elif DBH_PLATFORM_WINDOWS

#endif
    ASSERT(ptr != NULL);
    return (void *)ptr;
}

dbh_return_code __dbh_commit_virtual_memory(void *memory, s32 page_offset, s32 num_pages)
{
#ifdef DBH_PLATFORM_LINUX
    uintptr_t next_page_base_ptr = (uintptr_t)memory + (page_offset * DBH_PAGE_SIZE);
    s64       new_allocated_size = num_pages * DBH_PAGE_SIZE;
    s32       ret_code           = mprotect((void *)next_page_base_ptr, new_allocated_size, PROT_READ | PROT_WRITE);
    if (ret_code == -1)
    {
        printf("cannot commit: %d pages, arleady commited %d pages. increase the reserved virtual alloc size.\n",
               num_pages, page_offset);
        ASSERT(ret_code != -1);
    }

    // poison the memory
    asan_poison_memory_region((void *)next_page_base_ptr, new_allocated_size);

    return DBH_SUCCESS;
#elif DBH_PLATFORM_WINDOWS

#endif
    ASSERT(false);
    return DBH_ERROR;
}
// i dont think i will decomit individual pages, for example for an dynamic array i am pretty sure i will not decommit
// the last page or last 2 pages and so on. so decommit the whole allocated memory size of it.
// decommiting means letting the os reclaim the pages while retaining the virtual address space.
// idk when i will call this though, i think i will just unmap it but oh well :)
dbh_return_code __dbh_decommit_virtual_memory(void *memory, size_t size)
{
#ifdef DBH_PLATFORM_LINUX
    madvise(memory, size, MADV_DONTNEED);
    s32 ret_code = mprotect(memory, size, PROT_NONE);
    ASSERT(ret_code != -1);
    return DBH_SUCCESS;
#elif DBH_PLATFORM_WINDOWS
#endif
}
// unmaping the memory
dbh_return_code __dbh_release_virtual_memory(void *memory, size_t size)
{
#ifdef DBH_PLATFORM_LINUX
    s32 ret_code = munmap(memory, size);
    ASSERT(ret_code != -1);
    return DBH_SUCCESS;
#elif DBH_PLATFORM_WINDOWS
#endif
}

// the easy and the understandable way of doing this is to take an example:
// m = 13 and n = 8, the problem is that we need to align 13 to an multiple of 8.
// or in other words how much do i have to add to 13 in order to make it a multiple of 8.
// really naive solution:
// 1st) find out the interval in which m exists. (k - 1)n <= m <= kn, in our case 8 < 13 < 16
// 2nd) find out how much do we have to add. kn - m. 16 - 13 = 3
// 3rd) add it and then you have the next multiple of n from m.
// there is a problem with this solution. its really inefficeint because first we have to find the largest multiple of n
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
// this works because of the 2's complement so for example :
//  8: 0000000 00000000 00000000 00001000
//  to get -8 from 8 we do  the following
//  first we have 8's binary 0000000 00000000 00000000 00001000
//  then we inverse all the bits 0's map to 1 and 1 maps to 0
//  1111111 11111111 11111111 11110111 then we add  1 to it.
//
//   1111111 11111111 11111111 11110111
// + 0000000 00000000 00000000 00000001
//   1111111 11111111 11111111 11111000  which is -8
//
// -8: 1111111 11111111 11111111 11111000 .this is the 2's complemenent representation
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
#define dbh_align_to_multiple(mem, align_to) (((uintptr_t)mem + (align_to - 1)) & (-align_to))
#define DBH_DEFAULT_MEMORY_ALIGNEMENT 8

// use the macro if its a align_to is the power of 2
uintptr_t __dbh_align_to_multiple(uintptr_t mem, s32 align_to)
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
dbh_arena dbh_arena_init_with_size(size_t memory_size)
{
    size_t mem_size = memory_size;
    if (mem_size < DBH_ARENA_DEFAULT_COMMITED_MEMORY)
    {
        mem_size = DBH_ARENA_DEFAULT_COMMITED_MEMORY;
    }
    else if (mem_size > DBH_ARENA_DEFAULT_COMMITED_MEMORY)
    {
        mem_size = dbh_align_to_multiple(mem_size, DBH_ARENA_DEFAULT_COMMITED_MEMORY);
    }
    // well if you are allocating an arena which has a size greater than DBH_ARENA_DEFAULT_RESERVED_MEMORY usally 64mb.
    // then why are you allocating it? i cant think of a reason for that :).
    ASSERT(mem_size < DBH_ARENA_DEFAULT_RESERVED_MEMORY);

    s32   num_pages_to_commit = mem_size / DBH_PAGE_SIZE;
    void *memory              = __dbh_reserve_virtual_memory(DBH_ARENA_DEFAULT_RESERVED_MEMORY);
    ASSERT(memory != NULL);

    dbh_return_code code = __dbh_commit_virtual_memory(memory, 0, num_pages_to_commit);
    ASSERT(code != DBH_ERROR);

    dbh_arena arena          = {};
    arena.curr_page_offset   = num_pages_to_commit;
    arena.allocated_till_now = 0;
    arena.total_size         = mem_size;
    arena.memory             = memory;
    arena.curr_mem_pos       = (uintptr_t)arena.memory;

    return arena;
}

// args:
//  arena -> ptr to the dbh_arena form which you would like to allocate.
//  size ->  memory block size to allocate from the arena.
void *dbh_arena_alloc(dbh_arena *arena, size_t size)
{
    ASSERT(arena != NULL);
    ASSERT(size != 0);
    // if the size passed on is bigger than the toal size of the arena then increase the size of the arena to accodomate
    // the allocation.
    size_t aligned_size = dbh_align_to_multiple(size, DBH_DEFAULT_MEMORY_ALIGNEMENT);
    if (arena->allocated_till_now + aligned_size > (size_t)arena->total_size)
    {
        size_t new_size = 0;
        if (aligned_size < DBH_PAGE_SIZE)
        {
            new_size = DBH_PAGE_SIZE;
        }
        else
        {
            new_size = dbh_align_to_multiple(aligned_size, DBH_PAGE_SIZE);
        }

        s32 num_pages = new_size / DBH_PAGE_SIZE;

        // lets say we have commited n - 1 pages of total reserved memory and now we want to allocate n + k number of
        // pages. i am pretty sure that the os will not let us and its going to crash the application.
        dbh_return_code code = __dbh_commit_virtual_memory(arena->memory, arena->curr_page_offset, num_pages);

        arena->total_size       += num_pages * DBH_PAGE_SIZE;
        arena->curr_page_offset += num_pages;
        ASSERT(code != DBH_ERROR);
    }

    void *ret_mem = (void *)arena->curr_mem_pos;
    // unpoison the memory;
    asan_unpoison_memory_region(ret_mem, aligned_size);

    // align the mem ptr to a multiple of 8 for better cpu/read writes
    uintptr_t temp = arena->curr_mem_pos;

    arena->curr_mem_pos += aligned_size;
    arena->curr_mem_pos  = dbh_align_to_multiple(arena->curr_mem_pos, DBH_DEFAULT_MEMORY_ALIGNEMENT);

    // sanity check
    // if this triggers then i need to fix the aligned_size logic.
    ASSERT((temp + aligned_size) == arena->curr_mem_pos);

    arena->allocated_till_now += aligned_size;

    return ret_mem;
}

dbh_return_code dbh_arena_clear(dbh_arena *arena)
{
    ASSERT(arena != NULL);

    memset(arena->memory, 0, arena->allocated_till_now);
    arena->allocated_till_now = 0;
    arena->curr_mem_pos       = (uintptr_t)arena->memory;
    return DBH_SUCCESS;
}

dbh_return_code dbh_arena_free(dbh_arena *arena)
{
    ASSERT(arena != NULL);

    // there might be the case that we allocated/commited more than DBH_ARENA_DEFAULT_RESERVED_MEMORY.
    size_t total_reserved_size = max(arena->total_size, DBH_ARENA_DEFAULT_RESERVED_MEMORY);

    dbh_return_code res = __dbh_release_virtual_memory(arena->memory, total_reserved_size);
    ASSERT(res != DBH_ERROR);

    arena->allocated_till_now = 0;
    arena->curr_page_offset   = 0;
    arena->total_size         = 0;
    arena->memory             = NULL;
    arena->curr_mem_pos       = 0;
    return DBH_SUCCESS;
}

dbh_return_code __dbh_array_resize(void **array)
{
    ASSERT(array != NULL);

    dbh_array_header *header = dbh_array_get_header(*array);
    ASSERT(header != NULL);

    size_t new_size = header->total_length * DBH_ARRAY_DEFAULT_RESIZE_FACTOR;
    dbh_arena_alloc(&header->arena, new_size * header->type_size);
    header->total_length += new_size;
    return DBH_SUCCESS;
}

dbh_return_code __dbh_array_init(void **array, size_t type_size)
{
    dbh_arena arena = dbh_arena_init();

    // maybe a bit wasteful but we've already commited this much isnt it?
    size_t header_plus_array_size = arena.total_size;
    header_plus_array_size        = dbh_align_to_multiple(header_plus_array_size, DBH_DEFAULT_MEMORY_ALIGNEMENT);

    void *memory = dbh_arena_alloc(&arena, header_plus_array_size);

    dbh_array_header *header = memory;

    uintptr_t array_mem =
        dbh_align_to_multiple((uintptr_t)memory + sizeof(dbh_array_header), DBH_DEFAULT_MEMORY_ALIGNEMENT);

    ASSERT((array_mem - sizeof(dbh_array_header)) == (uintptr_t)memory);

    *array = (void *)array_mem;

    size_t array_size =
        dbh_align_to_multiple(header_plus_array_size - sizeof(dbh_array_header), DBH_DEFAULT_MEMORY_ALIGNEMENT);

    header->total_length = array_size / type_size;
    header->count        = 0;
    header->type_size    = type_size;
    header->arena        = arena;

    return DBH_SUCCESS;
}

void __dbh_array_free(void **array)
{
    ASSERT(*array != NULL);
    dbh_array_header *header = dbh_array_get_header(*array);
    header->total_length     = 0;
    header->count            = 0;
    header->type_size        = 0;
    dbh_arena_free(&header->arena);
    *array = NULL;
}

#define DBH_SIZE_T_BITS ((sizeof(size_t)) * 8)

#define dbh_rotate_left(val, n) (((val) << (n)) | ((val) >> (DBH_SIZE_T_BITS - (n))))
#define dbh_rotate_right(val, n) (((val) >> (n)) | ((val) << (DBH_SIZE_T_BITS - (n))))

u64 dbh_murmur64A_seed(const void *key, u64 len, u64 seed)
{
    const u64 m = 0xc6a4a7935bd1e995LLU;
    const int r = 47;

    u64 h = seed ^ (len * m);

    const u64 *data = (const u64 *)key;
    const u64 *end  = (len >> 3) + data;

    while (data != end)
    {
        u64 k = 0;
        memcpy(&k, data, 8);
        data++;
        k *= m;
        k ^= k >> r;
        k *= m;

        h ^= k;
        h *= m;
    }

    const unsigned char *data2 = (const unsigned char *)data;

    switch (len & 7)
    {
        case 7:
            h ^= (u64)(data2[6]) << 48;
        case 6:
            h ^= (u64)(data2[5]) << 40;
        case 5:
            h ^= (u64)(data2[4]) << 32;
        case 4:
            h ^= (u64)(data2[3]) << 24;
        case 3:
            h ^= (u64)(data2[2]) << 16;
        case 2:
            h ^= (u64)(data2[1]) << 8;
        case 1:
            h ^= (u64)(data2[0]);
            h *= m;
    };

    h ^= h >> r;
    h *= m;
    h ^= h >> r;

    return h;
}

dbh_string dbh_string_make_reserve(dbh_string str, s64 capacity)
{
}
dbh_string dbh_string_make(dbh_string str, char const *a)
{
}
dbh_string dbh_string_make_length(dbh_string str, void const *a, s64 num_bytes)
{
}
void dbh_string_free(dbh_string str)
{
}
dbh_string dbh_string_duplicate(dbh_string str, dbh_string const a)
{
}
s64 dbh_string_length(dbh_string const str)
{
}
s64 dbh_string_capacity(dbh_string const str)
{
}
s64 dbh_string_available_space(dbh_string const str)
{
}
void dbh_string_clear(dbh_string str)
{
}
dbh_string dbh_string_append(dbh_string str, dbh_string const other)
{
}
dbh_string dbh_string_append_length(dbh_string str, void const *other, s64 num_bytes)
{
}
dbh_string dbh_string_appendc(dbh_string str, char const *other)
{
}
// well this looks like for utf8 strings. Well Let me figure that out later
// dbh_string dbh_string_append_rune(dbh_string str, Rune r);
dbh_string dbh_string_append_fmt(dbh_string str, char const *fmt, ...)
{
}
dbh_string dbh_string_set(dbh_string str, char const *cstr)
{
}
dbh_string dbh_string_make_space_for(dbh_string str, s64 add_len)
{
}
s64 dbh_string_allocation_size(dbh_string const str)
{
}
b8 dbh_string_are_equal(dbh_string const lhs, dbh_string const rhs)
{
}
dbh_string dbh_string_trim(dbh_string str, char const *cut_set)
{
}
dbh_string dbh_string_trim_space(dbh_string str)
{
} // Whitespace ` \t\r\n\v\f`
#endif
