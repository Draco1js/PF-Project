# PF Lab Project-1





THIS REPO IS ARCHIVED, THE FINAL COMBINED VERSION OF THE PROJECT IS IN THE ROOT OF THE REPOSITORY








This is the main repository for the PF Lab Project, anyone contributing needs to verify your github account with me.

Please look up how to make a pull request, DO NOT commit directly to the repository.

## To run this project:

- Make sure you have some form of gcc installed for whatever platform you are using
- run `make` in your console
- That's it!

## Explanation for debugging purposes:


The `Makefile` file is a script that automatically takes all the source files from the `src` directory, and the headers from the `include` directory, and dumps all the object files into the `build` directory, it then creates an executable called `hotel` and automatically runs it for you.


Whenever you're working on this project, and need a method to be available in another file to use, make sure you are mentioning it in the respective header file of the exact name, in a similar format to the already-present methods.

## How to Contribute:

Use [this](https://www.dataschool.io/how-to-contribute-on-github/) guide to learn how to fork and create pull requests efficiently: [by dataschool.io](https://www.dataschool.io/how-to-contribute-on-github/)

## Testing

To test individual functions or components of this program, you can follow a modular testing approach. This will help you isolate and debug specific parts of your system without having to run the entire program every time. Below are some strategies for testing individual modules in C:


You can create a separate C file in the tests directory (e.g., test.c) dedicated to testing specific functions. This file will serve as a temporary test harness where you call individual functions, pass in sample data, and print the results to verify functionality.

You can run this by first uncommenting these lines at the start of `main.c`:
```c
.
.

int main()
{
	// //Uncomment the following line to run the test cases
	// return test();

.
.
```

then create your test cases in `test/test.c` and then run `make test`

Example Test File (test.c)
```c
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
```
