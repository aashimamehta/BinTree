//Author : Aashima Mehta, CSS343 -Wooyoung Kim 
//Modified By: Aashima Mehta 
//Date Created: 7/6/2020
//Date of Last Modification: 7/18/2020
//-------------------------------------
//Topic of this assignment : Binary Search Tree. The purpose of this
//assignment is to import the input data into the program and display
//them as binary search tree

#include<math.h> 
#include "bintree.h"
using namespace std;


//---------------------------BinTree()-----------------------
//default constructor
//Preconditions: NONE
//Postconditions: reads from the file. creates by adding all the nodes
//               to the binary tree. 
BinTree::BinTree()
{
	root = NULL;
}

//--------------------------- deleteTree(Node*) ---------------
//Destructor Helper --- which will delete all the nodes in the bin tree
//Preconditions: root is passed. Should delete everything but root.
//Postconditions: all nodes in the tree has been deleted
void BinTree::deleteTree(Node* cur) 
{
	if (cur == NULL) 
	{
		return;
	}
	//traverse until the leaves and then delete everything 
	//on its way up
	if(cur->left != NULL) deleteTree(cur->left);
	if(cur->right != NULL) deleteTree(cur->right);

	delete cur->data;
	cur->data = nullptr;
	cur = NULL;
	delete cur;
	root = NULL;
	delete root;
}

//--------------------------- ~BinTree()-----------------------
//destructor
//Preconditions: assumes BinTree exists.
//Postconditions: deletes all the nodes in the BinTree and free
//		up the memory.
BinTree::~BinTree()
{
	if (root != NULL) 
	{
		deleteTree(root); //should delete all nodes in the tree
	}
}

//---------------------------BinTree(const BinTree& b)-----------------------
//deep copy constructor
//Preconditions: NONE
//Postconditions: copies the passed bintree b into the BinTree(*this) 
BinTree::BinTree(const BinTree& b) 
{
	if (*this != b)
		this->deleteTree(root); // will delete everything in the tree
		*this = b;
}

//methods
//-------------------------------isEmpty()-------------------------
//Tells if the tree is Empty or not
//Preconditions: NONE
//Postconditions: BinTree remains unchanged.
bool BinTree::isEmpty() const 
{
	return root == NULL;
}

//------------------------- insert(NodeData*) ------------------------------
//Inserts a node in the tree
//Preconditions: NONE
//Postconditions: Adds a new node in its correct position in the BinTree
bool BinTree::insert(NodeData* val) 
{
	if (val == NULL)
		return false;
	if (root == NULL) //BinTree empty
	{
		root = new Node;
		root->left = NULL;
		root->right = NULL;
		root->data = val;
		return true;
	}
	else if (*val != * (root->data))
	{
		return insertHelper(root, val);
	}
	else  //for repeated values
		return false;
}

// utility functions

//------------------ insertHelper ------------------------
//Inserts the node at its correct position in the bintree
//Helper for insert()
//Preconditions: Passed the correct left/right boundary.
//				Assumed that val is not null(already check in insert)
//Postconditions: Inserts the node at the correct position
bool BinTree::insertHelper(Node* cur, NodeData* val) 
{	
	if (*val > *cur->data) //right
	{
		if (cur->right == NULL) 
		{
			cur->right = new Node;
			cur->right->data = val;
			cur->right->left = NULL;
			cur->right->right = NULL;
			return true;
		}
		else
			return insertHelper(cur->right, val);
	}
	else if (*val < *cur->data) //left
	{
		if (cur->left == NULL) 
		{
			cur->left = new Node;
			cur->left->left = NULL;
			cur->left->right = NULL;
			cur->left->data = val;
			return true;
		}
		else
			return insertHelper(cur->left, val);
	}
	else
		return false; //repeated values
}

//------------------------- makeEmpty() ------------------------------------
//empty outs the tree
//Preconditions: none
//PostConditions: Bintree is empty
void BinTree::makeEmpty()
{
	deleteTree(root);
}

//------------------------- displaySideways ---------------------------------
// Displays a binary tree as though you are viewing it from the side;
// hard coded displaying to standard output.
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::displaySideways() const 
{
	sideways(root, 0);
}

//---------------------------- Sideways -------------------------------------
// Helper method for displaySideways
// Preconditions: NONE
// Postconditions: BinTree remains unchanged.
void BinTree::sideways(Node* current, int level) const 
{
	if (current != NULL) 
	{
		level++; 
		sideways(current->right, level);// indent for readability, 4 spaces per depth level
		for (int i = level; i >= 0; i--)
		{
			cout << "    ";
		}
		cout << *current->data << endl;  
		// display information of object
		sideways(current->left, level);
	}
}

// -------------------- equalToHelper(Node*, Node*) -------------------
//assignment operator = Helper
//Preconditions: assumptions root of *this is null and binTree doesn't exist
//Postcondition: cur duplicate of cur2 tree is produced
void BinTree::equalToHelper(Node*& cur, Node* cur2) const
{
	if (cur2 != NULL) 
	{

		cur = new Node;   // new node for left tree
		NodeData* temp = new NodeData(*cur2->data); 
		cur->data = temp; // set left tree data to temp

		equalToHelper(cur->left, cur2->left); // left
		equalToHelper(cur->right, cur2->right);   //right
	}
	else // return empty tree
		cur = NULL;  
}


//---------------------------operator = -----------------------
//assingment operator "="
//Preconditions: assumes *this exists.
//Postconditions: copies all the nodes from b into the existing BinTree 
BinTree& BinTree::operator=(const BinTree& b)
{
	if (b != *this)
		equalToHelper(root, b.root);	
	return *this;
}

//------------------------- equalHelper(Node* , Node*) ------------------
//Helper to check if two bin trees are equal or not ==
//Preconditions: none
//Postconditions: both trees remain unchanged.
bool BinTree::equalHelper(Node* cur, Node* cur2)const 
{
	if (cur == NULL && cur2 == NULL)
		return true; //base
	else if (cur != NULL && cur2 != NULL)
	{
		//checker for the data in the roots
		if (*cur->data == *cur2->data) 
		{
			//recursive checker for left and right subtrees
			bool left = equalHelper(cur->left, cur2->left);
			bool right = equalHelper(cur->right, cur2->right);
			return left && right;
		}
		else
			return false;
	}
	else 
		return false;
}


//---------------------------operator == -----------------------
// Boolean comparison operators ==
//Preconditions: assumes the two comparing bintrees exists
//Postconditions: compares each node successfully. BinTree remains unchanged.
bool BinTree::operator==(const BinTree& b) const 
{
	Node* cur = root;
	Node* cur2 = b.root;
	bool check = equalHelper(cur, cur2);
	cur = NULL;
	delete cur;
	cur2 = NULL;
	delete cur2;
	return check;
}

//---------------------------operator != -----------------------
// Boolean comparison operators !=
//Preconditions: assumes == works
//Postconditions: compares each node successfully. BinTree remains unchanged.
bool BinTree::operator!=(const BinTree& b) const 
{
	return (*this == b) ? false: true;
}

//Accessors

//-------------- retrieve(const NodeData, NodeData*) -------------
// Helper for retrieve(const NodeData, NodeData*)
//Preconditions: assumes the two comparing bintrees exists
//Postconditions: compares each node successfully. BinTree remains unchanged.
bool BinTree::retrieveHelper(Node* node, const NodeData& data, NodeData*& dataPtr)
{
	if (node != NULL)  //if node is null then return false
	{
		if (*node->data == data)
		{
			dataPtr = node->data;
			return true;
		}
		else  //recurse to find the value in the tree
		{
			if (data > * node->data)
				return retrieveHelper(node->right, data, dataPtr);
			else
				return retrieveHelper(node->left, data, dataPtr);
		}
	}
	return false;
}

//-------------- retrieve(const NodeData&, NodeData*) -------------
// retrieve the data 
//Preconditions: assumes that the data is not repeated in the Binary search Tree.
//Postconditions: compares each node successfully. BinTree remains unchanged.
bool BinTree::retrieve(const NodeData& data, NodeData*& dataPtr) 
{
	bool found = false;
	if (root != NULL)  //CHECK ROOT
	{
		if (*root->data == data) //found?
		{
			dataPtr = root->data;
			return true;
		}
		else
		{ //keep searching until leaves if not found yet?
			if (data > * root->data)
				return (found = retrieveHelper(root->right, data, dataPtr));
			else
				return (found = retrieveHelper(root->left, data, dataPtr));
		}
	}
	return found;
}

//----------------------- getHeightHelper(Node* cur) const --------------
//Helper for getHeight(NodeData& val) method
//Preconditions: passed parameter's position is correct
//Postconditions: Bintree remains unchanged.
int BinTree::getHeightHelper(Node* cur, const NodeData& val) const
{
	if (cur == NULL)//if cur is invalid // or not found
		return 0; 
	else if (*cur->data == val) //val found
		return valFoundHeightHelper(cur);
	else
	{ //traverse until you find val?
		int left = getHeightHelper( cur->left, val);
		int right = getHeightHelper(cur->right, val);
		return left > right ? left: right;
	}
}
//----------------------- valFoundHeightHelper(Node* cur) const --------------
//Helper for getHeightHelper(NodeData& val) const
//Preconditions: assumptions value is been passed
//Postconditions: Height of the node passed is returned.
int BinTree::valFoundHeightHelper(Node* cur) const
{
	//stop count when reached the leaf node of the binTree 
	if (cur == NULL)
		return 0;
	else
	{
		//what level we are on counter
		return 1 + (valFoundHeightHelper(cur->left) > valFoundHeightHelper(cur->right) ?
			valFoundHeightHelper(cur->left) : valFoundHeightHelper(cur->right));
	}
}


//------------------ getHeight(const NodeData&) const ------------------
// returns the level of the node passed
//Preconditions: NONE
//Postconditions: BinTree remains unchanged.
int BinTree::getHeight(const NodeData& val) const 
{
	if (root == NULL)
		return 0;
	if (&val == NULL )
	{
		cout << "Error " << &val << " passed is nullptr. Try again. " << endl;
		return 0;
	}
	//traverse down the tree
	//check val while going up
	return getHeightHelper(root, val);
}


//Others
//------------------- bstreeToArrayHelper(Node* cur, NodeData* a[]) -----------
//Helper for bstreeToArray(NodeData* [])
//returns int, which represents the index where the element needs
//to inserted.
//Preconditions: None
//Postcondition: array is filled in parent - child format.
int BinTree::bstreeToArrayHelper(Node* cur, NodeData* a[])
{
	if (cur == NULL)
		return 0;   // end of BST
	int left = bstreeToArrayHelper(cur->left, a);
	NodeData* temp;
	temp = cur->data; // saves NodeData to temp
	cur->data = NULL; // current no longer points to node
	*(a + left) = temp; //arrayToFill points to temp
	temp = NULL;
	int right = bstreeToArrayHelper(cur->right, a + left + 1);
	return left + right + 1; // return position
}

//------------------ bstreeToArray(NodeData* []) ------------------
//fills an array of NodeData with bintree elements in inorder fashion.
//Preconditions: NONE
//Postconditions: BinTree is empty and the array is filled.
void BinTree::bstreeToArray(NodeData* a[]) 
{
	if (root == NULL)
		return;
	//now add evrything from left to right in the array
	bstreeToArrayHelper(root, a); 
	this->deleteTree(root);
}

//------------------ arrayToBSTreeHelper(NodeData* [], Node* cur, int i) ------------------
//Helper for arrayToBSTree(NodeData* [])
// 's' is starting index and 'e' is ending index
//Preconditions: Sorted Array is passed.
//Postconditions: BinTree is balanced and array is filled with NULLS.
void BinTree::arrayToBSTreeHelper(NodeData* a[], Node* cur, int from, int to)
{
	//end if to greater than from
	if (from > to)
		cur = NULL;
	else
	{
		int mid = (to + from) / 2;
		NodeData* cur2;
		cur2 = a[mid];
		a[mid] = NULL;
		insert(cur2);
		//traverse from 0 until mid
		arrayToBSTreeHelper (a, cur ,0, mid - 1);
		//traverse from mid +1 to end of the array
		arrayToBSTreeHelper(a, cur, mid + 1, to);
	}
}

//------------------ arrayToBSTree(NodeData* []) ------------------
//convert array to bst
//Preconditions: Sorted Array is passed. array size is 100.
//Postconditions: BinTree is balanced and array is filled with NULLS.
void BinTree::arrayToBSTree(NodeData* a[]) 
{
	//delete all nodes in the tree
	this->deleteTree(root);
	int counter = 0;
	for (int i = 0; i < 100; i++)
	{
		if (a[i] != NULL)
			counter++;
	}
	//counter = the size of the array
	arrayToBSTreeHelper(a, root, 0, counter - 1);
}

//------------------------inorderHepler(Node*)----------------------------------
//Displays all the nodes of the bintree using in order traversal
//Preconditions: NONE
//Postconditions: The nodes will be produced in an in order manner
void BinTree::inorderHelper(Node* cur) const
{
	if (cur == NULL)
	{
		return; //dont do anything
	}
	//recurse left node right (inorder)
	if(cur->left != NULL)
		inorderHelper(cur->left);
	cout << *(cur->data) << " ";
	if(cur->right != NULL)
		inorderHelper(cur->right);
}

//------------------ operator << ------------------
//Ostream overloading << operator -- prints the BinTree 
//Preconditions: NONE
//Postconditions: BinTree remains unchanged.
ostream& operator<<(ostream& ostm, const BinTree& b)
{
	if (b.root == NULL)
		return ostm << "Tree is empty!";
	b.inorderHelper(b.root); //pass the root to helper method
	ostm << endl;
	return ostm;
}



int BinTree::test() const {

	return helper(root, 1);

}



int BinTree::helper(Node* current, int n)const {

	if (current == NULL) return 0;

	if (current->right != NULL || current->left != NULL)

		return  2 + helper(current->left, n) + helper(current->right, n + 1);

	return n;

}


