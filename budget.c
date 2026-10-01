#include "budget.h"

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static DepartmentBudget budgets[BUDGET_MAX_DEPARTMENTS];
static int departmentCount = 0;

static void readLine(const char *prompt, char *buffer, size_t size)
{
    size_t length;

    printf("%s", prompt);
    if (fgets(buffer, (int)size, stdin) == NULL) {
        buffer[0] = '\0';
        return;
    }

    length = strlen(buffer);
    if (length > 0 && buffer[length - 1] == '\n') {
        buffer[length - 1] = '\0';
    } else {
        int ch;
        while ((ch = getchar()) != '\n' && ch != EOF) {
            /* Discard input that did not fit in the buffer. */
        }
    }
}

static int readInt(const char *prompt, int *value)
{
    char input[100];
    char *end;
    long parsed;

    readLine(prompt, input, sizeof input);
    if (input[0] == '\0') {
        return 0;
    }

    parsed = strtol(input, &end, 10);
    while (isspace((unsigned char)*end)) {
        ++end;
    }
    if (end == input || *end != '\0' || parsed < 1 || parsed > 2147483647L) {
        return 0;
    }

    *value = (int)parsed;
    return 1;
}

static int readMoney(const char *prompt, double *value)
{
    char input[100];
    char *end;
    double parsed;

    readLine(prompt, input, sizeof input);
    if (input[0] == '\0') {
        return 0;
    }

    parsed = strtod(input, &end);
    while (isspace((unsigned char)*end)) {
        ++end;
    }
    if (end == input || *end != '\0' || parsed < 0.0) {
        return 0;
    }

    *value = parsed;
    return 1;
}

static int findById(int id)
{
    int i;
    for (i = 0; i < departmentCount; ++i) {
        if (budgets[i].id == id) {
            return i;
        }
    }
    return -1;
}

static int readDepartmentName(char *name, size_t size)
{
    readLine("Department name: ", name, size);
    return name[0] != '\0';
}

static void addBudget(void)
{
    DepartmentBudget item;
    int id;

    if (departmentCount >= BUDGET_MAX_DEPARTMENTS) {
        printf("The department limit (%d) has been reached.\\n", BUDGET_MAX_DEPARTMENTS);
        return;
    }

    if (!readInt("Department ID (positive integer): ", &id)) {
        printf("Invalid ID. Enter a positive whole number.\\n");
        return;
    }
    if (findById(id) != -1) {
        printf("A department with that ID already exists.\\n");
        return;
    }
    if (!readDepartmentName(item.department, sizeof item.department)) {
        printf("Department name cannot be empty.\\n");
        return;
    }
    if (!readMoney("Allocated budget (N$): ", &item.allocated)) {
        printf("Invalid allocation. Enter a non-negative number.\\n");
        return;
    }
    if (!readMoney("Expenditure to date (N$): ", &item.expenditure)) {
        printf("Invalid expenditure. Enter a non-negative number.\\n");
        return;
    }

    item.id = id;
    budgets[departmentCount++] = item;
    printf("Budget registered successfully.\\n");
}

static void updateExpenditure(void)
{
    int id;
    int index;
    double expenditure;

    if (departmentCount == 0) {
        printf("No departmental budgets have been registered.\\n");
        return;
    }
    if (!readInt("Department ID: ", &id)) {
        printf("Invalid ID.\\n");
        return;
    }
    index = findById(id);
    if (index == -1) {
        printf("Department ID not found.\\n");
        return;
    }
    if (!readMoney("New total expenditure (N$): ", &expenditure)) {
        printf("Invalid expenditure. Enter a non-negative number.\\n");
        return;
    }

    budgets[index].expenditure = expenditure;
    printf("Expenditure updated successfully.\\n");
}

static void displayOne(const DepartmentBudget *item)
{
    double remaining = item->allocated - item->expenditure;

    printf("%-6d %-24s %14.2f %14.2f %14.2f  %s\\n",
           item->id, item->department, item->allocated, item->expenditure,
           remaining, remaining < 0.0 ? "OVER BUDGET" : "WITHIN BUDGET");
}

static void displayBudgets(void)
{
    int i;

    if (departmentCount == 0) {
        printf("No departmental budgets have been registered.\\n");
        return;
    }

    printf("\\n%-6s %-24s %14s %14s %14s  %s\\n",
           "ID", "DEPARTMENT", "ALLOCATED (N$)", "SPENT (N$)",
           "REMAINING (N$)", "STATUS");
    printf("-----------------------------------------------------------------------------------------------\\n");
    for (i = 0; i < departmentCount; ++i) {
        displayOne(&budgets[i]);
    }
}

static void displayExceeded(void)
{
    int i;
    int found = 0;

    printf("\\nDepartments exceeding their allocated budget:\\n");
    for (i = 0; i < departmentCount; ++i) {
        if (budgets[i].expenditure > budgets[i].allocated) {
            displayOne(&budgets[i]);
            found = 1;
        }
    }
    if (!found) {
        printf("None.\\n");
    }
}

static void displaySummary(void)
{
    printf("\\nMUNICIPAL BUDGET SUMMARY\\n");
    printf("Total allocated : N$ %.2f\\n", budgetTotalAllocated());
    printf("Total expenditure: N$ %.2f\\n", budgetTotalExpenditure());
    printf("Net remaining   : N$ %.2f\\n", budgetTotalRemaining());
    printf("Over-budget departments: %d\\n", budgetExceededCount());
}

void budgetInitialize(void)
{
    departmentCount = 0;
}

int budgetCount(void)
{
    return departmentCount;
}

const DepartmentBudget *budgetGetAll(void)
{
    return budgets;
}

double budgetTotalAllocated(void)
{
    int i;
    double total = 0.0;
    for (i = 0; i < departmentCount; ++i) {
        total += budgets[i].allocated;
    }
    return total;
}

double budgetTotalExpenditure(void)
{
    int i;
    double total = 0.0;
    for (i = 0; i < departmentCount; ++i) {
        total += budgets[i].expenditure;
    }
    return total;
}

double budgetTotalRemaining(void)
{
    return budgetTotalAllocated() - budgetTotalExpenditure();
}

int budgetExceededCount(void)
{
    int i;
    int count = 0;
    for (i = 0; i < departmentCount; ++i) {
        if (budgets[i].expenditure > budgets[i].allocated) {
            ++count;
        }
    }
    return count;
}

void budgetMenu(void)
{
    int choice;
    char input[100];

    for (;;) {
        printf("\\n========================================\\n");
        printf("          BUDGET MANAGEMENT\\n");
        printf("========================================\\n");
        printf("1. Enter departmental budget\\n");
        printf("2. Update expenditure\\n");
        printf("3. Display all budgets\\n");
        printf("4. Display over-budget departments\\n");
        printf("5. Budget summary\\n");
        printf("0. Return to main menu\\n");

        readLine("Enter choice: ", input, sizeof input);
        if (strcmp(input, "0") == 0) {
            return;
        } else if (strcmp(input, "1") == 0) {
            addBudget();
        } else if (strcmp(input, "2") == 0) {
            updateExpenditure();
        } else if (strcmp(input, "3") == 0) {
            displayBudgets();
        } else if (strcmp(input, "4") == 0) {
            displayExceeded();
        } else if (strcmp(input, "5") == 0) {
            displaySummary();
        } else {
            printf("Invalid choice. Select an option from 0 to 5.\\n");
        }
    }
}
