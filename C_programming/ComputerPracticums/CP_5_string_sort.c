#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_NEEDED_BUTTON 1
#define NEW_LINE 10
#define R_S "\033[1;31m"
#define R_F "\033[1;0m"
#define BUFFER_SIZE 100
#define SENT_QUANT_MAX 15

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <string.h>

bool isContinue();
bool isStrQuantity(int *strQuant);
bool isValidation(int scanfResult, int strQuant);
char **MakingArray(char **array, int strQuant);
char **sort(char **createdArrayOfStrings, int strQuant);
void printResult(char **sortedArrayOfStrings, int strQuant);
void freeMemory(char **sortedArrayOfStrings, int strQuant);

void main()
{
    printf("\nWelcome to the program for sorting an array of strings based on ASCII code!\n\nThis program will help you organize your array of strings by sorting them in ascending order of their ASCII code values.\nYou will need to enter the number of elements in your array of strings and then input the strings themselves.\nAfter that, the program will automatically sort them based on their ASCII codes and display the result on the screen.\n\nLet's get started and sort your array of strings by ASCII code!\n");
    do
    {
        int strQuant = 0;
        if (isStrQuantity(&strQuant))
        {
            char **array = malloc(sizeof(char *) * strQuant);
            char **createdArrayOfStrings = MakingArray(array, strQuant);
            char **sortedArrayOfStrings = sort(createdArrayOfStrings, strQuant);
            printResult(sortedArrayOfStrings, strQuant);
            freeMemory(sortedArrayOfStrings, strQuant);
        }

    } while (isContinue());
}

bool isContinue()
{
    int key = 0;
    do
    {
        printf("\nIf you want to continue, press 'enter', if you want to escape, press 'esc'\n");
        key = _getch();
        if (key == ENTER_BUTTON)
        {
            return true;
        }
        else if (key == EXIT_BUTTON)
        {
            return false;
        }
        else
        {
            key = NOT_NEEDED_BUTTON;
        }
    } while (key == NOT_NEEDED_BUTTON);
}

bool isStrQuantity(int *strQuant)
{
    printf("\nEnter the quantity of sentences you want to sort, you can enter up to fifteen sentences: ");
    int scanfResult = scanf("%d", strQuant);
    bool isValid = isValidation(scanfResult, *strQuant);
    fflush(stdin);
    return isValid;
}

bool isValidation(int scanfResult, int strQuant)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf(R_S "Error, you entered not a number\n" R_F);
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf(R_S "Error, you entered not a number\n" R_F);
        return false;
    }
    if (strQuant < 1 || strQuant > SENT_QUANT_MAX)
    {
        printf(R_S "Error, you entered too big/too small or even length\n" R_F);
        return false;
    }
    return true;
}

char **MakingArray(char **array, int strQuant)
{
    printf("\nStart enter the sentenses to sort, you can enter up to 1 hundred signs:\n");
    int counter = 0;
    while (counter < strQuant)
    {
        for (int i = 0; i < strQuant; i++)
        {
            printf("%d) ", i + 1);
            char buffer[BUFFER_SIZE];
            fgets(buffer, BUFFER_SIZE, stdin);
            fflush(stdin);
            int sentenceLen = strlen(buffer);
            array[i] = malloc(sizeof(char) * BUFFER_SIZE);
            for (int k = 0; k <= sentenceLen; k++)
            {
                array[i][k] = buffer[k];
            }
            counter++;
        }
    }
    return array;
}

char **sort(char **createdArrayOfStrings, int strQuant)
{
    int i, j;
    for (i = 0; i < strQuant - 1; i++)
    {
        for (j = i + 1; j < strQuant; j++)
        {
            if (strcmp(createdArrayOfStrings[i], createdArrayOfStrings[j]) > 0)
            {
                char *tmp = createdArrayOfStrings[i];
                createdArrayOfStrings[i] = createdArrayOfStrings[j];
                createdArrayOfStrings[j] = tmp;
            }
        }
    }
    return createdArrayOfStrings;
}

void printResult(char **sortedArrayOfStrings, int strQuant)
{
    printf("\nSorted strings:\n");
    for (int i = 0; i < strQuant; i++)
    {
        printf("%d) %s", i + 1, sortedArrayOfStrings[i]);
    }
}
void freeMemory(char **sortedArrayOfStrings, int strQuant)
{
    for (int i = 0; i < strQuant; i++)
    {
        free(sortedArrayOfStrings[i]);
    }
    free(sortedArrayOfStrings);
}