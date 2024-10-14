#include <stdio.h>
#include "guest.h"
#include "admin.h"
#include "room.h"
#include "services.h"
#include "database.h"
#include "error_handling.h"

int getUserType()
{
	int choice;
	printf("Welcome to Hotel Management System\n");
	printf("1. Guest\n2. Admin\n3. Exit\n");
	printf(">> ");
	scanf("%d", &choice);
	return choice;
}

int main()
{
	clearConsole();
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
