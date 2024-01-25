#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>

int main()
{
    int howMany;
    printf("How many times, do you want to generate: ");
    scanf("%d", &howMany);
    fflush(stdin);
    double finalArray[howMany];
    srand(time(NULL));
    for (int i; i < howMany; i++)
    {

        int wholePart = rand() % 999999;
        int fractionPart = rand() % 999999;
        int trickSign = rand() % 2;

        char arWhole[7];
        char arFrac[7];
        char arSign[2];
        char arDot[2] = ".";
        if (trickSign == 1)
        {
            sprintf(arSign, "%c", '-');
        }
        else
        {
            sprintf(arSign, "%c", ' ');
        }
        sprintf(arWhole, "%d", wholePart);
        sprintf(arFrac, "%d", fractionPart);
        char stack[19];
        sprintf(stack, "%s%s%s%s", arSign, arWhole, arDot, arFrac);
        double exactlyNum = atof(stack);
        finalArray[i] = exactlyNum;
        printf("%lf\n", finalArray[i]);
    }
}