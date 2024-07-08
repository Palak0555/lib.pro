#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_BOOKS 100
#define MAX_TITLE_LENGTH 100
#define MAX_AUTHOR_LENGTH 100
#define MAX_PUBLICATION_LENGTH 100
#define MAX_BORROWERS 50
#define MAX_BORROWER_NAME 100

// Data structures
struct Book {
    char bookId[MAX_TITLE_LENGTH];
    char title[MAX_TITLE_LENGTH];
    char author[MAX_AUTHOR_LENGTH];
    char publication[MAX_PUBLICATION_LENGTH];
    double cost; // Changed data type to double to represent rupees
    int isAvailable;
};

struct Borrowing {
    char bookId[MAX_BOOKS]; // Use MAX_BOOKS for bookId
    char borrowerName[MAX_BORROWER_NAME];
    char dateOfIssue[11]; // Format: YYYY-MM-DD
    char dateOfReturn[11]; // Format: YYYY-MM-DD
};

// Function prototypes
void showLibraryMasterMenu();
void showLibraryEditorMenu();
void searchBook();
void addBook();
void updateBook();
void deleteBook();
void displayAllBooks();
void borrowBook();
void returnBook();
int findAvailableBook();
int findBookById(const char* bookId);
void saveData();
void loadData();

// Global variables
struct Book library[MAX_BOOKS];
int numBooks = 0;
struct Borrowing borrowings[MAX_BORROWERS];
int numBorrowings = 0;

int main() {
    printf("\n");
    printf("*************************************************************\n");
    printf("*                                                           *\n");
    printf("*          Welcome to the Library Management System         *\n");
    printf("*                                                           *\n");
    printf("*************************************************************\n");

    loadData(); // Load data from the file at the beginning

    int menuChoice;

    do {
        // Display the main menu options
        printf("\nChoose any of the following option :\n");
        printf("1. Library Master\n");
        printf("2. Library Editor\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &menuChoice);

        switch (menuChoice) {
            case 1:
                showLibraryMasterMenu();
                break;
            case 2:
                showLibraryEditorMenu();
                break;
            case 3:
                saveData(); // Save data to the file before exiting
                printf("Exiting the program.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (menuChoice != 3);

    return 0;
}

void saveData() {
    FILE *file = fopen("library_data.txt", "w");
    if (file == NULL) {
        printf("Error opening file to save data.\n");
        return;
    }

    // Save book information
    fprintf(file, "%d\n", numBooks);
    for (int i = 0; i < numBooks; i++) {
        fprintf(file, "%s\n", library[i].bookId);
        fprintf(file, "%s\n", library[i].title);
        fprintf(file, "%s\n", library[i].author);
        fprintf(file, "%s\n", library[i].publication);
        fprintf(file, "%.2f\n", library[i].cost);
        fprintf(file, "%d\n", library[i].isAvailable);
    }

    // Save borrowing information
    fprintf(file, "%d\n", numBorrowings);
    for (int i = 0; i < numBorrowings; i++) {
        fprintf(file, "%s\n", borrowings[i].bookId);
        fprintf(file, "%s\n", borrowings[i].borrowerName);
        fprintf(file, "%s\n", borrowings[i].dateOfIssue);
        fprintf(file, "%s\n", borrowings[i].dateOfReturn);
    }

    fclose(file);
}

void loadData() {
    FILE *file = fopen("library_data.txt", "r");
    if (file == NULL) {
        printf("No previous data found.\n");
        return;
    }

    // Load book information
    fscanf(file, "%d\n", &numBooks);
    for (int i = 0; i < numBooks; i++) {
        fgets(library[i].bookId, sizeof(library[i].bookId), file);
        library[i].bookId[strcspn(library[i].bookId, "\n")] = '\0';
        fgets(library[i].title, sizeof(library[i].title), file);
        library[i].title[strcspn(library[i].title, "\n")] = '\0';
        fgets(library[i].author, sizeof(library[i].author), file);
        library[i].author[strcspn(library[i].author, "\n")] = '\0';
        fgets(library[i].publication, sizeof(library[i].publication), file);
        library[i].publication[strcspn(library[i].publication, "\n")] = '\0';
        fscanf(file, "%lf\n", &library[i].cost);
        fscanf(file, "%d\n", &library[i].isAvailable);
    }

    // Load borrowing information
    fscanf(file, "%d\n", &numBorrowings);
    for (int i = 0; i < numBorrowings; i++) {
        fgets(borrowings[i].bookId, sizeof(borrowings[i].bookId), file);
        borrowings[i].bookId[strcspn(borrowings[i].bookId, "\n")] = '\0';
        fgets(borrowings[i].borrowerName, sizeof(borrowings[i].borrowerName), file);
        borrowings[i].borrowerName[strcspn(borrowings[i].borrowerName, "\n")] = '\0';
        fgets(borrowings[i].dateOfIssue, sizeof(borrowings[i].dateOfIssue), file);
        borrowings[i].dateOfIssue[strcspn(borrowings[i].dateOfIssue, "\n")] = '\0';
        fgets(borrowings[i].dateOfReturn, sizeof(borrowings[i].dateOfReturn), file);
        borrowings[i].dateOfReturn[strcspn(borrowings[i].dateOfReturn, "\n")] = '\0';
    }

    fclose(file);
}

void showLibraryMasterMenu() {
    int choice;
    do {
        // Display Library Master menu options
        printf("\nLibrary Master Menu:\n");
        printf("1. Search a Book\n");
        printf("2. Add a Book\n");
        printf("3. Update Book Information\n");
        printf("4. Delete a Book\n");
        printf("5. Display All Books\n"); // New option to display all books
        printf("6. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                searchBook();
                break;
            case 2:
                addBook();
                break;
            case 3:
                updateBook();
                break;
            case 4:
                deleteBook();
                break;
            case 5:
                displayAllBooks(); // Call the new function to display all books
                break;
            case 6:
                printf("Exiting Library Master menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 6);
}

void showLibraryEditorMenu() {
    int choice;
    do {
        // Display Library Editor menu options
        printf("\nLibrary Editor Menu:\n");
        printf("1. Borrow a Book\n");
        printf("2. Return a Book\n");
        printf("3. Exit to Main Menu\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                borrowBook();
                break;
            case 2:
                returnBook();
                break;
            case 3:
                printf("Exiting Library Editor menu.\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 3);
}

void searchBook() {
    char bookId[MAX_TITLE_LENGTH];
    printf("Enter the Book ID to search for: ");
    getchar(); // Remove the newline character from the previous input
    fgets(bookId, sizeof(bookId), stdin);
    bookId[strcspn(bookId, "\n")] = '\0';

    int bookIndex = findBookById(bookId);

    if (bookIndex == -1) {
        printf("Book with ID %s not found.\n", bookId);
        return;
    }

    printf("\nBook Information:\n");
    printf("Book ID: %s\n", library[bookIndex].bookId);
    printf("Title: %s\n", library[bookIndex].title);
    printf("Author: %s\n", library[bookIndex].author);
    printf("Publication: %s\n", library[bookIndex].publication);
    printf("Cost: Rs %.2f\n", library[bookIndex].cost); // Display cost in rupees
    printf("Status: %s\n", library[bookIndex].isAvailable ? "Available" : "Borrowed");
}

void addBook() {
    if (numBooks == MAX_BOOKS) {
        printf("The library is full. Cannot add more books.\n");
        return;
    }

    struct Book newBook;
    printf("Enter Book ID: ");
    getchar(); // Remove the newline character from the previous input
    fgets(newBook.bookId, sizeof(newBook.bookId), stdin);
    newBook.bookId[strcspn(newBook.bookId, "\n")] = '\0';

    // Check if the Book ID is alphanumeric
    for (int i = 0; newBook.bookId[i] != '\0'; i++) {
        if (!isalnum(newBook.bookId[i])) {
            printf("Invalid Book ID. Only alphanumeric characters are allowed.\n");
            return;
        }
    }

    int bookIndex = findBookById(newBook.bookId);
    if (bookIndex != -1) {
        printf("Book with ID %s already exists.\n", newBook.bookId);
        return;
    }

    printf("Enter Title: ");
    fgets(newBook.title, sizeof(newBook.title), stdin);
    newBook.title[strcspn(newBook.title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(newBook.author, sizeof(newBook.author), stdin);
    newBook.author[strcspn(newBook.author, "\n")] = '\0';

    printf("Enter Publication: ");
    fgets(newBook.publication, sizeof(newBook.publication), stdin);
    newBook.publication[strcspn(newBook.publication, "\n")] = '\0';

    printf("Enter Cost in Rupees: ");
    scanf("%lf", &newBook.cost); // Read cost as double

    newBook.isAvailable = 1; // New book is available

    library[numBooks] = newBook;
    numBooks++;

    printf("Book added successfully.\n");
}

void updateBook() {
    char bookId[MAX_TITLE_LENGTH];
    printf("Enter the Book ID to update: ");
    getchar(); // Remove the newline character from the previous input
    fgets(bookId, sizeof(bookId), stdin);
    bookId[strcspn(bookId, "\n")] = '\0';

    int bookIndex = findBookById(bookId);

    if (bookIndex == -1) {
        printf("Book with ID %s not found.\n", bookId);
        return;
    }

    printf("Enter Title: ");
    fgets(library[bookIndex].title, sizeof(library[bookIndex].title), stdin);
    library[bookIndex].title[strcspn(library[bookIndex].title, "\n")] = '\0';

    printf("Enter Author: ");
    fgets(library[bookIndex].author, sizeof(library[bookIndex].author), stdin);
    library[bookIndex].author[strcspn(library[bookIndex].author, "\n")] = '\0';

    printf("Enter Publication: ");
    fgets(library[bookIndex].publication, sizeof(library[bookIndex].publication), stdin);
    library[bookIndex].publication[strcspn(library[bookIndex].publication, "\n")] = '\0';

    printf("Enter Cost in Rupees: ");
    scanf("%lf", &library[bookIndex].cost); // Read cost as double

    printf("Book information updated successfully.\n");
}

void deleteBook() {
    char bookId[MAX_TITLE_LENGTH];
    printf("Enter the Book ID to delete: ");
    getchar(); // Remove the newline character from the previous input
    fgets(bookId, sizeof(bookId), stdin);
    bookId[strcspn(bookId, "\n")] = '\0';

    int bookIndex = findBookById(bookId);

    if (bookIndex == -1) {
        printf("Book with ID %s not found.\n", bookId);
        return;
    }

    // Shift the array elements to remove the book at bookIndex
    for (int i = bookIndex; i < numBooks - 1; i++) {
        library[i] = library[i + 1];
    }

    numBooks--;

    printf("Book deleted successfully.\n");
}

int findBookById(const char* bookId) {
    for (int i = 0; i < numBooks; i++) {
        if (strcmp(library[i].bookId, bookId) == 0) {
            return i;
        }
    }
    return -1; // Book not found
}

void displayAllBooks() {
    if (numBooks == 0) {
        printf("No books in the library.\n");
        return;
    }

    printf("\nAll Books in the Library:\n");

    printf("| %-10s | %-40s | %-25s | %-15s | %-8s |\n",
           "Book ID", "Title", "Author", "Publication", "Cost");
    printf("+------------+----------------------------------------+-------------------------+---------------+-----------------+\n");
    for (int i = 0; i < numBooks; i++) {
        printf("| %-10s | %-40s | %-25s | %-15s | Rs %-8.2f |\n",
               library[i].bookId, library[i].title, library[i].author,
               library[i].publication, library[i].cost);
    }
    printf("+------------+----------------------------------------+-------------------------+---------------+-----------------+\n");
}

void borrowBook() {
    if (numBooks == 0) {
        printf("No books in the library.\n");
        return;
    }

    char bookId[MAX_TITLE_LENGTH];
    printf("Enter the Book ID to borrow: ");
    getchar(); // Remove the newline character from the previous input
    fgets(bookId, sizeof(bookId), stdin);
    bookId[strcspn(bookId, "\n")] = '\0';

    int bookIndex = findBookById(bookId);

    if (bookIndex == -1) {
        printf("Book with ID %s not found.\n", bookId);
        return;
    }

    if (!library[bookIndex].isAvailable) {
        printf("Book with ID %s is already borrowed.\n", bookId);
        return;
    }

    printf("Enter Borrower's Name: ");
    fgets(borrowings[numBorrowings].borrowerName, sizeof(borrowings[numBorrowings].borrowerName), stdin);
    borrowings[numBorrowings].borrowerName[strcspn(borrowings[numBorrowings].borrowerName, "\n")] = '\0';

    printf("Enter Date of Issue (DD-MM-YYYY): ");
    scanf("%s", borrowings[numBorrowings].dateOfIssue);

    printf("Enter Date of Return (DD-MM-YYYY): ");
    scanf("%s", borrowings[numBorrowings].dateOfReturn);

    // Update book availability status
    library[bookIndex].isAvailable = 0;

    // Copy bookId to borrowing array
    strcpy(borrowings[numBorrowings].bookId, bookId);

    numBorrowings++;

    printf("Book borrowed successfully.\n");
}

void returnBook() {
    if (numBorrowings == 0) {
        printf("No books are currently borrowed.\n");
        return;
    }

    char bookId[MAX_TITLE_LENGTH];
    printf("Enter the Book ID to return: ");
    getchar(); // Remove the newline character from the previous input
    fgets(bookId, sizeof(bookId), stdin);
    bookId[strcspn(bookId, "\n")] = '\0';

    int bookIndex = findBookById(bookId);

    if (bookIndex == -1) {
        printf("Book with ID %s not found.\n", bookId);
        return;
    }

    int borrowingIndex = -1;
    for (int i = 0; i < numBorrowings; i++) {
        if (strcmp(borrowings[i].bookId, bookId) == 0) {
            borrowingIndex = i;
            break;
        }
    }

    if (borrowingIndex == -1) {
        printf("Book with ID %s is not currently borrowed.\n", bookId);
        return;
    }

    printf("Enter Date of Return (DD-MM-YYYY): ");
    scanf("%s", borrowings[borrowingIndex].dateOfReturn);

    // Update book availability status
    library[bookIndex].isAvailable = 1;

    // Shift the array elements to remove the returned borrowing
    for (int i = borrowingIndex; i < numBorrowings - 1; i++) {
        borrowings[i] = borrowings[i + 1];
    }

    numBorrowings--;

    printf("Book returned successfully.\n");
}

