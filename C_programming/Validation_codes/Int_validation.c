#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool isIntValidation(int scanfResult, int a);

void main()
{
    int a = 0;
    bool isValid = true;
    do
    {
        a = 0;
        printf("\nEnter a number:");
        int scanfResult = scanf(" %d", &a);

        isValid = isIntValidation(scanfResult, a);
        if (isValid == true)
        {
            printf("Your input: %d", a);
        }
    } while (a != 999);
}
bool isIntValidation(int scanfResult, int a)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf("Error, you entered not a number\n");
        fflush(stdin);
        return false;
    }
    else if (received_ASCII_code != 10 && !isdigit(received_ASCII_code))
    {
        printf("Error, you entered not a number\n");
        fflush(stdin);
        // a = 0;
        return false;
    }
    if (a > 100 || a < -100)
    {
        printf("Error, you entered too big/too small number\n");
        fflush(stdin);
        return false;
    }
    return true;
}
