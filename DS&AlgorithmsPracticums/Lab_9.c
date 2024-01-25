#include <stdio.h>
#include <float.h>

#define SIZE 4
#define DBL_MINI -DBL_MAX

int main()
{
    double matrix[SIZE][SIZE];

    for (int i = 0; i < SIZE; i++)
    {
        printf("i = 0; %d < SIZE; %d++ (True)\n", i, i);
        // printf("Введіть елементи для рядку №%d:\n", i + 1);
        for (int j = 0; j < SIZE; j++)
        {
            printf("j = 0; %d < SIZE; %d++ (True)\n", j, j);
            printf("Введіть елемент [%d][%d]: ", i, j);

            scanf("%lf", &matrix[i][j]);
            printf("\nmatrix[%d][%d]= %g\n", i, j, matrix[i][j]);
        }
        printf("j = 0; 4 < SIZE; 4++ (false)\n");
    }
    printf("i = 0; 4 < SIZE; 4++ (False)\n");

    // printf("\n---------------------------------------\n");
    // printf("Введені дані: \n");
    // for (int i = 0; i < SIZE; i++)
    // {
    //     printf("\n");
    //     for (int j = 0; j < SIZE; j++)
    //     {
    //         printf("%g ", matrix[i][j]);
    //     }
    // }

    double max = DBL_MINI;
    double min = DBL_MAX;
    printf("max = DBL_MINI\n");
    printf("min = DBL_MAX\n");
    int maxPos = 0;
    int minPos = 0;
    double temp = 0;
    for (int i = 0; i < SIZE; i++)
    {
        printf("i = 0; %d < SIZE; %d++ (True)\n", i, i);
        if (matrix[i][i] > max)
        {
            printf("(matrix[%d][%d])%g > %g (True)\n", i, i, matrix[i][i], max);
            max = matrix[i][i];
            printf("max = %g(matrix[%d][%d])\n", matrix[i][i], i, i);
            maxPos = i;
            printf("maxPos = %d\n", i);
        }
        else
        {
            printf("%g > %g (False)\n", matrix[i][i], max);
        }
        if (matrix[i][i] <= min)
        {
            printf("(matrix[%d][%d])%g <= %g (True)\n", i, i, matrix[i][i], min);
            min = matrix[i][i];
            printf("min = %g(matrix[%d][%d])\n", matrix[i][i], i, i);
            minPos = i;
            printf("minPos = %d\n", i);
        }
        else
        {
            printf("%g <= %g (False)\n", matrix[i][i], min);
        }
    }
    printf("i = 0; 4 < SIZE; 4++ (False)\n");

    if (max != min)
    {
        printf("max != min (%g != %g) (True)\n", max, min);
        temp = matrix[maxPos][maxPos];
        printf("temp = %g(matrix[%d][%d])\n", matrix[maxPos][maxPos], maxPos, maxPos);
        matrix[maxPos][maxPos] = matrix[maxPos][SIZE - 1 - maxPos];
        printf("matrix[%d][%d] = %g(matrix[%d][%d])\n", maxPos, maxPos, matrix[maxPos][SIZE - 1 - maxPos], maxPos, SIZE - 1 - maxPos);
        matrix[maxPos][SIZE - 1 - maxPos] = temp;
        printf("matrix[%d][%d] = %g\n", maxPos, SIZE - 1 - maxPos, temp);
        temp = matrix[minPos][minPos];
        printf("temp = %g(matrix[%d][%d])\n", matrix[minPos][minPos], minPos, minPos);
        matrix[minPos][minPos] = matrix[minPos][SIZE - 1 - minPos];
        printf("matrix[%d][%d] = %g(matrix[%d][%d])\n", minPos, minPos, matrix[minPos][SIZE - 1 - minPos], minPos, SIZE - 1 - minPos);
        matrix[minPos][SIZE - 1 - minPos] = temp;
        printf("matrix[%d][%d] = %g\n", minPos, SIZE - 1 - minPos, temp);
    }
    else
    {
        printf("max != min (%g != %g) (False)\n", max, min);
    }

    printf("\n---------------------------------------\n");
    printf("Результат роботи програми: \n");
    for (int i = 0; i < SIZE; i++)
    {
        printf("\n");
        for (int j = 0; j < SIZE; j++)
        {
            printf("%g ", matrix[i][j]);
        }
    }
    printf("\n---------------------------------------\n");

    return 0;
}
