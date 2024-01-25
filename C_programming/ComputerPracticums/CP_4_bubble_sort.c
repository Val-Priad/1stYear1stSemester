#define NOT_NEEDED_NUMBER 0
#define GENERATED 49
#define YOUR_INPUT 50
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NEW_LINE 10
#define R_S "\033[1;31m"
#define R_F "\033[1;0m"
#define VALUE_MIN_MINUS -999999
#define VALUE_MAX_MINUS -1e-6
#define VALUE_MAX_PLUS 999999
#define VALUE_MIN_PLUS 1e-6
#define NUM_LEN 7
#define CHAR_LEN 2
#define MAX_RAND 999999
#define MAX_SIZE 100
#define MAX_LEN 19

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <conio.h>
#include <ctype.h>
#include <time.h>

bool isArrayLenBlock(int *len);
bool isValidationBlockInt(int scanfResult, int len);
void generateNumbers(double *array, int len);
bool inputValuesBlock(double *inpAr, int leng);
bool isValidationReal(int scanfResult, double value);
void bubleSort(double *array, int len);
void printArrayBlock(double *array, int len);
void printResultBlock(double *array, int len);
void zeroCase(double *value);
bool isContinue();

void main()
{
    printf("\n\nThis is a bubble sorting program, you can enter the size of the array you want to sort, or you can generate it at random\n");
    do
    {

        printf("\nIf you want to use randomly generated numbers - press 1\n");
        printf("If you want to enter your own numbers - press 2\n");
        int keyForOption = 0;
        bool isValid = true;
        do
        {
            int pressedButton = _getch();
            if (pressedButton == GENERATED)
            {
                int len = 0;
                isValid = isArrayLenBlock(&len);
                if (isValid)
                {
                    double ourArray[len];
                    generateNumbers(ourArray, len);
                    printArrayBlock(ourArray, len);
                    bubleSort(ourArray, len);
                    printResultBlock(ourArray, len);
                    break;
                }
                break;
            }
            else if (pressedButton == YOUR_INPUT)
            {
                int leng = 0;
                isValid = isArrayLenBlock(&leng);
                if (isValid)
                {
                    double inpAr[leng];
                    isValid = inputValuesBlock(inpAr, leng);
                    if (isValid)
                    {
                        bubleSort(inpAr, leng);
                        printResultBlock(inpAr, leng);
                        break;
                    }
                    break;
                }
                break;
            }
            else
            {
                printf("Please, choose the option\n");
                keyForOption = NOT_NEEDED_NUMBER;
            }
        } while (keyForOption == NOT_NEEDED_NUMBER);
    } while (isContinue());
}

bool isArrayLenBlock(int *len)
{
    double isValidInput = true;
    printf("-------------------------------------------------------------------------------\n");
    printf("Enter how many values you want to have: ");
    int scanfResult = scanf("%d", len);
    isValidInput = isValidationBlockInt(scanfResult, *len);
    fflush(stdin);
    if (!isValidInput)
    {
        return false;
    }
    return true;
}

bool isValidationBlockInt(int scanfResult, int len)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf("Error, you entered not a number\n");
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf("Error, you entered not a number\n");
        return false;
    }
    if (len <= 0 || len > MAX_SIZE)
    {
        printf("Error, you entered too big/too small or even length\n");
        return false;
    }
    return true;
}

void generateNumbers(double *array, int len)
{

    srand(time(NULL));
    int i = 0;
    for (i; i < len; i++)
    {

        int wholePart = rand() % MAX_RAND;
        int fractionPart = rand() % MAX_RAND;
        int trickSign = rand() % 2;

        char arWhole[NUM_LEN];
        char arFrac[NUM_LEN];
        char arSign[CHAR_LEN];
        char arDot[CHAR_LEN] = ".";
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
        char stack[MAX_LEN];
        sprintf(stack, "%s%s%s%s", arSign, arWhole, arDot, arFrac);
        double exactlyNum = atof(stack);
        array[i] = exactlyNum;
        // printf("%lf\n", array[i]);
    }
}

bool inputValuesBlock(double *inpAr, int leng)
{
    printf("-------------------------------------------------------------------------------\n");
    printf("You can enter any real number in range [-999999;999999], be careful numbers will be rounded to 1e-6,\n if number is very close to biger value, program also rounds it\n\n");
    int scanfResultR = 0;
    bool isValidR = true;
    double value = 0;
    for (int i = 0; i < leng; i++)
    {
        printf("%d) ", i + 1);
        scanfResultR = scanf("%lf", &value);
        isValidR = isValidationReal(scanfResultR, value);
        fflush(stdin);
        if (!isValidR)
        {
            return false;
        }
        zeroCase(&value);
        inpAr[i] = value;
    }
}

bool isValidationReal(int scanfResult, double value)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf("Error, you entered not a number\n");
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf("Error, you entered not a number\n");
        return false;
    }
    if (value > 0)
    {
        if (value < VALUE_MIN_PLUS || value > VALUE_MAX_PLUS)
        {
            printf("Error, you entered too big/too small value\n");
            return false;
        }
    }
    if (value < 0)
    {
        if (value < VALUE_MIN_MINUS || value > VALUE_MAX_MINUS)
        {
            printf("Error, you entered too big/too small value\n");
            return false;
        }
    }
    return true;
}

void bubleSort(double *array, int len)
{
    for (int step = 0; step < len; step++)
    {
        for (int i = 0; i < (len - 1); i++)
        {
            if (array[i] > array[i + 1])
            {
                double temp = array[i];
                array[i] = array[i + 1];
                array[i + 1] = temp;
            }
        }
    }
}

void printArrayBlock(double *array, int len)
{
    printf("-------------------------------------------------------------------------------\n");
    printf("Your generated array: \n");
    for (int i = 0; i < len; i++)
    {
        printf("%d. %lf\n", i + 1, array[i]);
    }
}

void printResultBlock(double *array, int len)
{
    printf("-------------------------------------------------------------------------------\n");
    printf("Your sorted array: \n");
    for (int i = 0; i < len; i++)
    {
        printf("%d. %lf\n", i + 1, array[i]);
    }
    printf("-------------------------------------------------------------------------------\n");
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
            key = NOT_NEEDED_NUMBER;
        }
    } while (key == NOT_NEEDED_NUMBER);
}

void zeroCase(double *value)
{
    if (*value == -0)
    {
        *value = 0;
    }
}
