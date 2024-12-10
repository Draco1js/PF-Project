#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_ROOMS 100
#define MAX_RESERVATIONS 50
#define MAX_FEEDBACKS 50
#define MAX_REQUESTS 50

const char *usersdb = "users.txt";
const char *roomsdb = "rooms.txt";
const char *reservationsdb = "reservations.txt";
const char *feedbackdb = "feedback.txt";
const char *requestsdb = "requests.txt";

// =========================== STRUCTURES =========================== //
typedef struct {
    char room_no[10];
    char room_type[50];
    float price;
    int quantity;
} Room;

typedef struct {
    char user[50];
    char room_no[10];
    char check_in_date[20];
    char check_out_date[20];
} Reservation;

typedef struct {
    char user[50];
    char feedback[200];
} Feedback;

typedef struct {
    char user[50];
    char request[200];
} ServiceRequest;

// =========================== GLOBAL VARIABLES =========================== //
Room rooms[MAX_ROOMS];
Reservation reservations[MAX_RESERVATIONS];
Feedback feedbacks[MAX_FEEDBACKS];
ServiceRequest requests[MAX_REQUESTS];

int room_count = 0;
int reservation_count = 0;
int feedback_count = 0;
int request_count = 0;
int isAdminLogin=1;
int loginChoice=0;
char loggedInUser[50] = ""; // Tracks the current logged-in user
int i, j;

// =========================== UTILITY FUNCTIONS =========================== //
void clearConsole() {
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
//system("cls||clear");
}

void pressKeyToContinue() {
    printf("\nPress any key to continue...");
    getchar();
    getchar();
}

void displayHeading() {
    clearConsole();
	printf("=================================================================================================================\n");
	printf("\n\t\t\t\t\t\tHotel Management Syetem\n");
	printf("\n=================================================================================================================\n");
}

void Title_heading() {
	clearConsole();
	printf("=============================================================================================================\n\n\n");
	printf("\t\t\t\t\tPROUDLY PRESENTED BY:\n");
	printf("\n\t\t\t\t01) Aayan Sultan (24K-2015)\n\t\t\t\t02) Ali Safir (24K-2039)\n\t\t\t\t03) Humayun Shahid (24K-2011)\n\t\t\t\t04) Umais Ahmed (24K-2043)\n\t\t\t\t05) Zumair Shamsi (24K-2040)");
	printf("\n\n\n=============================================================================================================");
	pressKeyToContinue();
}

// File Handling Functions
void loadRooms();  /* Load room data */ 
void saveRooms();  /* Save room data */ 
void loadReservations();  /* Load reservation data */ 
void saveReservations();  /* Save reservation data */ 
void loadFeedbacks();  /* Load feedbacks */ 
void saveFeedbacks();  /* Save feedbacks */ 
void loadRequests(); /* Load service requests */ 
void saveRequests();  /* Save service requests */ 

// Guest Functions
void guestMenu();
int userSignup();  /* User signup  */ 
int userLogin();/* User login */ 
void browseRooms();  /* Browse available rooms */ 
void bookRoom();  /* Book a room */ 
void requestService(); /* Submit service request */ 
void giveFeedback(); /* Submit feedback */ 

// Admin Functions
void adminMenu();
void adminLogin() ; /* Admin login */ 
void addRoom();  /* Add a room */ 
void modifyRoom(); /* Modify room details */ 
void deleteRoom(); /* Delete a room */ 
void viewRoom();  /* View room details */ 
void viewReservations();  /* View all reservations */ 
void viewFeedbacks();  /* View user feedback */ 
void viewRequests(); /* View user service requests */ 
void generateReport();  /* Generate revenue report */ 

// Guest Menu

// Main Function
void loadAllData() {
    loadRooms();
    loadReservations();
    loadFeedbacks();
    loadRequests();
}

void saveAllData() {
    saveRooms();
    saveReservations();
    saveFeedbacks();
    saveRequests();
}

void guestLoginSignup() {
    do {
        clearConsole();
        displayHeading();
        printf("\n\t\t\t1. Login\n\t\t\t2. Sign Up\n\t\t\t3. Exit\n");
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &loginChoice);
        switch (loginChoice) {
            case 1:
                if (userLogin()) {
                    guestMenu();
                }
                break;
            case 2:
                userSignup();
                break;
            case 3:
                printf("\n\t\t\tExiting....");
                break;
            default:
                printf("\nInvalid Input....");
                pressKeyToContinue();
        }
    } while (loginChoice != 3);
}

void mainMenu() {
    int choice;
    do {
        displayHeading();
        printf("\n\t\t\t1. Guest Login / Sign Up\n");
        printf("\t\t\t2. Admin Login\n");
        printf("\t\t\t3. Exit\n");
        printf("\n\t\t\tEnter your choice : ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                guestLoginSignup();
                break;
            case 2:
                adminLogin();
                if (isAdminLogin) {
                    adminMenu();
                }
                break;
            case 3:
                printf("\n\t\t\tExiting system. Goodbye!\n");
                break;
            default:
                printf("\n\t\t\tInvalid choice! Please try again.\n");
        }
        pressKeyToContinue();
    } while (choice != 3);
}

int main() {
    Title_heading();
    loadAllData();
    mainMenu();
    saveAllData();
    return 0;
}

// =========================== FILE HANDLING =========================== //

void loadRooms() {
	
    FILE *file = fopen(roomsdb, "r");
    
    if (file == NULL) {
    	
        printf("\nNo room data found.\n");
        
        return;
    }
    
    while (fscanf(file, "%s %s %f %d", rooms[room_count].room_no, rooms[room_count].room_type,  &rooms[room_count].price, &rooms[room_count].quantity) != EOF) {
                  	
        room_count++;
    }
    
    fclose(file);
}




void saveRooms() {
	
    FILE *file = fopen(roomsdb, "w");
    
    for (i = 0; i < room_count; i++) {
    	
        fprintf(file, "%s %s %.2f %d\n", rooms[i].room_no, rooms[i].room_type, rooms[i].price, rooms[i].quantity);
    }
    
    fclose(file);
}

void loadReservations() {
	
    FILE *file = fopen(reservationsdb, "r");
    
    if (file == NULL) {   	
        return;
    }
    
    while (fscanf(file, "%s %s %s %s", reservations[reservation_count].user, reservations[reservation_count].room_no, reservations[reservation_count].check_in_date,
        reservations[reservation_count].check_out_date) != EOF) {
                  	
        reservation_count++;
    }
    
    fclose(file);
}

void saveReservations() {
	
    FILE *file = fopen(reservationsdb, "w");
    
    for (i = 0; i < reservation_count; i++) {
    	
        fprintf(file, "%s %s %s %s\n", reservations[i].user, reservations[i].room_no, reservations[i].check_in_date,  reservations[i].check_out_date);
    }
    
    fclose(file);
}

void loadFeedbacks() {
	
    FILE *file = fopen(feedbackdb, "r");
    
    if (file == NULL) {
        return;
    }
    
    while (fscanf(file, "%s %[^\n]", feedbacks[feedback_count].user, feedbacks[feedback_count].feedback) != EOF) {
    	
        feedback_count++;
    }
    
    fclose(file);
}

void saveFeedbacks() {
	
    FILE *file = fopen(feedbackdb, "w");
    
    for (i = 0; i < feedback_count; i++) {
    	
        fprintf(file, "%s %s\n", feedbacks[i].user, feedbacks[i].feedback);
    }
    
    fclose(file);
}

void loadRequests() {
	
    FILE *file = fopen(requestsdb, "r");
    
    if (file == NULL) {
        return;
    }
    
    while (fscanf(file, "%s %[^\n]", requests[request_count].user, requests[request_count].request) != EOF) {
    	
        request_count++;
    }
    
    fclose(file);
}

void saveRequests() {
	
    FILE *file = fopen(requestsdb, "w");
    
    for (i = 0; i < request_count; i++) {
    	
        fprintf(file, "%s %s\n", requests[i].user, requests[i].request);
    }
    
    fclose(file);
}

// =========================== ADMIN FUNCTIONS =========================== //

// Admin Menu

void adminMenu() {
	
    int choice;
    
    do {
    	
        clearConsole();
        displayHeading();
        
        printf("\n\t\t\t===== ADMIN MENU =====\n\n");
        
        printf("\t\t\t1. Add Room\n");
        printf("\t\t\t2. Modify Room\n");
        printf("\t\t\t3. Delete Room\n");
        printf("\t\t\t4. View Rooms\n");
        printf("\t\t\t5. View Reservations\n");
        printf("\t\t\t6. View Feedbacks\n");
        printf("\t\t\t7. View Service Requests\n");
        printf("\t\t\t8. Generate Report\n");
        printf("\t\t\t9. Logout\n");
        
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        	
            case 1: 
				addRoom(); 
				break;
				
            case 2: 
				modifyRoom();
				break;
				
            case 3: 
				deleteRoom();
				break;
				
            case 4: 
				viewRoom(); 
				break;
				
            case 5: 
				viewReservations(); 
				break;
				
            case 6: 
				viewFeedbacks(); 
				break;
				
				
            case 7: 
				viewRequests(); 
				break;
				
            case 8: 
				generateReport(); 
				break;
				
            case 9:
                printf("\n\t\t\tLogging out...\n");
                return;
                
            default:
                printf("\nInvalid choice! Please try again.\n");
                
        }
        
        pressKeyToContinue();
        
    } while (choice != 9);
    
}

void adminLogin(){
    
	char admin[20], password[10] = "admin";
	int opt;
	
	printf ("\n\n\t\t\t\t\t\t=====ADMIN LOGIN=====\t\t\t\t\t\t\t");

	printf("\n\n\t\t\t\t\tEnter the password to login : ");
	scanf("%s", admin);
	
	if ( strcmp(admin, password) == 0) {
	
		printf("\nPassword Match \n");
		
		pressKeyToContinue();
		clearConsole();
		
	}
	
	else {

		printf("Invalid password \n\n\a\a");
		try_again:
			
		printf("Enter 1 to try again and 0 to exit :");
		scanf("%d", &opt);
		
		if (opt == 1) {
			
//			clearConsole();
//			displayHeading();

			isAdminLogin = 0;
			
			return;
		} 
		
		else if (opt == 0) {
			
//			clearConsole();
			isAdminLogin = 0;
			
			return ;		
		} 
		
		else {
			
			printf("invalid");
			clearConsole();
			
			goto try_again;
		}
		
	}
	
}

void addRoom() {
	
    if (room_count >= MAX_ROOMS) {
    	
        printf("Room capacity reached. Cannot add more rooms.\n");
        return;
    }
    
    printf("\nEnter Room Code : ");
    scanf("%s", rooms[room_count].room_no);
    
    getchar();
    
    printf("Enter Room Type : ");
    fgets(rooms[room_count].room_type, sizeof(rooms[room_count].room_type), stdin);
    rooms[room_count].room_type[strcspn(rooms[room_count].room_type, "\n")] = 0; // this line removes new line
    
    printf("Enter Room Price : ");
    scanf("%f", &rooms[room_count].price);
    
    printf("Enter Room Quantity : ");
    scanf("%d", &rooms[room_count].quantity);
    room_count++;
    
    saveRooms();
    
    printf("Room added successfully!\n");
}

void modifyRoom() {
	
    char room_no[10];
    
    printf("\nEnter Room Code to Modify : ");
    scanf("%s", room_no);
    
    getchar();

    for (i = 0; i < room_count; i++) {
    	
        if (strcmp(rooms[i].room_no, room_no) == 0) {
        	
            printf("Enter New Room Type : ");
            fgets(rooms[room_count].room_type, sizeof(rooms[room_count].room_type), stdin);
    		rooms[room_count].room_type[strcspn(rooms[room_count].room_type, "\n")] = 0; // this line removes new line
            
            printf("Enter New Room Price : ");
            scanf("%f", &rooms[i].price);
            
            printf("Enter New Room Quantity : ");
            scanf("%d", &rooms[i].quantity);
            
            saveRooms();
            
            printf("Room modified successfully!\n");
            return;
        }
        
    }
    
    printf("Room not found.\n");
}

void deleteRoom() {
	
    char room_no[10];
    
    printf("Enter Room Code to Delete: ");
    scanf("%s", room_no);

    for (i = 0; i < room_count; i++) {
    	
        if (strcmp(rooms[i].room_no, room_no) == 0) {
        	
            for (j = i; j < room_count - 1; j++) {
            	
                rooms[j] = rooms[j + 1];
            }
            
            room_count--;

            saveRooms();
            
            printf("Room deleted successfully!\n");
            return;
        }
    }
    
    printf("Room not found.\n");
}


void viewRoom() {
	
    printf("\n\t\t===Available Rooms:===\n\n%-13s %-15s %-10s %-10s\n", "Room Code", "Room Type", "Price", "Quantity");
    
    printf("------------------------------------------------------------------\n");
    
    for (i = 0; i < room_count; i++) {
    	
        printf("%-13s %-15s %-10.2f %-10d\n", rooms[i].room_no, rooms[i].room_type, rooms[i].price, rooms[i].quantity);
    }
    
}

void viewReservations() {
	
	FILE *file = fopen(reservationsdb, "r");
	
	if (file == NULL) {
    	
        printf("\nNo reservations found (file missing or empty).\n");
        return;
    }
	
    printf("\n\t\t\t--- Room Reservations ---\n\n");
    
    printf("%-13s %-15s %-15s %-10s\n", "Room Code", "Name", "Check-in", "Check-out");
    
    printf("------------------------------------------------------------------\n");
    
    for (i = 0; i < reservation_count; i++) {
    	
        printf("%-13s %-15s %-15s %-10s\n", reservations[i].room_no, reservations[i].user, reservations[i].check_in_date, reservations[i].check_out_date);
    }
    
}


void generateReport() {
	
    float revenue = 0.0;
    printf("\n\t\t\t=== Reservation Report ===\n\n");
    
    for (i = 0; i < reservation_count; i++) {
    	
        for (j = 0; j < room_count; j++) {
        	
            if (strcmp(reservations[i].room_no, rooms[j].room_no) == 0) {
            	
                revenue += rooms[j].price;
                break;
            }
        }
    }
    
    printf("Total Revenue: %.2f\n", revenue);
    
}

void viewFeedbacks() {
	
    FILE *file = fopen(feedbackdb, "r");
    
    if (file == NULL) {
    	
        printf("\nNo feedback found (file missing or empty).\n");
        return;
    }

    printf("\n\t\t\t===== Feedback =====\n\n");
    printf("%-20s %-50s\n", "User", "Feedback");
    printf("------------------------------------------------------------\n");

    char user[50], feedback[200];
    
    while (fscanf(file, "%s %[^\n]", user, feedback) != EOF) {
    	
        printf("%-20s %-50s\n", user, feedback);
    }

    fclose(file);
    
    printf("\n");
}

void viewRequests() {
	
    FILE *file = fopen(requestsdb, "r");
    
    if (file == NULL) {
    	
        printf("\nNo service requests found (file missing or empty).\n");
        return;
    }

    printf("\n\t\t\t===== Service Requests =====\n\n");
    printf("%-20s %-50s\n", "User", "Request");
    printf("------------------------------------------------------------\n");

    char user[50], request[200];
    
    while (fscanf(file, "%s %[^\n]", user, request) != EOF) {
    	
        printf("%-20s %-50s\n", user, request);
    }

    fclose(file);
    
    printf("\n");
}


// =========================== GUEST FUNCTIONS =========================== //

void guestMenu() {
	
    int choice;
    
    do {
        clearConsole();
        displayHeading();
        
        printf("\n\t\t\t===== GUEST MENU =====\n\n");
        
        printf("\t\t\t1. Browse Rooms\n");
        printf("\t\t\t2. Book Room\n");
        printf("\t\t\t3. Request Service\n");
        printf("\t\t\t4. Give Feedback\n");
        printf("\t\t\t5. Logout\n");
        
        printf("\n\t\t\tEnter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
        	
            case 1: 
				browseRooms(); 
				break;
				
            case 2: 
				bookRoom(); 
				break;
				
            case 3: 
				requestService(); 
				break;
				
            case 4: 
				giveFeedback(); 
				break;
				
            case 5:
                printf("\n\t\t\tLogging out...\n");
                strcpy(loggedInUser, "");
                return;
                
            default:
            	
                printf("\nInvalid choice! Please try again.\n");
                
        }
        
        pressKeyToContinue();
        
    } while (choice != 5);
    
}


int userSignup() {
	
    char username[50], password[50];
    
    FILE *file = fopen(usersdb, "a+");
    
    if (!file) {
    	
        printf("Error opening user file.\n");
        return 0;
    }

    // get user details
    printf("\nEnter your username : ");
    scanf("%s", username);
    
    printf("Enter your password : ");
    scanf("%s", password);

    // check if the user already exists
    char temp_username[50], temp_password[50];
    
    while (fscanf(file, "%s %s", temp_username, temp_password) != EOF) {
    	
        if (strcmp(temp_username, username) == 0) {
        	
            printf("User already exists.\n");
                      
			fclose(file);
			
			pressKeyToContinue(); 
            
            return 0; // user already exists
        }
    }

    // save new user to the file
    fprintf(file, "%s %s\n", username, password);
    
    printf("Sign-up successful!\n");

    fclose(file);
    
    pressKeyToContinue(); 
    
    return 1;
}

int userLogin() {
	
    char username[50], password[50];
    int success = 0;

    FILE *file = fopen(usersdb, "r");
    
    if (file == NULL) {
    	
        printf("No users found. Please sign up first.\n");
        return 0;
    }

    printf("\nEnter your username : ");
    scanf("%s", username);
    
    printf("Enter your password : ");
    scanf("%s", password);
    

    char temp_username[50], temp_password[50];
    
    while (fscanf(file, "%s %s", temp_username, temp_password) != EOF) {
    	
        if (strcmp(temp_username, username) == 0 && strcmp(temp_password, password) == 0) {
        	
            success = 1;
            strcpy(loggedInUser, username);  // store the logged-in user's name
            break;
        }
    }
    
    fclose(file);

    if (success == 1) {
    	
        printf("\nLogin successful! Welcome, %s.\n", loggedInUser);
        
        pressKeyToContinue(); 
        
        return 1;
    
    } 
	
	else {
		
        printf("\nInvalid username or password.\n");
        
        pressKeyToContinue(); 
        
        return 0;
    }
    
    
    
}


void browseRooms() {
	
    printf("\n\t\t===Available Rooms: ===\n\n%-13s %-20s %-10s %-10s\n", "Room Code", "Room Type", "Price", "Quantity");
    
    for (i = 0; i < room_count; i++) {
    	
        printf("%-13s %-20s %-10.2f %-10d\n", rooms[i].room_no, rooms[i].room_type, rooms[i].price, rooms[i].quantity);
    }
}


void bookRoom() {
	
    char room_no[10];
    char check_in_date[20];
    char check_out_date[20];

    if (strcmp(loggedInUser, "") == 0) {
    	
        printf("Please log in to book a room.\n");
        return;
    }

    printf("\nEnter Room Code to Book : ");
    scanf("%s", room_no);
    
    for (i = 0; i < room_count; i++) {
    	
        if (strcmp(rooms[i].room_no, room_no) == 0 && rooms[i].quantity > 0) {
        	
            //taking check-in and check-out dates from user
            printf("Enter Check-in Date (DD-MM-YYYY): ");
            scanf("%s", check_in_date);
            
            printf("Enter Check-out Date (DD-MM-YYYY): ");
            scanf("%s", check_out_date);

            // decreasing room quantity
            rooms[i].quantity--;

            // add reservation details
            strcpy(reservations[reservation_count].user, loggedInUser);
            strcpy(reservations[reservation_count].room_no, room_no);
            strcpy(reservations[reservation_count].check_in_date, check_in_date);
            strcpy(reservations[reservation_count].check_out_date, check_out_date);
            
            reservation_count++;

            // save changes
            saveRooms();
            saveReservations();

            printf("Room booked successfully from %s to %s!\n", check_in_date, check_out_date);
            
            return;
        }
        
    }

    printf("Invalid room number or room not available.\n");
    
}

void requestService() {
	
    if (strcmp(loggedInUser, "") == 0) {
    	
        printf("Please log in to request a service.\n");
        return;
    }
    
    printf("\nEnter your service request: ");
    getchar();
    fgets(requests[request_count].request, 200, stdin);
    requests[request_count].request[strcspn(requests[request_count].request, "\n")] = '\0';
    
    strcpy(requests[request_count].user, loggedInUser);
    
    request_count++;
    saveRequests();
    
    printf("Service request submitted successfully!\n");
    
}

void giveFeedback() {
	
    if (strcmp(loggedInUser, "") == 0) {
    	
        printf("Please log in to give feedback.\n");
        return;
    }
    
    printf("\nEnter your feedback: ");
    getchar();  
    fgets(feedbacks[feedback_count].feedback, 200, stdin);
    feedbacks[feedback_count].feedback[strcspn(feedbacks[feedback_count].feedback, "\n")] = '\0';
    
    strcpy(feedbacks[feedback_count].user, loggedInUser);
    
    feedback_count++;
    saveFeedbacks();
    
    printf("Feedback submitted successfully!\n");
    
}



