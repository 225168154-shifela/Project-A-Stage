#include <stdio.h>
#include <string.h>
#include "integration.h"
#include "validation.h"
#include "employees.h"
#include "suppliers.h"
#include "assets.h"
#include "report.h"

#define REPORT_TEXT_LEN 30     
#define MAX_ASSETS_REPORT 100

extern Employee employees[];
extern int employeeCount;
extern Asset assets[];
extern int assetCount;

static void copyText(char destination[], const char source[], int size)
{
    strncpy(destination, source, size - 1);
    destination[size - 1] = '\0';
}

static void showEmployeeReport(void)
{
    float salaries[MAX_EMPLOYEES];
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        salaries[i] = calculateSalary(employees[i]);
    }
    employeeReport(salaries, employeeCount);
}

static void showBudgetReport(void)
{
    float allocated[1] = {0};
    float spent[1] = {0};
    char dept[1][REPORT_TEXT_LEN];

    dept[0][0] = '\0';
    budgetReport(allocated, spent, dept, 0);
}

static void showSupplierReport(void)
{
    char names[MAX_SUPPLIERS][REPORT_TEXT_LEN];
    char towns[MAX_SUPPLIERS][REPORT_TEXT_LEN];
    int count = getSupplierCount();
    int i;

    for (i = 0; i < count; i++)
    {
        copyText(names[i], getSupplierName(i), REPORT_TEXT_LEN);
        copyText(towns[i], getSupplierTown(i), REPORT_TEXT_LEN);
    }
    supplierReport(names, towns, count);
}

static void showAssetReport(void)
{
    char names[MAX_ASSETS_REPORT][REPORT_TEXT_LEN];
    char types[MAX_ASSETS_REPORT][REPORT_TEXT_LEN];
    float values[MAX_ASSETS_REPORT];
    int i;

    for (i = 0; i < assetCount; i++)
    {
        copyText(names[i], assets[i].name, REPORT_TEXT_LEN);
        copyText(types[i], "N/A", REPORT_TEXT_LEN);   
        values[i] = (float)assets[i].value;
    }
    assetReport(names, types, values, assetCount);
}

void reportsMenu(void)
{
    int choice;

    do
    {
        printf("\n========================================\n");
        printf("                REPORTS\n");
        printf("========================================\n");
        printf("1. Employee Report\n");
        printf("2. Budget Report\n");
        printf("3. Supplier Report\n");
        printf("4. Asset Report\n");
        printf("5. Back to Main Menu\n");

        choice = getMenuChoice(1, 5);

        switch (choice)
        {
            case 1: showEmployeeReport(); break;
            case 2: showBudgetReport();   break;
            case 3: showSupplierReport(); break;
            case 4: showAssetReport();    break;
            case 5: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 5);
}
