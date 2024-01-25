#define NOT_NEEDED_NUMBER 0
#define EXIT_BUTTON 27
#define ENTER_BUTTON 13
#define YES 121
#define GRN "\033[0;32m"
#define HGRN "\033[0;92m"
#define CYN "\033[0;36m"
#define RED "\033[0;31m"
#define RESET "\033[0m"
#define UP 72
#define DOWN 80
#define LEFT 75
#define RIGHT 77
#define ROWS 4
#define COLS 3
#define CREATE_FILE 0
#define READ_FILE 1
#define DELETE_FILE 2
#define CREATE_NEW_NOTE 3
#define INSERT_NOTE 4
#define REWRITE_NOTE 5
#define READ_NOTE 6
#define DELETE_NOTE 7
#define SORT_NOTES_IN_FILE 8
#define HELP 9
#define AUTHOR 10
#define EXIT 11
#define MAX_FILENAME_LENGTH 255
#define MIN 0
#define MAX 9 * 10e9
#define NEW_LINE 10
#define MAX_NAME_LENGTH 36
#define MAX_RECORDS 50
#define ASCENDING 49
#define DESCENDING 50
#define PLACE_NAME 49
#define PLACE_SIZE 50
#define PLACE_POPULATION 51
#define SHOW true
#define NOT_SHOW false

#include <stdio.h>
#include <conio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

FILE *file = NULL;
char nameOfTheFile[MAX_FILENAME_LENGTH];
char currentFileName[MAX_FILENAME_LENGTH];
typedef struct
{
    char place[MAX_NAME_LENGTH];
    double size;
    double population;
    int number;

} RECORD;

RECORD records[MAX_RECORDS];
int howSortInsert = 0;
int whatToSortKeyInsert = 0;

void menu();
void createFile();
void readFile();
void deleteFile();
void createNewNote();
void insertNote();
void rewriteNote();
void readNote();
void deleteNote();
void sortNotesInFile();
void helpInfo();
void authorInfo();
void showCurrentFile();
bool isEmpty();
double getValue(double a);
double getValueInt(int a);
bool isValidation(int scanfResult, double value);
bool isValidationInt(int scanfResult, int value);
void errorPrint();
bool makeAList(int *recordCount, char *name);
bool isInputAdequate(char *buffer, char *tempBuffer);
void creatingnNoteAppend();
int whatAndSort(int howSort, int recordCount);
int sortBlock(int howSort, int whatToSortKey, int recordCount, bool isShow);
int compareByNameAsc(const void *a, const void *b);
int compareByNameDesc(const void *a, const void *b);
int compareBySizeAsc(const void *a, const void *b);
int compareBySizeDesc(const void *a, const void *b);
int compareByPopulationAsc(const void *a, const void *b);
int compareByPopulationDesc(const void *a, const void *b);
void rewriteNoteRewriting(int recordCount);
void readNoteReading(int recordCount);

int main()
{
    menu();
    return 0;
}

void menu()
{
    char *menu[ROWS][COLS] =
        {
            "   Create File   ", "    Read File    ", "   Delete File    ",
            " Create New Note ", "   Insert Note   ", "   Rewrite Note   ",
            "    Read Note    ", "   Delete Note   ", "Sort Notes In File",
            "      Help       ", "     Author      ", "       Exit       "};
    int activeMenuI = 0;
    int activeMenuJ = 0;
    int keyForOption = 0;
    printf("————————————————————————————————————————————————————————————————————\n");
    printf("|");
    printf(GRN "Please, read 'Help' before using the program                      " RESET);
    printf("|\n");
    printf("|");
    printf(GRN "Будь ласка, прочитайте розділ 'Help' перед використанням програми " RESET);
    printf("|\n");
    printf("————————————————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();

    do
    {
        system("CLS");
        showCurrentFile();
        for (int i = 0; i < ROWS; i++)
        {
            printf("\n");
            printf("————————————————————————————————————————————————————————\n");
            for (int j = 0; j < COLS; j++)
            {
                printf("|");
                if (activeMenuI == i && activeMenuJ == j)
                {
                    printf(HGRN "%s" RESET, menu[i][j]);
                }
                else
                {
                    printf("%s", menu[i][j]);
                }
            }
            printf("|");
        }
        printf("\n————————————————————————————————————————————————————————\n");

        printf("\n");
        int pressedButton = _getch();
        if (pressedButton == 0)
        {
            pressedButton = _getch();
        }

        switch (pressedButton)
        {
        case UP:
            if (activeMenuI > 0)
            {
                activeMenuI--;
            }
            break;
        case DOWN:
            if (activeMenuI < ROWS - 1)
            {
                activeMenuI++;
            }
            break;
        case LEFT:
            if (activeMenuJ > 0)
            {
                activeMenuJ--;
            }
            break;
        case RIGHT:
            if (activeMenuJ < COLS - 1)
            {
                activeMenuJ++;
            }
            break;
        case ENTER_BUTTON:
            int chosenMode = activeMenuI * COLS + activeMenuJ;
            switch (chosenMode)
            {
            case CREATE_FILE:
                createFile();
                break;
            case READ_FILE:
                readFile();
                break;
            case DELETE_FILE:
                deleteFile();
                break;
            case CREATE_NEW_NOTE:
                createNewNote();
                break;
            case INSERT_NOTE:
                insertNote();
                break;
            case REWRITE_NOTE:
                rewriteNote();
                break;
            case READ_NOTE:
                readNote();
                break;
            case DELETE_NOTE:
                deleteNote();
                break;
            case SORT_NOTES_IN_FILE:
                sortNotesInFile();
                break;
            case HELP:
                helpInfo();
                break;
            case AUTHOR:
                authorInfo();
                break;
            case EXIT:
                exit(0);
                break;
            default:
                printf(RED "Unexpected behavior\n" RESET);
                break;
            }

            break;
        case EXIT_BUTTON:
            exit(0);
        default:
            keyForOption = NOT_NEEDED_NUMBER;
            break;
        }
    } while (keyForOption == NOT_NEEDED_NUMBER);
}

void createFile()
{
    printf("————————————————————————————————————————————————————————\n");
    printf("Enter the name of the file that you want to create: ");

    char nameOfTheFile[MAX_FILENAME_LENGTH];
    scanf("%255s", nameOfTheFile);
    strcat(nameOfTheFile, ".txt");
    int key = 0;

    if ((file = fopen(nameOfTheFile, "r")) != NULL)
    {
        printf("The file already exists. Do you really want to create a new file with the exact name?\n");
        printf(RED "Be cautious, the previous file will be removed in this instance\n" RESET);
        printf("If you want to reuse current file name, press 'y', if not - any other button\n");
        key = _getch();
        fclose(file);
    }

    if (key == YES || key == 0)
    {
        if ((file = fopen(nameOfTheFile, "w")) == NULL)
        {
            printf(RED "Error occurred while opening the file\n" RESET);
        }
        else
        {
            strcpy(currentFileName, nameOfTheFile);
            printf(GRN "File was created successfully\n" RESET);
        }
        fclose(file);
    }
    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void readFile()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to read current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            if ((file = fopen(currentFileName, "r")) != NULL && !isEmpty())
            {
                char sign;
                for (int i = 0; i < recordCount; i++)
                {
                    printf("Name:%s Size:%g Population:%g\n", records[i].place, records[i].size, records[i].population);
                }
                printf("\n");
                fclose(file);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int recordCount = 0;
        if (makeAList(&recordCount, nameOfTheFile))
        {
            if ((file = fopen(nameOfTheFile, "r")) != NULL && !isEmpty())
            {
                char sign;
                for (int i = 0; i < recordCount; i++)
                {
                    printf("Name:%s Size:%g Population:%g\n", records[i].place, records[i].size, records[i].population);
                }
                printf("\n");
                fclose(file);
                strcpy(currentFileName, nameOfTheFile);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }

    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void deleteFile()
{

    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want delete current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int success = 0;
        if ((success = unlink(currentFileName)) == 0)
        {
            printf(GRN "File was successfuly deleted\n" RESET);
            strcpy(currentFileName, "");
        }
        else
        {
            printf(RED "Something went wrong during the file deleting process.\n" RESET);
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int success = 0;
        if ((success = unlink(nameOfTheFile)) == 0)
        {
            printf(GRN "File was successfuly deleted\n" RESET);
        }
        else
        {
            printf(RED "Something went wrong during the file deleting process.\n" RESET);
        }
    }
    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void createNewNote()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to create new note in current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        if ((file = fopen(currentFileName, "a")) != NULL)
        {
            creatingnNoteAppend();
            fclose(file);
        }
        else
        {
            printf(RED "Something went wrong\n" RESET);
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        char sign;
        if ((file = fopen(nameOfTheFile, "r")) != NULL && (file = fopen(nameOfTheFile, "a")) != NULL)
        {
            creatingnNoteAppend();
            fclose(file);
            strcpy(currentFileName, nameOfTheFile);
        }
        else
        {
            printf(RED "Something went wrong\n" RESET);
        }
    }

    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void insertNote()
{
    printf("————————————————————————————————————————————————————————\n");

    if (howSortInsert == 0 || whatToSortKeyInsert == 0)
    {
        printf(RED "You can't insert the note while you haven't sorted the data in the file\n" RESET);
    }
    else
    {
        int key = 0;
        if (strlen(currentFileName) > 0)
        {
            if ((file = fopen(currentFileName, "a")) != NULL)
            {
                creatingnNoteAppend();
                fclose(file);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            sortBlock(howSortInsert, whatToSortKeyInsert, recordCount, NOT_SHOW);
            if ((file = fopen(currentFileName, "w")) != NULL)
            {
                fseek(file, 0, SEEK_SET);

                for (int i = 0; i < recordCount; ++i)
                {
                    fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
                }

                fclose(file);
                strcpy(currentFileName, nameOfTheFile);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }

    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void rewriteNote()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to rewrite note in current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            if ((file = fopen(currentFileName, "r+")) != NULL && !isEmpty())
            {
                fclose(file);
                if ((file = fopen(currentFileName, "w")) != NULL)
                {
                    rewriteNoteRewriting(recordCount);
                }
                else
                {
                    printf(RED "Something went wrong during opening the file\n" RESET);
                }
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int recordCount = 0;
        if (makeAList(&recordCount, nameOfTheFile))
        {
            if ((file = fopen(nameOfTheFile, "r+")) != NULL && !isEmpty())
            {
                fclose(file);
                if ((file = fopen(nameOfTheFile, "w")) != NULL)
                {
                    rewriteNoteRewriting(recordCount);
                    strcpy(currentFileName, nameOfTheFile);
                }
                else
                {
                    printf(RED "Something went wrong during opening the file\n" RESET);
                }
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }

    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void readNote()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to read note in current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            if ((file = fopen(currentFileName, "r+")) != NULL && !isEmpty())
            {
                readNoteReading(recordCount);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int recordCount = 0;
        if (makeAList(&recordCount, nameOfTheFile))
        {
            if ((file = fopen(nameOfTheFile, "r+")) != NULL && !isEmpty())
            {
                readNoteReading(recordCount);
                strcpy(currentFileName, nameOfTheFile);
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }

    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void deleteNote()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to delete note in current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            if ((file = fopen(currentFileName, "r")) != NULL && !isEmpty())
            {
                fclose(file);
                if ((file = fopen(currentFileName, "w+")) != NULL)
                {
                    printf("Please, enter the number of the note, that you want to delete: ");
                    int numberOfnote = getValueInt(numberOfnote);
                    numberOfnote--;
                    if (numberOfnote >= 0 && numberOfnote < recordCount)
                    {
                        fseek(file, 0, SEEK_SET);

                        for (int i = 0; i < recordCount; ++i)
                        {
                            if (i != numberOfnote)
                            {
                                fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
                            }
                        }
                    }
                    fclose(file);
                }
                else
                {
                    printf("Something went wrong\n");
                }
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int recordCount = 0;
        if (makeAList(&recordCount, nameOfTheFile))
        {
            if ((file = fopen(nameOfTheFile, "r")) != NULL && !isEmpty())
            {

                fclose(file);
                if ((file = fopen(nameOfTheFile, "w+")) != NULL)
                {
                    printf("Please, enter the number of the note, that you want to delete: ");
                    int numberOfnote = getValueInt(numberOfnote);
                    numberOfnote--;
                    if (numberOfnote >= 0 && numberOfnote < recordCount)
                    {
                        fseek(file, 0, SEEK_SET);

                        for (int i = 0; i < recordCount; ++i)
                        {
                            if (i != numberOfnote)
                            {
                                fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
                            }
                        }
                    }
                    fclose(file);
                    strcpy(currentFileName, nameOfTheFile);
                }
                else
                {
                    printf(RED "Something went wrong\n" RESET);
                }
            }
            else
            {
                printf(RED "Note index to rewrite is out of bounds.\n" RESET);
            }
        }
    }
    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void sortNotesInFile()
{
    printf("————————————————————————————————————————————————————————\n");
    int key = 0;
    if (strlen(currentFileName) > 0)
    {
        printf("If you want to sort notes in current file, press 'y', if not - any other button\n");
        key = _getch();
    }
    if (key == YES)
    {
        int recordCount = 0;
        if (makeAList(&recordCount, currentFileName))
        {
            if ((file = fopen(currentFileName, "r+")) != NULL && !isEmpty())
            {
                fclose(file);
                if ((file = fopen(currentFileName, "w")) != NULL)
                {
                    printf("Please, chose the order: \n");
                    printf("Ascending - press 1\n");
                    printf("Descending - press 2\n");
                    int orderKey = 0;
                    do
                    {
                        orderKey = _getch();
                        switch (orderKey)
                        {
                        case ASCENDING:
                            printf(GRN "\nYou have chosen ascending\n\n" RESET);
                            whatAndSort(ASCENDING, recordCount);
                            break;
                        case DESCENDING:
                            printf(GRN "\nYou have chosen descending\n\n" RESET);
                            whatAndSort(DESCENDING, recordCount);
                            break;

                        default:
                            printf("Please, choose an option\n");
                            fflush(stdin);
                            orderKey = NOT_NEEDED_NUMBER;
                            break;
                        }
                    } while (orderKey == NOT_NEEDED_NUMBER);

                    fseek(file, 0, SEEK_SET);

                    for (int i = 0; i < recordCount; ++i)
                    {
                        fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
                    }
                    fclose(file);
                }
                else
                {
                    printf(RED "Something went wrong\n" RESET);
                }
            }
            else
            {
                printf(RED "Something went wrong during opening the file\n" RESET);
            }
        }
    }
    else
    {
        printf("Enter the file name that you want to open: ");
        scanf("%255s", nameOfTheFile);
        strcat(nameOfTheFile, ".txt");
        int recordCount = 0;
        if (makeAList(&recordCount, nameOfTheFile))
        {
            if ((file = fopen(nameOfTheFile, "r+")) != NULL && !isEmpty())
            {
                fclose(file);
                if ((file = fopen(nameOfTheFile, "w")) != NULL)
                {
                    printf("Please, chose the order: \n");
                    printf("Ascending - press 1\n");
                    printf("Descending - press 2\n");
                    int orderKey = 0;
                    do
                    {
                        orderKey = _getch();
                        switch (orderKey)
                        {
                        case ASCENDING:
                            printf(GRN "\nYou have chosen ascending\n\n" RESET);
                            whatAndSort(ASCENDING, recordCount);
                            break;
                        case DESCENDING:
                            printf(GRN "\nYou have chosen descending\n\n" RESET);
                            whatAndSort(DESCENDING, recordCount);
                            break;

                        default:
                            printf("Please, choose an option\n");
                            fflush(stdin);
                            orderKey = NOT_NEEDED_NUMBER;
                            break;
                        }
                    } while (orderKey == NOT_NEEDED_NUMBER);

                    fseek(file, 0, SEEK_SET);

                    for (int i = 0; i < recordCount; ++i)
                    {
                        fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
                    }
                    fclose(file);
                    strcpy(currentFileName, nameOfTheFile);
                }
                else
                {
                    printf(RED "Something went wrong\n" RESET);
                }
            }
            else
            {
                printf(RED "Something went wrong\n" RESET);
            }
        }
    }
    printf("————————————————————————————————————————————————————————\n");
    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void helpInfo()
{
    printf("\n—————————————————————————————————————————————————————————————————————————————————————\n");

    printf(GRN "English:\n" RESET);
    printf("1. \"Create File\": This option allows the user to create a new file.\n");
    printf("2. \"Read File\": This option enables the user to access the content of an existing file.\n");
    printf("3. \"Delete File\": This option allows the user to remove a file from the system.\n");
    printf("4. \"Create New Note\": This option allows the user to create a new note in an existing file.\n");
    printf("5.\"Insert Note\": This option allows the user to insert a new note into the file without breaking the sequence of records (possible only if the contents of the file were sorted).\n");
    printf("6. \"Rewrite Note\": This option allows the user to modify the content of an existing note.\n");
    printf("7. \"Read Note\": This option allows the user to access the content of a specific note within a file.\n");
    printf("8. \"Delete Note\": This option allows the user to delete a specific note from a file.\n");
    printf("9. \"Sort Notes In File\": This option enables the user to sort notes within a file based on a certain criterion.\n");
    printf("10. \"Help\": This option provides the user with information on how to use the program or specific functionalities.\n");
    printf("11. \"Author\": This option provides information about the author of the program.\n");
    printf("12. \"Exit\": This option allows the user to exit the program.\n\n");

    printf(RED "Addition\n" RESET);
    printf("1. The maximum length of a file name is 255 characters\n");
    printf("2. When you enter a file name to create/read/add records, etc. no need to write extensions ,\nthe program automatically creates files in the '.txt' extension\n");
    printf("3. The maximum length of the place name is 36 characters, taking into account spaces\n");
    printf("4. When entering a name, only the letters can be used\n");
    printf("5. Maximum area and population - 9 billion\n");
    printf("6. The data in the file must have the following structure for the correct operation of the program:\ntext (without spaces/tab characters), number, number\n");

    printf(GRN "Українська:\n" RESET);
    printf("1. \"Create File\": Цей пункт програми дозволяє користувачеві створити новий файл.\n");
    printf("2. \"Read File\": Цей пункт дозволяє користувачеві зчитати (отримати доступ до) вміст(у) вже існуючого файлу.\n");
    printf("3. \"Delete File\": Цей пункт дозволяє користувачеві видалити файл з системи.\n");
    printf("4. \"Create New Note\": Цей пункт програми дозволяє користувачеві створити нову нотатку у вже існуючий файл.\n");
    printf("5. \"Insert Note\": Цей пункт дозволяє користувачеві вставити нову нотатку в файл, не порушуючи послідовність записів(можлива тільки якщо вміст файлу сортувався).\n");
    printf("6. \"Rewrite Note\": Цей пункт програми дозволяє користувачеві змінити вміст вже існуючої нотатки.\n");
    printf("7. \"Read Note\": Цей пункт дозволяє користувачеві отримати доступ до вмісту конкретної нотатки у файлі.\n");
    printf("8. \"Delete Note\": Цей пункт програми дозволяє користувачеві видалити конкретну нотатку з файлу.\n");
    printf("9. \"Sort Notes In File\": Цей пункт дозволяє користувачеві відсортувати нотатки у файлі за певним критерієм.\n");
    printf("10. \"Help\": Цей пункт надає користувачеві інформацію про використання програми або конкретних функцій.\n");
    printf("11. \"Author\": Цей пункт надає інформацію про автора програми.\n");
    printf("12. \"Exit\": Цей пункт дозволяє користувачеві завершити роботу з програмою.\n\n");

    printf(RED "Додаток\n" RESET);
    printf("1. Мaксимальна довжина назви файлу дорівнює 255 символів\n");
    printf("2. Коли ви вводите назву файлу для створення/читання/додання записів і тд. не потрібно вписувати розширення,\nпрограма автоматично створює файли в розширенні '.txt'\n");
    printf("3. Максимальна довжина назви місьця 36 символів з урахуванням пробілів\n");
    printf("4. Під час введеня назви, можна використовувати тільки літери\n");
    printf("5. Максимальна площа та кількість населення - 9 мільярдів\n");
    printf("6. Дані в файлі мають мати таку структуру для коректної роботи програми:\nтекст(без пробілів/знаків табуляції), число, число\n");

    printf("—————————————————————————————————————————————————————————————————————————————————————\n");

    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void authorInfo()
{
    printf("\n—————————————————————————————————————————————————————————————————————————————————————\n");

    printf(GRN "English:\n" RESET);
    printf("I'm a student of group IP-33, Priadchenko Valerii.\n");
    printf("I adore reading books and spending time in nature during my free time.\n");
    printf("My favorite game is life because it's often more interesting than playing video games :)\n\n");

    printf(GRN "Українська:\n" RESET);
    printf("Я студент групи ІП-33, Прядченко Валерій.\n");
    printf("Обожнюю читати книжки та проводити час на природі у вільний час.\n");
    printf("Улюблена гра - життя, оскільки воно часто цікавіше, ніж грати в відеоігри :)\n");

    printf("—————————————————————————————————————————————————————————————————————————————————————\n");

    printf(CYN "Press any button to continue...\n" RESET);
    _getch();
}

void showCurrentFile()
{
    printf("————————————————————————————————————————————————————————\n");
    if (strlen(currentFileName) > 0)
    {
        printf("Current file is:" CYN " %s\n" RESET, currentFileName);
    }
    else
    {
        printf("No file is currently open\n");
    }
    printf("————————————————————————————————————————————————————————\n");
}

bool isEmpty()
{
    fseek(file, 0, SEEK_END);
    if (ftell(file) == 0)
    {
        printf("————————————————————————————————————————————————————————\n");

        printf(RED "File is empty, no need to read\n" RESET);

        printf("————————————————————————————————————————————————————————\n");
        fseek(file, 0, SEEK_SET);
        fclose(file);
        return true;
    }
    fseek(file, 0, SEEK_SET);
    return false;
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

double getValueInt(int a)
{
    bool isValid = true;
    int scanfResult = 0;
    do
    {
        scanfResult = scanf("%d", &a);
        isValid = isValidation(scanfResult, a);
        fflush(stdin);
    } while (!isValid);
    return a;
}

bool isValidationInt(int scanfResult, int value)
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
    printf(RED "Error, you entered not a number\n" RESET);
    printf("Please, enter the value again:");
}

bool makeAList(int *recordCount, char *name)
{
    if ((file = fopen(name, "r")) != NULL)
    {
        fseek(file, 0, SEEK_SET);

        int fscanfResult = 0;
        while (*recordCount < MAX_RECORDS && (fscanfResult = fscanf(file, "%s %lf %lf", records[*recordCount].place, &records[*recordCount].size, &records[*recordCount].population)) == 3)
        {
            records[*recordCount].number = *recordCount + 1;
            (*recordCount)++;
        }

        if (fscanfResult != EOF && fscanfResult != 3)
        {
            printf(RED "Wrong data in the file. Please check the file.\n" RESET);
            return false;
        }

        fseek(file, 0, SEEK_SET);

        fclose(file);
        return true;
    }
    else
    {
        printf(RED "Something went wrong\n" RESET);
        return false;
    }
    printf("————————————————————————————————————————————————————————\n");
}

bool isInputAdequate(char *buffer, char *tempBuffer)
{
    int q = 0;
    while (isspace(buffer[q]))
    {
        q++;
    }
    int length = strlen(buffer);
    if (length == q)
    {
        printf(RED "Please, enter something\n" RESET);
        return false;
    }
    char alphaBuffer[MAX_NAME_LENGTH];
    int letters = 0;
    while (q < length && !isspace(buffer[q]))
    {
        if (!isalpha(buffer[q]))
        {
            printf(RED "Please, without nubers\n" RESET);

            return false;
        }
        alphaBuffer[letters] = buffer[q];
        letters++;
        q++;
    }
    alphaBuffer[letters] = '\0';
    while (isspace(buffer[q]))
    {
        q++;
    }
    if (buffer[q] != '\0')
    {
        printf(RED "Error\n" RESET);
        return false;
    }
    strcpy(tempBuffer, alphaBuffer);
    return true;
}

int whatAndSort(int howSort, int recordCount)
{
    printf("Please, chose what you want to sort: \n");
    printf("Place name - press 1\n");
    printf("Place size - press 2\n");
    printf("Place population - press 3\n");
    int whatToSortKey = 5;
    do
    {
        whatToSortKey = _getch();
        whatToSortKey = sortBlock(howSort, whatToSortKey, recordCount, SHOW);
    } while (whatToSortKey == NOT_NEEDED_NUMBER);

    return 0;
}

int compareByNameAsc(const void *a, const void *b)
{
    const RECORD *placeA = (const RECORD *)a;
    const RECORD *placeB = (const RECORD *)b;

    return strcmp(placeA->place, placeB->place);
}

int compareByNameDesc(const void *a, const void *b)
{
    const RECORD *placeA = (const RECORD *)a;
    const RECORD *placeB = (const RECORD *)b;

    return strcmp(placeB->place, placeA->place);
}

int compareBySizeAsc(const void *a, const void *b)
{
    int sizeA = ((RECORD *)a)->size;
    int sizeB = ((RECORD *)b)->size;
    return sizeA - sizeB;
}

int compareBySizeDesc(const void *a, const void *b)
{
    int sizeA = ((RECORD *)a)->size;
    int sizeB = ((RECORD *)b)->size;
    return sizeB - sizeA;
}

int compareByPopulationAsc(const void *a, const void *b)
{
    int populationA = ((RECORD *)a)->population;
    int populationB = ((RECORD *)b)->population;
    return populationA - populationB;
}

int compareByPopulationDesc(const void *a, const void *b)
{
    int populationA = ((RECORD *)a)->population;
    int populationB = ((RECORD *)b)->population;
    return populationB - populationA;
}

void creatingnNoteAppend()
{
    RECORD note;
    fflush(stdin);
    char buffer[MAX_NAME_LENGTH];
    char tempBuffer[MAX_NAME_LENGTH];
    do
    {
        printf("Enter the name of the place(only alphabetic signs):");
        fgets(buffer, MAX_NAME_LENGTH, stdin);
        fflush(stdin);
    } while (!isInputAdequate(buffer, tempBuffer));
    strcpy(note.place, tempBuffer);
    printf("Enter the size in km^2[0;9e+9]: ");
    note.size = getValue(note.size);
    printf("Enter the population in thousands[0;9e+9]: ");
    note.population = getValue(note.population);
    fprintf(file, "%s %g %g\n", note.place, note.size, note.population);
}

int sortBlock(int howSort, int whatToSortKey, int recordCount, bool isShow)
{
    howSortInsert = howSort;
    whatToSortKeyInsert = whatToSortKey;
    if (howSort == ASCENDING)
    {
        switch (whatToSortKey)
        {
        case PLACE_NAME:
            qsort(records, recordCount, sizeof(RECORD), compareByNameAsc);
            if (isShow)
            {
                printf(GRN "\nSorted by name of the place in ascending order\n" RESET);
            }
            break;
        case PLACE_SIZE:
            qsort(records, recordCount, sizeof(RECORD), compareBySizeAsc);
            if (isShow)
            {
                printf(GRN "\nSorted by size in ascending order\n" RESET);
            }
            break;
        case PLACE_POPULATION:
            qsort(records, recordCount, sizeof(RECORD), compareByPopulationAsc);
            if (isShow)
            {
                printf(GRN "\nSorted by population in ascending order\n" RESET);
            }
            break;

        default:
            printf("Please, choose by which criterion you want to sort\n");
            fflush(stdin);
            return NOT_NEEDED_NUMBER;
        }
    }
    else
    {
        switch (whatToSortKey)
        {
        case PLACE_NAME:
            qsort(records, recordCount, sizeof(RECORD), compareByNameDesc);
            if (isShow)
            {
                printf(GRN "\nSorted by name of the place in descending order\n" RESET);
            }
            break;
        case PLACE_SIZE:
            qsort(records, recordCount, sizeof(RECORD), compareBySizeDesc);
            if (isShow)
            {
                printf(GRN "\nSorted by size in descending order\n" RESET);
            }
            break;
        case PLACE_POPULATION:
            qsort(records, recordCount, sizeof(RECORD), compareByPopulationDesc);
            if (isShow)
            {
                printf(GRN "\nSorted by population in descending order\n" RESET);
            }
            break;
        default:
            printf("Please, choose by which criterion you want to sort\n");
            fflush(stdin);
            return NOT_NEEDED_NUMBER;
        }
    }
}

void rewriteNoteRewriting(int recordCount)
{
    printf("Please, enter the number of the note, that you want to rewrite: ");
    int numberOfnote = getValueInt(numberOfnote);
    numberOfnote--;
    if (numberOfnote >= 0 && numberOfnote < recordCount)
    {
        fseek(file, 0, SEEK_SET);

        for (int i = 0; i < numberOfnote; ++i)
        {
            fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
        }

        fflush(stdin);
        char buffer[MAX_NAME_LENGTH];
        char tempBuffer[MAX_NAME_LENGTH];
        do
        {
            printf("Enter the name of the place(only alphabetic signs):");
            fgets(buffer, MAX_NAME_LENGTH, stdin);
            fflush(stdin);
        } while (!isInputAdequate(buffer, tempBuffer));
        strcpy(records[numberOfnote].place, tempBuffer);
        printf("Enter the size in km^2[0;9e+9]: ");
        records[numberOfnote].size = getValue(records[numberOfnote].size);
        printf("Enter the population in thousands[0;9e+9]: ");
        records[numberOfnote].population = getValue(records[numberOfnote].population);

        fprintf(file, "%s %g %g\n", records[numberOfnote].place, records[numberOfnote].size, records[numberOfnote].population);

        for (int i = numberOfnote + 1; i < recordCount; ++i)
        {
            fprintf(file, "%s %g %g\n", records[i].place, records[i].size, records[i].population);
        }
        fclose(file);
    }
    else
    {
        printf(RED "Note index to rewrite is out of bounds.\n" RESET);
    }
}

void readNoteReading(int recordCount)
{
    printf("Please, enter the number of the note, that you want to read: ");
    int numberOfnote = getValueInt(numberOfnote);
    numberOfnote--;
    if (numberOfnote >= 0 && numberOfnote < recordCount)
    {
        printf("Name:%s Size:%g Population:%g\n", records[numberOfnote].place, records[numberOfnote].size, records[numberOfnote].population);
        fclose(file);
    }
    else
    {
        printf(RED "Note index to rewrite is out of bounds.\n" RESET);
    }
}
