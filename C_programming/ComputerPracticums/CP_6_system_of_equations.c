#define R_S "\033[0;31m"
#define F "\033[0m"
#define G_S "\033[0;32m"
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_NEEDED_BUTTON 1
#define NEW_LINE 10
#define MAX_EXPRESSIONS_QUANT 4
#define LIMIT_PLUS_MAX 100
#define LIMIT_PLUS_MIN 1e-10
#define LIMIT_MINUS_MIN -100
#define LIMIT_MINUS_MAX -1e-10

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <ctype.h>
#include <conio.h>
#include <stdio.h>
#include <math.h>

bool isContinue();
bool isSecretValuesQuant(int *secretValuesQuant);
bool isValidation(int scanfResult, int secretValuesQuant);
void MakingSOLE(double **array, int secretValuesQuant);
bool isArgumentValidation(int scanfResult, double value);
void printSOLE(double **array, int secretValuesQuant);
bool isSOLEAdequate(double **array, int secretValuesQuant);
bool isPrecisionEnter(double *precision);
bool isPrecisionValidation(int scanfResult, double precision);
double *calculationBlock(double **array, int secretValuesQuant, double precision);
void printResult(double *resultRoots, int secretValuesQuant);
void freeMemory(double **array, int secretValuesQuant);

void main()
{
    printf("\n\nThis program is designed to solve systems of linear equations using the method of simple iteration.\nLet's get started!\n");
    printf("This is the example of correct linear equation:\n5" G_S "x1" F "-1" G_S "x2" F "+3" G_S "x3" F "=5\n1" G_S "x1" F "-4" G_S "x2" F "+2" G_S "x3" F "=20\n2" G_S "x1" F "-1" G_S "x2" F "+5" G_S "x3" F "=10\n\n");
    do
    {
        int secretValuesQuant = 0;
        if (isSecretValuesQuant(&secretValuesQuant))
        {
            double **array = malloc(sizeof(double *) * secretValuesQuant);
            MakingSOLE(array, secretValuesQuant);
            printSOLE(array, secretValuesQuant);
            if (isSOLEAdequate(array, secretValuesQuant))
            {
                double precision = 0;
                if (isPrecisionEnter(&precision))
                {
                    double *resultRoots = calculationBlock(array, secretValuesQuant, precision);
                    printResult(resultRoots, secretValuesQuant);
                    free(resultRoots);
                }
            }
            freeMemory(array, secretValuesQuant);
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

bool isSecretValuesQuant(int *secretValuesQuant)
{
    double isValidInput = true;
    printf("Please, enter the quantity of expressions you have, you can enter up to 4 expressions: ");
    int scanfResult = scanf("%d", secretValuesQuant);
    isValidInput = isValidation(scanfResult, *secretValuesQuant);
    fflush(stdin);
    return isValidInput;
}

bool isValidation(int scanfResult, int secretValuesQuant)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    if (secretValuesQuant <= 0 || secretValuesQuant > MAX_EXPRESSIONS_QUANT)
    {
        printf(R_S "Error, you entered too big/too small or even number\n" F);
        return false;
    }
    return true;
}

void MakingSOLE(double **array, int secretValuesQuant)
{
    printf("\nStart enter the arguments, you can enter any number up to 100:\n");
    double value = 0;
    int scanfResult = 0;
    bool isValidInput = true;

    for (int i = 0; i < secretValuesQuant; i++)
    {
        printf("\nEnter expression №%d\n", i + 1);
        array[i] = malloc(sizeof(double) * (secretValuesQuant + 1));
        for (int k = 0; k <= secretValuesQuant; k++)
        {
            do
            {
                (k == secretValuesQuant) ? (printf("equals to =")) : (printf("x%d=", k + 1));
                scanfResult = scanf("%lf", &value);
                isValidInput = isArgumentValidation(scanfResult, value);
                fflush(stdin);
            } while (!isValidInput);
            array[i][k] = value;
        }
    }
}

bool isArgumentValidation(int scanfResult, double value)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    if (value >= 0)
    {
        if ((value < LIMIT_PLUS_MIN || value > LIMIT_PLUS_MAX) && value != 0)
        {
            printf(R_S "Error, you entered too big/too small number\n" F);
            return false;
        }
    }
    else
    {
        if (value < LIMIT_MINUS_MIN || value > LIMIT_MINUS_MAX)
        {
            printf(R_S "Error, you entered too big/too small number\n" F);
            return false;
        }
    }
    return true;
}

void printSOLE(double **array, int secretValuesQuant)
{
    printf("\nYour input:");
    for (int i = 0; i < secretValuesQuant; i++)
    {
        printf("\n");
        for (int k = 0; k <= secretValuesQuant; k++)
        {
            if (k == 0)
            {
                printf("%g" G_S "x%d" F, array[i][k], k + 1);
            }
            else if (k == secretValuesQuant)
            {
                printf("=%g", array[i][k]);
            }
            else
            {
                printf("%+g" G_S "x%d" F, array[i][k], k + 1);
            }
        }
    }
}

bool isSOLEAdequate(double **array, int secretValuesQuant)
{
    double rowSummer = 0;
    for (int i = 0; i < secretValuesQuant; i++)
    {
        for (int k = 0; k < secretValuesQuant; k++)
        {
            if (k != i)
            {
                rowSummer += array[i][k];
            }
        }
        if (fabs(array[i][i]) <= rowSummer)
        {
            printf(R_S "\n\nError" F ", elements on the main diagonal have a smaller magnitude compared to the other elements in the row;\nfor such systems, the method of simple iteration is not suitable\n");
            return false;
        }
        rowSummer = 0;
    }
    return true;
}

bool isPrecisionEnter(double *precision)
{
    double isValidInput = true;
    printf("\nEntered data is suitable for computation using the method of simple iteration, please enter the precision: ");
    int scanfResult = scanf("%lf", precision);
    isValidInput = isPrecisionValidation(scanfResult, *precision);
    fflush(stdin);
    return isValidInput;
}

bool isPrecisionValidation(int scanfResult, double precision)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        printf(R_S "Error, you entered not a number\n" F);
        return false;
    }
    int trick = log10(precision);
    if (!(trick == -1 || trick == -2 || trick == -3 || trick == -4 || trick == -5 || trick == -6 || trick == -7 || trick == -8 || trick == -9 || trick == -10))
    {
        printf(R_S "Error, you entered strange accuracy, enter something like that '0.0..1', only up to 10 signs after the koma\n" F);
        return false;
    }
    return true;
}

double *calculationBlock(double **array, int secretValuesQuant, double precision)
{
    double *resultX = calloc(sizeof(double), secretValuesQuant);
    double *previousX = calloc(sizeof(double), secretValuesQuant);
    double *delta = calloc(sizeof(double), secretValuesQuant);
    double sumNeeded = 0.0;
    double maxDelta = 0.0;
    do
    {
        for (int i = 0; i < secretValuesQuant; i++)
        {
            previousX[i] = resultX[i];
        }
        for (int i = 0; i < secretValuesQuant; i++)
        {
            sumNeeded = 0;
            for (int j = 0; j < secretValuesQuant; j++)
            {
                if (j != i)
                {
                    sumNeeded += array[i][j] * resultX[j];
                }
            }
            resultX[i] = (array[i][secretValuesQuant] - sumNeeded) / array[i][i];
        }
        maxDelta = 0.0;
        for (int i = 0; i < secretValuesQuant; i++)
        {
            delta[i] = fabs(resultX[i] - previousX[i]);
            if (delta[i] > maxDelta)
            {
                maxDelta = delta[i];
            }
        }
    } while (maxDelta >= precision);
    free(previousX);
    free(delta);
    return resultX;
}

void printResult(double *resultRoots, int secretValuesQuant)
{
    for (int i = 0; i < secretValuesQuant; i++)
    {
        printf("\nx%d=%lf\n", i + 1, resultRoots[i]);
    }
}

void freeMemory(double **array, int secretValuesQuant)
{
    for (int i = 0; i < secretValuesQuant; i++)
    {
        free(array[i]);
    }
    free(array);
}
