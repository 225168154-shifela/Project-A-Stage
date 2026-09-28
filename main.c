#include <stdio.h>
#include "employees.h"

void displayMenu(void)
{
    printf("\n=====================================\n");
    printf(" MUNICIPAL FINANCIAL MANAGEMENT SYSTEM\n");
    printf("=====================================\n");
    printf("1. Employee Management\n");
    printf("2. Exit\n");
    printf("=====================================\n");
    printf("Enter your choice: ");

}

int main(void)
{
    int choice;

    do
    {
        displayMenu();

        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                employeeMenu();
                break;

            case 2:
                printf("\nThank you for using MFMS.\n");
                break;

            default:
                printf("\nInvalid choice. Please try again.\n");
        }

    } while (choice != 2);

    return 0;
}

