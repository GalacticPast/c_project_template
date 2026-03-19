#define DBH_IMPLEMENTATION
#include "dbh.h"

int main()
{
    u64 id = dbh_hash_string("Hello world abc");
    printf("%lu\n", id);
    u64 id_2 = dbh_hash_string("Hello world abd");
    printf("%lu\n", id_2);
}
