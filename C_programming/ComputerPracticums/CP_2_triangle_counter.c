#define MAX_ACCURACY 9
#define MAX_ACCURACY_For_Pe 4
#define COUNTING_LIMIT 6
#define ARRAY_LEN 6
#define VARIABLES_QUANTITY 3
#define VARIABLES_POSITION_QUANTITY 2
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define RED_START "\033[1;31m"
#define RED_FINISH "\033[1;0m"
#define STATIC_UPDATE 4

#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <conio.h>
#include <math.h>

bool isCorrectInput(char *string, float *floatingNum);
int calcAllNeeded(double a, double b, double c);
int printAllResults(double pe, double s, double ha, double hb, double hc, double ma, double mb, double mc, double ba, double bb, double bc);
int staticUpdate(int position);

int main(void)
{
    printf("\nЦя програма створена для обчислення периметру, площі, довжин медіан, висот та бісектрис заданого трикутника\n\n");
    printf("Програма приймає дійсні числа більші за нуль, максимальна кількість символів 4, все інше буде проігноровано\n");
    printf("Програма вважає пробіл після введеного рядка його кінцем, тому запис '123 hdf' буде читатися програмою як '123'\n");
    printf("Також не потрібно вводити знаки +-\n");
    printf("Програма не приймає експоненціальну форму числа та обчислює до 2 знаків після коми, вивід даних відбувається з точністю до 9 знаків після коми\n\n");

    bool isRepeat = true;
    do
    {
        float floatingNum = 0;
        char a[ARRAY_LEN];
        char b[ARRAY_LEN];
        char c[ARRAY_LEN];

        printf("Введіть сторону a:\n");
        scanf("%4s", a);
        fflush(stdin);

        printf("Введіть сторону b:\n");
        scanf("%4s", b);
        fflush(stdin);

        printf("Введіть сторону c:\n");
        scanf("%4s", c);
        fflush(stdin);
        int count;
        char *bigArray[VARIABLES_QUANTITY] = {a, b, c};

        for (count = 0; count <= VARIABLES_POSITION_QUANTITY; count++)
        {
            bool isOk = true;
            isOk = isCorrectInput(bigArray[count], &floatingNum);
            if (!isOk)
            {
                printf(RED_START "Введені не правильні дані!!!\nПерезпуск програми...\n...\n" RED_FINISH);
                break;
            }
            else
            {
                float perfectArray[ARRAY_LEN];
                static int position = 0;
                if (position == STATIC_UPDATE)
                {
                    position = staticUpdate(position);
                }
                perfectArray[position] = floatingNum;
                position++;
                if (position == VARIABLES_QUANTITY)
                {
                    position++;
                    double a = perfectArray[0];
                    double b = perfectArray[1];
                    double c = perfectArray[2];

                    if (a + b > c && a + c > b && b + c > a)
                    {
                        calcAllNeeded(a, b, c);
                    }
                    else
                    {
                        printf(RED_START "Трикутник не існує\nПерезпуск програми...\n...\n" RED_FINISH);
                        break;
                    }
                }
            }
        }
        int key;
        do
        {
            printf("\nЯкщо ви хочите продовжити, натисніть 'Enter'\n");
            key = _getch();
            if (key == ENTER_BUTTON)
            {
                isRepeat = true;
            }
            else if (key == EXIT_BUTTON)
            {
                isRepeat = false;
            }
            else
            {
                key = 1;
            }
        } while (key == 1);
    } while (isRepeat);
}
bool isCorrectInput(char *string, float *floatingNum)
{
    int stringReader = 0;
    int length = strlen(string);
    if (length > COUNTING_LIMIT)
    {
        return false;
    }
    char floatingNumBuffer[ARRAY_LEN];
    int floatingNum_nums = 0;
    while (stringReader < length)
    {
        if (string[stringReader] == '.')
        {
            floatingNumBuffer[floatingNum_nums] = '.';
            floatingNum_nums++;
            stringReader++;
        }
        if (!isdigit(string[stringReader]))
        {
            return false;
        }
        floatingNumBuffer[floatingNum_nums] = string[stringReader];
        floatingNum_nums++;
        stringReader++;
    }
    floatingNumBuffer[floatingNum_nums] = '\0';
    *floatingNum = atof(floatingNumBuffer);
    return true;
}
int calcAllNeeded(double a, double b, double c)
{
    double pe = a + b + c;
    double p = (a + b + c) / 2;
    double s = sqrt(p * (p - a) * (p - b) * (p - c));
    double ha = 2 * s / a;
    double hb = 2 * s / b;
    double hc = 2 * s / c;
    double ma = 0.5 * (sqrt(2 * pow(b, 2) + 2 * pow(c, 2) - pow(a, 2)));
    double mb = 0.5 * (sqrt(2 * pow(a, 2) + 2 * pow(c, 2) - pow(b, 2)));
    double mc = 0.5 * (sqrt(2 * pow(a, 2) + 2 * pow(b, 2) - pow(c, 2)));
    double ba = 2 / (b + c) * sqrt(b * c * p * (p - a));
    double bb = 2 / (a + c) * sqrt(a * c * p * (p - b));
    double bc = 2 / (b + a) * sqrt(b * a * p * (p - c));
    printAllResults(pe, s, ha, hb, hc, ma, mb, mc, ba, bb, bc);
    return 0;
}
int printAllResults(double pe, double s, double ha, double hb, double hc, double ma, double mb, double mc, double ba, double bb, double bc)
{
    printf("\nПериметр трикутника: %.*f\n\n", MAX_ACCURACY_For_Pe, pe);
    printf("Площа трикутника: %.*f\n\n", MAX_ACCURACY, s);
    printf("Висота до сторони а: %.*f\n\n", MAX_ACCURACY, ha);
    printf("Висота до сторони b: %.*f\n\n", MAX_ACCURACY, hb);
    printf("Висота до сторони c: %.*f\n\n", MAX_ACCURACY, hc);
    printf("Медіана до сторони a: %.*f\n\n", MAX_ACCURACY, ma);
    printf("Медіана до сторони b: %.*f\n\n", MAX_ACCURACY, mb);
    printf("Медіана до сторони c: %.*f\n\n", MAX_ACCURACY, mc);
    printf("Бісектриса до сторони a: %.*f\n\n", MAX_ACCURACY, ba);
    printf("Бісектриса до сторони b: %.*f\n\n", MAX_ACCURACY, bb);
    printf("Бісектриса до сторони c: %.*f\n\n", MAX_ACCURACY, bc);
    return 0;
}
int staticUpdate(int position)
{
    return 0;
}