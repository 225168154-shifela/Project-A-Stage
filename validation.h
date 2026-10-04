#ifndef VALIDATION_H
#define VALIDATION_H


#define MAX_NAME_LEN 50
#define MAX_AMOUNT   1000000000000.0   

void   clearInputBuffer(void);
int    isBlank(const char text[]);


int    getValidInt(const char prompt[], int min, int max);
double getValidDouble(const char prompt[], double min);
void   getValidString(const char prompt[], char text[], int size);


int    getYesNo(const char prompt[]);
int    getMenuChoice(int min, int max);

#endif
