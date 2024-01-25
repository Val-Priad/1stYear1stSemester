#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_THE_NEEDED_BUTTON 1
#define NEW_LINE 10
#define VALIDATION_FOR_DIAPASONE_AND_STEP 0
#define VALIDATION_FOR_EPSILON 1
#define LIMIT_PLUS_MAX 1500
#define LIMIT_PLUS_MIN 1e-12
#define LIMIT_MINUS_MIN -1500
#define LIMIT_MINUS_MAX -1e-12
#define EPSILON_MIN 1e-10
#define R_S "\033[1;31m"
#define R_F "\033[1;0m"
#define piNum 3.14159265358979323846

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

bool isEnterDataBlock(double *x, double *y, double *step, double *epsilon);
bool isValidation(int scanfResult, double ourNum, int whatValid);
void ourCalculationBlock(double x, double y, double step, double epsilon);
bool isInputAdequate(double *x, double *y, double *step, double *epsilon);
void printResultBlock(double x, double expected, double tailorSum, double difference);
bool isContinue();
double rounded(double a);
double roundWithPrecision(double epsilon, double tailorSum);
static double factorial(int counter);

void main()
{
    printf("\nThis program is designed to generate a table of values for sin calculated using\na Taylor series expansion, compared to tabulated sine values, and to display\ntheir differences within a specified range and with a specified precision.\nBoundaries(-1500;1500), all results are rounded up to 10 signs after the koma\n\n");
    do
    {
        double x = 0, y = 0, step = 0, epsilon = 0;
        bool isEverythingWell = isEnterDataBlock(&x, &y, &step, &epsilon);
        if (isEverythingWell)
        {
            ourCalculationBlock(x, y, step, epsilon);
        }

    } while (isContinue());
}

bool isEnterDataBlock(double *x, double *y, double *step, double *epsilon)
{
    bool isValid = true;
    printf("Enter the parametr x in range [x;y]: ");
    int whatValid = VALIDATION_FOR_DIAPASONE_AND_STEP;
    int scanfResult = scanf("%lf", x);
    isValid = isValidation(scanfResult, *x, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }

    printf("Enter the parametr y in range [x;y]: ");
    whatValid = VALIDATION_FOR_DIAPASONE_AND_STEP;
    scanfResult = scanf("%lf", y);
    isValid = isValidation(scanfResult, *y, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }

    printf("Enter the step with which you want to count sin: ");
    whatValid = VALIDATION_FOR_DIAPASONE_AND_STEP;
    scanfResult = scanf("%lf", step);
    isValid = isValidation(scanfResult, *step, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }

    printf("Enter the accuracy: ");
    whatValid = VALIDATION_FOR_EPSILON;
    scanfResult = scanf("%lf", epsilon);
    isValid = isValidation(scanfResult, *epsilon, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        return false;
    }
    isValid = isInputAdequate(x, y, step, epsilon);
    return isValid;
}

bool isValidation(int scanfResult, double ourNum, int whatValid)
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
    if (whatValid == VALIDATION_FOR_DIAPASONE_AND_STEP)
    {
        if (ourNum > 0)
        {
            if (ourNum < LIMIT_PLUS_MIN || ourNum > LIMIT_PLUS_MAX)
            {
                printf(R_S "Error, you entered too big/too small number\n" R_F);
                return false;
            }
        }
        else
        {
            if (ourNum < LIMIT_MINUS_MIN || ourNum > LIMIT_MINUS_MAX)
            {
                printf(R_S "Error, you entered too big/too small number\n" R_F);
                return false;
            }
        }
    }
    if (whatValid == VALIDATION_FOR_EPSILON)
    {
        int trick = log10(ourNum);
        if (!(trick == -1 || trick == -2 || trick == -3 || trick == -4 || trick == -5 || trick == -6 || trick == -7 || trick == -8 || trick == -9 || trick == -10))
        {
            printf(R_S "Error, you entered strange accuracy, enter something like that '0.0..1', only up to 10 signs after the koma\n" R_F);
            return false;
        }
    }
    return true;
}

bool isInputAdequate(double *x, double *y, double *step, double *epsilon)
{
    if (*x == *y)
    {
        printf(R_S "Extreme parameters cannot be equal" R_F);
        return false;
    }
    if (*x < *y)
    {
        if (*step < 0)
        {
            printf(R_S "In this situation the step cannot be negative" R_F);
            return false;
        }
        if ((*x + *step) > *y)
        {
            printf(R_S "You entered too big step" R_F);
            return false;
        }
    }
    if (*x > *y)
    {
        if (*step > 0)
        {
            printf(R_S "In this situation the step cannot be positive" R_F);
            return false;
        }
        if ((*x + *step) < *y)
        {
            printf(R_S "You entered too small step" R_F);
            return false;
        }
    }
    if (step == 0)
    {
        return false;
    }
    return true;
}

void ourCalculationBlock(double x, double y, double step, double epsilon)
{
    const double pi = piNum;
    if (step > 0)
    {
        for (x; (x + step) <= (y + step); x += step)
        {
            double tailorSum = 0;
            int counter = 0;
            double delta = 0;
            double difference = 0;
            double expectedSin = 0;
            double xC = (x * pi) / (180.);
            for (counter == 0;; counter++)
            {
                if (counter % 2 == 0)
                {
                    delta = (pow(xC, 2 * counter + 1)) / factorial(2 * counter + 1);
                }
                else
                {
                    delta = -(pow(xC, 2 * counter + 1)) / factorial(2 * counter + 1);
                }
                if (fabs(delta) < epsilon)
                {
                    break;
                }
                tailorSum += delta;
            }
            tailorSum = roundWithPrecision(epsilon, tailorSum);
            expectedSin = sin(xC);
            difference = (rounded(sin(xC)) - tailorSum);
            printResultBlock(x, expectedSin, tailorSum, difference);
        }
    }

    else
    {
        for (x; (x + step) >= (y + step); x += step)
        {
            double tailorSum = 0;
            int counter = 0;
            double delta = 0;
            double difference = 0;
            double expectedSin = 0;
            double xC = (x * pi) / (180.);
            for (counter == 0;; counter++)
            {
                if (counter % 2 == 0)
                {
                    delta = (pow(xC, 2. * counter + 1.)) / factorial(2 * counter + 1);
                }
                else
                {
                    delta = -(pow(xC, 2. * counter + 1.)) / factorial(2 * counter + 1);
                }
                if (fabs(delta) < epsilon)
                {
                    break;
                }
                tailorSum += delta;
            }
            tailorSum = roundWithPrecision(epsilon, tailorSum);
            expectedSin = rounded((sin(xC)));
            difference = (rounded(expectedSin) - tailorSum);

            printResultBlock(x, expectedSin, tailorSum, difference);
        }
    }
}

static double factorial(int counter)
{
    return (counter < 2) ? 1 : counter * factorial(counter - 1);
}

void printResultBlock(double x, double expected, double tailorSum, double difference)
{
    printf("---x--- \t ---sin(x)--- \t ---sin(Tailor)--- \t ---sin(x)-sin(Tailor)---\n");
    printf("%lf \t %.10lf \t %.10lf \t\t %.e or %.10lf\n", x, expected, tailorSum, difference, difference);
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
            key = NOT_THE_NEEDED_BUTTON;
        }
    } while (key == NOT_THE_NEEDED_BUTTON);
}

double rounded(double a)
{
    a = a * 1e10;
    a = round(a);
    a = a / 1e10;
    return a;
}

double roundWithPrecision(double epsilon, double tailorSum)
{
    double trick = 1 / epsilon;
    tailorSum = tailorSum * trick;
    tailorSum = round(tailorSum);
    tailorSum = tailorSum / trick;
    return tailorSum;
}