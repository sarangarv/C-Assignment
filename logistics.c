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

            // Update deliveries
            for (int j = 0; j < sys->deliveryCount; j++) {
                if (strcmp(sys->deliveries[j].from, oldName) == 0) strcpy(sys->deliveries[j].from, newName);
                if (strcmp(sys->deliveries[j].to, oldName) == 0) strcpy(sys->deliveries[j].to, newName);
            }

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

    // Remove deliveries related to this city
    for (int i = 0; i < sys->deliveryCount;) {
        if (strcmp(sys->deliveries[i].from, name) == 0 || strcmp(sys->deliveries[i].to, name) == 0) {
            for (int j = i; j < sys->deliveryCount - 1; j++)
                sys->deliveries[j] = sys->deliveries[j + 1];
            sys->deliveryCount--;
        } else {
            i++;
        }
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

float calculate_cost(float distance, float weight, struct Vehicle v) {
    float deliveryCost = distance * v.rate * (1 + weight / 10000);
    float fuelUsed = distance / v.efficiency;
    float fuelCost = fuelUsed * fuelPrice;
    float totalOperationalCost = deliveryCost + fuelCost;
    float profit = deliveryCost * 0.25;
    return totalOperationalCost + profit;
}

void create_delivery(struct SystemData *sys) {
    if (sys->cityCount < 2) {
        printf("Please add cities first!\n");
        return;
    }
    if (sys->deliveryCount >= MAX_DELIVERIES) {
        printf("Delivery limit reached!\n");
        return;
    }

    show_cities(sys);
    int from, to, vChoice;
    float w;
    printf("Enter source city number: ");
    scanf("%d", &from);
    printf("Enter destination city number: ");
    scanf("%d", &to);
    printf("Enter package weight (kg): ");
    scanf("%f", &w);
    printf("Select vehicle (1=Van, 2=Truck, 3=Lorry): ");
    scanf("%d", &vChoice);

    float d = sys->distanceTable[from - 1][to - 1];
    if (d == 0) {
        printf("** No distance recorded between selected cities!\n");
        return;
    }

    struct Vehicle v = vehicles[vChoice - 1];
    if (w > v.capacity) {
        printf("** Weight exceeds vehicle capacity (%d kg)!\n", v.capacity);
        return;
    }

    struct Delivery del;
    strcpy(del.from, sys->cities[from - 1].name);
    strcpy(del.to, sys->cities[to - 1].name);
    strcpy(del.vehicle, v.name);
    del.distance = d;
    del.weight = w;
    del.cost = calculate_cost(d, w, v);


    sys->deliveries[sys->deliveryCount++] = del;
    printf("\n** Delivery created successfully!\n");
    printf("From: %s To: %s\n", del.from, del.to);
    printf("Vehicle: %s | Distance: %.2f km | Time Duration: %.2f Hours | Cost: %.2f LKR\n", del.vehicle, del.distance,del.distance/v.speed, del.cost);
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
            case 1:  add_city(&sys);        break;
            case 2:  rename_city(&sys);     break;
            case 3:  remove_city(&sys);     break;
            case 4:  show_cities(&sys);     break;
            case 5:  set_distance(&sys);    break;
            case 6:  create_delivery(&sys); break;
            case 7:  break;
            case 8:  break;
            case 9: printf("Exiting program...\n"); break;
            default: printf("Invalid choice! Try again.\n");
        }
    } while (choice != 9);
    return 0;
}
