/*
Michael Mowad
Project 4
AVLTree.cp - functions for AVLTree class and AVLNode subclass
*/

#include "AVLTree.h"
#include <iostream>

using namespace std;

/*
 *
 * AVLNode methods
 *
 */

// AVLNode empty constructor
AVLTree::AVLNode::AVLNode()
{
	key = 0;
	value = "";
	height = 0;
	parent = NULL;
	left = NULL;
	right = NULL;
}

// AVLNode param constructor
// Params: int key and string value
AVLTree::AVLNode::AVLNode(int key, std::string value)
{
	this->key = key;
	this->value = value;
	height = 0;
	parent = NULL;
	left = NULL;
	right = NULL;
}

/*
 *
 * AVLTree methods
 *
 */

// AVLTree constructor
// Sets root to null and size to 0
AVLTree::AVLTree()
{
	root = NULL;
	size = 0;
}

// AVLTree Overloaded Copy Constructor
// Params: AVLTree pointer
// Creates a copy of an existing tree
AVLTree::AVLTree(const AVLTree& toCopy)
{
	root = NULL;
	size = 0;
	copy(toCopy.root);
}

// AVLTree = operator
// Params: pointer to AVLTree
// Sets equal to an existing tree
AVLTree& AVLTree::operator=(const AVLTree& toCopy)
{
	clear(root);
	root = NULL;
	size = 0;
	copy(toCopy.root);
	return *this;
}

// Destructor
// Clears all nodes
AVLTree::~AVLTree()
{
	clear(root);
}

// Clear
// Params: AVLNode pointer
// Deletes all nodes recursively in order
void AVLTree::clear(AVLNode* node) {
	if (node == NULL) {
		return;
	}
	else if (node->right != NULL) {
		clear(node->right);
	} 
	else if (node->left != NULL) {
		clear(node->left);
	}

	delete node;
	size -= 1;
}

// Copy
// Params: AVLNode pointer
// Recursively copies each entry from starting node
void AVLTree::copy(AVLNode* node) {
	if (node == NULL) {
		return;
	}
	
	copy(node->right);
	insert(node->key, node->value);
	copy(node->left);
}

// Insert
// Params: int key and string value
// Inserts new value into tree
bool AVLTree::insert(int key, std::string value)
{
	// Check if first node
	if (root == NULL) {
		root = new AVLNode(key, value);
		size += 1;
		return true;
	}

	// Set temp pointer to root
	AVLNode* node = root;

	// Iterate through tree searching for insertion location for new node
	while (true) {
		if (key < node->key) {
			// Continue to next node if not null
			if (node->left != NULL) {
				node = node->left;
			}
			// else Create node as left child
			else {
				AVLNode* temp = new AVLNode(key, value);
				temp->parent = node;
				node->left = temp;

				node = temp;

				size += 1;
				break;
			}
		}
		else if (key > node->key) {
			// Continue to next node if not null
			if (node->right != NULL) {
				node = node->right;
			}
			// Else create node as right child
			else {
				AVLNode* temp = new AVLNode(key, value);
				temp->parent = node;
				node->right = temp;

				node = temp;
				
				size += 1;
				break;
			}
		}
		// Else duplicate entry;
		else {
			return false;
		}
	}

	// Iterate back up to root and balance along the way
	node = node->parent;
	while (node != NULL) {
		balanceNode(node);
		node = node->parent;
	}


}

// Balance Node
// Params: AVLNode pointer
// Balances node by updating height then rotating if necessary
void AVLTree::balanceNode(AVLNode* node) {

	updateHeight(node);

	int balance = getNodeBalance(node);

	// Determine rotation from balances and rotate accordingly
	if (balance == -2) {
		if (getNodeBalance(node->right) == 1) {
			rotateRight(node->right);
		}
		rotateLeft(node);
	}
	else if (balance == 2) {
		if (getNodeBalance(node->left) == -1) {
			rotateLeft(node->left);
		}
		rotateRight(node);
	}
}

// Update Height
// Params: AVLNode pointer
// Updates the height value of input node
void AVLTree::updateHeight(AVLNode* node) {
	int leftHeight;
	int rightHeight;

	if (node->left == NULL) {
		leftHeight = -1;
	}
	else {
		leftHeight = node->left->height;
	}
	if (node->right == NULL) {
		rightHeight = -1;
	}
	else {
		rightHeight = node->right->height;
	}
	// Set height
	node->height = max(leftHeight, rightHeight) + 1;
}

// Rotate right
// Params: AVLNode pointer
// Rotates right around node
void AVLTree::rotateRight(AVLNode* node) {
	// Check if node is root then switch parent with left child
	if (node->parent == NULL) {
		root = node->left;
		root->parent = NULL;
	}
	else {
		// Switch parent with rotating child
		if (node->parent->left == node) {
			node->parent->left = node->left;
			node->left->parent = node->parent;
			updateHeight(node->parent);
		} 
		else if (node->parent->right == node) {
			node->parent->right = node->left;
			node->left->parent = node->parent;
			updateHeight(node->parent);
		}
	}

	// store left child's right child in temp pointer
	AVLNode* temp = node->left->right;

	// Set node to left child's right child
	node->left->right = node;
	node->parent = node->left;
	updateHeight(node->left->right);

	// Set temp to nodes left child
	node->left = temp;
	if (temp != NULL) {
		temp->parent = node;
	}
	updateHeight(node);


}

// Rotate left
// Params: AVLNode pointer
// Rotates left around node
void AVLTree::rotateLeft(AVLNode* node) {
	// Check if node is root then switch with right child
	if (node->parent == NULL) {
		root = node->right;
		root->parent = NULL;
	}
	else {
		// Switch parent with rotating child
		if (node->parent->left == node) {
			node->parent->left = node->right;
			node->right->parent = node->parent;
			updateHeight(node->parent);
		}
		else if (node->parent->right == node) {
			node->parent->right = node->right;
			node->right->parent = node->parent;
			updateHeight(node->parent);
		}
	}

	// Store right child left child in temp pointer
	AVLNode* temp = node->right->left;

	// Set node to right child's left child
	node->right->left = node;
	node->parent = node->right;
	updateHeight(node->right);

	// Set temp to nodes right child
	node->right = temp;
	if (temp != NULL) {
		temp->parent = node;
	}
	updateHeight(node);
}

// Get Node Balance
// Params: input AVL node
// Output: balance of node
int AVLTree::getNodeBalance(AVLNode* node) {
	int leftHeight;
	int rightHeight;
	
	if (node->left == NULL) {
		leftHeight = -1;
	}
	else {
		leftHeight = node->left->height;
	}
	if (node->right == NULL) {
		rightHeight = -1;
	}
	else {
		rightHeight = node->right->height;
	}

	return (leftHeight - rightHeight);

	
}

// Get Height
// Returns tree height
int AVLTree::getHeight() const
{
	if (root != NULL) {
		return root->height;
	}
	return 0;
}

// Get Size
// Returns size (number of nodes)
int AVLTree::getSize() const
{
	return size;
}

// Find
// Params: int key and string reference value
// Searches tree for key, sets string to value, and returns true/false
bool AVLTree::find(int key, std::string& value) const
{
	// pointer to root
	AVLNode* node = root;

	// Search tree until either null or equal key found
	while (node != NULL) {
		if (key < node->key) {
			node = node->left;
		}
		else if (key > node->key) {
			node = node->right;
		} 
		else if (key == node->key) {
			value = node->value;
			return true;
		}
	}

	// If reach here, key was not found in tree return false
	value = "";
	return false;
}

// Find Range
// Params: low and high key bounds
// Searches tree for keys within bounds and adds values to a return vector
std::vector<std::string> AVLTree::findRange(int lowKey, int highKey) const
{	
	string value;
	vector<string> result;

	// Search each int between keys and add to vector if found
	for (int i = lowKey; i <= highKey; i++) {
		if (find(i, value)) {
			result.push_back(value);
		}
	}

	return result;
}

// Print
// Params: ostream, AVLNode reference, and root height
// Recursively prints formatted nodes
std::ostream& AVLTree::print(std::ostream& os, AVLNode* node, int rootHeight)
{
	if (node == NULL) {
		return os;
	}
	// Traverse right subtree
	print(os, node->right, rootHeight);

	// Tab to correct height
	for (int i = 0; i < (rootHeight - node->height); i++) {
		os << "\t";
	}

	// Print node
	os << node->key << ", " << node->value << endl;

	// Traverse left subtree
	print(os, node->left, rootHeight);

	return os;
}

// << operator
// Prints contents of tree
std::ostream& operator<<(std::ostream& os, AVLTree& tree)
{
	AVLTree::print(os, tree.root, tree.root->height);
	return os;
}
