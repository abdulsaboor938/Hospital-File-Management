#include<iostream>
#include<math.h>
using namespace std;

#ifndef NODE_H
#define NODE_H
template<class T>
class node
{
	T data;
	node<T>* leftChild;
	node<T>* rightChild;

	node(T const val) // overloaded constructor
	{
		this->data = val;
		leftChild = nullptr;
		rightChild = nullptr;
	}

	template<class T> // making tree class a friend
	friend class BST;
};
#endif

// Binary search tree implementation
template<class T>
class BST
{
	node<T>* root;

	void insert(node<T>*&, T const); // function for recursive insertion
	node<T>* search(node<T>*, T const); // recursive search
	void preorderPrintKeys(node<T>*) const; // preorder printing recursive
	void inorderPrintKeys(node<T>*) const; // inorder printing recursive
	void postorderPrintKeys(node<T>*) const; // postorder printing recursive
	void deleteNode(T const, node<T>*&); // function to find and delete the node 
	void deleteNode(node<T>*&); // function to delete the passed pointer's node and re-route pointer
	int maxHeight(node<T>*) const; // function to find height of a given tree

public: // public functions of bst class
	BST() :root{ nullptr } {}
	~BST(); // post order destructor

	void insert(T const); // wrapper function for recursive insertion
	void insertIt(T const); // iterative insertion algorithm

	// deletion functions
	void deleteNode(T const); // wrapper for deleting a node
	void clear() { this->clear(this->root); } // function for clearing list
	void clear(node<T>*&); // function for clearing down current pointer

	node<T>* search(T const); // wrapper function for recurisve search
	node<T>* searchIt(T const); // function for iterative search

	// max possible nodes
	int maxNodes(int) const; // function for printing maximum possible nodes based on tree height
	int maxHeight() const; // wrapper function for giving height of tree

	// orderly recursive printing functions
	void preorderPrintKeys() const; // wrapper function for preorder key printing
	void inorderPrintKeys() const; // wrapper function for inorder key printing
	void postorderPrintKeys() const; // wrapper function for postorder key printing

	// merging functions
	void merge(BST<T>&);
};

template<class T>
BST<T>::~BST()
{
	this->clear(this->root);
}

template<class T>
void BST<T>::insert(T const data) // wrapper function for recursive insertion
{
	insert(root, data);
}
template<class T>
void BST<T>::insert(node<T>*& ptr, T const temp_data)
{
	if (ptr == nullptr)
		ptr = new node<T>(temp_data); // insertion operation
	else if (ptr->data < temp_data) // insertion at right child
		insert(ptr->rightChild, temp_data);
	else // insertion at left child
		insert(ptr->leftChild, temp_data);

	/* we compare currnet ptr's value with the one provided
	*	we move to left child if current value is greater than the one provided
	*	we move to right child if current value is smaller than the one provided
	*  This implementation is in case of recrsion
	*/
}

template<class T>
void BST<T>::insertIt(T const temp_data)
{
	/*
	* code for iterative insertion of data
	* we need two pointers
	*	one for current
	*	another for storing the parent of current pointer
	* we move current pointer according to the relation with provided key
	*/
	if (root == nullptr) // if empty tree
	{
		root = new node<T>(temp_data); // creating a new node at root
		return;
	}

	// in case if root is not null
	node<T>* temp = root; // pointing a temporary pointer to root
	node<T>* parent = nullptr; // a pointer to store parent
	bool flag = true; // a flag to see if a new node needs to be inserted (by default)
	while (temp != nullptr) // loop til a null child
	{
		parent = temp; // assigning current pointer to parent
		if (temp->data == temp_data) // checking if data of curretn node needs to be replaced
		{
			temp->data = temp_data; // changing current data
			flag = false;
			break; // going out of loop to save iterations
		}
		else if (temp->data < temp_data) // moving to right child if current data is smaller
			temp = temp->rightChild;
		else // moving to left child if current data is larger
			temp = temp->leftChild;
	}
	if (flag) // checking if an edit has not been made
	{
		if (parent->data < temp_data) // moving to right child if insertion is larger
			parent->rightChild = new node<T>(temp_data);
		else // moving to left child if insertion is smaller
			parent->leftChild = new node<T>(temp_data);
	}
}

template<class T>
void BST<T>::deleteNode(T const temp_data)
{
	// this is a wrapper function for delete node function
	this->deleteNode(temp_data, this->root);
}
template<class T>
void BST<T>::deleteNode(T const temp_data, node<T>*& ptr)
{
	if (ptr != nullptr)
	{
		if (ptr->data < temp_data)
			deleteNode(temp_data, ptr->rightChild);
		else if (ptr->data > temp_data)
			deleteNode(temp_data, ptr->leftChild);
		else
			deleteNode(ptr);
	}
}
template<class T>
void BST<T>::deleteNode(node<T>*& ptr)
{
	/*
	* This is the iterative definiton for delete node function and works as separate cases
	*	the node to be deleted is a leaf node
	*	the node to be deleted has one child
	*	the node to be deleted has two children
	*		in this case we will either look for successor or predecessor by once going left and then right or vice versa
	*/
	if (ptr != nullptr)
	{
		node<T>* temp = ptr;
		node<T>* previous = ptr;
		if (ptr->leftChild == nullptr) // routing to right child if left doesn't exist
			ptr = ptr->rightChild;
		else if (ptr->rightChild == nullptr) // routing to left child if right doesn't exist
			ptr = ptr->leftChild;
		// at this point the first two cases are handled

		// handling third case with two children
		else
		{
			temp = ptr->leftChild;
			while (temp->rightChild != nullptr) // loop to find the successor
			{
				previous = temp;
				temp = temp->rightChild;
			}
			ptr->data = temp->data;

			if (previous != ptr)
				previous->rightChild = temp->leftChild; // rerouting link to left tree
			else
				previous->leftChild = temp->leftChild; // rerouting link to left tree if no right link after the first left link
		}
		delete temp;
	}
}

template<class T>
void BST<T>::clear(node<T>*& ptr)
{
	if (ptr == nullptr) // if a nullptr
		return;
	else if ((ptr->leftChild == nullptr) && (ptr->rightChild == nullptr)) // if leaf node
		return; 
	else
	{
		clear(ptr->leftChild);
		clear(ptr->rightChild);
		delete ptr;
		ptr = nullptr;
	}
}

template<class T>
node<T>* BST<T>::search(T const temp_data) // wrapper function for recursive search
{
	return this->search(this->root, temp_data);
}
template<class T>
node<T>* BST<T>::search(node<T>* ptr, T const temp_data)
{
	if (ptr == nullptr) // if at last ptr
		return nullptr; // returning null if not found
	else if (ptr->data == temp_data) // if value matches the one provided
		return ptr;
	else if (ptr->data < temp_data) // going to right child in case current data is smaller than provided
		return search(ptr->rightChild, temp_data);
	else // going to left child in case current data is greater than provided
		return search(ptr->leftChild, temp_data);
}

template<class T>
node<T>* BST<T>::searchIt(T const temp_data)
{
	/*
	* This function is code for iterative search
	*	start from head and move accordingly
	*	return if found or if at last element
	*/

	node<T>* temp = this->root;
	while ((temp != nullptr) || (temp->data != temp_data))
	{
		if (temp->data < temp_data) // going right if current data is smaller
			temp = temp->rightChild;
		else
			temp = temp->leftChild; // going to left child if current data is greater
	}
	return temp; // returning the pointer to data or null if not found
}

template<class T>
int BST<T>::maxNodes(int height) const
{
	return (pow(2, (height + 1)) - 1); // returning maximum possible nodes
}

template<class T>
int BST<T>::maxHeight() const
{
	return this->maxHeight(this->root);
}
template<class T>
int BST<T>::maxHeight(node<T>* ptr) const
{
	if (ptr == nullptr)
		return -1;
	else
		return(max(maxHeight(ptr->leftChild), maxHeight(ptr->rightChild)) + 1);
}

template<class T>
void BST<T>::preorderPrintKeys() const
{
	// This is a function for preOrder key printing
	cout << "[ ";
	this->preorderPrintKeys(this->root);
	cout << "]" << endl;
}
template<class T>
void BST<T>::preorderPrintKeys(node<T>* curr) const
{
	if (curr != nullptr)
	{
		cout << curr->data << " "; // printing current 
		preorderPrintKeys(curr->leftChild); // visisting left child
		preorderPrintKeys(curr->rightChild); // visiting right child
	}
}

template<class T>
void BST<T>::inorderPrintKeys() const
{
	// This is a wrapper function for inOrder key printing
	cout << "[ ";
	this->inorderPrintKeys(this->root);
	cout << "]" << endl;
}
template<class T>
void BST<T>::inorderPrintKeys(node<T>* curr) const
{
	if (curr != nullptr)
	{
		inorderPrintKeys(curr->leftChild); // visisting left child
		cout << curr->data << " "; // printing current data
		inorderPrintKeys(curr->rightChild); // visiting right child
	}
}

template<class T>
void BST<T>::postorderPrintKeys() const
{
	// This is a wrapper function for postOrder key printing
	cout << "[ ";
	this->postorderPrintKeys(this->root);
	cout << "]" << endl;
}
template<class T>
void BST<T>::postorderPrintKeys(node<T>* curr) const
{
	if (curr != nullptr)
	{
		postorderPrintKeys(curr->leftChild); // visisting left child
		postorderPrintKeys(curr->rightChild); // visiting right child
		cout << curr->data << " "; // printing current data
	}
}