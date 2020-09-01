//Author : Aashima Mehta, CSS343 -Wooyoung Kim 
//Modified By: Aashima Mehta 
//Date Created: 7/6/2020
//Date of Last Modification: 7/18/2020
//-------------------------------------
//Topic of this assignment : Binary Search Tree. The purpose of this
//assignment is to import the input data into the program and display
//them as binary search tree

#ifndef BINTREE_H
#define BINTREE_H
#include <string>
#include <iostream>
#include <fstream>
#include "nodedata.h"
using namespace std;


class BinTree {
//Overloading << operator
	friend ostream& operator<<(ostream&, const BinTree&);

private:
	struct Node {
		NodeData* data;  // pointer to data object
		Node* left;           // left subtree pointer
		Node* right;               // right subtree pointer
	};
	Node* root;

	// utility functions
	void deleteTree(Node* cur); // destructor helper
	void inorderHelper(Node* n)const;
	bool insertHelper(Node* cur, NodeData* val);
	bool retrieveHelper(Node* cur, const NodeData&, NodeData*&);
	int valFoundHeightHelper(Node* current) const;
	int getHeightHelper(Node*, const NodeData& val)const;

	void sideways(Node*, int) const;
	void equalToHelper(Node*& cur, Node* cur2) const; // Helper for =
	bool equalHelper(Node* cur, Node* cur2) const; //Helper for comparison operators

	int bstreeToArrayHelper(Node* current, NodeData* arrayToFill[]);
	void arrayToBSTreeHelper(NodeData* a[], Node* cur, int from, int to);

public:
	BinTree(); //default constructor
	~BinTree(); //destructor
	BinTree(const BinTree& b); //deep copy constructor

	//other methods
	bool isEmpty() const; //checks if empty tree
	bool insert(NodeData*); //inserts a new node
	void displaySideways() const; 
	void makeEmpty();

	// Assignment operators
	BinTree& operator=(const BinTree& b);

	// Boolean comparison operators
	bool operator==(const BinTree& b) const;
	bool operator!=(const BinTree& b) const;

	//Accessors
	bool retrieve(const NodeData&, NodeData*&); //retrive the data 
	int getHeight(const NodeData&) const; //outputs the height of the
										// node we are looking for

	//convert into an array //others
	void bstreeToArray(NodeData* []);

	//convert array to bst
	void arrayToBSTree(NodeData* []);


	int test() const;
	int helper(Node*, int)const;
};
#endif
