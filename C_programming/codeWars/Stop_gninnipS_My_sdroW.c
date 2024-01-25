#include <stdio.h>
#include <string.h>
#include <ctype.h>

void spin_words(char *sentence, char *result);

void main()
{

    char sentence[] = "Hey fellow warriors";
    char result[strlen(sentence)];
    spin_words(sentence, result);
    printf("%s", result);
}
void spin_words(char *sentence, char *result)
{
    int leng = strlen(sentence);
    int whenSplit = -1;
    int k = 0;
    int saveI = 0;
    for (int i = 0; i <= leng; i++)
    {
        if (isspace(sentence[i]) || sentence[i] == '\0')
        {
            result[i] = sentence[i];
            if (i - whenSplit > 5)
            {
                saveI = i;
                k = whenSplit + 1;
                for (i; i > whenSplit + 1; i--)
                {
                    result[k] = sentence[i - 1];
                    k++;
                }
                i = saveI;
            }
            whenSplit = i;
        }
        else
        {
            result[i] = sentence[i];
        }
    }
}
//  <----  hajime!
