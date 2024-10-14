#include <stdio.h>
#include "error_handling.h"

void handleInputError()
{
    printf("Invalid input. Please try again.\n");
}

void handleDatabaseError()
{
    printf("Database error. Please contact support.\n");
}

void handleServiceError()
{
    printf("Service request failed. Please try again later.\n");
}

void clearConsole()
{
    // Clear the console
    printf("\033[H\033[J");
}
