#include <stdlib.h>
#define DBH_IMPLEMENTATION
#include "dbh.h"

typedef struct node
{
    f32          value;
    struct node *left;
    struct node *right;
} node;

int main()
{
    dbh_array(s32) vector= {0};
    dbh_array_init(vector);
    
    dbh_array_append(vector, 0);
    dbh_array_append(vector, 1);
    dbh_array_append(vector, 2);
    dbh_array_append(vector, 3);
    dbh_array_append(vector, 4);
    dbh_array_append(vector, 5);
   
    for(s32 i = 0 ; i < dbh_array_get_count(vector) ; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");

    dbh_array_remove_range(vector,2,3);

    for(s32 i = 0 ; i < dbh_array_get_count(vector) ; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");

    dbh_array_insert(vector,2, 189);
    for(s32 i = 0 ; i < dbh_array_get_count(vector) ; i++)
    {
        printf("%d ", vector[i]);
    }
    printf("\n");
    
}
