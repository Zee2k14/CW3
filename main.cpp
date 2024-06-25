#include <limits>
#include <iostream>
#include <vector>
#include <string>
#include "FileSystem.hpp"

using namespace std;

void printMenu() {
    cout << "=======================================\n";
    cout << "Filesystem Menu:\n";
    cout << "1. Create File\n";
    cout << "2. Delete File\n";
    cout << "3. Read File\n";
    cout << "4. Write File\n";
    cout << "5. Create Directory\n";
    cout << "6. Delete Directory\n";
    cout << "7. List Directory Contents\n";
    cout << "8. Change Directory\n";
    cout << "9. Display Current Directory\n";
    cout << "10. Exit\n";
    cout << "Enter your choice: ";
}

void listDirectoryContents(Directory* dir) {
    auto contents = dir->listContents();
    cout << "Directory contents:\n";
    for (const auto& item : contents) {
        cout << item << "\n";
    }
}

int main() {
    FileSystem fs;
    int choice;
    string filename, dirname;
    vector<char> data;
    string inputData, path;

    while (true) {
        printMenu();
        cin >> choice;
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        switch (choice) {
            case 1:
                cout << "Enter filename: ";
                getline(cin, filename);
                fs.createFile(filename);
                cout << "File created successfully.\n";
                break;

            case 2:
                cout << "Enter filename: ";
                getline(cin, filename);
                fs.deleteFile(filename);
                cout << "File deleted successfully.\n";
                break;

            case 3:
                cout << "Enter filename: ";
                getline(cin, filename);
                try {
                    data = fs.readFile(filename);
                    cout << "File content: ";
                    for (char c : data) {
                        cout << c;
                    }
                    cout << "\n";
                } catch (const runtime_error& e) {
                    cout << e.what() << "\n";
                }
                break;

            case 4:
                cout << "Enter filename: ";
                getline(cin, filename);
                cout << "Enter data to write: ";
                getline(cin, inputData);
                data.assign(inputData.begin(), inputData.end());
                try {
                    fs.writeFile(filename, data);
                    cout << "Data written successfully.\n";
                } catch (const runtime_error& e) {
                    cout << e.what() << "\n";
                }
                break;

            case 5:
                cout << "Enter directory name: ";
                getline(cin, dirname);
                fs.createDirectory(dirname);
                cout << "Directory created successfully.\n";
                break;

            case 6:
                cout << "Enter directory name: ";
                getline(cin, dirname);
                fs.deleteDirectory(dirname);
                cout << "Directory deleted successfully.\n";
                break;

            case 7:
                listDirectoryContents(fs.getCurrentDirectory());
                break;

            case 8:
                cout << "Enter path (.. to go back): ";
                getline(cin, path);
                try {
                    fs.changeDirectory(path);
                    cout << "Current directory changed to: " << fs.getCurrentDirectory()->getName() << "\n";
                } catch (const runtime_error& e) {
                    cout << e.what() << "\n";
                }
                break;

            case 9:
                cout << "Current directory: " << fs.getCurrentDirectory()->getName() << "\n";
                break;

            case 10:
                cout << "Exiting...\n";
                return 0;

            default:
                cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}
