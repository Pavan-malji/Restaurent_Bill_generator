#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ITEMS 10
struct MenuItems
{
    int id;
    char name[20];
    float price;
};
struct Order
{
    int itemId;
    int quantity;
    float totalPrice;
};
//Menu
struct MenuItems menu[MAX_ITEMS] = {
    {1, "Burger", 120.0},
    {2, "Pizza", 250.0},
    {3, "Fries", 80.0},
    {4, "Coke", 40.0},
    {5, "Pasta", 150.0},
    {6, "Samosa", 15.0},
    {7, "Veg puff", 25.0},
    {8, "Biryani", 120.0},
    {9,"Coffee",15.0},
    {10, "Ice Cream", 60.0}};
struct Order orders[50];
int orderCount = 0;
//Functions declarations
void displayMenu();
void takeOrder();
void generateBill();
void clearOrders();
void saveBillToFile();
//Display menu function
void displayMenu()
{
    printf("\n--------Pavan's Restro--------\n");
    printf("\n-------------MENU-------------\n");
    for (int i = 0; i < MAX_ITEMS && menu[i].id != 0; i++)
    {
        printf("%d. %-10s Rs. %.2f\n", menu[i].id, menu[i].name, menu[i].price);
    }
    printf("\n");
}
//take order function
void takeOrder()
{
    int itemId, quantity;
    while (1)
    {
        printf("Enter item ID and quantity (0 to stop): ");
        scanf("%d", &itemId);
        if (itemId == 0)
            break;
        scanf("%d", &quantity);

        int found = 0;
        for (int i = 0; i < MAX_ITEMS; i++)
        {
            if (menu[i].id == itemId)
            {
                orders[orderCount].itemId = itemId;
                orders[orderCount].quantity = quantity;
                orders[orderCount].totalPrice = quantity * menu[i].price;
                orderCount++;
                found = 1;
                break;
            }
        }
        if (!found)
        {
            printf("Item not found. Try again.\n");
        }
    }
}

//Total bill value generator 
float getTotal()
{
    float total = 0;
    for (int i = 0; i < orderCount; i++)
    {
        total += orders[i].totalPrice;
    }
    return total;
}

//Bill generator
void generateBill()
{
    printf("\n--------Pavan's Restro--------\n");
    printf("\n----------Your Bill------------\n");
    printf("Item       Qty      Price\n");
    for (int i = 0; i < orderCount; i++)
    {
        int itemId = orders[i].itemId;
        for (int j = 0; j < MAX_ITEMS; j++)
        {
            if (menu[j].id == itemId)
            {
                printf("%-10s x %-5d = Rs. %.2f\n", menu[j].name, orders[i].quantity, orders[i].totalPrice);
                break;
            }
        }
    }
    printf("----------------------\n");
    printf("Total: Rs. %.2f\n", getTotal());
}
void saveBillToFile()
{
    static int billNumber = 1;
    char filename[50];
    sprintf(filename, "Bill_%d.txt", billNumber);

    FILE *fp = fopen(filename, "w");
    if (fp == NULL) {
        printf("Error saving bill to file.\n");
        return;
    }

    fprintf(fp, "\n--------Pavan's Restro--------\n");
    fprintf(fp, "\n----------Your Bill------------\n");
    fprintf(fp, "Item       Qty      Price\n");
    for (int i = 0; i < orderCount; i++) {
        int itemId = orders[i].itemId;
        for (int j = 0; j < MAX_ITEMS; j++) {
            if (menu[j].id == itemId) {
                fprintf(fp, "%-10s x %-5d = Rs. %.2f\n", menu[j].name, orders[i].quantity, orders[i].totalPrice);
                break;
            }
        }
    }
    fprintf(fp, "----------------------\n");
    fprintf(fp, "Total: Rs. %.2f\n", getTotal());
    fclose(fp);

    printf("Bill saved as %s\n", filename);
    billNumber++;
}
//Clear orders
void clearOrders()
{
    orderCount = 0;
}

int main()
{
    int choice;
    float paidAmount;

    while (1)
    {
        printf("\n===== Pavan's Restro =====\n");
        printf("1. Show Menu\n");
        printf("2. Place Order\n");
        printf("3. Generate Bill\n");
        printf("4. SaveBillToFile\n");
        printf("5. Pay and Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            displayMenu();
            break;
        case 2:
            takeOrder();
            break;
        case 3:
            generateBill();
            break;
        case 4:saveBillToFile();
            break;
        case 5:
            generateBill();
            float total = getTotal();
            do
            {
                printf("Enter amount paid: Rs. ");
                scanf("%f", &paidAmount);

                if (paidAmount < total)
                {
                    printf("Insufficient amount. Please pay at least Rs. %.2f\n", total);
                }
            } while (paidAmount < total);

            printf("Payment successful! Change returned: Rs. %.2f\n", paidAmount - total);
            clearOrders();
            exit(0);
        default:
            printf("Invalid choice. Try again.\n");
        }
    }
    return 0;
}
