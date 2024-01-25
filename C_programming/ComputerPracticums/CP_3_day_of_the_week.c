#define RED_START "\033[1;31m"
#define RED_FINISH "\033[1;0m"
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define NOT_THE_NEEDED_BUTTON 1
#define VALIDATION_FOR_DAY 0
#define VALIDATION_FOR_MONTH 1
#define VALIDATION_FOR_YEAR 2
#define STATIC_UPDATE 3
#define MONDAY 0
#define TUESDAY 1
#define WEDNESDAY 2
#define THURSDAY 3
#define FRIDAY 4
#define SATURDAY 5
#define SUNDAY 6
#define YEAR_lIMIT_MIN 1583
#define YEAR_LIMIT_MAX 9999
#define LIMIT_FOR_MONTH 13
#define NEW_LINE 10

#include <stdio.h>
#include <ctype.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

bool isEnterDataBlock(int *day, int *month, int *year);
bool isValidation(int scanfResult, int ourNum, int whatValid);
void ourCalculationBlock(int day, int month, int year);
void printResults(int dayOfTheWeek, int dayToShow, int monthToShow, int yearToShow);
int limitForDays(int *ptrMonthForLimit, int *ptrYearForLimit);

void main()
{
    printf("\nThis program calculates the Gregorian calendar[1583;9999] day of the week by user input\n\n");

    bool isContinue = true;

    do
    {
        int day = 0;
        int month = 0;
        int year = 0;

        bool isEverythingWell = isEnterDataBlock(&day, &month, &year);
        if (isEverythingWell == true)
        {
            ourCalculationBlock(day, month, year);
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

bool isEnterDataBlock(int *day, int *month, int *year)
{
    bool isValid = true;

    printf("\nEnter the year number: ");
    int scanfResult = scanf("%d", year);
    int whatValid = VALIDATION_FOR_YEAR;
    isValid = isValidation(scanfResult, *year, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the month number: ");
    scanfResult = scanf("%d", month);
    whatValid = VALIDATION_FOR_MONTH;
    isValid = isValidation(scanfResult, *month, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }

    printf("\nEnter the day number: ");
    scanfResult = scanf("%d", day);
    whatValid = VALIDATION_FOR_DAY;
    isValid = isValidation(scanfResult, *day, whatValid);
    fflush(stdin);
    if (isValid == false)
    {
        printf(RED_START "\nRestarting the program..." RED_FINISH);
        return false;
    }
    return true;
}

bool isValidation(int scanfResult, int ourNum, int whatValid)
{
    int limit = 0;
    int static monthForLimit = 0;
    int static yearForLimit = 0;
    int *ptrYearForLimit = &yearForLimit;
    int *ptrMonthForLimit = &monthForLimit;
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

    if ((ourNum < YEAR_lIMIT_MIN || ourNum > YEAR_LIMIT_MAX) && whatValid == VALIDATION_FOR_YEAR)
    {
        printf("Error, you entered too big/too small year number\n");
        return false;
    }

    if (whatValid == VALIDATION_FOR_YEAR)
    {
        *ptrYearForLimit = ourNum;
    }

    if ((ourNum <= 0 || ourNum > LIMIT_FOR_MONTH) && whatValid == VALIDATION_FOR_MONTH)
    {
        printf("Error, you entered too big/too small month number\n");
        return false;
    }

    if (whatValid == VALIDATION_FOR_MONTH)
    {
        *ptrMonthForLimit = ourNum;
    }

    if ((ourNum <= 0 || ourNum > (limit = limitForDays(ptrMonthForLimit, ptrYearForLimit))) && whatValid == VALIDATION_FOR_DAY)
    {
        printf("Error, this day does not exist\n");
        return false;
    }
    return true;
}

void ourCalculationBlock(int day, int month, int year)
{
    int dayToShow = day;
    int monthToShow = month;
    int yearToShow = year;
    if (month <= 2)
    {
        year = year - 1;
        day = day + 3;
    }

    int dayOfTheWeek = ((day + year + (int)(year / 4) - (int)(year / 100) + (int)(year / 400) + (int)((31 * month + 10) / 12)) % 7);
    printResults(dayOfTheWeek, dayToShow, monthToShow, yearToShow);
}

int limitForDays(int *ptrMonthForLimit, int *ptrYearForLimit)
{
    int leep = 0;
    if (((*ptrYearForLimit % 100) != 0 && (*ptrYearForLimit % 4) == 0) || ((*ptrYearForLimit % 100) == 0 && (*ptrYearForLimit % 400) == 0))
    {
        leep = 1;
    }
    else
    {
        leep = 0;
    }
    if (*ptrMonthForLimit == 4 || *ptrMonthForLimit == 6 || *ptrMonthForLimit == 9 || *ptrMonthForLimit == 11)
    {
        return 30;
    }

    else if (*ptrMonthForLimit == 2 && leep == 1)
    {
        return 29;
    }
    else if (*ptrMonthForLimit == 2 && leep == 0)
    {
        return 28;
    }

    else
    {
        return 31;
    }
}

void printResults(int dayOfTheWeek, int dayToShow, int monthToShow, int yearToShow)
{
    printf("\nDate: %d.%d.%d\n", dayToShow, monthToShow, yearToShow);
    switch (dayOfTheWeek)
    {
    case MONDAY:
        printf("The day is Monday\n");
        break;
    case TUESDAY:
        printf("The day is Tuesday\n");
        break;
    case WEDNESDAY:
        printf("The day is Wednesday\n");
        break;
    case THURSDAY:
        printf("The day is Thursday\n");
        break;
    case FRIDAY:
        printf("The day is Friday\n");
        break;
    case SATURDAY:
        printf("The day is Saturday\n");
        break;
    case SUNDAY:
        printf("The day is Sunday\n");
        break;

    default:
        printf(RED_START "Error!\n" RED_FINISH);
        break;
    }
}