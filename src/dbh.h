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
                printf("Assertion failure: %s:%d on %s", __FILE__, __LINE__, #expr);                                   \
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

// verify later on though if I could have huge pages or not
#define DBH_PAGE_SIZE KB(4)

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
    ASSERT(ret_code != -1);

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

typedef struct dbh_arena
{
    // how many pages has the arena commited till now.
    // We need this because if we need the arena to grow it will use the page offset to find out how many pages to
    // commit.
    s32    curr_page_offset;
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

s64 __dbh_round_up_multiple(s64 num, s64 round_to)
{
    ASSERT(round_to != 0);
    s64 round_up_multiple = ceil(num / round_to) * round_to;
    return round_up_multiple;
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
        mem_size = __dbh_round_up_multiple(mem_size, DBH_ARENA_DEFAULT_COMMITED_MEMORY);
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
    size_t aligned_size = __dbh_round_up_multiple(size, 2);
    if (arena->allocated_till_now + aligned_size > (size_t)arena->total_size)
    {
        size_t new_size      = __dbh_round_up_multiple(aligned_size, DBH_PAGE_SIZE);
        s32    num_pages     = new_size / DBH_PAGE_SIZE;
        // Lets say we have commited n - 1 pages of total reserved memory and now we want to allocate n + k number of
        // pages. I am pretty sure that the os will not let us and its going to crash the application.
        dbh_return_code code = __dbh_commit_virtual_memory(arena->memory, arena->curr_page_offset, num_pages);

        arena->total_size        = num_pages * DBH_PAGE_SIZE;
        arena->curr_page_offset += num_pages;
        ASSERT(code != DBH_ERROR);
    }

    void *ret_mem = (void *)arena->curr_mem_pos;
    // unpoison the memory;
    ASAN_UNPOISON_MEMORY_REGION(ret_mem, aligned_size);

    arena->curr_mem_pos       += aligned_size;
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

// Args:
#define dbh_array(Type) Type *



typedef struct dbh_darray_header
{
    size_t     total_length;
    s64        count;
    s64        type_size;
    dbh_arena *arena;
    void      *mem;
} dbh_darray_header;

void *_dbh_darray_init(size_t max_length);
void dbh_array_append(void* array, void *element);
void *dbh_array_pop(void* array);


#define DBH_DARRAY_INIT() _dbh_darray_init(0)

#endif
