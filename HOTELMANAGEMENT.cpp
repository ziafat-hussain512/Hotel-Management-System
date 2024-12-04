#include <iostream>
#include <string>
#include <map>
#include <queue> // For queue logic
using namespace std;

class Hotel {
private:
    struct Node {
        int id;
        string date;
        string name, roomtype;
        Node* next = nullptr;
    };

    queue<Node*> waitlist; // Queue for managing the waiting list

public:
    Node* head = nullptr;

    void insert();
    void menu();
    void update();
    void search();
    void del();
    void sort();
    void show();
    void addToQueue(const string& name, const string& date, const string& roomtype);
    void processQueue();
};

// User authentication system
map<string, string> users;

void signup() {
    string username, password;
    cout << "\n--- Signup ---\n";
    cout << "Enter Username: ";
    cin >> username;

    if (users.find(username) != users.end()) {
        cout << "Username already exists. Please try a different one.\n";
        return;
    }

    cout << "Enter Password: ";
    cin >> password;
    users[username] = password;
    cout << "Signup Successful!\n";
}

bool login() {
    string username, password;
    cout << "\n--- Login ---\n";
    cout << "Enter Username: ";
    cin >> username;

    if (users.find(username) == users.end()) {
        cout << "Username not found. Please signup first.\n";
        return false;
    }

    cout << "Enter Password: ";
    cin >> password;

    if (users[username] == password) {
        cout << "Login Successful!\n";
        return true;
    } else {
        cout << "Incorrect Password. Try again.\n";
        return false;
    }
}

void Hotel::menu() {
    int choice;
    do {
        system("cls");

        cout << "\n\t\t\t\t\tWelcome to Hotel Management System\n\n\n\n";
        cout << "\n\t|******** Hotel Management System ********|";
        cout << "\n\nS.No    Function                       Description" << endl;
        cout << "\n1\tAllocate Room\t\t\tInsert New Room";
        cout << "\n2\tSearch Room\t\t\tSearch Room with RoomID";
        cout << "\n3\tUpdate Room\t\t\tUpdate Room Record";
        cout << "\n4\tDelete Room\t\t\tDelete Room with RoomID";
        cout << "\n5\tShow Room Records\t\tShow Room Records that (we Added)";
        cout << "\n6\tProcess Waiting List\t\tAllocate rooms to queued customers";
        cout << "\n7\tExit" << endl;

        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                insert();
                break;
            case 2:
                search();
                break;
            case 3:
                update();
                break;
            case 4:
                del();
                break;
            case 5:
                sort();
                show();
                break;
            case 6:
                processQueue();
                break;
            case 7:
                exit(0);
            default:
                cout << "Invalid Choice\n";
        }
        cout << "\nPress Enter to return to the menu...";
        cin.ignore();
        cin.get();
    } while (choice != 7);
}

#include <regex> // For regex validation

void Hotel::insert() {
    cout << "\n\t_________ Hotel Management System________";

    Node* newnode = new Node;

    // Validate Room ID (Numbers Only)
    while (true) {
        cout << "\nEnter Room ID (numeric): ";
        cin >> newnode->id;
        if (cin.fail()) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Invalid input. Please enter numeric Room ID only.\n";
        } else {
            break;
        }
    }

    // Validate Customer Name (Alphabets Only)
    cin.ignore();
    while (true) {
        cout << "Enter Customer Name (alphabets only): ";
        getline(cin, newnode->name);
        if (regex_match(newnode->name, regex("^[a-zA-Z ]+$"))) {
            break;
        } else {
            cout << "Invalid input. Please enter alphabets only.\n";
        }
    }

    // Validate Allocated Date (Format: YYYY-MM-DD)
    while (true) {
        cout << "Enter Allocated Date (format: YYYY-MM-DD): ";
        getline(cin, newnode->date);
        if (regex_match(newnode->date, regex("^\\d{4}-\\d{2}-\\d{2}$"))) {
            break;
        } else {
            cout << "Invalid date format. Please enter in YYYY-MM-DD format.\n";
        }
    }

    // Validate Room Type (single/double only)
    while (true) {
        cout << "Enter Room Type (single/double): ";
        cin >> newnode->roomtype;
        if (newnode->roomtype == "single" || newnode->roomtype == "double") {
            break;
        } else {
            cout << "Invalid room type. Please enter 'single' or 'double' only.\n";
        }
    }

    // Insert the node into the linked list or add to the waiting list
    if (head == nullptr) {
        head = newnode;
        cout << "\n\n\t\t New Room Inserted";
    } else {
        Node* ptr = head;
        while (ptr->next != nullptr) {
            ptr = ptr->next;
        }

        if (ptr->id == newnode->id) {
            cout << "\nRoom already allocated. Adding to waitlist...\n";
            addToQueue(newnode->name, newnode->date, newnode->roomtype);
            delete newnode;
        } else {
            ptr->next = newnode;
            cout << "\n\n\t\t New Room Inserted";
        }
    }
}


void Hotel::search() {
    cout << "\n\t_________ Hotel Management System________";
    int t_id;
    if (head == nullptr) {
        cout << "\n\nNo records to search.\n";
    } else {
        cout << "\nEnter Room ID: ";
        cin >> t_id;
        Node* ptr = head;
        while (ptr != nullptr) {
            if (t_id == ptr->id) {
                cout << "\n\nRoom ID: " << ptr->id;
                cout << "\nCustomer Name: " << ptr->name;
                cout << "\nAllocated Date: " << ptr->date;
                cout << "\nRoom Type: " << ptr->roomtype;
                return;
            }
            ptr = ptr->next;
        }
        cout << "Room not found.\n";
    }
}

void Hotel::update() {
    // Existing code
    cout << "\n\t_________ Hotel Management System________";
    int t_id;
    if (head == nullptr) {
        cout << "\n\nNo records to update.\n";
    } else {
        cout << "\nEnter Room ID: ";
        cin >> t_id;
        Node* ptr = head;
        while (ptr != nullptr) {
            if (t_id == ptr->id) {
                cout << "Enter New Room ID: ";
                cin >> ptr->id;
                cout << "Enter New Customer Name: ";
                cin.ignore();
                getline(cin, ptr->name);
                cout << "Enter New Allocated Date: ";
                cin >> ptr->date;
                cout << "Enter New Room Type (single/double): ";
                cin >> ptr->roomtype;
                cout << "\n\n\t\t Record Updated Successfully";
                return;
            }
            ptr = ptr->next;
        }
        cout << "Room not found.\n";
    }
}


void Hotel::del() {
    cout << "\n\t_________ Hotel Management System________";
    int t_id;
    if (head == nullptr) {
        cout << "\n\nNo records to delete.\n";
    } else {
        cout << "\nEnter Room ID: ";
        cin >> t_id;

        if (head->id == t_id) {
            Node* ptr = head;
            head = head->next;
            delete ptr;
            cout << "Deleted Room Record Successfully\n";

            // Process the queue after deleting a room
            processQueue();
            return;
        }

        Node* prev = head;
        Node* ptr = head->next;
        while (ptr != nullptr) {
            if (ptr->id == t_id) {
                prev->next = ptr->next;
                delete ptr;
                cout << "Deleted Room Record Successfully\n";

                // Process the queue after deleting a room
                processQueue();
                return;
            }
            prev = ptr;
            ptr = ptr->next;
        }
        cout << "Room not found.\n";
    }
}

void Hotel::show() {
    cout << "\n\t_________ Hotel Management System________";
    Node* ptr = head;
    if (ptr == nullptr) {
        cout << "\n\nNo records to show.\n";
        return;
    }
    while (ptr != nullptr) {
        cout << "\n\nRoom ID: " << ptr->id;
        cout << "\nCustomer Name: " << ptr->name;
        cout << "\nAllocated Date: " << ptr->date;
        cout << "\nRoom Type: " << ptr->roomtype;
        ptr = ptr->next;
    }
}
void Hotel::sort() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }
    for (Node* i = head; i->next != nullptr; i = i->next) {
        for (Node* j = head; j->next != nullptr; j = j->next) {
            if (j->id > j->next->id) {
                swap(j->id, j->next->id);
                swap(j->name, j->next->name);
                swap(j->date, j->next->date);
                swap(j->roomtype, j->next->roomtype);
            }
        }
    }
}



void Hotel::addToQueue(const string& name, const string& date, const string& roomtype) {
    Node* waitCustomer = new Node;
    waitCustomer->name = name;
    waitCustomer->date = date;
    waitCustomer->roomtype = roomtype;
    waitlist.push(waitCustomer);
    cout << "Added to waiting list.\n";
}

void Hotel::processQueue() {
    if (head == nullptr) {
        cout << "No rooms available to process queue.\n";
        return;
    }

    // Find the last room ID
    int newId = 1;
    Node* ptr = head;
    while (ptr->next != nullptr) {
        ptr = ptr->next;
    }
    newId = ptr->id + 1;

    while (!waitlist.empty()) {
        Node* waitCustomer = waitlist.front();
        waitlist.pop();

        Node* newRoom = new Node;
        newRoom->id = newId++;
        newRoom->name = waitCustomer->name;
        newRoom->date = waitCustomer->date;
        newRoom->roomtype = waitCustomer->roomtype;
        newRoom->next = nullptr;

        ptr->next = newRoom;
        ptr = newRoom; // Move ptr to the new room

        cout << "Allocated Room ID: " << newRoom->id << " to " << newRoom->name << "\n";
        delete waitCustomer;
    }
}

int main() {
    Hotel h;
    int choice;

    do {
        system("cls");

        cout << "\n\t\t\t\tWelcome to Hotel Management System\n\n";
        cout << "1. Signup\n";
        cout << "2. Login\n";
        cout << "3. Exit\n";
        cout << "Enter Your Choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                signup();
                break;
            case 2:
                if (login()) {
                    h.menu();
                }
                break;
            case 3:
                cout << "Exiting... Goodbye!\n";
                exit(0);
            default:
                cout << "Invalid Choice. Please try again.\n";
        }
        cout << "\nPress Enter to return to the main menu...";
        cin.ignore();
        cin.get();
    } while (choice != 3);

    return 0;
}
