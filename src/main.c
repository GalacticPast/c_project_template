#define DB_IMPLEMENTATION
#include "db.h"

db_stack_decl(abc, s32)

    int main()
{
    db_arena arena      = db_arena_init();
    db_arena main_arena = db_arena_init(.type = TYPE_ARENA_CHUNKED, .chunk_size = 64);

    db_string str =
        db_string_make(&main_arena, "abcdafasdfasdfasdfasdfasdfasdfadlfkjas;lfkdjas;lfkjas;ldkfjas;ldfkjasdl;fkj");

    printf("%s\n", db_string_get_cstr(&arena, str));
}
