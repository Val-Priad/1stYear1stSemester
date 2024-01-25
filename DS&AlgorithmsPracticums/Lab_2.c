#include <stdio.h>
#include <Math.h>

void main()
{
    float a;
    do
    {
        float x;
        printf("\nEnter the number:");
        scanf("%f", &a);
        if (a > 0)
        {
            x = -(abs(a - 1)) / (2 * a);
        }
        else
        {
            x = log(sqrt(1 + pow(a, 2)));
        }
        printf("%f", x);
    } while (a != 999);
}