#include <stdio.h>

void printArray(int array[]);
void main()
{
    int firstArray[10];
    int secondArray[10];
    int thirdArray[10];
    int counter = 0;
    for (int i = 0; i < 10; i++)
    {
        printf("for(i = %d; %d < 10;%d++) (True)\n", i, i, i);
        firstArray[i] = 130 - i;
        printf("firstArray[%d] = 130 - %d = %d\n", i, i, (130 - i));
        secondArray[i] = 120 + i;
        printf("secondArray[%d] = 120 + %d = %d\n", i, i, (120 + i));
    }
    printf("for(i = 10; 10 < 10; 10++) (False)\n");
    // printArray(firstArray);
    // printArray(secondArray);
    int k = 0;
    printf("counter = 0\n");
    for (int a = 0; a < 10; a++)
    {
        printf("for(i = %d; %d < 10;%d++) (True)\n", a, a, a);
        for (int z = 0; z < 10; z++)
        {
            printf("for(j = %d; %d < 10;%d++) (True)\n", z, z, z);
            if (firstArray[a] == secondArray[z])
            {
                printf("if (firstArray[%d] == secondArray[%d]) (%d == %d) (True)\n", a, z, firstArray[a], secondArray[z]);
                thirdArray[k] = firstArray[a];
                printf("thirdArray[%d] = firstArray[%d]\n", k, a);
                k++;
                printf("counter++ (%d++ (%d))\n", k - 1, k);
            }
            else
            {
                printf("if (firstArray[%d] == secondArray[%d]) (%d == %d) (False)\n", a, z, firstArray[a], secondArray[z]);
            }
        }
        printf("for(j = 10; 10 < 10; 10++) (False)\n");
    }
    printf("for(i = 10; 10 < 10; 10++) (False)\n");
    printf("quantityCounter = 0\n");
    for (int q = 0; q < 10; q++)
    {
        printf("for (int %d = 0; %d < 10; %d++) (True)\n", q, q, q);
        if (thirdArray[q] < 127 && thirdArray[q] != 0)
        {
            printf("if (thirdArray[%d] < 127) (%d < 127) (True)\n", q, thirdArray[q]);
            counter++;
            printf("quantityCounter++ (%d++ (%d))\n", counter - 1, counter);
        }
        else
        {
            printf("if (thirdArray[%d] < 127) (%d < 127) (False)\n", q, thirdArray[q]);
        }
    }
    printf("for(i = 10; 10 < 10; 10++) (False)\n");

    // printArray(thirdArray);
    // printf("%d\n", counter);
}

void printArray(int array[])
{
    for (int i = 0; i < 10; i++)
    {
        printf("%d\n", array[i]);
    }
    printf("\n");
}
