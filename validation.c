#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "validation.h"

static void handleEndOfInput(void)
{
    printf("\nInput closed. Exiting MFMS.\n");
    exit(0);
}

void clearInputBuffer(void)
{
    int ch;
    while ((ch = getchar()) != '\n' && ch != EOF)
    {
       
    }
}

int isBlank(const char text[])
{
    int i;
    for (i = 0; i < (int)strlen(text); i++)
    {
        if (!isspace((unsigned char)text[i]))
        {
            return 0;
        }
    }
    return 1;
}

int getValidInt(const char prompt[], int min, int max)
{
    int value = 0;
    int result;

    while (1)
    {
        printf("%s", prompt);
        result = scanf("%d", &value);
        if (result == EOF) handleEndOfInput();
        clearInputBuffer();

        if (result != 1)
        {
            printf("  Error: please enter a whole number.\n");
        }
        else if (value < min || value > max)
        {
            printf("  Error: value must be between %d and %d.\n", min, max);
        }
        else
        {
            return value;
        }
    }
}

double getValidDouble(const char prompt[], double min)
{
    double value = 0.0;
    int result;

    while (1)
    {
        printf("%s", prompt);
        result = scanf("%lf", &value);
        if (result == EOF) handleEndOfInput();
        clearInputBuffer();

        if (result != 1)
        {
            printf("  Error: please enter a valid number.\n");
        }
        else if (!(value >= min))
        {
            printf("  Error: value cannot be less than %.2f.\n", min);
        }
        else if (value > MAX_AMOUNT)
        {
            printf("  Error: value is too large.\n");
        }
        else
        {
            return value;
        }
    }
}

void getValidString(const char prompt[], char text[], int size)
{
    char temp[256];
    int length;

    while (1)
    {
        printf("%s", prompt);

        if (fgets(temp, sizeof(temp), stdin) == NULL)
        {
            handleEndOfInput();
        }

        length = (int)strlen(temp);

        if (length > 0 && temp[length - 1] == '\n')
        {
            temp[length - 1] = '\0';
            length--;
        }
        else
        {
            clearInputBuffer();
        }

        if (isBlank(temp))
        {
            printf("  Error: this field cannot be empty.\n");
        }
        else if (length >= size)
        {
            printf("  Error: maximum %d characters allowed.\n", size - 1);
        }
        else
        {
            strcpy(text, temp);
            return;
        }
    }
}

int getYesNo(const char prompt[])
{
    char answer;
    int result;

    while (1)
    {
        printf("%s (Y/N): ", prompt);
        result = scanf(" %c", &answer);
        if (result == EOF) handleEndOfInput();
        clearInputBuffer();

        if (result == 1)
        {
            answer = (char)toupper((unsigned char)answer);
            if (answer == 'Y') return 1;
            if (answer == 'N') return 0;
        }
        printf("  Error: please enter Y or N.\n");
    }
}

int getMenuChoice(int min, int max)
{
    return getValidInt("Enter your choice: ", min, max);
}
