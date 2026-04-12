#define DB_IMPLEMENTATION
#include "db.h"

db_stack_decl(abc, s32)

    int main()
{
    db_arena main_arena = db_arena_init();

    db_stack_abc init = db_stack_init();
}
