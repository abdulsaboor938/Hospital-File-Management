/*
* This file is an impplementation of avl trees with balancing by length and balance factor included
*/

#include<iostream>
using namespace std;

#ifndef NODE_H
#define NODE_H
template<class T>
class node
{
	T data;
	int length;
	node<T>* left;
	node<T>* right;

	// default overloaded constructor
	node(T, node<T>* t_left=nullptr, node<T>* t_right=nullptr);

	template<class T>
	friend class avl;
};

template<class T>
node<T>::node(T t_data, node<T>* t_left, node<T>* t_right)
{
	this->data = t_data;
	this->left = t_left;
	this->right = t_right;
	this->length = 0;
}
#endif

#ifndef AVL_H
#define AVL_H
template<class T>
class avl
{
	node<T>* root;

public:
	// public functions of class
	avl();
};
#endif

template<class T>
avl<T>::avl():root(nullptr){}