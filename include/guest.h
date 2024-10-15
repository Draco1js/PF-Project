#ifndef GUEST_H
#define GUEST_H

// Function declarations for the guest menu and related operations
void guestMenu(void);                 // Displays the guest menu and handles user choices
void signUp(void);                   // Handles user registration
void login(void);                    // Handles user login
void browseRooms(void);              // Displays available rooms
void bookRoom(void);                 // Allows the user to book a room
void cancelUserReservation(void);         // Allows the user to cancel a reservation
void requestService(void);           // Allows the user to request a service
void giveFeedback(void);             // Allows the user to give feedback
void logout(void);                   // Handles user logout

#endif // GUEST_H
