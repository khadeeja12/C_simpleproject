#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Product {
    char itemName[50];
    char itemCode[10];
    float stockPrice;
    float taxPercentage;
    struct Product* next;
};

struct Product* createProductNode() {//create new node
    struct Product* newNode = (struct Product*)malloc(sizeof(struct Product));
    newNode->next = NULL;
    return newNode;
}

void calculateFinalPrice(struct Product* product) {//calculate the final prices for each product
    float totalCost = product->stockPrice + (product->stockPrice * product->taxPercentage / 100);
    float finalPrice = totalCost;

    printf("\nProduct - %s (%s)\n", product->itemName, product->itemCode);
    printf("Final price: %.2f\n", finalPrice);
}

void insert(struct Product* product)//insert each values of a product to the list
{
printf("Enter item name: ");
scanf("%s", product->itemName);
printf("Enter item code: ");
scanf("%s", product->itemCode);
printf("Enter stock price: ");
scanf("%f", &product->stockPrice);
printf("Enter tax percentage: ");
scanf("%f", &product->taxPercentage);	
}


int main() {
    int choice;
    

    do {
        printf("Select an option:\n");
        printf("1. Calculate final price for a single product\n");
        printf("2. Calculate final prices for multiple products\n");
        printf("3. Exit\n");
        scanf("%d", &choice);

        switch (choice) {
            case 1: 
                {
	            struct Product* product = createProductNode();
                insert(product);
                calculateFinalPrice(product);
                free(product);
                break;
                }
            case 2: 
                {
		         int numProducts;
		        float totalPrices=0.0;
                  struct Product* product;
                printf("Enter the number of products: ");//number of products which we want to enter
                scanf("%d", &numProducts);

                for (int i = 0; i < numProducts; i++) {
                    struct Product* product = createProductNode();

                    printf("\nEnter details for product %d:\n", i + 1);

                    insert(product);

                    calculateFinalPrice(product);
                    
                    //code to find the totalprices for all the products.
                    totalPrices += product->stockPrice + (product->stockPrice * product->taxPercentage / 100);

                    free(product);
               }
               printf("\nTotal prices for all products: %.2f\n", totalPrices);
                    break;
              
          }
            case 3:
                break; // Exit the loop
       
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 3);

    
    printf("Exiting the program.\n");

    return 0;
}


