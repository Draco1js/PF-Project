#ifndef DATABASE_H
#define DATABASE_H

// Constants
#define MAX_ROOMS 10  // Specify the default number of rooms for the hotel
#define USER_FILE "users.txt"
#define RESERVATION_FILE "reservations.txt"
#define ROOM_FILE "rooms.txt"
#define FEEDBACK_FILE "feedback.txt"

// Reservation struct to represent reservation details
typedef struct
{
    int reservationID;
    int guestID;
    int roomNumber;
    char checkInDate[11];  // Format: yyyy-mm-dd
    char checkOutDate[11]; // Format: yyyy-mm-dd
} Reservation;

// Declare the logged-in user ID variable as extern to be accessible in other files
extern int loggedInUserID;

// Functions for managing rooms and reservations

/**
 * Initializes the database by creating room entries and setting initial statuses.
 * Creates empty reservation and feedback files if they do not exist.
 */
void initializeDatabase();

/**
 * Cancels a reservation by reservation ID.
 * @param reservationID The unique reservation identifier to cancel.
 */
void cancelReservation(int reservationID);

/**
 * Returns the first available room number.
 * @return int - The room number if available, otherwise -1 if no rooms are available.
 */
int getAvailableRoom();

/**
 * Marks a specific room as occupied by updating the room status in the room file.
 * @param roomNumber The room number to mark as occupied.
 */
void markRoomAsOccupied(int roomNumber);

/**
 * Marks a specific room as available by updating the room status in the room file.
 * @param roomNumber The room number to mark as available.
 */
void markRoomAsAvailable(int roomNumber);

/**
 * Saves a reservation to the reservations file and marks the associated room as occupied.
 * @param reservationID The unique reservation identifier.
 * @param guestID The guest ID making the reservation.
 * @param roomNumber The room number assigned for the reservation.
 * @param checkInDate The check-in date (formatted as yyyy-mm-dd).
 * @param checkOutDate The check-out date (formatted as yyyy-mm-dd).
 */
void saveReservation(int reservationID, int guestID, int roomNumber, const char *checkInDate, const char *checkOutDate);

/**
 * Loads and displays all reservations from the reservations file.
 */
void loadReservations();

/**
 * Loads and displays a specific reservation by its reservation ID.
 * @param reservationID The unique reservation identifier to search for.
 */
void loadReservationByID(int reservationID);

/**
 * Loads and displays all room statuses (Available/Occupied).
 */
void loadRooms();

/**
 * Saves feedback from a guest to the feedback file.
 * @param guestID The guest ID providing the feedback.
 * @param feedback The feedback text provided by the guest.
 */
void saveFeedback(int guestID, const char *feedback);

// Functions for user login/logout and registration

/**
 * Registers a new user by saving the username and password to the users file.
 * Returns 1 if successful, 0 if the user already exists.
 */
int registerUser(const char *username, const char *password);

/**
 * Logs in a user by checking if the username and password exist in the users file.
 * Returns 1 if login is successful, 0 otherwise.
 */
int loginUser(const char *username, const char *password);

/**
 * Logs out the currently logged-in user.
 * Returns 1 if successful, 0 if no user was logged in.
 */
int logoutUser();

#endif // DATABASE_H
