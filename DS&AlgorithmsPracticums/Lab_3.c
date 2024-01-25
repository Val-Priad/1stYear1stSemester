#include <stdio.h>
#include <math.h>
void helloUser();
void allOtherOperations();
void inputData(double *xPointer, double *accuracyPointer);
void countingBlock(double *xPointer, double *accuracyPointer);
void printResults(double sumOfAll, int n, double previousNum, double ourCalculatedNum);

void main()
{
    do
    {
        helloUser();
        allOtherOperations();
    } while (1);
}
void helloUser()
{
    printf("\n\nThis program is made for counting sum of mathematical sequence with user accuracy:\n");
    printf("Our mathematical sequance is:\n");
    printf("Sum(-1)^n*(1^(2n-1))/(4n^2-1)\n\n");
}
void allOtherOperations()
{
    double x = 0, *xPointer = &x;
    double accuracy = 0, *accuracyPointer = &accuracy;
    inputData(xPointer, accuracyPointer);
    countingBlock(xPointer, accuracyPointer);
}
void inputData(double *xPointer, double *accuracyPointer)
{
    printf("Enter the x value: ");
    scanf("%lf", xPointer);
    printf("Enter the accuracy value: ");
    scanf("%lf", accuracyPointer);
}
void countingBlock(double *xPointer, double *accuracyPointer)
{
    double sumOfAll = 0;
    double ourCalculedNum = 0;
    double previousNum = 0;
    int n = 0;
    int thing = 0;
    double trickForX = (*xPointer > 0) ? (pow(*xPointer, (2 * n - 1))) : (pow(fabs(*xPointer), (2 * n - 1)) * -1);
    if ((n) % 2 != 0)
    {
        thing = -1;
    }
    else
    {
        thing = 1;
    }
    ourCalculedNum = thing * ((trickForX) / (4 * pow(n, 2) - 1));
    sumOfAll += ourCalculedNum;
    printf("Iteration is: %d, num is: %lf, sum is: %lf\n", n + 1, ourCalculedNum, sumOfAll);
    n++;
    while (fabs(ourCalculedNum - previousNum) > *accuracyPointer)
    {
        if ((n) % 2 != 0)
        {
            thing = -1;
        }
        else
        {
            thing = 1;
        }
        double trickForX = (*xPointer > 0) ? (pow(*xPointer, (2 * n - 1))) : (pow(fabs(*xPointer), (2 * n - 1)) * -1);
        previousNum = ourCalculedNum;
        ourCalculedNum = thing * ((trickForX) / (4 * pow(n, 2) - 1));
        sumOfAll += ourCalculedNum;
        printf("\nIteration is: %d, num is: %lf, sum is: %lf\n", n + 1, ourCalculedNum, sumOfAll);
        printf("pNum = num = %lf\n", previousNum);
        printf("num = pow(-1,%d) * ((pow(%lf, (2 * %d - 1))) / (4 * pow(%d, 2) - 1))=%lf\n", n, *xPointer, n, n, ourCalculedNum);
        printf("sum +=num= %lf (!!!+(%lf))\n", sumOfAll, ourCalculedNum);
        printf("n++(n=%d)\n", n + 1);
        printf("fabs(%lf -(%lf))= %lf (fabs(%lf) > %lf)\n\n", ourCalculedNum, previousNum, (ourCalculedNum - previousNum), (ourCalculedNum - previousNum), *accuracyPointer);
        n++;
    }
    printResults(sumOfAll, n, previousNum, ourCalculedNum);
}
void printResults(double sumOfAll, int n, double previousNum, double ourCalculatedNum)
{
    printf("\nSum of mathematical sequence is: %lf, iteration is: %d, ourLastNum is: %lf, previousNum is: %lf", sumOfAll, n - 1, ourCalculatedNum, previousNum);
}
