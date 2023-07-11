//Christopher SanGiovanni
//COP 4530 assignment 4
//bet.hpp
//#ifndef _BET_HPP
//#define _BET_HPP
#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <stack>

using namespace std; 

BET :: BET()
{
	root = new BinaryNode; 			//allocate a new BinaryNode for the root 
}

BET :: BET(const string& postfix)
{
	if(!buildFromPostfix(postfix))		
	{
		makeEmpty(root);
		root = new BinaryNode;
	}
}
BET :: BET(const BET& rhs)
{
	root = clone(rhs.root);
}		

BET :: ~BET()
{
	makeEmpty(root); 
}			

bool BET :: buildFromPostfix(const string& postfix)
{
	vector<string> holder;
	string temp;
	stringstream ss(postfix);
	while(ss>>temp)
	{ 
		holder.push_back(temp);
	}
	stack<BinaryNode*> stackofNodes;
	for(unsigned int i = 0; i < holder.size(); ++i)
	{
		if(testForOperator(holder[i]))
		{
			if(stackofNodes.size() >= 2)
			{
				BinaryNode *right = stackofNodes.top();
				stackofNodes.pop(); 
				BinaryNode *left = stackofNodes.top();
				stackofNodes.pop();
				BinaryNode *tmp = new BinaryNode(holder[i], left, right);
				stackofNodes.push(tmp);
			}
			else
			{
				cerr << "Wrong postfix expression" << endl;;
				return false;
			}
		}
		else
		{
			BinaryNode *tmp = new BinaryNode(holder[i]);
			stackofNodes.push(tmp);
		}
	}
	if(stackofNodes.size() == 1)
	{
		swap(root, stackofNodes.top());
		return true;
	}
	else
	{
		cout << "Wrong postfix expression" << endl;
		return false;
	}
} 	

bool BET:: testForOperator(const string & s)		//helper function to shorten code later on when testing for operators 
{
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "(");
}

const BET& BET :: operator= (const BET& rhs)		//assignment operator 
{
	makeEmpty(root);			//deallocate the current data 
	root = clone(rhs.root);		//clone the rhs and insert into this 
	return *this;				//return this 
}			
void BET :: printInfixExpression()
{
	printInfixExpression(root);		//call recursive function 
	cout << endl;					//endline after all output 
}

void BET :: printPostfixExpression()
{
	printPostfixExpression(root);	//call recursive function 
	cout << endl;					//endline 
}

size_t BET :: size()
{
	return size(root);			//call recursive function 
}			

size_t BET :: leaf_nodes()
{
	return leaf_nodes(root);	//call recursive function 
}	

bool BET :: empty()				
{
	if(root->element.empty() && root->left == nullptr && root->right == nullptr)
		return true;
	else
		return false;
}					
//helper functions 

void BET :: printInfixExpression(BinaryNode *n)
{
	if( n != nullptr )
    {	//for the left child we check if it is not null, is an operator, and whether the precedense is higher than the parent 
		if(n->left != nullptr && testForOperator(n->left->element) && getPrecedence(n->element) > getPrecedence(n->left->element) )
		{		//if so we print with paranthesis
			cout << "( ";
			printInfixExpression( n->left );	// call recursive function 
			cout << ") ";
		}
		else	//else is just normal print 
			printInfixExpression( n->left );
			//if the left is nullptr then print the current element 
		cout << n->element << " ";
		//for the right child we have to check if the precedense is less than OR EQUAL to get the paranthesis in the proper location 
		if(n->right != nullptr && testForOperator(n->right->element) && getPrecedence(n->element) >= getPrecedence(n->right->element) )
		{	//same as left otherwise 
			cout << "( ";
			printInfixExpression( n->right );
			cout << ") ";
		}
		else
			printInfixExpression( n->right );
    }
}	

int BET :: getPrecedence(const string & s)		//another helper function which will return values given the precedense of the operator 
{												//makes the algorithems look cleaner 
	if(s == "+" || s == "-")
		return 1;
	else if(s == "*" || s == "/")
		return 2;
	else
		cout << "error";
	return 0;
}

void BET :: makeEmpty(BinaryNode* &t)			//recursive code which empties BET 
{
	if( t != nullptr )
    {
        makeEmpty( t->left );		//here we have a post order traversal 
        makeEmpty( t->right );
        delete t;					//and delete the parent after the children 
    }
    t = nullptr;		
}		

typename BET :: BinaryNode* BET :: clone(BinaryNode *t)		//clone for making deep copy simpler 
{
	if(t == nullptr)				//if the BinaryNode is empty 
		return nullptr;
	else				//if the BinaryNode is full use new to allocate more space and recursivally call clone on left and right 
		return new BinaryNode{t->element, clone(t->left),clone(t->right)};
}			

void BET :: printPostfixExpression(BinaryNode *n)
{
	if( n != nullptr )	//simple post order traversal 
    {
        printPostfixExpression( n->left );		//print left 
        printPostfixExpression( n->right );		//print right 
		cout << n->element << " ";				//print parent 
    }
}	

size_t BET :: size(BinaryNode *t) 	//recursive size function  
{
	int i = 0;			//have holder i to return the number of actual binary nodes in the tree
	if(t != nullptr)	//if the entered binarynode is null then just return nothing 
	{
		i += size(t->left);	//when it is not recursivally call size in a post order traversal 
		i += size(t->right);
		++i;				//add one when done 
	}
	return i;			//return i 
}

size_t BET :: leaf_nodes(BinaryNode *t)
{
	int i = 0;
	if(t != nullptr)	//if entered t is not null 
	{
		i += leaf_nodes(t->left);	//recursivally call again in post order traversal 
		i += leaf_nodes(t->right);
		if(t->left == nullptr && t->right == nullptr)	//if the node has no children it is a leaf 
			++i;		//add one 
	}
	return i;			//return the counter 
}