#include <stdio.h>
#include "guest.h"
#include "database.h"
#include "error_handling.h"

void signUp() {
    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (registerUser(username, password)) {
        printf("Registration successful! You can now log in.\n");
    } else {
        printf("Registration failed.\n");
    }
}

void login() {
    char username[50], password[50];
    printf("Enter Username: ");
    scanf("%s", username);
    printf("Enter Password: ");
    scanf("%s", password);

    if (loginUser(username, password)) {
        printf("Login successful!\n");
    } else {
        printf("Login failed. Please check your credentials.\n");
    }
}

void browseRooms() {
    loadRooms();
    printf("Input 1 to go back... ");
    scanf("%d");
}

void bookRoom() {
    if (loggedInUserID == -1) {
        printf("You need to be logged in to book a room.\n");
        return;
    }

    int reservationID;
    printf("Enter Reservation ID (for reference): ");
    scanf("%d", &reservationID);

    int availableRoom = getAvailableRoom();
    if (availableRoom != -1) {
        char checkInDate[11], checkOutDate[11];
        printf("Enter Check-In Date (yyyy-mm-dd): ");
        scanf("%s", checkInDate);
        printf("Enter Check-Out Date (yyyy-mm-dd): ");
        scanf("%s", checkOutDate);

        saveReservation(reservationID, loggedInUserID, availableRoom, checkInDate, checkOutDate);
    } else {
        printf("No available rooms at the moment.\n");
    }
}

void cancelUserReservation() {
    if (loggedInUserID == -1) {
        printf("You need to be logged in to cancel a reservation.\n");
        return;
    }

    int reservationID;
    printf("Enter Reservation ID to cancel: ");
    scanf("%d", &reservationID);
    cancelReservation(reservationID);
}

void requestService() {
    if (loggedInUserID == -1) {
        printf("You need to be logged in to request services.\n");
        return;
    }

    char serviceRequest[100];
    printf("Enter your service request (e.g., food, maintenance): ");
    scanf(" %[^\n]s", serviceRequest);  // To read a line with spaces
    
    printf("Service request for '%s' has been submitted, staff will arrive at your room shortly\n", serviceRequest);
}

void giveFeedback() {
    if (loggedInUserID == -1) {
        printf("You need to be logged in to give feedback.\n");
        return;
    }

    char feedback[256];
    printf("Enter your feedback: ");
    scanf(" %[^\n]s", feedback);  // To read a line with spaces

    saveFeedback(loggedInUserID, feedback);
}

void logout() {
    if (logoutUser()) {
        printf("You have logged out successfully.\n");
    } else {
        printf("Error logging out.\n");
    }
}


void guestMenu() {
    int choice;
    printf("Guest Menu:\n");
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
            cancelUserReservation();
            break;
        case 6:
            requestService();
            break;
        case 7:
            giveFeedback();
            break;
        case 8:
            logout();
            break;
        default:
            handleInputError();
    }
}
