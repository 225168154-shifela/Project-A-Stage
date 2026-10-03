#ifndef ASSETS_H
#define ASSESTS_H
typedef struct {
    int id;
    char name[50];
    double value;
    char date [15];
} Asset;
void addAsset();
void viewAssets();
void searchAsset();
void updateAsset();
void deleteAsset();
void displayTotalValue();
#endif
