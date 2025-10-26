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

void rename_city(struct SystemData *sys) {
    if (sys->cityCount == 0) {
        printf("No cities to rename!\n");
        return;
    }

    char oldName[20], newName[20];
    printf("Enter city to rename: ");
    scanf("%s", oldName);
    printf("Enter new name: ");
    scanf("%s", newName);

    for (int i = 0; i < sys->cityCount; i++) {
        if (strcmp(sys->cities[i].name, oldName) == 0) {
            strcpy(sys->cities[i].name, newName);


            printf("City renamed successfully!\n");
            return;
        }
    }
    printf("City not found!\n");
}

void remove_city(struct SystemData *sys) {
    if (sys->cityCount == 0) {
        printf("No cities to remove!\n");
        return;
    }

    char name[20];
    printf("Enter city to remove: ");
    scanf("%s", name);

    // Find city
    int found = 0;
    for (int i = 0; i < sys->cityCount; i++) {
        if (strcmp(sys->cities[i].name, name) == 0) {
            found = 1;
            // Shift cities
            for (int j = i; j < sys->cityCount - 1; j++)
                sys->cities[j] = sys->cities[j + 1];
            sys->cityCount--;
            break;
        }
    }

    if (!found) {
        printf("City not found!\n");
        return;
    }


    printf("City and related deliveries removed.\n");
}

void show_cities(struct SystemData *sys) {
    printf("\n--- City List ---\n");
    for (int i = 0; i < sys->cityCount; i++)
        printf("%d. %s\n", i + 1, sys->cities[i].name);
}

void set_distance(struct SystemData *sys) {
    if (sys->cityCount < 2) {
        printf("Please add at least 2 cities first!\n");
        return;
    }
    printf("\nTo Exit Enter '0'\n\n");
    while(1){
    show_cities(sys);
    int a, b;
    float d;
    printf("Enter source city number: ");
    scanf("%d", &a);

    if(a==0)
        break;

    printf("Enter destination city number: ");
    scanf("%d", &b);
    do{if(b==a){
        printf("Invalid Destination.\n");
        printf("Enter destination city number: ");
        scanf("%d", &b);
    }}while(b==a);

    if(sys->distanceTable[a-1][b-1]>0){
        printf("\nAlready Entered Data.\n");
        break;
    }

    printf("Enter distance (km): ");
    scanf("%f", &d);
    sys->distanceTable[a - 1][b - 1] = d;
    sys->distanceTable[b - 1][a - 1] = d;
    printf("Distance recorded successfully!\n");
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
            case 1:  add_city(&sys);     break;
            case 2:  rename_city(&sys);  break;
            case 3:  remove_city(&sys);  break;
            case 4:  show_cities(&sys);  break;
            case 5:  set_distance(&sys); break;
            case 6:  break;
            case 7:  break;
            case 8:  break;
            case 9: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 9);
    return 0;
}
