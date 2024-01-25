#include <stdio.h>
#include <math.h>

void main()
{
    while (1)
    {

        int num = 0;
        printf("\nEnter the number: ");
        scanf("%d", &num);
        int list[30];
        int list2[30];
        int r = 0;
        int i = 0;
        int k = 0;
        int s = 0;
        for (i = 0; num != 0; i++)
        {
            r = num % 2;
            list[i] = r;
            num = num / 2;
            s++;
            printf("Iteration: %d, Value to list: %d, n after iteration: %d\n", i + 1, r, num);
        }
        s--;
        for (k = 0; s >= 0; k++)
        {
            list2[k] = list[s];
            s--;
        }
        for (int j = 0; j < k; j++)
        {
            printf("%d", list2[j]);
        }
    }
}
