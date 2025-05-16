#include <iostream>
#include <fstream>
#include <vector>
#include <string>
using namespace std;

class Book {
public:
    int id;
    string title;
    string author;
    bool isIssued;

    Book() {
        id = 0;
        title = "";
        author = "";
        isIssued = false;
    }

    void addBook() {
        cout << "Enter Book ID: ";
        cin >> id;
        cin.ignore(); // clear input buffer
        cout << "Enter Title: ";
        getline(cin, title);
        cout << "Enter Author: ";
        getline(cin, author);
        isIssued = false;
    }

    void display() {
        cout << "ID: " << id << ", Title: " << title << ", Author: " << author;
        cout << ", Status: " << (isIssued ? "Issued" : "Available") << endl;
    }
};

class Library {
    vector<Book> books;

public:
    void loadFromFile() {
        ifstream file("books.txt");
        if (!file) return; // file not found, start fresh

        Book b;
        while (file >> b.id) {
            file.ignore();
            getline(file, b.title);
            getline(file, b.author);
            file >> b.isIssued;
            file.ignore();
            books.push_back(b);
        }
        file.close();
    }

    void saveToFile() {
        ofstream file("books.txt");
        for (auto &b : books) {
            file << b.id << "\n" << b.title << "\n" << b.author << "\n" << b.isIssued << "\n";
        }
        file.close();
    }

    void addBook() {
        Book b;
        b.addBook();
        books.push_back(b);
        cout << "Book added successfully!\n";
    }

    void viewBooks() {
        if (books.empty()) {
            cout << "No books in library.\n";
            return;
        }
        for (auto &b : books)
            b.display();
    }

    Book* findBookById(int id) {
        for (auto &b : books) {
            if (b.id == id) return &b;
        }
        return nullptr;
    }

    void issueBook() {
        int id;
        cout << "Enter book ID to issue: ";
        cin >> id;
        Book* b = findBookById(id);
        if (b == nullptr) {
            cout << "Book not found.\n";
            return;
        }
        if (b->isIssued) {
            cout << "Book already issued.\n";
        } else {
            b->isIssued = true;
            cout << "Book issued successfully.\n";
        }
    }

    void returnBook() {
        int id;
        cout << "Enter book ID to return: ";
        cin >> id;
        Book* b = findBookById(id);
        if (b == nullptr) {
            cout << "Book not found.\n";
            return;
        }
        if (!b->isIssued) {
            cout << "This book is not issued.\n";
        } else {
            b->isIssued = false;
            cout << "Book returned successfully.\n";
        }
    }
};

int main() {
    Library lib;
    lib.loadFromFile();

    int choice;
    do {
        cout << "\n=== Library Management System ===\n";
        cout << "1. Add Book\n2. View All Books\n3. Issue Book\n4. Return Book\n5. Save & Exit\n";
        cout << "Enter choice: ";
        cin >> choice;

        switch (choice) {
            case 1: lib.addBook(); break;
            case 2: lib.viewBooks(); break;
            case 3: lib.issueBook(); break;
            case 4: lib.returnBook(); break;
            case 5: lib.saveToFile(); cout << "Data saved. Exiting...\n"; break;
            default: cout << "Invalid choice. Try again.\n";
        }
    } while (choice != 5);

    return 0;
}
