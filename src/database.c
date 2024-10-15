#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "database.h"

#define USER_FILE "users.txt"
#define RESERVATION_FILE "reservations.txt"
#define ROOM_FILE "rooms.txt"
#define FEEDBACK_FILE "feedback.txt"


#define MAX_ROOMS 10  // Specify how many rooms to initialize in the hotel


// A simple variable to track if a user is logged in (for session management)
int loggedInUserID = -1;  // -1 means no user is logged in

// Initialize the database, including rooms and reservations
void initializeDatabase() {
    FILE *file;

    // Create reservation file if it doesn't exist
    file = fopen(RESERVATION_FILE, "a");
    if (file) {
        fclose(file);
    }

    // Create rooms file and initialize rooms with status 'Available'
    file = fopen(ROOM_FILE, "w");
    if (file == NULL) {
        printf("Error: Unable to create rooms file!\n");
        return;
    }

    for (int i = 1; i <= MAX_ROOMS; i++) {
        fprintf(file, "%d|Available\n", i);  // Initialize each room as Available
    }

    fclose(file);
    printf("Rooms initialized successfully with %d rooms.\n", MAX_ROOMS);
}

// Cancel a reservation by reservationID
void cancelReservation(int reservationID) {
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open reservation file!\n");
        return;
    }

    char tempFileName[] = "temp_reservations.txt";
    FILE *tempFile = fopen(tempFileName, "w");
    if (tempFile == NULL) {
        printf("Error: Unable to create temporary reservation file!\n");
        fclose(file);
        return;
    }

    char line[256];
    int resID;
    int guestID, roomNumber;
    char checkInDate[11], checkOutDate[11];
    int found = 0;

    // Copy reservations to a temporary file, skipping the one to be canceled
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%d|%d|%s|%s", &resID, &guestID, &roomNumber, checkInDate, checkOutDate);
        if (resID == reservationID) {
            markRoomAsAvailable(roomNumber);  // Mark the room as available
            found = 1;  // Reservation found and canceled
            continue;  // Skip writing this reservation
        }
        fprintf(tempFile, "%s", line);
    }

    fclose(file);
    fclose(tempFile);

    // Replace old reservations file with the temporary file
    remove(RESERVATION_FILE);
    rename(tempFileName, RESERVATION_FILE);

    if (found) {
        printf("Reservation ID %d has been canceled successfully.\n", reservationID);
    } else {
        printf("Reservation with ID %d not found.\n", reservationID);
    }
}

// Function to check room availability and return the first available room number
int getAvailableRoom() {
    FILE *file = fopen(ROOM_FILE, "r+");
    if (file == NULL) {
        printf("Error: Could not open room file!\n");
        return -1;
    }

    char line[256];
    int roomNumber;
    char status[20];

    // Find the first room that is marked as 'Available'
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%s", &roomNumber, status);
        if (strcmp(status, "Available") == 0) {
            fclose(file);
            return roomNumber;
        }
    }

    fclose(file);
    return -1;  // No available room found
}

// Function to mark a room as Occupied
void markRoomAsOccupied(int roomNumber) {
    FILE *file = fopen(ROOM_FILE, "r+");
    if (file == NULL) {
        printf("Error: Could not open room file!\n");
        return;
    }

    char line[256];
    int currentRoomNumber;
    char status[20];
    long position;

    // Find the room number and mark it as 'Occupied'
    while (fgets(line, sizeof(line), file)) {
        position = ftell(file);  // Get the position before reading the next line
        sscanf(line, "%d|%s", &currentRoomNumber, status);
        if (currentRoomNumber == roomNumber) {
            fseek(file, position - strlen(line), SEEK_SET);  // Move back to the beginning of the line
            fprintf(file, "%d|Occupied\n", roomNumber);  // Overwrite the line with the updated status
            break;
        }
    }

    fclose(file);
}

// Function to mark a room as Available (for cancellations)
void markRoomAsAvailable(int roomNumber) {
    FILE *file = fopen(ROOM_FILE, "r+");
    if (file == NULL) {
        printf("Error: Could not open room file!\n");
        return;
    }

    char line[256];
    int currentRoomNumber;
    char status[20];
    long position;

    // Find the room number and mark it as 'Available'
    while (fgets(line, sizeof(line), file)) {
        position = ftell(file);  // Get the position before reading the next line
        sscanf(line, "%d|%s", &currentRoomNumber, status);
        if (currentRoomNumber == roomNumber) {
            fseek(file, position - strlen(line), SEEK_SET);  // Move back to the beginning of the line
            fprintf(file, "%d|Available\n", roomNumber);  // Overwrite the line with the updated status
            break;
        }
    }

    fclose(file);
}

// Save a reservation to the database and update room status to Occupied
void saveReservation(int reservationID, int guestID, int roomNumber, const char *checkInDate, const char *checkOutDate) {
    if (roomNumber == -1) {
        printf("Error: No available rooms for this reservation.\n");
        return;
    }

    FILE *file = fopen(RESERVATION_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open reservation file!\n");
        return;
    }

    // Write the reservation to the file
    fprintf(file, "%d|%d|%d|%s|%s\n", reservationID, guestID, roomNumber, checkInDate, checkOutDate);
    fclose(file);

    // Mark the room as Occupied
    markRoomAsOccupied(roomNumber);

    printf("Reservation saved successfully! Room %d is now occupied.\n", roomNumber);
}

// Load and display all reservations
void loadReservations() {
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (file == NULL) {
        printf("No reservations found.\n");
        return;
    }

    char line[256];
    printf("Reservations:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Print each reservation
    }

    fclose(file);
}

// Load a specific reservation by reservationID
void loadReservationByID(int reservationID) {
    FILE *file = fopen(RESERVATION_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open reservation file!\n");
        return;
    }

    char line[256];
    int resID;
    int guestID, roomNumber;
    char checkInDate[11], checkOutDate[11];

    // Search for the reservation by ID
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%d|%d|%d|%s|%s", &resID, &guestID, &roomNumber, checkInDate, checkOutDate);
        if (resID == reservationID) {
            printf("Reservation Found:\n");
            printf("Reservation ID: %d, Guest ID: %d, Room: %d, Check-In: %s, Check-Out: %s\n", resID, guestID, roomNumber, checkInDate, checkOutDate);
            fclose(file);
            return;
        }
    }

    printf("Reservation with ID %d not found.\n", reservationID);
    fclose(file);
}

// Load and display all room statuses
void loadRooms() {
    FILE *file = fopen(ROOM_FILE, "r");
    if (file == NULL) {
        printf("No rooms found.\n");
        return;
    }

    char line[256];
    printf("Room Statuses:\n");
    while (fgets(line, sizeof(line), file)) {
        printf("%s", line);  // Print each room status
    }

    fclose(file);
}

// Save feedback from a guest
void saveFeedback(int guestID, const char *feedback) {
    FILE *file = fopen(FEEDBACK_FILE, "a");
    if (file == NULL) {
        printf("Error: Unable to open feedback file!\n");
        return;
    }

    // Write the feedback to the file
    fprintf(file, "Guest ID: %d, Feedback: %s\n", guestID, feedback);
    fclose(file);

    printf("Feedback saved successfully!\n");
}


/**
 * Registers a new user by saving the username and password to the users file.
 * Returns 1 if successful, 0 if the user already exists.
 */
int registerUser(const char *username, const char *password) {
    FILE *file = fopen(USER_FILE, "a+");
    if (file == NULL) {
        printf("Error: Unable to open user file!\n");
        return 0;
    }

    char line[256];
    char existingUsername[50];
    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%s", existingUsername);
        if (strcmp(existingUsername, username) == 0) {
            printf("Error: Username '%s' already exists.\n", username);
            fclose(file);
            return 0;
        }
    }

    // Write the new username and password
    fprintf(file, "%s|%s\n", username, password);
    fclose(file);
    printf("User '%s' registered successfully!\n", username);
    return 1;
}

/**
 * Logs in a user by checking if the username and password exist in the users file.
 * Sets the `loggedInUserID` to a positive value if login is successful.
 * Returns 1 if login is successful, 0 otherwise.
 */
int loginUser(const char *username, const char *password) {
    FILE *file = fopen(USER_FILE, "r");
    if (file == NULL) {
        printf("Error: Unable to open user file!\n");
        return 0;
    }

    char line[256];
    char existingUsername[50], existingPassword[50];
    int userID = 1;

    while (fgets(line, sizeof(line), file)) {
        sscanf(line, "%[^|]|%s", existingUsername, existingPassword);
        if (strcmp(existingUsername, username) == 0 && strcmp(existingPassword, password) == 0) {
            loggedInUserID = userID;  // Set the logged-in user ID
            fclose(file);
            printf("User '%s' logged in successfully!\n", username);
            return 1;
        }
        userID++;
    }

    fclose(file);
    printf("Error: Invalid username or password.\n");
    return 0;
}

/**
 * Logs out the current user by resetting the `loggedInUserID`.
 * Returns 1 if a user was logged in and successfully logged out, 0 if no user was logged in.
 */
int logoutUser() {
    if (loggedInUserID == -1) {
        printf("Error: No user is currently logged in.\n");
        return 0;
    }

    loggedInUserID = -1;
    printf("User logged out successfully!\n");
    return 1;
}
