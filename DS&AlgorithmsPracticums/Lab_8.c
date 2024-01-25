#include <stdio.h>

#define ROWS 5
#define COLS 4

int main()
{
    int matrix[ROWS][COLS];
    float array[ROWS];

    for (int i = 0; i < ROWS; i++)
    {
        printf("Введіть елементи для рядку №%d:\n", i + 1);
        for (int j = 0; j < COLS; j++)
        {
            printf("Введіть елемент [%d][%d]: ", i, j);
            scanf("%d", &matrix[i][j]);
        }
    }

    for (int i = 0; i < ROWS; i++)
    {
        int negCount = 0;
        float sum = 0;

        for (int j = 0; j < COLS; j++)
        {
            if (matrix[i][j] < 0)
            {
                sum += matrix[i][j];
                negCount++;
            }
        }
        if (negCount > 0)
        {
            array[i] = sum / negCount;
        }
        else
        {
            array[i] = 0;
        }
    }

    int gap = ROWS / 2;
    while (gap > 0)
    {
        for (int i = gap; i < ROWS; i++)
        {
            float temp = array[i];
            int j = i;
            while (j >= gap && array[j - gap] < temp)
            {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = temp;
        }
        gap /= 2;
    }

    printf("\nВідсортований масив середніх арифметичних від'ємних елементів за спаданням:\n");
    for (int i = 0; i < ROWS; i++)
    {
        printf("%g ", array[i]);
    }
    printf("\n");

    return 0;
}
