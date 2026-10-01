#ifndef SUPPLIERS_H
#define SUPPLIERS_H

#define MAX_SUPPLIERS 100
#define SUP_ID_LEN     15
#define SUP_NAME_LEN  100
#define SUP_EMAIL_LEN 100
#define SUP_PHONE_LEN  30
#define SUP_TOWN_LEN   50

void supplierMenu(void);

void addSupplier(void);
void displaySuppliers(void);
void searchSupplier(void);
void compareSuppliers(void);
void showNameLength(void);
void showSupplierDescription(void);

int  getSupplierCount(void);

#endif
