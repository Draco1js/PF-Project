#include <stdio.h>
#include "guest.h"
#include "admin.h"
#include "database.h"
#include "error_handling.h"
#include "test.h"

int getUserType()
{
	int choice;
	printf("------------------------------------------------\n");
	printf("|     Welcome to Hotel Management System       |\n");
	printf("|     1. Guest                                 |\n");
	printf("|     2. Admin                                 |\n");
	printf("|     3. Exit                                  |\n");
	printf("------------------------------------------------\n");
	printf(">> ");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	
	// Uncomment the following line to run the test cases
	// return test();

	clearConsole();
	initializeDatabase();

	int userType = getUserType();
	while (userType != 3)
	{

		if (userType == 1)
		{
			clearConsole();
			guestMenu();
		}
		else if (userType == 2)
		{
			clearConsole();
			adminMenu();
		}
		else
		{
			clearConsole();
			handleInputError();
		}
		userType = getUserType();
	}
	printf("Exiting the system. Goodbye!\n");
	return 0;
}
