#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"


int supplierCount = 0;

char supplierID[MAX_SUPPLIERS][10];
char supplierName[MAX_SUPPLIERS][50];
char supplierEmail[MAX_SUPPLIERS][50];
char supplierPhone[MAX_SUPPLIERS][20];
char supplierTown[MAX_SUPPLIERS][30];

int findSupplier(char id[])
{
int i;

for (i = 0; i < supplierCount; i++)
{
if (strcmp(supplierID[i], id) == 0)
{
return i;
}
}

return -1;
}


void addSupplier()
{
char answer;
char id[10];
int i;

do
{
if (supplierCount >= MAX_SUPPLIERS)
{
printf("\nSupplier limit reached!\n");
return;
}

printf("\n========== ADD SUPPLIER ==========\n");

printf("Enter Supplier ID: ");
scanf(" %9s", id);


if (findSupplier(id) != -1)
{
printf("Supplier ID already exists!\n");
}
else
{
strcpy(supplierID[supplierCount], id);

printf("Enter Supplier Name: ");
scanf(" %49[^\n]", supplierName[supplierCount]);

printf("Enter Supplier Email: ");
scanf(" %49s", supplierEmail[supplierCount]);

printf("Enter Supplier Phone: ");
scanf(" %19s", supplierPhone[supplierCount]);

printf("Enter Supplier Town: ");
scanf(" %29[^\n]", supplierTown[supplierCount]);

supplierCount++;

printf("\nSupplier added successfully!\n");
}

printf("\nAdd another supplier? (Y/N): ");
scanf(" %c", &answer);
answer = toupper((unsigned char)answer);

} while (answer == 'Y');
}


void displaySuppliers()
{
int i;

printf("\n========== SUPPLIER LIST ==========\n");

if (supplierCount == 0)
{
printf("No suppliers available.\n");
return;
}

for (i = 0; i < supplierCount; i++)
{
printf("\nSupplier %d\n", i + 1);
printf("Supplier ID: %s\n", supplierID[i]);
printf("Name: %s\n", supplierName[i]);
printf("Email: %s\n", supplierEmail[i]);
printf("Phone: %s\n", supplierPhone[i]);
printf("Town: %s\n", supplierTown[i]);
}
}


void searchSupplier()
{
int choice;
int i;
int found = 0;
char searchValue[50];

if (supplierCount == 0)
{
printf("\nNo suppliers available to search.\n");
return;
}

printf("\n========== SEARCH SUPPLIER ==========\n");
printf("1. Search by Supplier ID\n");
printf("2. Search by Name\n");
printf("3. Search by Town\n");
printf("Enter your choice: ");

if (scanf("%d", &choice) != 1)
{
printf("Invalid input. Please enter a number.\n");

while (getchar() != '\n');

return;
}

switch (choice)
{
case 1:
printf("Enter Supplier ID: ");
scanf(" %49s", searchValue);

i = findSupplier(searchValue);

if (i != -1)
{
printf("\nSupplier found!\n");
printf("ID: %s\n", supplierID[i]);
printf("Name: %s\n", supplierName[i]);
printf("Email: %s\n", supplierEmail[i]);
printf("Phone: %s\n", supplierPhone[i]);
printf("Town: %s\n", supplierTown[i]);
}
else
{
printf("Supplier not found.\n");
}
break;

case 2:
printf("Enter Supplier Name: ");
scanf(" %49[^\n]", searchValue);

for (i = 0; i < supplierCount; i++)
{
if (strstr(supplierName[i], searchValue) != NULL)
{
printf("\nSupplier found!\n");
printf("ID: %s\n", supplierID[i]);
printf("Name: %s\n", supplierName[i]);
printf("Email: %s\n", supplierEmail[i]);
printf("Phone: %s\n", supplierPhone[i]);
printf("Town: %s\n", supplierTown[i]);

found = 1;
}
}

if (!found)
{
printf("No supplier with that name found.\n");
}
break;

case 3:
printf("Enter Supplier Town: ");
scanf(" %49[^\n]", searchValue);

for (i = 0; i < supplierCount; i++)
{
if (strstr(supplierTown[i], searchValue) != NULL)
{
printf("\nSupplier found!\n");
printf("ID: %s\n", supplierID[i]);
printf("Name: %s\n", supplierName[i]);
printf("Email: %s\n", supplierEmail[i]);
printf("Phone: %s\n", supplierPhone[i]);
printf("Town: %s\n", supplierTown[i]);

found = 1;
}
}

if (!found)
{
printf("No supplier in that town found.\n");
}
break;

default:
printf("Invalid search option.\n");
}
}


void compareSuppliers()
{
char id1[10];
char id2[10];

int index1;
int index2;

if (supplierCount < 2)
{
printf("\nAt least two suppliers are required for comparison.\n");
return;
}

printf("\n========== COMPARE SUPPLIERS ==========\n");

printf("Enter first Supplier ID: ");
scanf(" %9s", id1);

printf("Enter second Supplier ID: ");
scanf(" %9s", id2);

index1 = findSupplier(id1);
index2 = findSupplier(id2);

if (index1 == -1 || index2 == -1)
{
printf("One or both suppliers were not found.\n");
return;
}

if (index1 == index2)
{
printf("Please enter two different Supplier IDs.\n");
return;
}

printf("\nSupplier 1: %s\n", supplierName[index1]);
printf("Town: %s\n", supplierTown[index1]);
printf("Email: %s\n", supplierEmail[index1]);
printf("Phone: %s\n", supplierPhone[index1]);

printf("\nSupplier 2: %s\n", supplierName[index2]);
printf("Town: %s\n", supplierTown[index2]);
printf("Email: %s\n", supplierEmail[index2]);
printf("Phone: %s\n", supplierPhone[index2]);

printf("\n========== COMPARISON RESULTS ==========\n");

if (strcmp(supplierTown[index1], supplierTown[index2]) == 0)
{
printf("Both suppliers are located in the same town.\n");
}
else
{
printf("The suppliers are located in different towns.\n");
}

if (strlen(supplierName[index1]) > strlen(supplierName[index2]))
{
printf("%s has the longer supplier name.\n",
supplierName[index1]);
}
else if (strlen(supplierName[index1]) < strlen(supplierName[index2]))
{
printf("%s has the longer supplier name.\n",
supplierName[index2]);
}
else
{
printf("Both supplier names have the same length.\n");
}
}


void showNameLength()
{
char id[10];
int index;

printf("\n========== SUPPLIER NAME LENGTH ==========\n");
printf("Enter Supplier ID: ");
scanf(" %9s", id);

index = findSupplier(id);

if (index == -1)
{
printf("Supplier not found.\n");
return;
}

printf("Supplier Name: %s\n", supplierName[index]);
printf("Name Length: %lu characters\n",
(unsigned long)strlen(supplierName[index]));
}

void showSupplierDescription()
{
char id[10];
char description[150];

int index;

printf("\n========== SUPPLIER DESCRIPTION ==========\n");
printf("Enter Supplier ID: ");
scanf(" %9s", id);

index = findSupplier(id);

if (index == -1)
{
printf("Supplier not found.\n");
return;
}

strcpy(description, "Supplier: ");
strcat(description, supplierName[index]);

strcat(description, " | Located in: ");
strcat(description, supplierTown[index]);

printf("\n%s\n", description);
}
