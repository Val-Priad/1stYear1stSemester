#define R_L_SERIES 1
#define R_C_SERIES 2
#define R2_C_L_SERIES 3
#define R2_L_SERIES_R1_C_PARALLEL 4
#define NEW_LINE 10
#define NOT_NEEDED_NUMBER 0
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define EPSILON 1e-15
#define G_S "\033[0;32m"
#define R_S "\033[0;31m"
#define F "\033[0m"
#define MIN 1e-5
#define MAX 10

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <ctype.h>
#include <math.h>

typedef struct
{
    double resistance1;
    double resistance2;
    double capacitance;
    double inductance;
    double minFrequency;
    double maxFrequency;
    double step;
} RLC_Circuit;

typedef struct
{
    double real;
    double imaginary;
} Complex;

void greeting();
int selectCircuit();
RLC_Circuit enterParametersBlock(int chosenCircuit);
double getValue(double a);
bool isValidation(int scanfResult, double value);
void errorPrint();
bool isInputAdequate(double minFrequency, double maxFrequency, double step);
void calculationShowBlock(RLC_Circuit circuit, int chosenCircuit);
void R_L_Series(RLC_Circuit circuit);
void R_C_Series(RLC_Circuit circuit);
void R2_C_L_Series(RLC_Circuit circuit);
void R2_L_Series_R1_C_Parallel(RLC_Circuit circuit);
double rounded(double a);
void printResult(double currentFrequency, Complex complexResistance, double f0);
bool isContinue();

int main()
{
    greeting();
    do
    {
        int chosenCircuit = selectCircuit();
        RLC_Circuit circuit = enterParametersBlock(chosenCircuit);
        calculationShowBlock(circuit, chosenCircuit);
    } while (isContinue());

    return 0;
}

void greeting()
{
    printf("\n");
    printf("Program for calculating the complex resistance of oscillatory circuits\n");
    printf("depending on the current frequency.\n\n");
    printf(G_S "-------------------------------------------\n" F);
    printf("Possible types of oscillatory circuits:\n");
    printf("1. R, L in series, C in parallel\n");
    printf("2. R, C in series, L in parallel\n");
    printf("3. R2, C, L in series, R1 in parallel\n");
    printf("4. R2, L in series, R1, C in parallel\n\n");
    printf(G_S "-------------------------------------------\n" F);
    printf("The user can choose the type of oscillatory circuit\n");
    printf("and input the component values to compute the resistance.\n");
    printf("\n");
}

int selectCircuit()
{
    printf("Plese, chose the oscillatory circuit, that you want to count:\n");
    int keyForOption = 0;
    do
    {
        int pressedButton = _getch();
        pressedButton = pressedButton - '0';
        switch (pressedButton)
        {
        case R_L_SERIES:
            printf(G_S "You have chosen:" F " R, L in series, C in parallel\n\n");
            return R_L_SERIES;
        case R_C_SERIES:
            printf(G_S "You have chosen:" F " R, C in series, L in parallel\n");
            return R_C_SERIES;
        case R2_C_L_SERIES:
            printf(G_S "You have chosen:" F " R2, C, L in series, R1 in parallel\n");
            return R2_C_L_SERIES;
        case R2_L_SERIES_R1_C_PARALLEL:
            printf(G_S "You have chosen:" F " R2, L in series, R1, C in parallel\n");
            return R2_L_SERIES_R1_C_PARALLEL;
        default:
            printf("Please, choose the option\n");
            keyForOption = NOT_NEEDED_NUMBER;
            break;
        }
    } while (keyForOption == NOT_NEEDED_NUMBER);
}

RLC_Circuit enterParametersBlock(int chosenCircuit)
{
    double resistance1 = 0;
    double resistance2 = 0;
    double capacitance = 0;
    double inductance = 0;
    double minFrequency = 0;
    double maxFrequency = 0;
    double step = 0;
    bool isValid = true;
    printf("Diapasone for all values [1e-5, 10]\n");
    if (chosenCircuit < R2_C_L_SERIES)
    {
        printf("Enter the Resistance(R): ");
        resistance1 = getValue(resistance1);
    }
    else
    {
        printf("Enter the Resistance(R1): ");
        resistance1 = getValue(resistance1);

        printf("Enter the Resistance(R2): ");
        resistance2 = getValue(resistance2);
    }

    printf("Enter the capacitance in microfarads(C): ");
    capacitance = getValue(capacitance);

    printf("Enter the inductance in millihenry(L): ");
    inductance = getValue(inductance);
    printf(G_S "----------------------------------------\n" F);
    do
    {
        printf("Enter the minFrequency: ");
        minFrequency = getValue(minFrequency);

        printf("Enter the maxFrequency: ");
        maxFrequency = getValue(maxFrequency);

        printf("Enter the step: ");
        step = getValue(step);
    } while (!isInputAdequate(minFrequency, maxFrequency, step));
    printf(G_S "----------------------------------------\n" F);
    RLC_Circuit circuit = {resistance1, resistance2, capacitance, inductance, minFrequency, maxFrequency, step};
    return circuit;
}

double getValue(double a)
{
    bool isValid = true;
    int scanfResult = 0;
    do
    {
        scanfResult = scanf("%lf", &a);
        isValid = isValidation(scanfResult, a);
        fflush(stdin);
    } while (!isValid);
    return a;
}

bool isValidation(int scanfResult, double value)
{
    int received_ASCII_code = getchar();
    if (scanfResult != 1)
    {
        errorPrint();
        return false;
    }
    else if (received_ASCII_code != NEW_LINE && !isdigit(received_ASCII_code))
    {
        errorPrint();
        return false;
    }
    if (value < MIN || value > MAX)
    {
        errorPrint();
        return false;
    }
    return true;
}

void errorPrint()
{
    printf(R_S "Error, you entered not a number\n" F);
    printf("Please, enter the value again:");
}

bool isInputAdequate(double minFrequency, double maxFrequency, double step)
{
    if (minFrequency == maxFrequency)
    {
        printf(R_S "Extreme parameters cannot be equal\n" F);
        return false;
    }
    if (minFrequency < maxFrequency)
    {
        if ((minFrequency + step) > maxFrequency)
        {
            printf(R_S "You entered too big step\n" F);
            return false;
        }
    }
    if (minFrequency > maxFrequency)
    {

        printf(R_S "Initial frequency cannot be greater than last\n" F);
        return false;
    }
    if (step < 0.1)
    {
        return false;
    }
    return true;
}

void calculationShowBlock(RLC_Circuit circuit, int chosenCircuit)
{
    switch (chosenCircuit)
    {
    case R_L_SERIES:
        R_L_Series(circuit);
        break;

    case R_C_SERIES:
        R_C_Series(circuit);
        break;
    case R2_C_L_SERIES:
        R2_C_L_Series(circuit);
        break;
    case R2_L_SERIES_R1_C_PARALLEL:
        R2_L_Series_R1_C_Parallel(circuit);
        break;

    default:
        printf("Error, unexpected situation\n");
        break;
    }
}

void R_L_Series(RLC_Circuit circuit)
{
    double currentFrequency = circuit.minFrequency;
    double f0 = 1. / (2. * M_PI * sqrt(circuit.inductance * circuit.capacitance));
    double omega = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
    Complex complexResistance;
    for (currentFrequency; currentFrequency <= circuit.maxFrequency; currentFrequency += circuit.step)
    {
        omega = 2. * M_PI * currentFrequency;
        a = circuit.inductance / circuit.capacitance;
        b = -circuit.resistance1 / (omega * circuit.capacitance);
        c = circuit.resistance1;
        d = omega * circuit.inductance - (1. / (omega * circuit.capacitance));
        complexResistance.real = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
        complexResistance.imaginary = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
        printResult(currentFrequency, complexResistance, f0);
    }
}

void R_C_Series(RLC_Circuit circuit)
{
    double currentFrequency = circuit.minFrequency;
    double f0 = 1. / (2. * M_PI * sqrt(circuit.inductance * circuit.capacitance));
    double omega = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
    Complex complexResistance;
    for (currentFrequency; currentFrequency <= circuit.maxFrequency; currentFrequency += circuit.step)
    {
        omega = 2 * M_PI * currentFrequency;
        a = circuit.inductance / circuit.capacitance;
        b = circuit.resistance1 / (omega * circuit.capacitance);
        c = circuit.resistance1;
        d = omega * circuit.inductance - (1. / (omega * circuit.capacitance));
        complexResistance.real = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
        complexResistance.imaginary = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
        printResult(currentFrequency, complexResistance, f0);
    }
}

void R2_C_L_Series(RLC_Circuit circuit)
{
    double currentFrequency = circuit.minFrequency;
    double f0 = 1. / (2. * M_PI * sqrt(circuit.inductance * circuit.capacitance));
    double omega = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
    Complex complexResistance;
    for (currentFrequency; currentFrequency <= circuit.maxFrequency; currentFrequency += circuit.step)
    {
        omega = 2 * M_PI * currentFrequency;
        a = circuit.resistance1 * circuit.resistance2;
        b = circuit.resistance1 * (omega * circuit.inductance - (1. / (omega * circuit.capacitance)));
        c = circuit.resistance1 + circuit.resistance2;
        d = (omega * circuit.inductance) - (1. / (omega * circuit.capacitance));
        complexResistance.real = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
        complexResistance.imaginary = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
        printResult(currentFrequency, complexResistance, f0);
    }
}

void R2_L_Series_R1_C_Parallel(RLC_Circuit circuit)
{
    double currentFrequency = circuit.minFrequency;
    double f0 = 1. / (2. * M_PI * sqrt(circuit.inductance * circuit.capacitance));
    double omega = 0;
    double a = 0;
    double b = 0;
    double c = 0;
    double d = 0;
    Complex complexResistance;
    for (currentFrequency; currentFrequency <= circuit.maxFrequency; currentFrequency += circuit.step)
    {
        omega = 2. * M_PI * currentFrequency;
        a = (circuit.resistance1 * circuit.resistance2) + (circuit.inductance / circuit.capacitance);
        b = (omega * circuit.inductance * circuit.resistance1) - (circuit.resistance2 / (omega * circuit.capacitance));
        c = circuit.resistance1 + circuit.resistance2;
        d = (omega * circuit.inductance) - (1. / (omega * circuit.capacitance));
        complexResistance.real = (a * c + b * d) / (pow(c, 2) + pow(d, 2));
        complexResistance.imaginary = (b * c - a * d) / (pow(c, 2) + pow(d, 2));
        printResult(currentFrequency, complexResistance, f0);
    }
}

double rounded(double a)
{
    double trick = 0;
    double intPart = 0;
    intPart = floor(a);
    a = a - intPart;
    trick = (long long int)(a * (1 / EPSILON) * 10) % 10;
    a = a * (1 / EPSILON);
    a = round(a);
    a = a / (1 / EPSILON);
    if (trick > 4)
    {
        return a - EPSILON + intPart;
    }
    else if (trick < -4)
    {
        return a + EPSILON + intPart;
    }
    return a + intPart;
}

void printResult(double currentFrequency, Complex complexResistance, double f0)
{
    printf("---currentFrequency--- \t\t ---complex resistance--- \t      ---f0---\n");
    printf("\t%lf \t %.15lf%+.15lfi \t %.15lf\n", currentFrequency, rounded(complexResistance.real), rounded(complexResistance.imaginary), rounded(f0));
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
