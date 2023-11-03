/*
    River Smith
    CS222
    Creates the Tree object while using the Database to only need the use of Modify and Search to create any data for the tree.
    This will add,remove,edit,lookup,print, and reverse print any and all data added and not added into the Tree.
*/

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "PG4.h"
#include "Database.h"
using namespace std;

Database* Studs;

int main(int argc, char** argv) { //Creates the Tree then runs commands until Exit is issued then ends program.
    //Studs = new Tree();

    //ifstream bah("C:\\Users\\rivsmith\\Desktop\\PG4.in");

    //string command;
    //while (true) {
    //    getline(bah, command);
    //    cout << "command was: " << command << endl;
    //    ProcessCommand(command);
    //    if (command == "EXIT") break;
    //}
    //cout << "finished" << endl;

    Studs = new Tree(); //creates the tree
    while (ProcessCommand()); //runs all necessary commands the user wants
    delete Studs; //removes memory leak
    return 0;
}

bool ProcessCommand() { //Looped command list to constantly allow new info to be added or removes from the Tree until EXIT is called.

    string cmd;
    cout << "Enter a command" << endl;
    getline(cin, cmd);
    if (cmd == "EXIT") return false;
    if (cmd == "PRINT") Print();
    else if (cmd == "RPRINT") RPrint();
    else if (cmd.substr(0, 3) == "ADD") AddCommand(cmd);
    else if (cmd.substr(0, 6) == "REMOVE") RemoveCommand(cmd);
    else if (cmd.substr(0, 6) == "LOOKUP") LookupCommand(cmd);
    else if (cmd.substr(0, 4) == "EDIT") EditCommand(cmd);
    else cout << "Invalid Command!" << endl;
    return true;
}

void Print() { //prints the tree from least to greatest

    cout << "Printing list forwards:" << endl;
    DRT* T = Studs->search("");//Gets DRT that has first and last
    string k = T->getnext();
    while (k != "") {
        delete T; //Removes memory leak so that it may loop back again
        T = Studs->search(k); //gets info for printing
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getnext(); //starts furthest left then goes to furthest right
    }
    delete T;
    cout << endl;
}

void RPrint() { //prints the tree from greatest to least

    cout << "Printing list backwards:" << endl;
    DRT* T = Studs->search(""); //Gets a DRT that has first and last.
    string k = T->getprev();
    while (k != "") {
        delete T; //removes memory leak so that it may loop back again.
        T = Studs->search(k); //gets the info for printing
        cout << "Name:  " << k << "\tGPA:  " << T->getdata() << endl;
        k = T->getprev();//starts furtherst right gets furthest left
    }
    delete T;
    cout << endl;
}

void AddCommand(string cmd) { //adds a node into the tree. If node is already there it doesn't add it.
    string name; //vars to hold name and gpa
    string gpa;
    int ct = 0;
    for (int x = 3; x < cmd.length(); x++) { //finds the last " then gets the substr based on it's position.
        if (cmd[x] == '"') {
            ct++;
        }
        if (ct == 2) {
            name = cmd.substr(4, x - 3);
            gpa = cmd.substr(x+2);
            break;
        }
    }
    DRT* T = Studs->search(name); //See if it's already in the Tree
    if (T->getdata() == "") {
        T = Studs->modify(name,gpa); //Adds the info into the Tree
        cout << name << " has been added with a GPA of " << gpa << endl;
    }
    else {
        cout << name << " is already in the Database" << endl;
    }

    delete T; //Removes memory leak.
}

void RemoveCommand(string cmd) { //searches the tree for node, if there removes it else it doesnt do anything.
    int ct = 0;
    string now = "";
    for (int x = 6; x < cmd.length(); x++) { //gets the substr from the cmd to then be used to search the list and remove
        if (cmd[x] == '"') {
            ct += 1;
        }
        if (ct == 2) {
            now = cmd.substr(7, x - 4);
            break;
        }
    }
    string k = now;
    DRT* T = Studs->search(k);
    if (T->getdata() == "") { //checks if not available in tree
        cout << "\"" << k << "\" does not exist in the database!" << endl;
    }
    else {
        delete T;
        T = Studs->modify(k, ""); //if it is available remove it
        cout << k << " has been removed from the database!" << endl;
    }
    delete T;
}

void LookupCommand(string cmd) { //searches tree for Node, if there says where it is in relation to the tree. Else says where it would be
    int ct = 0;
    string now = "";
    string next;
    string prev;
    for (int x = 6; x < cmd.length(); x++) { //gets the substr of the key to find then updates it with the data.
        if (cmd[x] == '"') {
            ct += 1;
        }
        if (ct == 2) {
            now = cmd.substr(7, x - 4);
            break;
        }
    }
    DRT* T = Studs->search(now);
    if (T->getdata() == "") { //if key is not in tree print out where it would have been
        next = T->getnext();
        prev = T->getprev();
        if (next == "") next = "the end of the list";
        if (prev == "") prev = "the start of the list";
        cout << now << " is not present in the Tree but would be present between " << prev << " and " << next << endl;
    } else { //if key is in tree print out where it is and its data.
        next = T->getnext();
        prev = T->getprev();
        if (next == "") next = "the end of the list";
        if (prev == "") prev = "the start of the list";
        cout << now << " with a GPA of " << T->getdata() << " is present in the Tree between " << prev << " and " << next << endl;
    }

}

void EditCommand(string cmd) { //Uses same logic as Add except only changes data if node is in the tree, else do nothing
    int ct = 0;
    string now = "";
    string newt = "";

    for (int x = 4; x < cmd.length(); x++) { //gets the substr of key and new data to add
        if (cmd[x] == '"') {
            ct++;
        }
        if (ct == 2) {
            now = cmd.substr(5, x - 4);
            newt = cmd.substr(x + 2);
            break;
        }
    }

    DRT* T = Studs->search(now);
    if (T->getdata() == "") { //if not in tree nothing to manipulate
        cout << now << " is not present to be modified" << endl;
    } else {
        delete T;
        T = Studs->modify(now, newt); //else change its data.
        cout << now << " has been edited" << endl;
    }

}