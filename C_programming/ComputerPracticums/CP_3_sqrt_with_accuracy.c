#define RED_START "\033[1;31m"
#define RED_FINISH "\033[1;0m"
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_THE_NEEDED_BUTTON 1
#define EPSILON_MIN 0.00000000000001
#define RADICAND_MIN_MINUS -1000000
#define RADICAND_MAX_MINUS -0.000000000001
#define RADICAND_MAX_PLUS 1000000
#define RADICAND_MIN_PLUS 0.000000000001
#define ROOT_MIN -100
#define ROOT_MAX 100
#define NEW_LINE 10

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

bool isEnterDataBlock(int *root, double *radicand, double *epsilon);
bool isRootValidation(int scanfResult, int root);
bool isRadicandValidation(int scanfResult, double radicand);
bool isEpsilonValidation(int scanfResult, double epsilon);
bool isInputAdequate(int *root, double *radicand);
void ourCalculationBlock(int root, double radicand, double epsilon);
void printResults(int counter, double yi);

void main()
{
    printf("\nThis program is made for counting the y=sqrt[k]{x} expression with your own accuracy\n\n");
    printf("The root(k) can only be in the diapason [-100;100] and cannot be 0\n");
    printf("Accuracy must be a real number [1.0E-14; 1) \n");
    printf("Radicand(x) [-1e+06; 1e-12)⋃(1e+12; 1e+06] can be:\n");
    printf("• If root is even and bigger than 0(k % 2 = 0, k>0), radicand can be only bigger or equal to zero(x>=0)\n");
    printf("• If root is odd and bigger than 0(k % 2 != 0, k>0), radicand can be any(x∈(-∞;∞))\n");
    printf("• If root is even and less than 0(k % 2 = 0, k<0), radicand can be only bigger than zero(x>0)\n");
    printf("• If root is odd and less than 0(k % 2 != 0, k<0), radicand can be any, except 0(x∈(-∞;∞)\\{0})\n");

    bool isContinue = true;

    do
    {
        int root = 0;
        double radicand = 0;
        double epsilon = 0;

        bool isEverythingWell = isEnterDataBlock(&root, &radicand, &epsilon);
        if (isEverythingWell == true)
        {
            ourCalculationBlock(root, radicand, epsilon);
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

bool isEnterDataBlock(int *root, double *radicand, double *epsilon)
{
    bool isValid = true;

    printf("\nEnter the root: ");
    int scanfResult = scanf("%d", root);
    isValid = isRootValidation(scanfResult, *root);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the radicand: ");
    scanfResult = scanf("%lf", radicand);
    isValid = isRadicandValidation(scanfResult, *radicand);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the accuracy: ");
    scanfResult = scanf("%lf", epsilon);
    isValid = isEpsilonValidation(scanfResult, *epsilon);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }
    isValid = isInputAdequate(root, radicand);
    if (isValid == false)
    {
        return false;
    }
    return true;
}

bool isRootValidation(int scanfResult, int root)
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
    if (root < -100 || root > 100 || root == 0)
    {
        printf("Error, you entered too big/too small or even root\n");
        return false;
    }
    return true;
}

bool isRadicandValidation(int scanfResult, double radicand)
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
    if (radicand > 0)
    {
        if (radicand < RADICAND_MIN_PLUS || radicand > RADICAND_MAX_PLUS)
        {
            printf("Error, you entered too big/too small Radicand\n");
            return false;
        }
    }
    if (radicand < 0)
    {
        if (radicand < RADICAND_MIN_MINUS || radicand > RADICAND_MAX_MINUS)
        {
            printf("Error, you entered too big/too small radicand\n");
            return false;
        }
    }

    return true;
}

bool isEpsilonValidation(int scanfResult, double epsilon)
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
    if (epsilon < EPSILON_MIN || epsilon >= 1)
    {
        printf("Error, you entered too big or negative accuracy\n");
        return false;
    }

    return true;
}

bool isInputAdequate(int *root, double *radicand)
{
    if (*root > 0 && *root % 2 == 0)
    {
        if (*radicand < 0)
        {
            printf(RED_START "\nIf root is even and bigger than 0(k % 2 = 0, k>0), radicand can be only bigger or equal to zero(x>=0)\n" RED_FINISH);
            return false;
        }
    }

    if (*root < 0 && *root % 2 == 0)
    {
        if (*radicand <= 0)
        {
            printf(RED_START "\nIf root is even and less than 0(k % 2 = 0, k<0), radicand can be only bigger than zero(x>0)\n" RED_FINISH);
            return false;
        }
    }

    if (*root < 0 && *root % 2 != 0)
    {
        if (*radicand == 0)
        {
            printf(RED_START "\nIf root is odd and less than 0(k % 2 != 0, k<0), radicand can be any, except 0(x∈(-∞;∞)\{0})\n" RED_FINISH);
            return false;
        }
    }
    return true;
}

void ourCalculationBlock(int root, double radicand, double epsilon)
{
    int rootTrick = 1;
    int radicandTrick = 1;
    double delta = 1;
    double yi = 1;
    int counter = 1;
    double trick = 0;
    if (root < 0)
    {
        root = -root;
        rootTrick = -1;
    }
    if (radicand < 0)
    {
        radicand = -radicand;
        radicandTrick = -1;
    }
    for (counter = 1;; counter++)
    {
        delta = (1.0 / root) * ((radicand / (pow(yi, root - 1.0))) - yi);
        if (fabs(delta) < epsilon)
        {
            break;
        }
        yi += delta;
    }
    printResults(counter, pow(yi, rootTrick) * radicandTrick);
}

void printResults(int counter, double yi)
{
    printf("Final iteration: %d, y: %lf, y in exponential form: %e\n", counter, yi, yi);
}