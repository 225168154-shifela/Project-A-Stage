#include <stdio.h>
#include <string.h>
#include "employees.h"

Employee employees[MAX_EMPLOYEES];

int employeeCount = 0;

/* Calculate gross employee salary */
float calculateSalary(Employee employee)
{
    float grossSalary;

    grossSalary = employee.basicSalary + employee.housingAllowance + employee.transportAllowance;

    return grossSalary;
}


/* Add a new employee */
void addEmployee(void)
{
    if (employeeCount >= MAX_EMPLOYEES)
    {
        printf("\nEmployee storage is full.\n");
        return;
    }

    printf("\n--- Add New Employee ---\n");

    printf("Enter Employee ID: ");
    scanf("%d", &employees[employeeCount].id);

    getchar(); 

    printf("Enter Employee Name: ");
    fgets(employees[employeeCount].name, 50, stdin);

    employees[employeeCount].name[strcspn(employees[employeeCount].name, "\n")] = '\0';

    printf("Enter Department: ");
    fgets(employees[employeeCount].department, 50, stdin);

    employees[employeeCount].department[strcspn(employees[employeeCount].department, "\n")] = '\0';

    /* Validate basic salary */
     do
     {
        printf("Enter Basic Salary: ");
        scanf("%f", &employees[employeeCount].basicSalary);

        if (employees[employeeCount].basicSalary < 0)
        {
            printf(" Salary cannot be negative.\n");
        }

     }while (employees[employeeCount].basicSalary < 0);


    /* Validate housing allowance */
    do
    {
        printf("Enter Housing Allowance: ");
        scanf("%f", &employees[employeeCount].housingAllowance);

        if (employees[employeeCount].housingAllowance < 0)
        {
            printf(" Allowance cannot be negative.\n");
        }   

    }while (employees[employeeCount].housingAllowance < 0);


    /* Validate transport allowance */
    do
    {
        printf("Enter Transport Allowance: ");
        scanf("%f", &employees[employeeCount].transportAllowance);

        if (employees[employeeCount].transportAllowance < 0)
        {
            printf(" Allowance cannot be negative.\n");
        }

    }while (employees[employeeCount].transportAllowance < 0);

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
    int found = 0;

    printf("\n======== SEARCH EMPLOYEE  ========\n");

    printf("Enter Employee ID: ");
    scanf("%d", &searchId);

    for (int i = 0; i < employeeCount; i++)
    {
        if (employees[i].id == searchId)
        {
            printf("\nEmployee Found!\n");
            printf("--------------------\n");

            printf("ID: %d\n", employees[i].id);
            printf("Name: %s\n", employees[i].name);
            printf("Department: %s\n", employees[i].department);

            printf("Basic Salary: N$%.2f\n", employees[i].basicSalary);

            printf("Housing Allowance: N$%.2f\n", employees[i].housingAllowance);

            printf("Transport Allowance: N$%.2f\n", employees[i].transportAllowance);

            printf("Gross Salary: N$%.2f\n", calculateSalary(employees[i]));

            found = 1;
            break;
        }
    }

    if (found == 0)
    {
        printf("\nEmployee with ID %d not found.\n", searchId);
    }
}


/* Employee Management Menu*/
void employeeMenu(void)
{
    int choice;

    do
    {
        printf("\n==========================================\n");
        printf("        EMPLOYEE MANAGEMENT MENU          \n"); 
        printf("=====================================\n");
        printf("1. Add Employee\n");
        printf("2. Display Employees\n");
        printf("3. Search Employee\n");
        printf("4. Return to Main Menu\n");
        printf("==========================================\n");
        printf("Enter your choice: ");

        scanf("%d", &choice);

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

            default:
                printf("Invalid choice. Please try again.\n");
        }
        
    } while (choice != 4);
}