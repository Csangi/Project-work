//Christopher SanGiovanni
//Assignment 4
//March 18, 2022
//BET .h class defining
#ifndef _BET_H
#define _BET_H
#include <iostream>
#include <string>

using namespace std; 

class BET {
	private:
		struct BinaryNode{
			string element;  
            BinaryNode *left;
            BinaryNode *right;
			
			BinaryNode(const string & d = string{}, BinaryNode *p = nullptr, BinaryNode *n = nullptr) 
                : element{d}, left{p}, right{n} {};
			BinaryNode(string && d, BinaryNode *p = nullptr, BinaryNode *n = nullptr)
                : element{move(d)}, left{p}, right{n} {};
		};
	public: 
		BET(); 						//default zero-parameter constructor. Builds an empty tree.
		BET(const string& postfix); //one-parameter constructor, where parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces.
		BET(const BET&);			// copy constructor -- makes appropriate deep copy of the tree
		~BET(); 					//destructor -- cleans up all dynamic space in the tree
		bool buildFromPostfix(const string& postfix); 	//parameter "postfix" is string containing a postfix expression. The tree should be built based on the postfix expression. Tokens in the postfix expression are separated by spaces. If the tree contains nodes before the function is called, you need to first delete the existing nodes. Return true if the new tree is built successfully. Return false if an error is encountered.
		const BET & operator= (const BET &); 			//assignment operator -- makes appropriate deep copy
		void printInfixExpression(); 	//Print out the infix expression. Should do this by making use of the private (recursive) version
		void printPostfixExpression(); 	//Print the postfix form of the expression. Use the private recursive function to help
		size_t size(); 					//Return the number of nodes in the tree (using the private recursive function)
		size_t leaf_nodes();	 			//Return the number of leaf nodes in the tree. (Use the private recursive function to help)
		bool empty(); 					//return true if the tree is empty. Return false otherwise.
		
		//helper functions 
		void printInfixExpression(BinaryNode *n); 	//print to the standard output the corresponding infix expression. Note that you may need to add parentheses depending on the precedence of operators. You should not have unnecessary parentheses.
		void makeEmpty(BinaryNode* &t); 			//delete all nodes in the subtree pointed to by t.
		BinaryNode* clone(BinaryNode *t); 			//clone all nodes in the subtree pointed to by t. Can be called by functions such as the assignment operator=.
		void printPostfixExpression(BinaryNode *n);	//print to the standard output the corresponding postfix expression.
		size_t size(BinaryNode *t); 				//return the number of nodes in the subtree pointed to by t.
		size_t leaf_nodes(BinaryNode *t); 			// return the number of leaf nodes in the subtree pointed to by t.
		bool testForOperator(const string & s);	//helper class that tests for operators 
		int getPrecedence(const string & s);	//helper function which will return an int indecating precedence for operators
		
	private:
		BinaryNode *root;
};
#include "bet.hpp"
#endif