#include <stdio.h>

// Employee Report
void employeeReport(float salaries[], int count) {
    if (count == 0) {
        printf("\nNo employees found.\n");
        return;
    }
    float total = 0, highest = salaries[0], lowest = salaries[0];
    for (int i = 0; i < count; i++) {
        total += salaries[i];
        if (salaries[i] > highest) highest = salaries[i];
        if (salaries[i] < lowest) lowest = salaries[i];
    }
    printf("\n--- Employee Report ---\n");
    printf("Total Employees: %d\n", count);
    printf("Average Salary: %.2f\n", total / count);
    printf("Highest Salary: %.2f\n", highest);
    printf("Lowest Salary: %.2f\n", lowest);
}

// Budget Report
void budgetReport(float allocated[], float spent[], char dept[][30], int count) {
    if (count == 0) {
        printf("\nNo budgets found.\n");
        return;
    }
    float totalAlloc = 0, totalSpent = 0;
    printf("\n--- Budget Report ---\n");
    for (int i = 0; i < count; i++) {
        float remain = allocated[i] - spent[i];
        totalAlloc += allocated[i];
        totalSpent += spent[i];
        printf("%s | Allocated: %.2f | Spent: %.2f | Remaining: %.2f | %s\n",
               dept[i], allocated[i], spent[i], remain,
               remain >= 0 ? "WITHIN BUDGET" : "EXCEEDED");
    }
    printf("Total Allocated: %.2f\n", totalAlloc);
    printf("Total Spent: %.2f\n", totalSpent);
    printf("Remaining: %.2f\n", totalAlloc - totalSpent);
}

// Supplier Report
void supplierReport(char names[][30], char towns[][30], int count) {
    if (count == 0) {
        printf("\nNo suppliers found.\n");
        return;
    }
    printf("\n--- Supplier Report ---\n");
    for (int i = 0; i < count; i++) {
        printf("Supplier: %s | Town: %s\n", names[i], towns[i]);
    }
}

// Asset Report
void assetReport(char names[][30], char types[][30], float values[], int count) {
    if (count == 0) {
        printf("\nNo assets found.\n");
        return;
    }
    printf("\n--- Asset Report ---\n");
    for (int i = 0; i < count; i++) {
        printf("Asset: %s | Type: %s | Value: %.2f\n", names[i], types[i], values[i]);
    }
}
