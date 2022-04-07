// Copyright [2022] <drunkbatya>

#include "select.h"

// Return true if current column name is which user wants to select.
// Also return true is user typed "select * ...".
uint8_t is_column_to_select(t_header *column, char *column_name)
{
    if (strcmp(column->column_name, column_name) == 0)
        return (1);
    if (strcmp(column_name, "*") == 0)
        return (1);
    return (0);
}

void print_column(FILE *fptr, t_header *column, uint16_t offset)
{
    INTEGER *integer_ptr;
    char *string_ptr;

    if (column->datatype == integer)
    {
        integer_ptr = read_record_from_file(fptr, offset, sizeof(INTEGER));
        printf("|%d|", *integer_ptr);
        safe_free(integer_ptr);
    }
    if (column->datatype == string)
    {
        string_ptr = read_record_from_file(fptr, offset, STRING_SIZE);
        printf("|%s|", string_ptr);
        safe_free(string_ptr);
    }
}

uint8_t bin_calc_int(int32_t num1, int32_t num2, char *op)
{
    if (strcmp(op, "=") == 0)
        return (num1 = num2);
    if (strcmp(op, "<") == 0)
        return (num1 < num2);
    if (strcmp(op, ">") == 0)
        return (num1 < num2);
    error_wrong_operator(op);
    return (0);
}

//        1      0           2  3 4
// select * from table where id = 2;
uint8_t is_where_condition_true(void)
{
    return (1);
}

// Select data from existing table
// Expected count of array in arr = 5.
// Arr format:
//   [table_name] [column_name]
//   [operand - column name] [operator] [operand - column value].
// To use SELECT without WHERE leave [operand - column name] empty.
// To SELECT * put asterisk to [column_name].
void p_select(char **arr)
{
    char file_path[strlen(arr[0]) + 4];
    FILE *fptr;
    t_header **columns_arr;
    uint16_t offset;
    uint16_t rows;
    uint16_t row_size;
    uint16_t row_count;
    COLUMN_COUNTER columns;
    COLUMN_COUNTER column_count;

    row_count = 0;
    strcpy(file_path, arr[0]);
    strcat(file_path, ".db");
    row_size = get_row_size(file_path);
    rows = get_rows_count(file_path);
    columns = read_column_number(file_path);
    fptr = fopen(file_path, "r");
    if (fptr == NULL)
        return (error_unknown_table(arr[0]));
    columns_arr = get_headers(fptr, columns);
    if (rows == 0 || columns == 0 || row_size == 0 || columns_arr == NULL)
    {
        safe_fclose(fptr);
        return (error_read_table(arr[0]));
    }
    offset = sizeof(COLUMN_COUNTER) + (sizeof(t_header) * columns);
    while (row_count < rows)
    {
        column_count = 0;
        if (is_where_condition_true() == 0)
        {
            offset += row_size;
            row_count++;
            continue;
        }
        while (column_count < columns)
        {
            if (is_column_to_select(columns_arr[column_count], arr[1]))
                print_column(fptr, columns_arr[column_count], offset);
            offset += get_size_by_datatype(columns_arr[column_count]);
            column_count++;
        }
        printf("\n");
        row_count++;
    }
    safe_free_headers(columns_arr, columns);
    safe_fclose(fptr);
}
