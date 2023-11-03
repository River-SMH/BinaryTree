/*
    River Smith
    CS222
    Handles which methods to choose for which condition is met when constructing the Tree via add/remove/search/modify. Whichever
    is used will then go further in depth with the TreeNode to apply any changes made to the Tree itself.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "Tree.h"
#include "DRT.h"
#include "TreeNode.h"
using namespace std;

Tree::Tree() { root = NULL; } //tree constructor

Tree::~Tree() { delete root; } //tree destructor

void Tree::setroot(TreeNode* r) { root = r; } //sets the root for tree

DRT* Tree::add(string key, string data) { //very similar to sample code

    if (!root) { //checks if there is no root. If none assign new root to new treenode
        root = new TreeNode(key, data, NULL, NULL, NULL, this);
        return new DRT(data, "", "");
    }
    return root->add(key, data, "", ""); //else adds the node starting from root.
}

DRT* Tree::searchnode(string key) { //searches the tree for the given key
    DRT* test;
    if (root) {
        test = root->searchnode(key,"","");
    }
    else {
        test = new DRT("", "", "");
    }
    return test;

}

string Tree::first() { //gets the furthest down left node of the tree. If there is no root then return empty string.

    string f = "";
    if (root) {
        f = root->first()->getk();
    }
    return f;

}

string Tree::last() { //last key in the tree (right all the way down). Returns empty string if no root
    string l = "";
    if (root) {
        l=root->last()->getk();
    }
    return l;

}

DRT* Tree::remove(string key) { //removes an item from the list
    if (!root) {
        return new DRT("", "", "");
    }
    return root->remove(key, "", "");

}

DRT* Tree::search(string key) { //Database search method
    //checks to see if we're searching on the empty string, if so builds a DRT with first() and last (), otherwise calls searchnode
    string f;
    string l;
    DRT* test;
    if (key == "") { //if search is empty return DRT of first/last
        f = first();
        l = last();
        test = new DRT(key, f, l);
    }
    else {
        test = searchnode(key);
        //drt return from searchnode then return this drt
    }
    
    return test;

}


DRT* Tree::modify(string key, string data) { //Database modify method

    if (key == "") return new DRT("", first(), last());
    if (data == "") return remove(key);
    return add(key, data); //handles both adding and editing
}