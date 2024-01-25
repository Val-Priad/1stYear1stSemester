#define RED_START "\033[1;31m"
#define RED_FINISH "\033[1;0m"
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_THE_NEEDED_BUTTON 1
#define BOUNDARIES_MIN_NEGATIVE -1000000
#define BOUNDARIES_MAX_NEGATIVE -0.000000000001
#define BOUNDARIES_MAX_POSITIVE 1000000
#define BOUNDARIES_MIN_POSITIVE 0.000000000001
#define NEW_LINE 10

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

bool isEnterDataBlock(double *a, double *b, double *c);
bool isValidation(int scanfResult, double ourNum);
void ourCalculationBlock(double a, double b, double c);
void printResultsDiscrimPositive(double x1, double x2, double x3, double complex);
void printResultDiscrimNegative(double x1, double x2, double x3);

void main()
{
    printf("\nThis program is made for counting the root of the equation (x^3 + a*x^2 + b*x + c = 0)\n");
    printf("Boundaries: x x∈(-1e+06;1e+06)\n\n");

    bool isContinue = true;

    do
    {
        double a = 0;
        double b = 0;
        double c = 0;

        bool isEverythingWell = isEnterDataBlock(&a, &b, &c);
        if (isEverythingWell == true)
        {
            ourCalculationBlock(a, b, c);
        }

        int key = 0;
        do
        {
            printf("\nIf you want to continue, press 'enter', if you want to escape, press 'esc'\n");
            key = _getch();
            if (key == ENTER_BUTTON)
            {
                isContinue = true;
            }
            else if (key == EXIT_BUTTON)
            {
                isContinue = false;
            }
            else
            {
                key = NOT_THE_NEEDED_BUTTON;
            }
        } while (key == NOT_THE_NEEDED_BUTTON);

    } while (isContinue == true);
}

bool isEnterDataBlock(double *a, double *b, double *c)
{
    bool isValid = true;

    printf("\nEnter the a parameter: ");
    int scanfResult = scanf("%lf", a);
    isValid = isValidation(scanfResult, *a);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the b parameter: ");
    scanfResult = scanf("%lf", b);
    isValid = isValidation(scanfResult, *b);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the c parameter: ");
    scanfResult = scanf("%lf", c);
    isValid = isValidation(scanfResult, *c);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }
    return true;
}

bool isValidation(int scanfResult, double ourNum)
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
    if (ourNum != 0)
    {
        if (ourNum < 0)
        {
            if (ourNum < BOUNDARIES_MIN_NEGATIVE || ourNum > BOUNDARIES_MAX_NEGATIVE)
            {
                printf("Error, you entered too big/too small number\n");
                return false;
            }
        }
        else
        {
            if (ourNum < BOUNDARIES_MIN_POSITIVE || ourNum > BOUNDARIES_MAX_POSITIVE)
            {
                printf("Error, you entered too big/too small number\n");
                return false;
            }
        }
    }

    return true;
}

void ourCalculationBlock(double a, double b, double c)
{

    double trickForPinDiscrim = 0;
    double trickForQinDiscrim = 0;

    double p = -(pow(a, 2.) / 3.) + b;
    double q = 2. * (pow(a, 3.) / 27.) - ((a * b) / 3.) + c;

    double discrim = (pow(p, 3.) / 27.) + (pow(q, 2) / 4.);

    if (discrim >= 0)
    {
        double A = cbrt(-(q / 2.) + sqrt(discrim));
        double B = cbrt(-(q / 2.) - sqrt(discrim));

        double y1 = A + B;
        double complex = ((A - B) / 2.) * sqrt(3.);
        double y2 = -((A + B) / 2.);
        double y3 = -((A + B) / 2.);
        double x1 = y1 - (a / 3.);
        double x2 = y2 - (a / 3.);
        double x3 = y3 - (a / 3.);
        printResultsDiscrimPositive(x1, x2, x3, complex);
    }
    else
    {
        const double pi = 3.14159265358979323846;
        double r = sqrt(-((pow(p, 3.)) / 27.));
        double angle = acos(-(q / (2 * r)));
        double y1 = 2. * fabs(cbrt(r)) * cos(angle / 3.);
        double y2 = 2. * fabs(cbrt(r)) * cos((angle + (2. * pi)) / 3.);
        double y3 = 2. * fabs(cbrt(r)) * cos((angle + (4. * pi)) / 3.);
        double x1 = y1 - (a / 3.);
        double x2 = y2 - (a / 3.);
        double x3 = y3 - (a / 3.);
        printResultDiscrimNegative(x1, x2, x3);
    }
}
void printResultsDiscrimPositive(double x1, double x2, double x3, double complex)
{
    printf("x1: %g\n", x1);
    printf("x2: %g + %lfi\n", x2, complex);
    printf("x3: %g - %lfi\n", x3, complex);
}

void printResultDiscrimNegative(double x1, double x2, double x3)
{
    printf("x1: %g\n", x1);
    printf("x2: %g\n", x2);
    printf("x3: %g\n", x3);
}
