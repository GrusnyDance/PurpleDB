// Copyright [2022] <drunkbatya>

#include "main.h"

int main(void)
{
    // create table my_table (id integer, name string);
    char *arr[7];
    arr[0] = "my_table";
    arr[1] = "id";
    arr[2] = "integer";
    arr[3] = "name";
    arr[4] = "string";
    arr[5] = "age";
    arr[6] = "integer";
    if (!create_table(arr, 3))
    {
        printf("Create table error!\n");
        // return (1);
    }
    arr[0] = "my_table";
    arr[1] = "65535";
    arr[2] = "Test string";
    arr[3] = "32523";
    if (!insert(arr))
    {
        printf("Insert error!\n");
        return (1);
    }
    return (0);
}
