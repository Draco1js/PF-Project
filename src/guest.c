#include <stdio.h>
#include "guest.h"
#include "database.h"
#include "error_handling.h"

void guestMenu() {
    int choice;
    printf("\nGuest Menu:\n");
    printf("1. Sign-Up\n2. Login\n3. Browse Rooms\n4. Book a Room\n5. Cancel Reservation\n6. Request Services\n7. Give Feedback\n8. Logout\n");
    printf(">> ");
    scanf("%d", &choice);
    clearConsole();
    
    switch (choice) {
        case 1:
            signUp();
            break;
        case 2:
            login();
            break;
        case 3:
            browseRooms();
            break;
        case 4:
            bookRoom();
            break;
        case 5:
            cancelReservation();
            break;
        case 6:
            requestService();
            break;
        case 7:
            giveFeedback();
            break;
        case 8:
            printf("Logging out...\n");
            break;
        default:
            handleInputError();
    }
}

void signUp() {
    // Logic for user registration
}

void login() {
    // Logic for user login
}

void browseRooms() {
    // Logic for displaying available rooms
}

void bookRoom() {
    // Logic for booking a room
}

void cancelReservation() {
    // Logic for cancelling a reservation
}

void requestService() {
    // Logic for requesting services like food or maintenance
}

void giveFeedback() {
    // Logic for submitting feedback
}

void Hello() {
    printf("Hello\n");
}