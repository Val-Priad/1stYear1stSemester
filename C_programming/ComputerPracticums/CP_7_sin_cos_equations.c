#define SECOND_OPTION 50
#define FIRST_OPTION 49
#define COS_FUNCT 0
#define SIN_FUNCT 1
#define NOT_NEEDED_NUMBER 0
#define NEW_LINE 10
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NO_ROOTS 101
#define LIMIT_PLUS_MAX 10
#define LIMIT_MINUS_MIN -10
#define R_S "\033[0;31m"
#define F "\033[0m"
#define G_S "\033[0;32m"
#define EPSILON 1e-6

#include <stdio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>
#include <conio.h>

int selectEquation();
int chooseMethod();
bool isEnterDataBlock(double *a, double *b, double *y, int equation);
bool isInputAdequate(double *a, double *b);
bool isValidation(int scanfResult, double value, int equation);
double cosFunct(double x, double y);
double sinFunct(double x, double y);
double halfDivisionMethod(double (*chosenEquation)(double, double), double a, double b, double y);
double NewtonMethod(double (*chosenEquation)(double, double), double a, double b, double y);
bool isContinue();
double rounded(double a);
double (*chosenEquation[2])(double, double) = {cosFunct, sinFunct};

int main()
{
    printf("\n\nThis program is designed to calculate the roots of nonlinear equations at a given interval x∈[a1;a2]. You can enter the interval in range [-10;10]\n\n");
    do
    {
        printf(G_S "---------------------------------------------------------------------------------------------------\n" F);
        int equation = selectEquation();
        int method = chooseMethod();
        double a = 0;
        double b = 0;
        double y = 0;
        double result = 0;

        if (isEnterDataBlock(&a, &b, &y, equation))
        {
            if (method == FIRST_OPTION)
            {
                result = halfDivisionMethod(chosenEquation[equation], a, b, y);
            }
            else
            {
                result = NewtonMethod(chosenEquation[equation], a, b, y);
            }
            (result != NO_ROOTS)
                ? printf(G_S "\nResult by this method is:" F " %.6lf\n", result)
                : printf(R_S "No roots" F " of equation in range [%lf; %lf]\n", a, b);
        }
    } while (isContinue());
    return 0;
}

int selectEquation()
{
    printf("Plese, chose the equation, that you want to use:\nPress 1: cos(y / x) - 2 * sin(1 / x) + (1 / x)\nPress 2: sin(log(x)) - cos(log(x)) + y * log(x)\n");
    int keyForOption = 0;
    do
    {
        int pressedButton = _getch();
        if (pressedButton == FIRST_OPTION)
        {
            printf(G_S "You have chosen:" F " cos(y / x) - 2 * sin(1 / x) + (1 / x)\n\n");
            return COS_FUNCT;
        }
        else if (pressedButton == SECOND_OPTION)
        {
            printf(G_S "You have chosen:" F " sin(log(x)) - cos(log(x)) + y * log(x)\n");
            printf("Be careful, if you have chosen this function," G_S " your range must to be [0; 10]" F "\n\n");
            return SIN_FUNCT;
        }
        else
        {
            printf("Please, choose the option\n");
            keyForOption = NOT_NEEDED_NUMBER;
        }
    } while (keyForOption == NOT_NEEDED_NUMBER);
}

int chooseMethod()
{
    printf("Plese, chose the method, that you want to use:\nPress 1: Half Division Method\nPress 2: Newton Method\n");
    int keyForOption = 0;
    do
    {
        int pressedButton = _getch();
        if (pressedButton == FIRST_OPTION)
        {
            printf(G_S "You have chosen:" F " Half Division Method\n\n");
            return FIRST_OPTION;
        }
        else if (pressedButton == SECOND_OPTION)
        {
            printf(G_S "You have chosen:" F " Newton Method\n\n");
            return SECOND_OPTION;
        }
        else
        {
            printf("Please, choose the option\n");
            keyForOption = NOT_NEEDED_NUMBER;
        }
    } while (keyForOption == NOT_NEEDED_NUMBER);
}

bool isEnterDataBlock(double *a, double *b, double *y, int equation)
{
    bool isValid = true;
    printf("Enter the parametr a in range [a;b]: ");
    int scanfResult = scanf("%lf", a);
    isValid = isValidation(scanfResult, *a, equation);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }

    printf("Enter the parametr b in range [a;b]: ");
    scanfResult = scanf("%lf", b);
    isValid = isValidation(scanfResult, *b, equation);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }
    printf("Enter the parametr y in the equation: ");
    scanfResult = scanf("%lf", y);
    isValid = isValidation(scanfResult, *y, equation);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }
    return isInputAdequate(a, b);
}

bool isInputAdequate(double *a, double *b)
{
    if (*b < *a)
    {
        printf(R_S "You can't enter such boundaries\n" F);
        return false;
    }
    return true;
}

bool isValidation(int scanfResult, double value, int equation)
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
    if (equation == COS_FUNCT && (value < LIMIT_MINUS_MIN || value > LIMIT_PLUS_MAX))
    {
        printf(R_S "Error, you entered too big, too small number\n" F);
        return false;
    }
    if (equation == SIN_FUNCT && (value < 0 || value > LIMIT_PLUS_MAX))
    {
        printf("If you have chosen sin() function," R_S " your range must to be [0; 10]" F "\n");
        return false;
    }
    return true;
}

double cosFunct(double x, double y)
{
    return cos(y / x) - 2 * sin(1 / x) + (1 / x);
}

double sinFunct(double x, double y)
{
    return sin(log(x)) - cos(log(x)) + y * log(x);
}

double halfDivisionMethod(double (*chosenEquation)(double, double), double a, double b, double y)
{
    int counterForExtraSituations = 0;
    double epsilon = EPSILON * (1 / 10);
    double x = 0;
    double functByA = 0;
    double functByX = 0;
    double functByB = 0;
    if (a == 0)
    {
        a += epsilon;
    }
    functByA = chosenEquation(a, y);
    functByB = chosenEquation(b, y);
    if (functByA * functByB > 0)
    {
        printf("\nIf a function f(x) maintains the same sign in extreme points, the half division method will be" R_S " unable to determine" F " the interval containing a root.\n");
        return NO_ROOTS;
    }
    do
    {
        x = (a + b) / 2.;
        functByA = chosenEquation(a, y);
        functByX = chosenEquation(x, y);
        (functByA * functByX > 0) ? (a = x) : (b = x);
        counterForExtraSituations++;
    } while (fabs(b - a) > epsilon && counterForExtraSituations < 1000);
    return rounded(x);
}

double NewtonMethod(double (*chosenEquation)(double, double), double a, double b, double y)
{
    int counterForExtraSituations = 0;
    double epsilon = EPSILON;
    double derivative = 0;
    double delta = 0;
    if (a == 0)
    {
        a += epsilon;
    }
    double functByA = 0;
    double functByB = 0;
    functByA = chosenEquation(a, y);
    functByB = chosenEquation(b, y);
    if (functByA * functByB > 0)
    {
        printf("\nIf a function f(x) maintains the same sign in extreme points, the Newton method will be" R_S " unable to determine" F " the interval containing a root.\n");
        return NO_ROOTS;
    }
    double x = (a + b) / 2.0;
    if (x == 0)
    {
        x += epsilon;
    }
    do
    {
        derivative = (chosenEquation(x + epsilon, y) - chosenEquation(x, y)) / epsilon;
        if (derivative == 0)
        {
            printf("Sorry, dirivative is too small, it approximately equals to zero, so no roots by this method\n");
            return NO_ROOTS;
        }
        delta = chosenEquation(x, y) / derivative;
        x = x - delta;
        counterForExtraSituations++;
    } while (fabs(delta) >= epsilon && counterForExtraSituations < 1000);
    return rounded(x);
}

double rounded(double a)
{
    double trick = 0;
    trick = (int)(a * (1 / EPSILON) * 10) % 10;
    a = a * (1 / EPSILON);
    a = round(a);
    a = a / (1 / EPSILON);
    if (trick > 4)
    {
        return a - EPSILON;
    }
    else if (trick < -4)
    {
        return a + EPSILON;
    }
    return a;
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
