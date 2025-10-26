#include <stdio.h>
#include <stdlib.h>


int main() {
    struct SystemData sys = {0}; // all values set to 0

    int choice;
    do {
        printf("\n=== Logistics Management System ===\n");
        printf("1. Add City.\n");
        printf("2. Rename City.\n");
        printf("3. Remove City.\n");
        printf("4. Show Cities.\n");
        printf("5. Set Distance.\n");
        printf("6. Create Delivery.\n");
        printf("7. Show Deliveries.\n");
        printf("8. Show Report.\n");
        printf("9. Exit\n");
        printf("Enter choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1: add_city(&sys); break;
            case 2: rename_city(&sys); break;
            case 3: remove_city(&sys); break;
            case 4: show_cities(&sys); break;
            case 5: set_distance(&sys); break;
            case 6: create_delivery(&sys); break;
            case 7: show_deliveries(&sys); break;
            case 8: show_report(&sys); break;
            case 9: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 9);
    return 0;
}
