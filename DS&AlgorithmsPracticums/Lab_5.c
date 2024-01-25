#include <stdio.h>
#include <math.h>

void main()
{
    double y = 0;
    double x = -3;
    double saver = 0;
    while (x <= 6.1)
    {
        // printf("x<=6 (True) x=%.1lf\n", x);
        if (x < 1)
        {
            // printf("%.1lf >= 1 (False)\n", x);
            // printf("y = 0\n");
            // printf("i = 1\n");
            y = 0;
            int i = 1;
            while (i <= 8)
            {
                saver = y;
                // printf("%d<=8; (True)\n", i);
                y += (x + i) / (x - i);
                // printf("y+= (%.1lf + %d) / (%.1lf - %d) = %lf + %lf = %lf\n", x, i, x, i, saver, (y - saver), y);
                i++;
                // printf("i++ (i = %d)\n", i);
            }
            // printf("%d<=8; (False)\n", i);
            printf("y =%lf\n\n", y);
        }
        if (x >= 1)
        {
            // printf("%.1lf >= 1 (True)\n", x);
            y = pow(x, 2) + 5 * x + 4;
            // printf("pow(%.1lf, 2) + 5 * x + 4 = %.2lf\n", x, y);
            printf("y =%lf\n\n", y);
        }
        saver = x;
        x += 0.2;
        // printf("x+=0.2 = %.1lf + 0.2 = %.1lf\n", saver, x);
    }
}