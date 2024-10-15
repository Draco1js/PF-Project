#include <stdio.h>
#include "admin.h"
#include "database.h"
#include "error_handling.h"

void adminMenu() {
    int choice;
    adminLogin();
    printf("\nAdmin Menu:\n");
    printf("1. Manage Rooms\n2. View Reservations\n3. Generate Statistics\n4. Generate Report\n5. Logout\n");
    printf(">> ");
    scanf("%d", &choice);
    clearConsole();

    switch (choice) {
        case 1:
            manageRooms();
            break;
        case 2:
            viewReservations();
            break;
        case 3:
            generateStatistics();
            break;
        case 4:
            generateReport();
            break;
        case 5:
            printf("Logging out...\n");
            break;
        default:
            handleInputError();
    }
}

void adminLogin() {
    //  admin authentication
}

void manageRooms() {
    // adding, modifying, deleting room details
}

void viewReservations() {
    // viewing all guest reservations
}

void generateStatistics() {
    // generating statistics
}

void generateReport() {
    // generating booking and revenue reports
}
