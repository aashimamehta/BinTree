//Author : Aashima Mehta, CSS343 -Wooyoung Kim 
//Modified By: Aashima Mehta 
//Date Created: 7/6/2020
//Date of Last Modification: 7/18/2020
//-------------------------------------
//Topic of this assignment : Binary Search Tree. The purpose of this
//assignment is to import the input data into the program and display
//them as binary search tree

#include <iostream>
using namespace std;
#include "bintree.h"

const int ARRAYSIZE = 100;

//global function prototypes
void buildTree(BinTree&, ifstream&);      // builds the tree from a text file
void initArray(NodeData* []);             // initialize array to NULL


int main()
{
	cout << "This driver tests all the methods in binTree.h file " << endl;
	// create file object infile and open it
	// for testing, call your data file something appropriate, e.g., inputdata.txt
	ifstream infile("inputdata.txt");
	if (!infile) {
		cout << "File could not be opened." << endl;
		return 1;
	}

	// the NodeData class must have a constructor that takes a string
	NodeData notND("not");
	NodeData andND("and");
	NodeData sssND("sss");
	NodeData ttttND("tttt");
	NodeData oooND("ooo");
	NodeData yND("y");
	NodeData eND("e");
	NodeData mND("m");
	NodeData tND("t");


	cout << "Initialize BinTree T, T2, dup " << endl;
	BinTree T, T2, dup;
	//cout << "This is initialized T " << endl << "Tree Inorder: " << endl << T << endl;
	NodeData* ndArray[ARRAYSIZE];
	initArray(ndArray);
	cout << "Initial data:" << endl << "  ";
	buildTree(T, infile);              // builds and displays initial data
	//cout << endl <<"This is after initializing from the file inputdata.txt data >> " << "Tree Inorder: " << endl << T;
	cout << "Display T using displaySideways() >> " << endl;
	T.displaySideways();
    cout << endl;
	cout << T.test();

	//NodeData* p;
	//bool found;

	////test retrieve
	//cout << "Now we will test retrieve method" << endl;
	//found = T.retrieve(andND, p);
	//cout << "Retrieve ---> and: " << (found ? "found" : "not found") << endl;
	//found = T.retrieve(notND, p);
	//cout << "Retrieve ---> not: " << (found ? "found" : "not found") << endl;
	//found = T.retrieve(sssND, p);
	//cout << "Retrieve ---> sss: " << (found ? "found" : "not found") << endl;

	////// test getHeight 
	//cout << endl <<"Now we will test retrieve method" << endl;
	//cout << "Height    --> and:  " << T.getHeight(andND) << endl;
	//cout << "Height    --> not:  " << T.getHeight(notND) << endl;
	//cout << "Height    --> sss:  " << T.getHeight(sssND) << endl;
	//cout << "Height    --> tttt:  " << T.getHeight(ttttND) << endl;
	//cout << "Height    --> ooo:  " << T.getHeight(oooND) << endl;
	//cout << "Height    --> y:  " << T.getHeight(yND) << endl;

	//cout << endl << "Now we test copy constructor >> first(T) = " << endl;
	//BinTree first(T);                  // test copy constructor
	//first.displaySideways();

	//cout << "Now we test = using dup = dup = T statement >> " << endl;
	//dup = dup = T;                     // test operator=, self-assignment
	//cout << "Tree Inorder dup = " << dup << endl;

	//// test ==, and != 

	//cout << "We assign T2 to T using = operator and will test == and != operator >> " << endl;
	//T2 = T;
	//cout << "T2 = " << T2 << endl;
	//cout << "T == T2?     " << (T == T2 ? "equal" : "not equal") << endl;
	//cout << "T != first?  " << (T != first ? "not equal" : "equal") << endl;
	//cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;

	//cout << "Now we will test insert by adding second line ";
	//cout << "from inputdata.txt file into dup " << endl;
	//cout << "(Before) dup  = " << dup << endl;
	//initArray(ndArray);
	//cout << "Initial data:" << endl << "  ";
	//buildTree(dup, infile);              // builds and displays initial data
	//cout << endl << "(After adding second line) dup = " << dup;

	//dup.displaySideways();
	//cout << endl;

	//cout << "Compare dup and T using == and != " << endl;
	//cout << "T != dup?  " << (T != dup ? "equal" : "not equal") << endl;
	//cout << "T == dup?    " << (T == dup ? "equal" : "not equal") << endl;

	//// somewhat test bstreeToArray and arrayToBSTree
	//cout << "Tester for to convert binary tree to array: ";
	//T.bstreeToArray(ndArray);
	//cout << endl; // << "Tester to convert array to binary tree: ";
	//cout << "Diplay the array >> ";
	//for (int i = 0; i < 100; i++) {
	//	if(ndArray[i] != NULL)
	//		cout << *ndArray[i] << " ";
	//}

	//cout << endl << endl<< "Now convert array to Binary Tree again" << endl;
	//T.arrayToBSTree(ndArray);
	//cout << endl << "Tree Inorder T = " << T << endl;
	//T.displaySideways();

	//cout << "Test destructor by deleting T " << endl;
	//T.~BinTree();
	//cout << "Tree Inorder T = " << T << endl;
}


//------------------------------- buildTree ----------------------------------
// To build a tree, read strings from a line, terminating when "$$" is
// encountered. Since there is some work to do before the actual insert that is
// specific to the client problem, it's best that building a tree is not a 
// member function. It's a global function. 
//Preconditions: none
//Postconditions: Builds a binary tree
void buildTree(BinTree& T, ifstream& infile) {
	string s;

	for (;;) {
		infile >> s;
		cout << s << ' ';
		if (s == "$$") break;                // at end of one line
		if (infile.eof()) break;             // no more lines of data
		NodeData* ptr = new NodeData(s);     // NodeData constructor takes string
		// would do a setData if there were more than a string

		bool success = T.insert(ptr);
		if (!success)
			delete ptr;                       // duplicate case, not inserted 
	}
}

//------------------------------- initArray ----------------------------------
//initArray: this method initializes the array
//Preconditions: none.
//Postconditions: initialize the array of NodeData* to NULL pointers
void initArray(NodeData* ndArray[]) {
	for (int i = 0; i < ARRAYSIZE; i++)
		ndArray[i] = NULL;
}
