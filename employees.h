#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#define MAX_EMPLOYEES 100

typedef struct
{
    int id;
    char name[50];
    char department[50];
    float basicSalary;
    float housingAllowance;
    float transportAllowance;
} Employee;

/* Function declarations */
void employeeMenu(void);
void addEmployee(void);
void displayEmployees(void);
void searchEmployee(void);
float calculateSalary(Employee employee);

#endif 
