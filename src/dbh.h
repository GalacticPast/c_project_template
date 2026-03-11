#pragma once

#ifdef DBH_IMPLEMENTATION
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

#define DEBUG_BREAK asm("int $3")

#define ASSERT(expr)                                                                                                   \
    {                                                                                                                  \
        do                                                                                                             \
        {                                                                                                              \
            if (!(expr))                                                                                               \
            {                                                                                                          \
                printf("Assertion failure: %s:%d on %s\n", __FILE__, __LINE__, #expr);                                 \
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
                printf("Assertion failure: %s:%d on %s\n", __FILE__, __LINE__, #expr);                                 \
                DEBUG_BREAK;                                                                                           \
            }                                                                                                          \
        } while (0);                                                                                                   \
    }

/*
▗▖  ▗▖▗▖  ▗▖    ▗▄▄▄▖▗▖  ▗▖▗▄▄▖ ▗▄▄▄▖ ▗▄▄▖
▐▛▚▞▜▌ ▝▚▞▘       █   ▝▚▞▘ ▐▌ ▐▌▐▌   ▐▌
▐▌  ▐▌  ▐▌        █    ▐▌  ▐▛▀▘ ▐▛▀▀▘ ▝▀▚▖
▐▌  ▐▌  ▐▌        █    ▐▌  ▐▌   ▐▙▄▄▖▗▄▄▞▘
*/
// types Typedef
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

typedef s8 bool;

/*
▗▖ ▗▖ ▗▄▄▖▗▄▄▄▖▗▄▄▄▖▗▖ ▗▖▗▖       ▗▖  ▗▖ ▗▄▖  ▗▄▄▖▗▄▄▖  ▗▄▖  ▗▄▄▖
▐▌ ▐▌▐▌   ▐▌   ▐▌   ▐▌ ▐▌▐▌       ▐▛▚▞▜▌▐▌ ▐▌▐▌   ▐▌ ▐▌▐▌ ▐▌▐▌
▐▌ ▐▌ ▝▀▚▖▐▛▀▀▘▐▛▀▀▘▐▌ ▐▌▐▌       ▐▌  ▐▌▐▛▀▜▌▐▌   ▐▛▀▚▖▐▌ ▐▌ ▝▀▚▖
▝▚▄▞▘▗▄▄▞▘▐▙▄▄▖▐▌   ▝▚▄▞▘▐▙▄▄▖    ▐▌  ▐▌▐▌ ▐▌▝▚▄▄▖▐▌ ▐▌▝▚▄▞▘▗▄▄▞▘
*/
#define false 0
#define true 1

#define S32_MIN -2147483648
#define S32_MAX 2147483647
#define MAX(n, m) (s64) n >= (s64)m ? (s64)n : (s64)m

#define KB(n) ((s32)n * 1024)
#define MB(n) ((s32)n * 1024 * 1024)
#define GB(n) ((s32)n * 1024 * 1024 * 1024)

// thanks google https://github.com/google/sanitizers/wiki/AddressSanitizerManualPoisoning
// User code should use macros instead of functions.
#if __has_feature(address_sanitizer) || defined(__SANITIZE_ADDRESS__)
#define ASAN_POISON_MEMORY_REGION(addr, size) __asan_poison_memory_region((addr), (size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) __asan_unpoison_memory_region((addr), (size))
#else
#define ASAN_POISON_MEMORY_REGION(addr, size) ((void)(addr), (void)(size))
#define ASAN_UNPOISON_MEMORY_REGION(addr, size) ((void)(addr), (void)(size))
#endif

typedef enum dbh_return_code
{
    DBH_ERROR   = 0,
    DBH_SUCCESS = 1,
} dbh_return_code;

/*
▗▖  ▗▖▗▄▄▄▖▗▖  ▗▖ ▗▄▖ ▗▄▄▖▗▖  ▗▖
▐▛▚▞▜▌▐▌   ▐▛▚▞▜▌▐▌ ▐▌▐▌ ▐▌▝▚▞▘
▐▌  ▐▌▐▛▀▀▘▐▌  ▐▌▐▌ ▐▌▐▛▀▚▖ ▐▌
▐▌  ▐▌▐▙▄▄▖▐▌  ▐▌▝▚▄▞▘▐▌ ▐▌ ▐▌
*/

// verify later on though if I could have huge pages or not
#define DBH_PAGE_SIZE KB(4)

void *__dbh_reserve_virtual_memory(size_t reserve_memory_size)
{
    void *ptr = NULL;
#ifdef DBH_PLATFORM_LINUX
    // thanks @tsoding (Mista Zozin) for the mmap explanation https://youtu.be/sFYFuBzu9Ow
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
        printf("Cannot commit: %d pages, arleady commited %d pages. Increase the reserved virtual alloc size.\n",
               num_pages, page_offset);
        ASSERT(ret_code != -1);
    }

    // poison the memory
    ASAN_POISON_MEMORY_REGION((void *)next_page_base_ptr, new_allocated_size);

    return DBH_SUCCESS;
#elif DBH_PLATFORM_WINDOWS

#endif
    ASSERT(false);
    return DBH_ERROR;
}
// i dont think I will decomit individual pages, for example for an dynamic array I am pretty sure I will not decommit
// the last page or last 2 pages and so on. so decommit the whole allocated memory size of it.
// Decommiting means letting the os reclaim the pages while retaining the virtual address space.
// idk when I will call this though, I think I will just unmap it but oh well :)
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
/*
 ▗▄▖ ▗▄▄▖ ▗▄▄▄▖▗▖  ▗▖ ▗▄▖  ▗▄▄▖
▐▌ ▐▌▐▌ ▐▌▐▌   ▐▛▚▖▐▌▐▌ ▐▌▐▌
▐▛▀▜▌▐▛▀▚▖▐▛▀▀▘▐▌ ▝▜▌▐▛▀▜▌ ▝▀▚▖
▐▌ ▐▌▐▌ ▐▌▐▙▄▄▖▐▌  ▐▌▐▌ ▐▌▗▄▄▞▘
*/
#define DBH_ARENA_DEFAULT_RESERVED_MEMORY MB(64)
#define DBH_ARENA_DEFAULT_COMMITED_MEMORY KB(64)

// the easy and the understandable way of doing this is to take an example:
// m = 13 and n = 8, the problem is that we need to align 13 to an multiple of 8.
// or in other words how much do I have to add to 13 in order to make it a multiple of 8.
// REALLY NAIVE SOLUTION:
// 1st) find out the interval in which m exists. (k - 1)n <= m <= kn, in our case 8 < 13 < 16
// 2nd) find out how much do we have to add. kn - m. 16 - 13 = 3
// 3rd) add it and then you have the next multiple of n from m.
// There is a problem with this solution. Its really inefficeint because first we have to find the largest multiple of n
// which is bigger than m. And for large values we might have to do multiple multiplication and then check if that
// number is greater than n. psudo code
//             k = 1
//             while(n * k < m)k++;
//             how_much_to_add = n * k - m
//             m + how_much_to_add == n * k
// So to simplyfy it we do a neat math trick
// we take the mod of the divisor and the quotient for example: m (mod) n
// when we do the mod we get the remainder. The remainder will help us find how much do we have to add to make it an
// multiple of n. for example: 13 mod 8
//       8|13|1
//        - 8      the remainder is the remaning part when an integer cannot divide another interger.
//          5      we can use this fact to find out which integer will divide it.
//    lets visualize this
//       if we wanted to find out the lowest multiple we cound just minus the remainder and be done with it.
//       to find out the next largest integer which can be divided we can do (8 - remainder) + 13
//                          8____13__16
// So this simplifies our solution
//  pseudo code:
//      remainder = m % n
//      padding   = (n - remainder)
//      next_multiple = m + padding
// There is a one small caviat with this solution. Lets say m = 8
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
// Another faster way is to do a bitwise operation if and only if n is a multiple of 2
// this one is a little confusing. I sill dont understand it compeletly
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
// -8: 1111111 11111111 11111111 11111000 .This is the 2's complemenent representation
// which I didnt know even though I have been programming for about 4 years with c :(. Damn wtf.....
//
// so how does the following work?
// For example mem = 13 and align to = 8
// 13 in binary      : 00000000 00000000 00000000 00001101
//  8 in binary      : 00000000 00000000 00000000 00001000
// (8 - 1) in binary : 00000000 00000000 00000000 00000111
// 13 + (8 - 1)      : 00000000 00000000 00000000 00010100
// (13 + (8 - 1)) & (-8)
//
// 13 + (8 - 1)      : 00000000 00000000 00000000 00010100
// -8                : 11111111 11111111 11111111 11111000 -> which we derived from the above example
//(13 +(8 - 1)) & -8 : 00000000 00000000 00000000 00010000 -> which would be 16
#define DBH_ALIGN_TO_MULTIPLE(mem, align_to) (((uintptr_t)mem + (align_to - 1)) & (-align_to))
#define DBH_DEFAULT_MEMORY_ALIGNEMENT 8

typedef struct dbh_arena
{
    // how many pages has the arena commited till now.
    // We need this because if we need the arena to grow it will use the page offset to find out how many pages to
    // commit.
    s64    curr_page_offset;
    size_t allocated_till_now;
    size_t total_size;
    //  @ = memory in use/ already allocated
    //  @@@@@@@@@@@@--------------------
    //              ^-- starting ptr for the next allocation
    uintptr_t curr_mem_pos;
    // original or the first ptr, this is also the starting page's memory ptr. We will need to pass this ptr if we want
    // to unmap the memory.
    void *memory;
} dbh_arena;

// use the macro if its a align_to is the power of 2
uintptr_t __dbh_align_to_multiple(uintptr_t mem, s32 align_to)
{
    /*
       https://en.wikipedia.org/wiki/Data_structure_alignment
      padding = (align - (offset mod align)) mod align
     aligned = offset + padding
     = offset + ((align - (offset mod align)) mod align)
    */
    size_t    padding     = (align_to - (mem % align_to)) % align_to;
    uintptr_t aligned_mem = mem + padding;
    return aligned_mem;
}

//
// Args:
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
        mem_size = DBH_ALIGN_TO_MULTIPLE(mem_size, DBH_ARENA_DEFAULT_COMMITED_MEMORY);
    }
    // well if you are allocating an arena which has a size greater than DBH_ARENA_DEFAULT_RESERVED_MEMORY usally 64mb.
    // Then why are you allocating it? I cant think of a reason for that :).
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
#define DBH_ARENA_INIT() dbh_arena_init_with_size(DBH_ARENA_DEFAULT_COMMITED_MEMORY)

// Args:
//  arena -> ptr to the dbh_arena form which you would like to allocate.
//  size ->  memory block size to allocate from the arena.
void *dbh_arena_alloc(dbh_arena *arena, size_t size)
{
    ASSERT(arena != NULL);
    ASSERT(size != 0);
    // if the size passed on is bigger than the toal size of the arena then increase the size of the arena to accodomate
    // the allocation.
    size_t aligned_size = DBH_ALIGN_TO_MULTIPLE(size, DBH_DEFAULT_MEMORY_ALIGNEMENT);
    if (arena->allocated_till_now + aligned_size > (size_t)arena->total_size)
    {
        size_t new_size = 0;
        if (aligned_size < DBH_PAGE_SIZE)
        {
            new_size = DBH_PAGE_SIZE;
        }
        else
        {
            new_size = DBH_ALIGN_TO_MULTIPLE(aligned_size, DBH_PAGE_SIZE);
        }

        s32 num_pages = new_size / DBH_PAGE_SIZE;

        // Lets say we have commited n - 1 pages of total reserved memory and now we want to allocate n + k number of
        // pages. I am pretty sure that the os will not let us and its going to crash the application.
        dbh_return_code code = __dbh_commit_virtual_memory(arena->memory, arena->curr_page_offset, num_pages);

        arena->total_size       += num_pages * DBH_PAGE_SIZE;
        arena->curr_page_offset += num_pages;
        ASSERT(code != DBH_ERROR);
    }

    void *ret_mem = (void *)arena->curr_mem_pos;
    // unpoison the memory;
    ASAN_UNPOISON_MEMORY_REGION(ret_mem, aligned_size);

    // align the mem ptr to a multiple of 8 for better cpu/read writes
    uintptr_t temp = arena->curr_mem_pos;

    arena->curr_mem_pos += aligned_size;
    arena->curr_mem_pos  = DBH_ALIGN_TO_MULTIPLE(arena->curr_mem_pos, DBH_DEFAULT_MEMORY_ALIGNEMENT);

    // sanity check
    // if this triggers then I need to fix the aligned_size logic.
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
    size_t total_reserved_size = MAX(arena->total_size, DBH_ARENA_DEFAULT_RESERVED_MEMORY);

    dbh_return_code res = __dbh_release_virtual_memory(arena->memory, total_reserved_size);
    ASSERT(res != DBH_ERROR);

    arena->allocated_till_now = 0;
    arena->curr_page_offset   = 0;
    arena->total_size         = 0;
    arena->memory             = NULL;
    arena->curr_mem_pos       = 0;
    return DBH_SUCCESS;
}

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

#define dbh_array(Type) Type *
#define dbh_array_init(Array) __dbh_array_init((void **)&Array, sizeof(*Array))
#define dbh_array_free(Array) __dbh_array_free((void **)&Array)
#define dbh_array_get_header(Array) (dbh_array_header *)((char *)Array - (sizeof(dbh_array_header)))

#define dbh_array_get_count(Array) (dbh_array_get_header(Array))->count

#define dbh_array_append(Array, Element)                                                                               \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(Array != NULL, "Array is Null");                                                               \
        dbh_array_header *header = dbh_array_get_header(Array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "Array Header is Null. This is a serius bug :(.");                             \
        if (header->count + 1 >= header->total_length)                                                                 \
        {                                                                                                              \
            __dbh_array_resize((void **)&Array);                                                                       \
        }                                                                                                              \
        Array[header->count++] = Element;                                                                              \
    } while (0);

#define dbh_array_pop(Array)                                                                                           \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(Array != NULL, "Array is Null");                                                               \
        dbh_array_header *header = dbh_array_get_header(Array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "Array Header is Null. ");                                                     \
        ASSERT_WITH_MSG(header->count != 0, "Array has no elements yet.");                                             \
        header->count--;                                                                                               \
    } while (0);

// 0 1 2 3 4 5 6
// dbh_array_splice(V, 2, 4)
// removes 2 3 4 5

// removes from the starting index + num_elems elements
#define dbh_array_remove_range(Array, start, num_elems)                                                                \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(Array != NULL, "Array is Null");                                                               \
        dbh_array_header *header = dbh_array_get_header(Array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "Array Header is Null. This is a serius bug :(.");                             \
        ASSERT_WITH_MSG((start) < header->count, "Starting index is greater than array length");                       \
        /*get the remaining length of the array after start + num_elems                                                \
         *  For example: start = 2, num_elems = 3, V = n0 n1 n2 n3 n4 n5 n6 ... n                                      \
         *     V = n0 n1 n2 n3 n4 n5 n6 ...    we want to remove elmems n2, n3, n4                                     \
         * to get the length of the n5+ array. we have to do V.count -   Len(n0,n1,...n4)                              \
         * Length of the whole array - the length from the starting of array up to the last element we want to remove  \
         * */                                                                                                          \
        s64 rem_length = header->count - ((start) + (num_elems));                                                      \
        ASSERT(rem_length >= 0);                                                                                       \
        memmove(&Array[(start)], &Array[(start) + (num_elems)], rem_length * header->type_size);                       \
        header->count -= num_elems;                                                                                    \
        memset(&Array[header->count], 0, num_elems * header->type_size);                                               \
    } while (0);

#define dbh_array_insert(Array, Index, Element)                                                                        \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(Array != NULL, "Array is Null");                                                               \
        dbh_array_header *header = dbh_array_get_header(Array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "Array Header is Null. This is a serius bug :(.");                             \
        ASSERT_WITH_MSG((Index < header->count), "Index out of bounds");                                               \
        if (header->count + 1 >= header->total_length)                                                                 \
        {                                                                                                              \
            __dbh_array_resize((void **)&Array);                                                                       \
        }                                                                                                              \
        s64 move_length = header->count - Index;                                                                       \
        memmove(&Array[Index + 1], &Array[Index], move_length * header->type_size);                                    \
        Array[Index] = Element;                                                                                        \
        header->count++;                                                                                               \
    } while (0);

// I dont reset the array's length so it might be wasteful.
// for example in the first instance we used 1gb data for the array.
// then we cleared it.  and then we didnt exceed more than a kb of usage for the array.
// well because we had allocated a gb beforehand the array's total length would be a gb. I dont reset that even if you
// call dbh_array_clear()
// WARNING: if possible
#define dbh_array_clear(Array)                                                                                         \
    do                                                                                                                 \
    {                                                                                                                  \
        ASSERT_WITH_MSG(Array != NULL, "Array is Null");                                                               \
        dbh_array_header *header = dbh_array_get_header(Array);                                                        \
        ASSERT_WITH_MSG(header != NULL, "Array Header is Null. This is a serius bug :(.");                             \
        if (header->count > 0)                                                                                         \
        {                                                                                                              \
            memset((void *)Array, 0, header->count * header->type_size);                                               \
        }                                                                                                              \
        header->count = 0;                                                                                             \
    } while (0);

/*
[x] vec_init(v)
[x] Initialises the vector, this must be called before the vector can be used.
[X] vec_deinit(v)
[x] vec_push(v, val)
[x] vec_pop(v)
[x] vec_splice(v, start, count)
[x] vec_insert(v, idx, val)
[ ] vec_sort(v, fn)
[X] vec_clear(v)
[ ] vec_compact(v)
*/

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
    dbh_arena arena = DBH_ARENA_INIT();

    // maybe a bit wasteful but we've already commited this much isnt it?
    size_t header_plus_array_size = arena.total_size;
    header_plus_array_size        = DBH_ALIGN_TO_MULTIPLE(header_plus_array_size, DBH_DEFAULT_MEMORY_ALIGNEMENT);

    void *memory = dbh_arena_alloc(&arena, header_plus_array_size);

    dbh_array_header *header = memory;

    uintptr_t array_mem =
        DBH_ALIGN_TO_MULTIPLE((uintptr_t)memory + sizeof(dbh_array_header), DBH_DEFAULT_MEMORY_ALIGNEMENT);

    ASSERT((array_mem - sizeof(dbh_array_header)) == (uintptr_t)memory);

    *array = (void *)array_mem;

    size_t array_size =
        DBH_ALIGN_TO_MULTIPLE(header_plus_array_size - sizeof(dbh_array_header), DBH_DEFAULT_MEMORY_ALIGNEMENT);

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

#define DeferLoop(begin, end) for (int _i_ = ((begin), 0); !_i_; _i_ += 1, (end))


#endif
