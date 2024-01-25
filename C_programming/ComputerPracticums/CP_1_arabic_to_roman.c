#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define buffer_size 5
int roman(int i, int j, char *c);
bool is_input_analyse(char *string, int *integer);

int main(void)
{
    int integer = 0;
    bool everything_is_well = true;
    int a;
    char y_or_n;
    printf("Ця програма створена для конвертації арабських чисел в римські:D\n");
    do
    {
        do
        {
            printf("Введіть ціле число від 1 до 3999\n");
            char buffer[buffer_size];
            fgets(buffer, buffer_size, stdin);
            fflush(stdin);
            everything_is_well = is_input_analyse(buffer, &integer);
            if (!everything_is_well)
            {
                printf("Має бути ціле число в діапазоні від 1 до 3999!!!\n");
            }
        } while (!everything_is_well);
        a = integer;
        a = roman(a, 1000, "M");
        a = roman(a, 900, "CM");
        a = roman(a, 500, "D");
        a = roman(a, 400, "CD");
        a = roman(a, 100, "C");
        a = roman(a, 90, "XC");
        a = roman(a, 50, "L");
        a = roman(a, 40, "XL");
        a = roman(a, 10, "X");
        a = roman(a, 9, "IX");
        a = roman(a, 5, "V");
        a = roman(a, 4, "IV");
        a = roman(a, 1, "I");
        printf("\nЯкщо ви хочите ввести наступне число, натисніть 'y'\n");
        scanf(" %c", &y_or_n);
        getchar();
    } while (y_or_n == 'y' || y_or_n == 'Y');
}
int roman(int i, int j, char *c)
{
    while (i >= j)
    {
        printf("%s", c);
        i = i - j;
    }
    return (i);
}
bool is_input_analyse(char *string, int *integer)
{
    int q = 0;
    while (isspace(string[q]))
    {
        q++;
    }
    int length = strlen(string);
    if (length == q)
    {
        return false;
    }
    char integer_buffer[buffer_size];
    int integer_nums = 0;
    while (q < length && !isspace(string[q]))
    {
        if (!isdigit(string[q]))
        {
            return false;
        }
        integer_buffer[integer_nums] = string[q];
        integer_nums++;
        q++;
    }
    integer_buffer[integer_nums] = '\0';
    while (isspace(string[q]))
    {
        q++;
    }
    if (string[q] != '\0')
    {
        return false;
    }
    *integer = atoi(integer_buffer);

    return (*integer >= 1 && *integer <= 3999) ? true : false;
}
