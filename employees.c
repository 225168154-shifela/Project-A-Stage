#include <stdio.h>
#include <string.h>
#include "employees.h"
#include "validation.h"

Employee employees[MAX_EMPLOYEES];

int employeeCount = 0;

/* Calculate gross employee salary */
float calculateSalary(Employee employee)
{
    float grossSalary;

    grossSalary = employee.basicSalary + employee.housingAllowance + employee.transportAllowance;

    return grossSalary;
}

/* Returns the position of an employee ID, or -1 if not found */
static int findEmployeeIndex(int id)
{
    int i;

    for (i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == id)
        {
            return i;
        }
    }
    return -1;
}

/* Add a new employee */
void addEmployee(void)
{
    int id;

    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("\nEmployee storage is full.\n");
        return;
    }

    printf("\n--- Add New Employee ---\n");

    id = getValidInt("Enter Employee ID: ", 1, 999999);

    if (findEmployeeIndex(id) != -1)
    {
        printf("Error: Employee ID %d already exists.\n", id);
        return;
    }
    employees[employeeCount].id = id;

    getValidString("Enter Employee Name: ", employees[employeeCount].name, 50);
    getValidString("Enter Department: ", employees[employeeCount].department, 50);

    /* getValidDouble rejects negative values and repeats until valid */
    employees[employeeCount].basicSalary =
        (float)getValidDouble("Enter Basic Salary: ", 0);
    employees[employeeCount].housingAllowance =
        (float)getValidDouble("Enter Housing Allowance: ", 0);
    employees[employeeCount].transportAllowance =
        (float)getValidDouble("Enter Transport Allowance: ", 0);

    employeeCount++;

    printf("\nEmployee added successfully!\n");
}

/* Display all employees */
void displayEmployees(void)
{
    if (employeeCount == 0)
    {
        printf("\nNo employees have been registered.\n");
        return;
    }

    printf("\n--- Employee List ---\n");

    for (int i = 0; i < employeeCount; i++)
    {
        printf("\nEmployee %d\n", i + 1);
        printf("--------------------\n");

        printf("ID: %d\n", employees[i].id);
        printf("Name: %s\n", employees[i].name);
        printf("Department: %s\n", employees[i].department);

        printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);

        printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);

        printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance);

        printf("Gross Salary: N$%.2f\n", calculateSalary(employees[i]));
    }
}

/* Search for an employee by ID */
void searchEmployee(void)
{
    int searchId;
    int index;

    printf("\n======== SEARCH EMPLOYEE  ========\n");

    searchId = getValidInt("Enter Employee ID: ", 1, 999999);
    index = findEmployeeIndex(searchId);

    if (index == -1)
    {
        printf("\nEmployee with ID %d not found.\n", searchId);
        return;
    }

    printf("\nEmployee Found!\n");
    printf("--------------------\n");

    printf("ID: %d\n", employees[index].id);
    printf("Name: %s\n", employees[index].name);
    printf("Department: %s\n", employees[index].department);

    printf("Basic Salary: N$%.2f\n", employees[index].basicSalary);

    printf("Housing Allowance: N$%.2f\n", employees[index].housingAllowance);

    printf("Transport Allowance: N$%.2f\n", employees[index].transportAllowance);

    printf("Gross Salary: N$%.2f\n", calculateSalary(employees[index]));
}

/* Employee Management Menu */
void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n==========================================\n");
        printf("        EMPLOYEE MANAGEMENT MENU          \n");
        printf("==========================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Return to Main Menu\n");
        printf("==========================================\n");

        choice = getMenuChoice(1, 4);

        switch (choice)
        {
            case 1:
                addEmployee();
                break;

            case 2:
                displayEmployees();
                break;

            case 3:
                searchEmployee();
                break;

            case 4:
                printf("\nReturning to Main Menu...\n");
                break;
        }

    } while (choice != 4);
}
