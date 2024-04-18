#include <iostream>
#include <fstream>
#include <cstdlib>
#include <iomanip>

using namespace std;

// Function prototypes
void displayMenu();
void userLogin();
void manageBooks();
void addBook();
void searchBooks();
void deleteBook();
void editBook();
void manageOrders();
void placeOrder();
void printQuotation();
void logout();

// Global variables
string currentUser;

// Structure to represent a Book
struct Book {
    string title;
    string author;
    double price;
    int quantity;
};

// Structure to represent an Order
struct Order {
    string bookTitle;
    int quantity;
};

int main() {
    userLogin();  // User login at the beginning

    int choice;
    do {
        displayMenu();  // Display the main menu
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                manageBooks();
                break;
            case 2:
                manageOrders();
                break;
            case 3:
                printQuotation();
                break;
            case 4:
                logout();
                break;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}

void displayMenu() {
    system ("cls");
    cout << "\n";
    cout << "===== Main  Menu =====\n";
    cout << "| 1. Manage Books    |\n";
    cout << "| 2. Manage Orders   |\n";
    cout << "| 3. Print Quotation |\n";
    cout << "| 4. Logout          |\n";
    cout << "======================\n";
}

void userLogin() {
    system ("cls");
    const string username = "admin";
    const string password = "admin1234";

    cout << "====================\n";
    cout << "| Nethra Book Shop |\n";
    cout << "| Automated System |\n";
    cout << "====================\n";
    cout << "\n";
    cout << "== User Login ==\n";
    cout << "Enter username: ";
    cin >> username;
    cout << "Enter password: ";
    cin >> password;

    // You can implement user authentication logic here
    // For simplicity, let's assume any non-empty username and password is valid
    if (username==admin && password==admin1234) {
        cout << "**Invalid login. Exiting program.**\n";
        exit(1);
    }

    currentUser = username;
}

void manageBooks() {
    system ("cls");
    int choice;
    do {
        cout << "\n";
        cout << "===== Manage Books =====\n";
        cout << "| 1. Add Book          |\n";
        cout << "| 2. Search Books      |\n";
        cout << "| 3. Delete Book       |\n";
        cout << "| 4. Edit Book         |\n";
        cout << "| 5. Back to Main Menu |\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addBook();
                break;
            case 2:
                searchBooks();
                break;
            case 3:
                deleteBook();
                break;
            case 4:
                editBook();
                break;
            case 5:
                break;
            default:
                cout << "**Invalid choice. Please try again.**" << endl;
        }
    } while (choice != 5);
}

void addBook() {
    system ("cls");
    ofstream outFile("books.txt", ios::app);  // Open file in append mode
    if (!outFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    Book newBook;
    cout << "\n";
    cout << "==== Add Book ====\n";
    cout << "Enter Book Title: ";
    cin.ignore();
    getline(cin, newBook.title);
    cout << "Enter Author: ";
    getline(cin, newBook.author);
    cout << "Enter Price: ";
    cin >> newBook.price;
    cout << "Enter Quantity: ";
    cin >> newBook.quantity;

    // Write the book information to the file
    outFile << newBook.title << "," << newBook.author << "," << newBook.price << "," << newBook.quantity << endl;

    outFile.close();
    cout << "**Book added successfully.**\n";
}

void searchBooks() {
    system ("cls");
    ifstream inFile("books.txt");
    if (!inFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    string searchTitle;
    cout << "\n";
    cout << "========= Search Book =========\n";
    cout << "Enter the Book Title to search: ";
    cin.ignore();
    getline(cin, searchTitle);

    bool found = false;
    while (!inFile.eof()) {
        Book currentBook;
        getline(inFile, currentBook.title, ',');
        getline(inFile, currentBook.author, ',');
        inFile >> currentBook.price;
        inFile.ignore();
        inFile >> currentBook.quantity;
        inFile.ignore();

        if (currentBook.title == searchTitle) {
            found = true;
            cout << "\n";
            cout << "----- Book Details -----\n";
            cout << "Title: " << currentBook.title << "\n";
            cout << "Author: " << currentBook.author << "\n";
            cout << "Price: " << currentBook.price << "\n";
            cout << "Quantity: " << currentBook.quantity << "\n";
        }
    }

    if (!found) {
        cout << "**Book not found.**\n";
    }

    inFile.close();
}

void deleteBook() {
    system ("cls");
    string titleToDelete;
    cout << "\n";
    cout << "========= Delete Book =========\n";
    cout << "Enter the Book Title to delete: ";
    cin.ignore();
    getline(cin, titleToDelete);

    ifstream inFile("books.txt");
    if (!inFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "**Error opening temporary file.**" << endl;
        inFile.close();
        return;
    }

    bool found = false;
    while (!inFile.eof()) {
        Book currentBook;
        getline(inFile, currentBook.title, ',');
        getline(inFile, currentBook.author, ',');
        inFile >> currentBook.price;
        inFile.ignore();
        inFile >> currentBook.quantity;
        inFile.ignore();

        if (currentBook.title == titleToDelete) {
            found = true;
            cout << "\n----- Book Deleted -----\n";
            cout << "Title: " << currentBook.title << "\n";
            cout << "Author: " << currentBook.author << "\n";
            cout << "Price: " << currentBook.price << "\n";
            cout << "Quantity: " << currentBook.quantity << "\n";
        } else {
            // Write non-matching books to the temporary file
            tempFile << currentBook.title << "," << currentBook.author << "," << currentBook.price << ","
                     << currentBook.quantity << endl;
        }
    }

    if (!found) {
        cout << "**Book not found.**\n";
    }

    inFile.close();
    tempFile.close();

    // Remove the original file and rename the temporary file
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void editBook() {
    system ("cls");
    string titleToEdit;
    cout << "\n";
    cout << "========= Edit Book =========\n";
    cout << "Enter the Book Title to edit: ";
    cin.ignore();
    getline(cin, titleToEdit);

    ifstream inFile("books.txt");
    if (!inFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    ofstream tempFile("temp.txt");
    if (!tempFile) {
        cerr << "**Error opening temporary file.**" << endl;
        inFile.close();
        return;
    }

    bool found = false;
    while (!inFile.eof()) {
        Book currentBook;
        getline(inFile, currentBook.title, ',');
        getline(inFile, currentBook.author, ',');
        inFile >> currentBook.price;
        inFile.ignore();
        inFile >> currentBook.quantity;
        inFile.ignore();

        if (currentBook.title == titleToEdit) {
            found = true;
            cout << "\n----- Editing Book -----\n";
            cout << "Title: " << currentBook.title << "\n";
            cout << "Author: " << currentBook.author << "\n";
            cout << "Price: " << currentBook.price << "\n";
            cout << "Quantity: " << currentBook.quantity << "\n";

            cout << "\nEnter new details:\n";
            cout << "Enter new Title: ";
            getline(cin, currentBook.title);
            cout << "Enter new Author: ";
            getline(cin, currentBook.author);
            cout << "Enter new Price: ";
            cin >> currentBook.price;
            cout << "Enter new Quantity: ";
            cin >> currentBook.quantity;

            tempFile << currentBook.title << "," << currentBook.author << "," << currentBook.price << ","
                     << currentBook.quantity << endl;

            cout << "**Book details updated.**\n";
        } else {
            // Write non-matching books to the temporary file
            tempFile << currentBook.title << "," << currentBook.author << "," << currentBook.price << "," << currentBook.quantity << endl;
        }
    }

    if (!found) {
        cout << "**Book not found.**\n";
    }

    inFile.close();
    tempFile.close();

    // Remove the original file and rename the temporary file
    remove("books.txt");
    rename("temp.txt", "books.txt");
}

void manageOrders() {
    system ("cls");
    int choice;
    do {
        cout << "\n";
        cout << "==== Manage  Orders ====\n";
        cout << "| 1. Place Order       |\n";
        cout << "| 2. Back to Main Menu |\n";
        cout << "========================\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                placeOrder();
                break;
            case 2:
                break;
            default:
                cout << "**Invalid choice. Please try again.**" << endl;
        }
    } while (choice != 2);
}

void placeOrder() {
    system ("cls");
    ifstream inFile("books.txt");
    if (!inFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    string orderTitle;
    int orderQuantity;

    cout << "\n";
    cout << "======== Place Order ========\n";
    cout << "Enter the Book Title to order: ";
    cin.ignore();
    getline(cin, orderTitle);

    bool found = false;
    while (!inFile.eof()) {
        Book currentBook;
        getline(inFile, currentBook.title, ',');
        getline(inFile, currentBook.author, ',');
        inFile >> currentBook.price;
        inFile.ignore();
        inFile >> currentBook.quantity;
        inFile.ignore();

        if (currentBook.title == orderTitle) {
            found = true;
            cout << "Available Quantity: " << currentBook.quantity << endl;
            cout << "Enter Quantity to Order: ";
            cin >> orderQuantity;

            if (orderQuantity > 0 && orderQuantity <= currentBook.quantity) {
                // Reduce the available quantity in the file
                currentBook.quantity -= orderQuantity;

                // Update the book information in the file
                ofstream outFile("books.txt");
                if (!outFile) {
                    cerr << "**Error opening file.**" << endl;
                    inFile.close();
                    return;
                }

                while (!inFile.eof()) {
                    outFile << currentBook.title << "," << currentBook.author << "," << currentBook.price << ","
                            << currentBook.quantity << endl;
                    inFile.ignore();
                    getline(inFile, currentBook.title, ',');
                    getline(inFile, currentBook.author, ',');
                    inFile >> currentBook.price;
                    inFile.ignore();
                    inFile >> currentBook.quantity;
                    inFile.ignore();
                }

                cout << "**Order placed successfully.**\n";
            } else {
                cout << "**Invalid Quantity. Order not placed.**\n";
            }
        }
    }

    if (!found) {
        cout << "**Book not found.**\n";
    }

    inFile.close();
}

void printQuotation() {
    system ("cls");
    ifstream inFile("books.txt");
    if (!inFile) {
        cerr << "**Error opening file.**" << endl;
        return;
    }

    ofstream outFile("quotation.txt");
    if (!outFile) {
        cerr << "**Error opening file.**" << endl;
        inFile.close();
        return;
    }

    double totalAmount = 0;

    outFile << "======= Quotation =======\n";
    outFile << setw(20) << left << "Title" << setw(20) << left << "Author"
            << setw(10) << right << "Price" << setw(15) << right << "Quantity" << setw(15) << right << "Amount" << endl;
    outFile << setfill('-') << setw(70) << "" << setfill(' ') << endl;

    while (!inFile.eof()) {
        Book currentBook;
        getline(inFile, currentBook.title, ',');
        getline(inFile, currentBook.author, ',');
        inFile >> currentBook.price;
        inFile.ignore();
        inFile >> currentBook.quantity;
        inFile.ignore();

        double amount = currentBook.price * currentBook.quantity;
        totalAmount += amount;

        outFile << setw(20) << left << currentBook.title << setw(20) << left << currentBook.author
                << setw(10) << right << currentBook.price << setw(15) << right << currentBook.quantity
                << setw(15) << right << amount << endl;
    }

    outFile << setfill('-') << setw(70) << "" << setfill(' ') << endl;
    outFile << setw(65) << right << "Total Amount:" << setw(5) << right << totalAmount << endl;

    cout << "**Quotation printed successfully. Check 'quotation.txt' for details.**\n";

    inFile.close();
    outFile.close();
}

void logout() {
    system ("cls");
    cout << "Logging out. Have a nice day, " << currentUser << "!\n";
    exit(0);
}
