/*
	River Smith
	CS222
	Holds all the info needed for the DRT that the tree will then use to create and return all info.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "DRT.h"
#include "Tree.h"
using namespace std;

DRT::DRT(string d, string n, string p) { //DRT constructor

	data = d; next = n; prev = p;
}

string DRT::getdata() { return data; } //returns string info from data

string DRT::getnext() { return next; } //returns string info from next

string DRT::getprev() { return prev; } //returns string info from prev