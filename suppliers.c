#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "suppliers.h"

static char supplierId   [MAX_SUPPLIERS][SUP_ID_LEN];
static char supplierName [MAX_SUPPLIERS][SUP_NAME_LEN];
static char supplierEmail[MAX_SUPPLIERS][SUP_EMAIL_LEN];
static char supplierPhone[MAX_SUPPLIERS][SUP_PHONE_LEN];
static char supplierTown [MAX_SUPPLIERS][SUP_TOWN_LEN];
static int  supplierCount = 0;

static void readString(const char *prompt, char text[], int size);
static int  readChoice(int min, int max);
static void toLowerCopy(const char source[], char destination[]);
static int  isBlank(const char text[]);
static int  isValidEmail(const char email[]);
static int  isValidPhone(const char phone[]);
static int  findById(const char id[]);
static int  findByName(const char name[]);
static int  askForSupplier(const char *prompt);
static void printHeader(void);
static void printRow(int i);

static void readString(const char *prompt, char text[], int size)
{
    int c;

    printf("%s", prompt);
    if (fgets(text, size, stdin) == NULL) {
        text[0] = '\0';
        return;
    }
    if (strchr(text, '\n') == NULL) {

        while ((c = getchar()) != '\n' && c != EOF)
            ;
    }
    text[strcspn(text, "\n")] = '\0';
}

static int readChoice(int min, int max)
{
    char line[32];
    int value, used;

    for (;;) {
        readString("Enter choice: ", line, sizeof(line));
        if (sscanf(line, "%d %n", &value, &used) == 1 &&
            line[used] == '\0' && value >= min && value <= max)
            return value;
        printf("Invalid choice. Enter a number from %d to %d.\n", min, max);
    }
}

static void toLowerCopy(const char source[], char destination[])
{
    int i;

    strcpy(destination, source);
    for (i = 0; destination[i] != '\0'; i++)
        destination[i] = (char)tolower((unsigned char)destination[i]);
}

static int isBlank(const char text[])
{
    int i;

    if (strlen(text) == 0)
        return 1;
    for (i = 0; text[i] != '\0'; i++)
        if (!isspace((unsigned char)text[i]))
            return 0;
    return 1;
}

static int isValidEmail(const char email[])
{
    const char *at, *dot;
    int i;

    if (strlen(email) < 5)
        return 0;
    for (i = 0; email[i] != '\0'; i++)
        if (isspace((unsigned char)email[i]))
            return 0;

    at = strchr(email, '@');
    if (at == NULL || at == email || strchr(at + 1, '@') != NULL)
        return 0;
    dot = strrchr(at, '.');
    if (dot == NULL || dot == at + 1 || *(dot + 1) == '\0')
        return 0;
    return 1;
}

static int isValidPhone(const char phone[])
{
    int i, digits = 0;

    for (i = 0; phone[i] != '\0'; i++) {
        if (isdigit((unsigned char)phone[i]))
            digits++;
        else if (phone[i] == '+' && i == 0)
            continue;
        else if (phone[i] == ' ' || phone[i] == '-')
            continue;
        else
            return 0;
    }
    return digits >= 7 && digits <= 15;
}

static int findById(const char id[])
{
    char wanted[SUP_ID_LEN], current[SUP_ID_LEN];
    int i;

    toLowerCopy(id, wanted);
    for (i = 0; i < supplierCount; i++) {
        toLowerCopy(supplierId[i], current);
        if (strcmp(wanted, current) == 0)
            return i;
    }
    return -1;
}

static int findByName(const char name[])
{
    char wanted[SUP_NAME_LEN], current[SUP_NAME_LEN];
    int i;

    toLowerCopy(name, wanted);
    for (i = 0; i < supplierCount; i++) {
        toLowerCopy(supplierName[i], current);
        if (strcmp(wanted, current) == 0)
            return i;
    }
    return -1;
}

static int askForSupplier(const char *prompt)
{
    char id[SUP_ID_LEN];
    int index;

    for (;;) {
        readString(prompt, id, sizeof(id));
        index = findById(id);
        if (index != -1)
            return index;
        printf("Supplier '%s' not found. Try again.\n", id);
    }
}

static void printHeader(void)
{
    printf("\n%-8s %-24s %-26s %-16s %-14s\n",
           "ID", "Name", "Email", "Phone", "Town");
    printf("------------------------------------------------------"
           "------------------------------\n");
}

static void printRow(int i)
{
    printf("%-8.8s %-24.24s %-26.26s %-16.16s %-14.14s\n",
           supplierId[i], supplierName[i], supplierEmail[i],
           supplierPhone[i], supplierTown[i]);
}

int getSupplierCount(void)
{
    return supplierCount;
}

void addSupplier(void)
{
    char id[SUP_ID_LEN], name[SUP_NAME_LEN], email[SUP_EMAIL_LEN];
    char phone[SUP_PHONE_LEN], town[SUP_TOWN_LEN];

    printf("\n--- ADD SUPPLIER ---\n");

    if (supplierCount >= MAX_SUPPLIERS) {
        printf("The supplier list is full (%d suppliers).\n", MAX_SUPPLIERS);
        return;
    }

    for (;;) {
        readString("Enter supplier ID (e.g. S001): ", id, sizeof(id));
        if (isBlank(id))
            printf("Supplier ID cannot be empty.\n");
        else if (strchr(id, ' ') != NULL)
            printf("Supplier ID cannot contain spaces.\n");
        else if (strlen(id) > 8)
            printf("Supplier ID is too long (maximum 8 characters).\n");
        else if (findById(id) != -1)
            printf("Supplier ID '%s' already exists.\n", id);
        else
            break;
    }

    for (;;) {
        readString("Enter supplier name: ", name, sizeof(name));
        if (isBlank(name))
            printf("Supplier name cannot be empty.\n");
        else if (findByName(name) != -1)
            printf("A supplier called '%s' already exists.\n", name);
        else
            break;
    }

    for (;;) {
        readString("Enter email: ", email, sizeof(email));
        if (isValidEmail(email))
            break;
        printf("Invalid email. Use a format like sales@abc.com\n");
    }

    for (;;) {
        readString("Enter phone: ", phone, sizeof(phone));
        if (isValidPhone(phone))
            break;
        printf("Invalid phone number (7-15 digits, e.g. 0611234567).\n");
    }

    for (;;) {
        readString("Enter town: ", town, sizeof(town));
        if (!isBlank(town))
            break;
        printf("Town cannot be empty.\n");
    }

    strcpy(supplierId[supplierCount],    id);
    strcpy(supplierName[supplierCount],  name);
    strcpy(supplierEmail[supplierCount], email);
    strcpy(supplierPhone[supplierCount], phone);
    strcpy(supplierTown[supplierCount],  town);
    supplierCount++;

    printf("\nSupplier '%s' added. Total suppliers: %d\n", name, supplierCount);
}

void displaySuppliers(void)
{
    int i;

    printf("\n--- SUPPLIER DETAILS ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printHeader();
    for (i = 0; i < supplierCount; i++)
        printRow(i);
    printf("\nTotal suppliers: %d\n", supplierCount);
}

void searchSupplier(void)
{
    char term[SUP_NAME_LEN], lowTerm[SUP_NAME_LEN], lowTown[SUP_TOWN_LEN];
    int choice, i, index, found = 0;

    printf("\n--- SEARCH SUPPLIER ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    printf("1. Search by supplier name\n");
    printf("2. Search by supplier ID\n");
    printf("3. Search by town\n");
    choice = readChoice(1, 3);

    for (;;) {
        readString("Enter text to search for: ", term, sizeof(term));
        if (!isBlank(term))
            break;
        printf("Search text cannot be empty.\n");
    }

    if (choice == 1 || choice == 2) {
        index = (choice == 1) ? findByName(term) : findById(term);
        if (index == -1) {
            printf("Supplier not found.\n");
        } else {
            printf("Supplier found.\n");
            printHeader();
            printRow(index);
        }
        return;
    }

    toLowerCopy(term, lowTerm);
    for (i = 0; i < supplierCount; i++) {
        toLowerCopy(supplierTown[i], lowTown);
        if (strcmp(lowTerm, lowTown) == 0) {
            if (found == 0)
                printHeader();
            printRow(i);
            found++;
        }
    }
    if (found == 0)
        printf("No suppliers found in '%s'.\n", term);
    else
        printf("\n%d supplier(s) found in '%s'.\n", found, term);
}

void compareSuppliers(void)
{
    char lowA[SUP_NAME_LEN], lowB[SUP_NAME_LEN];
    int a, b, result;

    printf("\n--- COMPARE SUPPLIERS ---\n");
    if (supplierCount < 2) {
        printf("At least two suppliers are needed to compare.\n");
        return;
    }

    a = askForSupplier("Enter first supplier ID: ");
    do {
        b = askForSupplier("Enter second supplier ID: ");
        if (b == a)
            printf("Please choose a different supplier.\n");
    } while (b == a);

    printf("\n%-10s | %-26s | %-26s\n", "Field", supplierId[a], supplierId[b]);
    printf("-----------+----------------------------+---------------------------\n");
    printf("%-10s | %-26.26s | %-26.26s\n", "Name",  supplierName[a],  supplierName[b]);
    printf("%-10s | %-26.26s | %-26.26s\n", "Email", supplierEmail[a], supplierEmail[b]);
    printf("%-10s | %-26.26s | %-26.26s\n", "Phone", supplierPhone[a], supplierPhone[b]);
    printf("%-10s | %-26.26s | %-26.26s\n", "Town",  supplierTown[a],  supplierTown[b]);

    toLowerCopy(supplierTown[a], lowA);
    toLowerCopy(supplierTown[b], lowB);
    printf("\nSame town: %s\n", strcmp(lowA, lowB) == 0 ? "YES" : "NO");

    toLowerCopy(supplierName[a], lowA);
    toLowerCopy(supplierName[b], lowB);
    result = strcmp(lowA, lowB);
    if (result < 0)
        printf("'%s' comes before '%s' alphabetically.\n",
               supplierName[a], supplierName[b]);
    else if (result > 0)
        printf("'%s' comes before '%s' alphabetically.\n",
               supplierName[b], supplierName[a]);
    else
        printf("The two names are identical.\n");

    printf("Name length: %zu characters vs %zu characters.\n",
           strlen(supplierName[a]), strlen(supplierName[b]));
}

void showNameLength(void)
{
    int index;

    printf("\n--- SHOW NAME LENGTH ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    index = askForSupplier("Enter supplier ID: ");
    printf("Supplier name length: %zu\n", strlen(supplierName[index]));
    printf("Email length: %zu\n",         strlen(supplierEmail[index]));
    printf("Town length: %zu\n",          strlen(supplierTown[index]));
}

void showSupplierDescription(void)
{
    char sentence[SUP_NAME_LEN + SUP_TOWN_LEN + 32];
    int index;

    printf("\n--- SUPPLIER DESCRIPTION ---\n");
    if (supplierCount == 0) {
        printf("No suppliers registered yet.\n");
        return;
    }

    index = askForSupplier("Enter supplier ID: ");

    strcpy(sentence, supplierName[index]);
    strcat(sentence, " operates in ");
    strcat(sentence, supplierTown[index]);
    strcat(sentence, ".");

    printf("%s\n", sentence);
}

static void displaySupplierMenu(void)
{
    printf("\n========================================\n");
    printf("           SUPPLIER MANAGEMENT\n");
    printf("========================================\n");
    printf("1. Add Supplier\n");
    printf("2. Display Suppliers\n");
    printf("3. Search Supplier\n");
    printf("4. Compare Suppliers\n");
    printf("5. Show Name Length\n");
    printf("6. Show Supplier Description\n");
    printf("7. Back to Main Menu\n");
}

void supplierMenu(void)
{
    int choice;

    do {
        displaySupplierMenu();
        choice = readChoice(1, 7);

        switch (choice) {
        case 1: addSupplier();             break;
        case 2: displaySuppliers();        break;
        case 3: searchSupplier();          break;
        case 4: compareSuppliers();        break;
        case 5: showNameLength();          break;
        case 6: showSupplierDescription(); break;
        case 7: printf("Returning to main menu...\n"); break;
        }
    } while (choice != 7);
}
