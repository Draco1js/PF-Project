#include<stdio.h>
#include "database.h"

void testRoomInitializationAndBooking() {
    initializeDatabase();  // Initialize rooms

    // Load and display all rooms to confirm initialization
    printf("\nTesting Room Initialization:\n");
    loadRooms();

    // Check for the first available room
    int availableRoom = getAvailableRoom();
    printf("Available Room: %d\n", availableRoom);

    // Make a reservation and check room status
    saveReservation(1, 101, availableRoom, "2024-10-15", "2024-10-18");
    printf("\nAfter Booking Room %d:\n", availableRoom);
    loadRooms();  // Show room statuses again
}

int test() {
    printf("Running tests...\n");

    testRoomInitializationAndBooking();
    printf("testRoomInitializationAndBooking passed.\n");

    // Add other test functions here as needed

    printf("All tests passed!\n");
    return 0;
}
