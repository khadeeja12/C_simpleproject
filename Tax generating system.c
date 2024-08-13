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

struct Product* createProductNode() {      //create new node
    struct Product* newNode = (struct Product*)malloc(sizeof(struct Product));
    newNode->next = NULL;
    return newNode;
}

void calculateFinalPrice(struct Product* product) { //calculate the final prices for each product
    float totalCost = product->stockPrice + (product->stockPrice * product->taxPercentage / 100);
    float finalPrice = totalCost;

    printf("\nProduct - %s (%s)\n", product->itemName, product->itemCode);
    printf("Final price: %.2f\n", finalPrice);
}

void insert(struct Product* product) { //insert each values of a product to the list
    printf("Enter item name: ");
    scanf("%s", product->itemName);
    printf("Enter item code: ");
    scanf("%s", product->itemCode);
    printf("Enter stock price: ");
    scanf("%f", &product->stockPrice);
    printf("Enter tax percentage: ");
    scanf("%f", &product->taxPercentage);
}

void updateProduct(struct Product* product) {
    printf("Enter new item name (or press Enter to keep it as \"%s\"): ", product->itemName);
    while (getchar() != '\n');
    fgets(product->itemName, sizeof(product->itemName), stdin);
    product->itemName[strcspn(product->itemName, "\n")] = '\0';

    printf("Enter new item code (or press Enter to keep it as \"%s\"): ", product->itemCode);
    fgets(product->itemCode, sizeof(product->itemCode), stdin);
    product->itemCode[strcspn(product->itemCode, "\n")] = '\0';

    printf("Enter new stock price (or press Enter to keep it as %.2f): ", product->stockPrice);
    char buffer[20];
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &product->stockPrice);
    }

    printf("Enter new tax percentage (or press Enter to keep it as %.2f): ", product->taxPercentage);
    fgets(buffer, sizeof(buffer), stdin);
    if (buffer[0] != '\n') {
        sscanf(buffer, "%f", &product->taxPercentage);
    }
}

int main() {
    int choice;
    struct Product* products = NULL;
    
    do {
        printf("Select an option:\n");
        printf("1. Calculate final price for a single product\n");
        printf("2. Calculate final prices for multiple products\n");
        printf("3. Update product information\n");
        printf("4. Delete a product\n");
        printf("5. Search for a product\n");
        printf("6. Exit\n");
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
                    float totalPrices = 0.0;
                    printf("Enter the number of products: ");
                    scanf("%d", &numProducts);

                    for (int i = 0; i < numProducts; i++) {
                        struct Product* product = createProductNode();

                        printf("\nEnter details for product %d:\n", i + 1);
                        insert(product);
                        calculateFinalPrice(product);
                         //code to find the totalprices for all the products.
                        totalPrices += product->stockPrice + (product->stockPrice * product->taxPercentage / 100);

                        // Add the product to a linked list for future management
                        product->next = products;
                        products = product;
                    }
                    printf("\nTotal prices for all products: %.2f\n", totalPrices);
                    break;
                }
            case 3:
                {
                    char searchCode[10];  //update the product
                    printf("Enter the item code to update: ");
                    scanf("%s", searchCode);

                    struct Product* currentProduct = products;
                    while (currentProduct != NULL) {
                        if (strcmp(currentProduct->itemCode, searchCode) == 0) {
                            updateProduct(currentProduct);
                            printf("Product updated successfully!\n");
                            break;
                        }
                        currentProduct = currentProduct->next;
                    }
                    if (currentProduct == NULL) {
                        printf("Product not found.\n");
                    }
                    break;
                }
            case 4:
                {
                    char searchCode[10]; //delete a product
                    printf("Enter the item code to delete: ");
                    scanf("%s", searchCode);

                    struct Product* prevProduct = NULL;
                    struct Product* currentProduct = products;
                    while (currentProduct != NULL) {
                        if (strcmp(currentProduct->itemCode, searchCode) == 0) {
                            if (prevProduct == NULL) {
                                // Deleting the first product in the list
                                products = currentProduct->next;
                            } else {
                                prevProduct->next = currentProduct->next;
                            }
                            free(currentProduct);
                            printf("Product deleted successfully!\n");
                            break;
                        }
                        prevProduct = currentProduct;
                        currentProduct = currentProduct->next;
                    }
                    if (currentProduct == NULL) {
                        printf("Product not found.\n");
                    }
                    break;
                }
            case 5:
                {
                    char searchCode[10];  //search an item 
                    printf("Enter the item code to search for: ");
                    scanf("%s", searchCode);

                    struct Product* currentProduct = products;
                    while (currentProduct != NULL) {
                        if (strcmp(currentProduct->itemCode, searchCode) == 0) {
                            printf("\nProduct found:\n");
                            calculateFinalPrice(currentProduct);
                            break;
                        }
                        currentProduct = currentProduct->next;
                    }
                    if (currentProduct == NULL) {
                        printf("Product not found.\n");
                    }
                    break;
                }
            case 6:
                break; // Exit the loop
            default:
                printf("Invalid choice. Please select a valid option.\n");
                break;
        }
    } while (choice != 6);

    // Free memory allocated for the products
    struct Product* currentProduct = products;
    while (currentProduct != NULL) {
        struct Product* temp = currentProduct;
        currentProduct = currentProduct->next;
        free(temp);
    }

    printf("Exiting the program.\n");

    return 0;
}