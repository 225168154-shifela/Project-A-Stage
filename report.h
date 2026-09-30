// reports.h

#ifndef REPORTS_H
#define REPORTS_H

void employeeReport(float salaries[], int count);
void budgetReport(float allocated[], float spent[], char dept[][30], int count);
void supplierReport(char names[][30], char towns[][30], int count);
void assetReport(char names[][30], char types[][30], float values[], int count);

#endif
