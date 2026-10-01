#ifndef BUDGET_H
#define BUDGET_H

#define BUDGET_MAX_DEPARTMENTS 100
#define BUDGET_NAME_LENGTH 50

typedef struct {
    int id;
    char department[BUDGET_NAME_LENGTH];
    double allocated;
    double expenditure;
} DepartmentBudget;

/* Starts the budget module with no registered departments. */
void budgetInitialize(void);

/* Interactive budget-management menu. Returns to the caller when user exits. */
void budgetMenu(void);

/* Exposed helpers for integration with the system's reports module. */
int budgetCount(void);
const DepartmentBudget *budgetGetAll(void);
double budgetTotalAllocated(void);
double budgetTotalExpenditure(void);
double budgetTotalRemaining(void);
int budgetExceededCount(void);

#endif
