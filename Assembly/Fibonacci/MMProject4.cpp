/*
Michael Mowad
Project 4
MMProject4.cpp - provided test driver
*/


#include "AVLTree.h"
#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {

    cout << boolalpha;

    AVLTree tree;
    cout << tree.insert(50, "Fifty") << endl;
    // This should print false, because it returns false (no duplicates allowed):
    cout << tree.insert(50, "Another fifty") << endl;
    cout << tree.insert(100, "One hundred") << endl;
    cout << tree.insert(200, "Two hundred") << endl;//single rotate left
    /*
    true
    false
    true
    true
    */
    cout << "\n\n";
    cout << tree << endl;

    cout << tree.insert(40, "Fourty") << endl;
    cout << tree.insert(30, "Thirty") << endl;//single rotate right
    cout << tree.insert(150, "One hundred fifty") << endl;
    cout << tree.insert(175, "One hundred seventy-five") << endl;//double rotate right
    cout << tree.insert(35, "Thirty-five") << endl;
    cout << tree.insert(34, "Thirty-four") << endl;//double rotate left
    cout << tree.insert(50, "Fifty yet again") << endl;//should be false
    cout << tree.insert(34, "Thirty-four again") << endl;//should be false;
    cout << tree.insert(200, "Two hundred") << endl;//should be false;
    /*
    true
    true
    true
    true
    true
    true
    false
    false
    false
    */
    cout << "\n\n";

    cout << tree << endl;
    cout << tree.getSize() << endl;//9
    cout << tree.getHeight() << endl;//3

    string result;

    cout << tree.find(50, result) << endl;//true
    cout << result << endl; //Fifty

    cout << tree.find(40, result) << endl;//true
    cout << result << endl; //Fourty

    cout << tree.find(175, result) << endl;//true
    cout << result << endl; //One hundred seventy-five

    cout << tree.find(600, result) << endl; //false

    vector<string> vec = tree.findRange(30, 200);//all of it
    for (string s : vec) {
        cout << s << endl;
    }
    cout << "\n\n" << endl;

    vec = tree.findRange(100, 200);//right subtree
    for (string s : vec) {
        cout << s << endl;
    }
    cout << "\n\n" << endl;
    vec = tree.findRange(30, 100);//left subtree
    for (string s : vec) {
        cout << s << endl;
    }
    cout << "\n\n" << endl;

    return 0;


}
