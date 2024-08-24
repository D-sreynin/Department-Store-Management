#include <iostream>
#include <fstream>
#include <string>

using namespace std;

const string FILE_NAME = "inventory.txt";

// Product class
class Product {
private:
    string name;
    int quantity;

public:
    Product() {}
    Product(const string& name, int quantity) : name(name), quantity(quantity) {}

    string getName() const {
        return name;
    }

    int getQuantity() const {
        return quantity;
    }

    friend ostream& operator<<(ostream& os, const Product& product) {
        os << "Name: " << product.name << ", Quantity: " << product.quantity << endl;
        return os;
    }
};

// Function prototypes
void addProduct();
void searchProduct();
void deleteProduct();
void displayInventory();

int main() {
    int choice;

    while (1) {
        cout << "\nDepartmental Store Management System" << endl;
        cout << "1. Add Product" << endl;
        cout << "2. Search Product" << endl;
        cout << "3. Delete Product" << endl;
        cout << "4. Display Inventory" << endl;
        cout << "5. Exit" << endl;
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                addProduct();
                break;
            case 2:
                searchProduct();
                break;
            case 3:
                deleteProduct();
                break;
            case 4:
                displayInventory();
                break;
            case 5:
                cout << "Exiting the program. Goodbye!" << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }
    }

    return 0;
}

void addProduct() {
    string name;
    int quantity;

    cout << "\nEnter product name: ";
    cin >> name;
    cout << "Enter product quantity: ";
    cin >> quantity;

    ofstream file(FILE_NAME, ios::app);
    if (!file) {
        cout << "Error opening file for writing." << endl;
        return;
    }

    file << name << " " << quantity << endl;
    file.close();

    cout << "Product added successfully." << endl;
}

void searchProduct() {
    string searchName;
    string name;
    int quantity;
    bool found = false;

    cout << "\nEnter product name to search: ";
    cin >> searchName;

    ifstream file(FILE_NAME);
    if (!file) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    while (file >> name >> quantity) {
        if (name == searchName) {
            cout << "Product found:" << endl;
            cout << "Name: " << name << ", Quantity: " << quantity << endl;
            found = true;
            break;
        }
    }

    file.close();

    if (!found) {
        cout << "Product not found." << endl;
    }
}

void deleteProduct() {
    string deleteName;
    string name;
    int quantity;
    bool found = false;

    cout << "\nEnter product name to delete: ";
    cin >> deleteName;

    ifstream inputFile(FILE_NAME);
    if (!inputFile) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    ofstream outputFile("temp.txt");
    if (!outputFile) {
        cout << "Error opening file for writing." << endl;
        inputFile.close();
        return;
    }

    while (inputFile >> name >> quantity) {
        if (name != deleteName) {
            outputFile << name << " " << quantity << endl;
        } else {
            found = true;
        }
    }

    inputFile.close();
    outputFile.close();

    if (found) {
        remove(FILE_NAME.c_str());
        rename("temp.txt", FILE_NAME.c_str());
        cout << "Product deleted successfully." << endl;
    } else {
        cout << "Product not found." << endl;
        remove("temp.txt");
    }
}

void displayInventory() {
    string name;
    int quantity;

    cout << "\nInventory:" << endl;

    ifstream file(FILE_NAME);
    if (!file) {
        cout << "Error opening file for reading." << endl;
        return;
    }

    while (file >> name >> quantity) {
        cout << "Name: " << name << ", Quantity: " << quantity << endl;
    }

    file.close();
}