#include <stdio.h>

int solution(int number);

void main()
{

    printf("%d", solution(10));
}
int solution(int number)
{
    if (number < 1)
    {
        return 0;
    }
    int sum = 0;
    int searcher = 0;
    do
    {
        if (searcher % 3 == 0 || searcher % 5 == 0)
        {
            sum += searcher;
        }
        searcher++;
    } while (searcher != number);
    return sum;
    //  <----  hajime!
}
