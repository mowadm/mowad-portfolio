/*
 Michael Mowad
 Project 4
 AVLTree.h - Header file for AVLTree and AVLNode classes
 */
#pragma once

#include <string>
#include <vector>
#include <ostream>

class AVLTree
{
private:

	// inner node class
	struct AVLNode
	{
		int key;
		std::string value;

		int height;
		AVLNode* left;
		AVLNode* right; 
		AVLNode* parent;

		AVLNode();

		AVLNode(int key, std::string value);

		friend std::ostream& operator<<(std::ostream& os, const AVLTree::AVLNode& node)
		{
			os << "<" << node.key << ": " << node.value << ">";
			return os;
		}
	};

	// private member data
	AVLNode* root;
	int size;

public:

	AVLTree();

	AVLTree(const AVLTree& toCopy);

	AVLTree& operator=(const AVLTree& toCopy);

	~AVLTree();

	void clear(AVLNode* node);

	void copy(AVLNode* node);

	bool insert(int key, std::string value);

	void balanceNode(AVLNode* node);

	void updateHeight(AVLNode* node);

	void rotateLeft(AVLNode* node);

	void rotateRight(AVLNode* node);

	int getNodeBalance(AVLNode* node);

	int getHeight() const;

	int getSize() const;

	bool find(int key, std::string& value) const;

	std::vector<std::string> findRange(int lowKey, int highKey) const;

	static std::ostream& print(std::ostream& os, AVLNode* node, int rootHeight);

	friend std::ostream& operator<<(std::ostream& os, AVLTree& tree);
};