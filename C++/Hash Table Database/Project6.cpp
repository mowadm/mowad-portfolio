// Michael Mowad
// Project 6
// Project6.cpp
// Main class for handling various functions in a student information database


#include <iostream>
#include "HashTable.h"
#include "Database.h"

int main()
{   
    Database db = Database();
    string choice = "";

    string last = "";
    string first = "";
    int uid = 0;
    string year = "";
    int collisions = 0;

    while (true) {

        cout << "Would you like to (I)nsert, (D)elete, (S)earch, (P)rint, or (Q)uit?" << endl;
        cout << "Enter action: ";
        cin >> choice;

        // If Q exit
        if (choice == "Q" || choice == "q") {
            exit(0);
        }
        // If I insert
        else if (choice == "I" || choice == "i") {
            cout << "Inserting a new record." << endl;

            // Get inputs
            cout << "Last name: ";
            cin >> last;
            cout << "First name: ";
            cin >> first;
            cout << "UID: ";
            cin >> uid;
            cout << "Year: ";
            cin >> year;

            Record record = Record(first, last, uid, year);

            if (db.insert(record, collisions)) {
                cout << "Record inserted (" << collisions << " colissions during insert)." << "\n" << endl;
            }
            else {
                cout << "ERROR: Record insertion failed" << "\n" << endl;
            }


        }
        // If D delete
        else if (choice == "D" || choice == "d") {
            cout << "Deleting a record." << endl;

            // Get input
            cout << "UID to delete: ";
            cin >> uid;

            if (db.remove(uid)) {
                cout << "Record successfully deleted" << "\n" << endl;
            }
            else {
                cout << "ERROR: Record deletion failed" << "\n" << endl;
            }

        }
        // If S search
        else if (choice == "S" || choice == "s") {
            cout << "Searching for a record." << endl;

            // Get input
            cout << "UID to search for: ";
            cin >> uid;

            Record record;

            if (db.find(uid, record, collisions)) {
                cout << "Record found (" << collisions << " collisions during search)" << endl;
                cout << "--------------------------------------" << endl;
                cout << "Last name: " << record.getLastName() << endl;
                cout << "First name: " << record.getFirstName() << endl;
                cout << "UID: " << record.getUID() << endl;
                cout << "Year: " << record.getYear() << endl;
                cout << "--------------------------------------" << "\n" << endl;
            }
            else {
                cout << "ERROR: Record search failed" << "\n" << endl;
            }
        }
        // If P print
        else if (choice == "P" || choice == "p") {

            cout << "\n" << "Database contents:" << endl;
            cout << db << "\n" << endl;
        }


    }
}