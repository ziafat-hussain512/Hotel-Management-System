# Hotel-Management-System


 Overview of the Hotel Management System:

This is a console-based hotel management system designed to manage room bookings, users, and waiting lists. The code is structured with linked lists and a queue for managing room allocation and handling customer requests.


 Key Components and Features:

1. **Data Structures:**
   - **Node Struct**: Represents a room in the hotel with attributes such as Room ID, Customer Name, Date, and Room Type (single/double).
   - **Linked List**: A linked list is used to store room records. The `head` pointer tracks the first room in the list.
   - **Queue**: A queue (`waitlist`) is used to handle customers waiting for a room when all rooms are occupied.

2. **User Authentication:**
   - **Signup**: Allows a user to sign up with a unique username and password, which are stored in a `map`.
   - **Login**: Prompts the user to log in by entering their username and password. If valid, they can access the hotel management menu.

3. **Room Management:**
   - **Insert Room (`insert`)**: Adds a new room to the system, validates inputs (Room ID, Customer Name, Date, Room Type). If all rooms are taken, the customer is added to the waiting list.
   - **Search Room (`search`)**: Searches for a room by Room ID and displays the details of the room if found.
   - **Update Room (`update`)**: Allows updating room details (ID, Customer Name, Date, Room Type).
   - **Delete Room (`del`)**: Deletes a room by Room ID, and processes the queue to allocate a room to a customer in the waiting list.
   - **Show Rooms (`show`)**: Displays all allocated rooms in the system.
   - **Sort Rooms (`sort`)**: Sorts rooms by Room ID in ascending order.

 4. Queue Management:
   - **Add to Queue (`addToQueue`)**: Adds customers to the waiting list if no room is available.
   - **Process Queue (`processQueue`)**: Allocates rooms to customers from the waiting list when a room is deleted or becomes available. The new room is allocated with an incremented 
     Room ID.

5.  Menu System:
   - After logging in, the user can interact with a menu offering options like inserting, searching, updating, deleting, and displaying rooms, processing the waiting list, and more.

6. Input Validation:
     - The code includes validation for:
     - **Room ID**: Numeric input only.
     - **Customer Name**: Only alphabetic characters are allowed.
     - **Date**: Validates date format (YYYY-MM-DD).
     - **Room Type**: Only accepts 'single' or 'double' as valid room types.

7. Program Flow:
   - The system starts with a login screen. After a successful login, the user is presented with a menu to perform hotel management tasks.
   - The program continues running until the user chooses to exit.

8. Error Handling:
   - The system handles invalid inputs (e.g., non-numeric Room IDs, incorrect date formats) and prompts users to correct them.

