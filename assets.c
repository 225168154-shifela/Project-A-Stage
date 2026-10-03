#include <stdio.h>
 #include <string.h>
 #include "assets.h"
 Asset assets[100];
 int assetCount = 0;
 void addAsset() {
     printf("Enter Asset ID: ");
     scanf("%d", &assets[assetCount].id);
     printf("Enter Asset Name: ");
     scanf(" %[^\n]s", assets[assetCount].name);
     printf("Enter Value: ");
     scanf("%lf", &assets[assetCount].value);
     printf("Enter Date: ");
     scanf(" %[^\n]s", assets[assetCount].date);
     assetCount++;
     printf("Asset added successfully!\n");
 }
 void viewAssets() {
     if (assetCount == 0) {
         printf("No assets to display.\n");
         return;
     }
     printf("\n--- All Assets ---\n");
     for (int i = 0; i < assetCount; i++) {
         printf("ID: %d | Name: %s | Value: N$%.2f | Date: %s\n",
                assets[i].id, assets[i].name, assets[i].value, assets[i].date);
     }
 }
 void displayTotalValue() {
     double total = 0;
     for (int i = 0; i < assetCount; i++) {
         total += assets[i].value;
     }
     printf("\nTotal Value of ALL Assets:N$%.2f\n", total):
       }
     printf("\nTotal Value of All Assets: N$%.2f\n", total);
