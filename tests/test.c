#include <stdio.h>
#include "guest.h"
#include "admin.h"
#include "room.h"
#include "services.h"
#include "error_handling.h"

// Test function for Guest features
void testGuestFunctions() {
    printf("\nTesting Guest Functions:\n");
    
    // Simulate Sign Up
    printf("Running signUp()...\n");
    signUp();

    // Simulate Browse Rooms
    printf("Running browseRooms()...\n");
    browseRooms();
    
    // Simulate Book Room
    printf("Running bookRoom()...\n");
    bookRoom();
}

// Test function for Admin features
void testAdminFunctions() {
    printf("\nTesting Admin Functions:\n");
    
    // Simulate Admin Login
    printf("Running adminLogin()...\n");
    adminLogin();
    
    // Simulate Manage Rooms
    printf("Running manageRooms()...\n");
    manageRooms();
}

// Main function to call test cases
int test() {
    printf("Running individual function tests...\n");

    // Call individual test functions
    testGuestFunctions();
    testAdminFunctions();
    
    printf("Testing complete.\n");
    return 0;
}