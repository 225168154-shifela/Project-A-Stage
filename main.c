#include <stdio.h>
#include <stdlib.h>

#include "employees.h"
#include "budget.h"
#include "assets.h"
#include "suppliers.h"
#include "report.h"

int main(void)
{
    int choice;

    do
    {
        printf("\n================================\n");
        printf("       MFMS MAIN MENU\n");
        printf("================================\n");

        printf("1. Employee Management\n");
        printf("2. Budget Management\n");
        printf("3. Asset Management\n");
        printf("4. Supplier Management\n");
        printf("5. Reports\n");
        printf("0. Exit\n");

        printf("\nEnter your choice: ");

        if (scanf("%d", &choice) != 1)
        {
            printf("Invalid input. Please enter a number.\n");

            int ch;
            while ((ch = getchar()) != '\n' && ch != EOF);

            continue;
        }

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                budgetMenu();
                break;

            case 3:
                assetMenu();
                break;

            case 4:
                supplierMenu();
                break;

            case 5:
                reportMenu();
                break;

            case 0:
                printf("\nThank you for using MFMS!\n");
                break;

            default:
                printf("\nInvalid choice. Try again.\n");
        }

    } while (choice != 0);

    return 0;
}

