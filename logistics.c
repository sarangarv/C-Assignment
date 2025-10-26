#include <stdio.h>
#include <string.h>

#define MAX_CITIES 30
#define MAX_DELIVERIES 50

struct City {
    char name[20];
};

struct Vehicle {
    char name[10];
    int capacity;
    float rate;
    float speed;
    float efficiency;
};

struct Delivery {
    char from[20];
    char to[20];
    float distance;
    float weight;
    char vehicle[10];
    float cost;
};

struct SystemData {
    struct City cities[MAX_CITIES];
    int cityCount;
    float distanceTable[MAX_CITIES][MAX_CITIES];
    struct Delivery deliveries[MAX_DELIVERIES];
    int deliveryCount;
};

struct Vehicle vehicles[3] = {
    {"Van", 1000, 30, 60, 12},
    {"Truck", 5000, 40, 50, 6},
    {"Lorry", 10000, 80, 45, 4}
};

float fuelPrice = 310.0; // LKR per litre

/* -------- Functions -------- */

void add_city(struct SystemData *sys) {
    printf("To Exit Enter '0'\n\n");
    while (1) {
        if (sys->cityCount >= MAX_CITIES) {
            printf("City limit reached!\n");
            return;
        }

        char name[20];
        printf("Enter %d city name: ", sys->cityCount + 1);
        scanf("%s", name);

        if (strcmp(name, "0") == 0)
            break;

        strcpy(sys->cities[sys->cityCount].name, name);
        sys->cityCount++;
        printf("City added successfully!\n");
    }
}



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
            case 1:  add_city(&sys); break;
            case 2:  break;
            case 3:  break;
            case 4:  break;
            case 5:  break;
            case 6:  break;
            case 7:  break;
            case 8:  break;
            case 9: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 9);
    return 0;
}
