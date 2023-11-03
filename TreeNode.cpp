/*
	River Smith
	CS222
	Manipulates the Tree's Data via TreeNodes that are part of DRTs. This will add nodes if not already in the system. Edit them if they
	are in the system and called through EDIT command. Removes the Node and its Data. Searches through the Tree to find the nodes needed
	to make all of these changes possible.
*/

#include <iostream>
#include <string>
#include <cstdlib>
#include "TreeNode.h"
#include "DRT.h"
using namespace std;

TreeNode::TreeNode(string key, string data, TreeNode* l, TreeNode* r, TreeNode* p, Tree* T) { //TreeNode Constructor

	k = key; d = data; left = l; right = r; parent = p; t = T;
}

TreeNode::~TreeNode() { //destructor

	delete left; //deletes each subnode of this TreeNode
	delete right;
}

DRT* TreeNode::add(string key, string data, string n, string p) { //Checks if there is a right or left node when going down the Tree to then apply the new Node
	
	DRT* track = new DRT(data, n, p); //DRT to be manipulated by the Add.

	if (key > this->getk()) {//Checks if right

		if (this->getright()) {
			track = this->getright()->add(key, data, n, this->getk()); //if right call method again to go further down
		}
		else {
			TreeNode* rightNode = new TreeNode(key, data, NULL, NULL, this, t);
			this->setright(rightNode);
		}
	}

	if (this->getk() == key) { //Used for EDIT. If key is similar to what is called, change its data.
		d = data;
		track = new DRT(data, n, p);
	}


	if (key < this->getk()) { //check if there is a left Node.

		if (this->getleft()) {
			track = this->getleft()->add(key, data, n, this->getk()); //if left then continues to call itself.
		}
		else {
			TreeNode* leftNode = new TreeNode(key, data, NULL, NULL, this, t);
			this->setleft(leftNode);
		}
	}

	return track; //after all moves have been made, return the new DRT.
	
}

DRT* TreeNode::searchnode(string key, string n, string p) { //Searches the Tree itself while keeping track of psf and nsf for proper pointer relationship.

	if (k == key) { //if search is found
		string next, prev;
		if (!right) next = n;
		else next = right->first()->getk();
		if (!left) prev = p;
		else prev = left->last()->getk();
		return new DRT(d, next, prev);
	}
	if (k < key) { //if search is greater than current node go down right 
		if (right) return right->searchnode(key, n, k); //k is now the psf
		return new DRT("", n, k);
	}
	if (left) return left->searchnode(key, k, p); //goes down left if search is less than current node
	return new DRT("", k, p); //k is now the nsf

}
TreeNode* TreeNode::first() {//left all the down
	TreeNode* b;
	if (left) { //checks if left exists
		b=left->first();
	}
	else {
		return this;
	}
	return b;


}

TreeNode* TreeNode::last() { //right all the way down
	TreeNode* b;
	if (right) { //checks if right exists
		b=right->last();
	}
	else {
		return this;
	}
	return b;

}

string TreeNode::getk() { return k; } //returns string info of key for node
string TreeNode::getd() { return d; } //returns string info of data for node
TreeNode* TreeNode::getright() { return right; } //returns the right node of this
TreeNode* TreeNode::getleft() { return left; } //returns the left node of this
string TreeNode::next() { return ""; }
string TreeNode::prev() { return ""; }

DRT* TreeNode::remove(string key, string n, string p) {
	//similar to search; keeps track of nsf and psf
	 //just works its down to the tree to find the node to remove
	 //then calls remove ()
	if (this->getk() == key) { //if key is in the Tree remove and return new "empty" DRT
		this->remove();
		return new DRT("", n, p);
	}
	if (this->getk() < key) { //if right go down right recursivly
		if (right) {
			return right->remove(key, n, k);
			return new DRT("", n, k); //k is now the psf
		}
	}
	if (left) { //if not right then last move is left
		return left->remove(key, k, p); //k is now the nsf
	}
	return new DRT("", k, p); 


}

void TreeNode::remove() {
	//the physical removal (decides whether it's 0, 1, or 2-child case and possibly copies key and data values and physically removes the deleted node
	if (left && right) { //2 child case
		d = left->last()->getd();
		k = left->last()->getk();
		left->last()->remove();
	}
	else if (left || right) { //1 child case.
		if (this->parent == nullptr) { //checks if root
			if (left) { //checks where child is in relation to THIS.
				t->setroot(left);
				left->setparent(nullptr); //if its left node set left to be new root and remove its parent and change left pointer
				this->setleft(nullptr);
			}
			else {
				t->setroot(right);
				right->setparent(nullptr); //if its right node set left to be new root and remove its parent and change right pointer
				this->setright(nullptr);
			}
		}
		else if (this->parent->getleft() == this) {
			if (left) {//checks where child is in relation to THIS.
				this->getleft()->setparent(this->parent); 
				this->parent->setleft(this->getleft()); //switches up the pointers so that child of This is pointing to parent of This
				this->setleft(nullptr);
			}
			else {
				this->getright()->setparent(this->parent);
				this->parent->setleft(this->getright()); //switches up the pointers so that child of This is pointing to parent of This
				this->setright(nullptr);
			}
		}
		else {
			if (left) {//checks where child is in relation to THIS.
				this->getleft()->setparent(this->parent);
				this->parent->setright(this->getleft());
				this->setleft(nullptr);
			}
			else {
				this->getright()->setparent(this->parent);
				this->parent->setright(this->getright());
				this->setright(nullptr);
			}
		}
		this->setparent(nullptr); //removes last pointer of THIS that is being deleted then deletes THIS.
		delete this;
	}
	else { //0 child case
		if (this->parent == nullptr) { //checks if root
			t->setroot(nullptr);
		}
		else if (this->parent->getleft() == this) { //checks if left
			this->parent->setleft(nullptr);
		}
		else {
			this->parent->setright(nullptr); //else sets right.
		}
		this->setparent(nullptr);
		delete this; //Remove Memory Leak
	}


}



void TreeNode::setparent(TreeNode* p) { parent = p; } //sets the parent pointer of this node
void TreeNode::setleft(TreeNode* l) { left = l; } //sets the left pointer of this node
void TreeNode::setright(TreeNode* r) { right = r; } //sets the right pointer of this node

