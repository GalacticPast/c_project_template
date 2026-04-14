#define DB_IMPLEMENTATION
#include "db.h"

int main()
{
    db_arena  main_arena = db_arena_init();
    db_arena  arena      = db_arena_init(.type = TYPE_ARENA_CHUNKED, .chunk_size = 64);
    db_string str        = db_string_make(
        &arena,
        "                                                                                                    Hello "
        "World   !!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!!");
    printf("%s\n", db_string_get_cstr(&main_arena, &str));
    db_string trimmed_str = db_string_trim(&str, "abc!");
    printf("%s\n", db_string_get_cstr(&main_arena, &trimmed_str));
}
