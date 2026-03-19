#define DBH_IMPLEMENTATION
#include "dbh.h"

int main()
{
    dbh_string str = dbh_string_make("Hello world");
    printf("%s\n", str);
    dbh_string dup = dbh_string_duplicate(str);
    printf("dup: %s\n", dup);
}
