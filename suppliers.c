#include <stdio.h>
#include <string.h>
#include "suppliers.h"


int supplierCount = 0;

char supplierID[MAX_SUPPLIERS][];
char supplierName[MAX_SUPPLIERS][];
char supplierEmail[MAX_SUPPLIERS][];
char supplierPhone[MAX_SUPPLIERS][];
char supplierTown[MAX_SUPPLIERS][];


int findSupplier(char id[])
{
    int i;

    for(i = 0; i < supplierCount; i++)
    {
        if(strcmp(supplierID[i], id) == 0)
        {
            return i;
        }
    }

    return -1;
}


void addSupplier()
{
    printf("\n--- ADD SUPPLIER ---\n");

    if(supplierCount >= MAX_SUPPLIERS)
    {
        printf("Supplier list is full.\n");
        return;
    }

    printf("Enter Supplier ID: ");
    scanf("%9s", supplierID[supplierCount]);

    if(findSupplier(supplierID[supplierCount]) != -1)
    {
        printf("Supplier ID already exists.\n");
        return;
    }

    printf("Enter Supplier Name: ");
    scanf(" %49[^\n]", supplierName[supplierCount]);

    printf("Enter Supplier Email: ");
    scanf("%49s", supplierEmail[supplierCount]);

    printf("Enter Supplier Phone: ");
    scanf("%19s", supplierPhone[supplierCount]);

    printf("Enter Supplier Town: ");
    scanf(" %29[^\n]", supplierTown[supplierCount]);

    supplierCount++;

    printf("\nSupplier added successfully!\n");
}


void displaySuppliers()
{
    int i;

    printf("\n--- SUPPLIER DETAILS ---\n");

    if(supplierCount == 0)
    {
        printf("No suppliers registered.\n");
        return;
    }

    for(i = 0; i < supplierCount; i++)
    {
        printf("\nSupplier %d\n", i + 1);
        printf("ID: %s\n", supplierID[i]);
        printf("Name: %s\n", supplierName[i]);
        printf("Email: %s\n", supplierEmail[i]);
        printf("Phone: %s\n", supplierPhone[i]);
        printf("Town: %s\n", supplierTown[i]);
    }

    printf("\nTotal Suppliers: %d\n", supplierCount);
}


void searchSupplier()
{
    int choice, i, found = 0;
    char search[50];

    printf("\n--- SEARCH SUPPLIER ---\n");

    if(supplierCount == 0)
    {
        printf("No suppliers registered.\n");
        return;
    }

    printf("1. Search by Name\n");
    printf("2. Search by ID\n");
    printf("3. Search by Town\n");

    printf("Enter choice: ");
    scanf("%d", &choice);

    if(choice < 1 || choice > 3)
    {
        printf("Invalid search choice.\n");
        return;
    }

    printf("Enter search value: ");
    scanf(" %49[^\n]", search);

    for(i = 0; i < supplierCount; i++)
    {
        if((choice == 1 && strcmp(supplierName[i], search) == 0) ||
           (choice == 2 && strcmp(supplierID[i], search) == 0) ||
           (choice == 3 && strcmp(supplierTown[i], search) == 0))
        {
            found = 1;

            printf("\nSupplier Found!\n");
            printf("ID: %s\n", supplierID[i]);
            printf("Name: %s\n", supplierName[i]);
            printf("Email: %s\n", supplierEmail[i]);
            printf("Phone: %s\n", supplierPhone[i]);
            printf("Town: %s\n", supplierTown[i]);
        }
    }

    if(found == 0)
    {
        printf("Supplier not found.\n");
    }
}


void compareSuppliers()
{
    char id1[10], id2[10];
    int a, b;

    printf("\n--- COMPARE SUPPLIERS ---\n");

    if(supplierCount < 2)
    {
        printf("At least two suppliers are required.\n");
        return;
    }

    printf("Enter first supplier ID: ");
    scanf("%9s", id1);

    printf("Enter second supplier ID: ");
    scanf("%9s", id2);

    a = findSupplier(id1);
    b = findSupplier(id2);

    if(a == -1 || b == -1)
    {
        printf("One or both suppliers were not found.\n");
        return;
    }

    if(a == b)
    {
        printf("Choose two different suppliers.\n");
        return;
    }

    printf("\n--- SUPPLIER COMPARISON ---\n");

    printf("\nSupplier 1: %s\n", supplierName[a]);
    printf("Email: %s\n", supplierEmail[a]);
    printf("Phone: %s\n", supplierPhone[a]);
    printf("Town: %s\n", supplierTown[a]);

    printf("\nSupplier 2: %s\n", supplierName[b]);
    printf("Email: %s\n", supplierEmail[b]);
    printf("Phone: %s\n", supplierPhone[b]);
    printf("Town: %s\n", supplierTown[b]);

    if(strcmp(supplierTown[a], supplierTown[b]) == 0)
    {
        printf("\nBoth suppliers are from the same town.\n");
    }
    else
    {
        printf("\nSuppliers are from different towns.\n");
    }

    printf("Name length 1: %d\n",
           (int)strlen(supplierName[a]));

    printf("Name length 2: %d\n",
           (int)strlen(supplierName[b]));
}


void showNameLength()
{
    char id[10];
    int index;

    printf("\n--- SHOW NAME LENGTH ---\n");

    printf("Enter Supplier ID: ");
    scanf("%9s", id);

    index = findSupplier(id);

    if(index == -1)
    {
        printf("Supplier not found.\n");
    }
    else
    {
        printf("Supplier Name: %s\n", supplierName[index]);

        printf("Name Length: %d\n",
               (int)strlen(supplierName[index]));
    }
}


void showSupplierDescription()
{
    char id[10];
    char description[100];
    int index;

    printf("\n--- SUPPLIER DESCRIPTION ---\n");

    printf("Enter Supplier ID: ");
    scanf("%9s", id);

    index = findSupplier(id);

    if(index == -1)
    {
        printf("Supplier not found.\n");
    }
    else
    {
        strcpy(description, supplierName[index]);

        strcat(description, " operates in ");

        strcat(description, supplierTown[index]);

        printf("\n%s\n", description);
    }
}
