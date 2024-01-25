
#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>

bool isDoubleValidation(int scanfResult, double a);

void main()
{
    bool isValid = true;
    double a = 0;
    do
    {
        a = 0;
        printf("\nEnter a number:");
        int scanfResult = scanf(" %lf", &a);

        isValid = isDoubleValidation(scanfResult, a);

        if (isValid)
        {
            printf("Your input: %lf", a);
        }
    } while (a != 999);
}
bool isDoubleValidation(int scanfResult, double a)
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
        return false;
    }
    if (a > 100 || a < -100)
    {
        printf("Error, you entered too big/too small number\n");
        fflush(stdin);
        return false;
    } // number boundaries

    return true;
}