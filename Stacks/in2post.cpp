//Christopher SanGiovanni
//Assignment 3
//file for converting infix to post fix notation and exaluation in.
#include <iostream>
#include <cstdlib>
#include "stack.h"
#include <string>
#include <vector>
#include <sstream>
#include <cctype>

using namespace std;
using namespace cop4530;


bool inToPost(vector<string> & v1, bool & areNumbers);
vector<string> stringToVector(string& s);
bool testForOperator(const string & s);
int getPrecedence(const string & s);
float evaluatePost(vector<string> & v1);



int main() {
string input;
bool isValid, areNumbers;
stringstream sso;
do
{
	areNumbers = true;
	cout << "Enter infix expression (\"exit\" to quit): " << endl;
	getline(cin, input);
	
	if(input != "exit")
	{
		auto vect = stringToVector(input);
		isValid = inToPost(vect,areNumbers);
		if(isValid)
		{
		cout << "Postfix expression:" << " ";
		for(auto i: vect)
			cout << i << " ";
		cout << "\n";
		}
		
		if(isValid && areNumbers)
		{
			cout << "Postfix evaluation: ";
			for(auto i: vect)
				cout << i << " ";
			cout << " = " << evaluatePost(vect) << endl;
		}
		else if(isValid)
		{
			cout << "Postfix evaluation: ";
			for(auto i: vect)
				cout << i << " ";
			cout << " = ";
			for(auto i: vect)
				cout << i << " ";
			cout << endl;
		}		
	}
}while(input != "exit");
return 0;
}


vector<string> stringToVector(string & s)
{
	vector<string> v1;
	string filler;
	for(unsigned int i = 0; i < s.length(); ++i)
	{
		if(s[i] == ' ')
		{
			if(!filler.empty()){
				v1.push_back(filler);
				filler.clear();
			}
		}
		else if(i == s.length() - 1)
		{
			filler += s[i];
			v1.push_back(filler);
		}
		else
		{
			filler += s[i];
		}
	}
	return v1;
}


bool inToPost(vector<string> & infix, bool & areNumbers)
{
	vector<string> postFix;			//vector to hold the post fix expression 
	Stack<string> s;				//stack to help with algorithm
	int numOfVar = 0, numOfOp = 0;
	bool correctOrder; 				//a boolean that helps check to see if the operands and operators are in the correct order
	for (unsigned int i = 0; i < infix.size(); ++i) 
	{
		if (!testForOperator(infix[i]) && infix[i] != ")") 	//send to the test for operators function which will return true if the value is an operator 
		{
			for(unsigned int j = 0; j < infix[i].length(); j++)
				if(!isdigit(infix[i][j]) && infix[i][j] != '.')
					areNumbers = false; 
		if(correctOrder)		//if correct order is true twice in a row then there are 2 operands next to each other
		{
			cout <<"Error: Missing operators in the expression"<< endl;
			return false; 
		}
		postFix.push_back(infix[i]);	//add to the output vector 
		++numOfVar;
		correctOrder = true;	//set to true because the last input was an operand
		}
		else if (testForOperator(infix[i])) //if the next value is an operator 
		{			//and not an '(' meaning that other precedence will have to wait
		if(!correctOrder && infix[i] != "(")	//if the input is not open paran and if the last input was an operator
		{
			cout <<"Error: Missing operands in the expression"<< endl;
			return false;
		}
			while (!s.empty() && s.top() != "(" && (getPrecedence(s.top()) >= getPrecedence(infix[i]))) //getPrecedence returns a value depending on the precedence of the operator  
			{
				postFix.push_back(s.top()); 		//add to the postFix array 
				s.pop();							//and pop the stack 
				++numOfOp;
			}
			s.push(infix[i]);				//push the new operator 
			if(infix[i] != "(")
				correctOrder = false;
		} 
		else if (infix[i] == ")" ) 			//if the next value is ")" then add to the postFix array until the "("
		{
			if(!s.empty()){
				while(s.top() != "(" ) 
				{
					if(s.empty())		//if we never find the open paran then there was a misplaced close paran 
					{
						cout << "Error: Infix expression: ";
						for(auto i : infix)
							cout << i << " ";
						cout << "has mismatched parens!" << endl;
						return false;
					}
					postFix.push_back(s.top()); 
					s.pop();
					++numOfOp;
				}
				s.pop();					//and then pop the "("
			}
		}	
	}
	while (!s.empty()) 						//then we push the rest of the operators in the stack to the answer
	{ 
		if(s.top() == "(")			//if we have a left over paran in the stack then there was a missing close
		{
			cout << "Error: Infix expression: ";
			for(auto i : infix)
				cout << i << " ";
			cout << "has mismatched parens!" << endl;
			return false;
		}
		postFix.push_back(s.top()); 
		s.pop(); 
		++numOfOp;
	}
	swap(infix,postFix);					//use move semantics because we want postfix and we want to get rid of the data in infix 
	return (numOfOp + 1 == numOfVar);							//return the boolean 
}


float evaluatePost(vector<string> & v1)
{
	Stack<float> s;
	float x = 0, y = 0;
	bool isFloat;
	for(unsigned int i = 0; i < v1.size();++i)
	{
		if(testForOperator(v1[i]))
		{
			y = s.top();
			s.pop();
			x = s.top();
			s.pop();
			
			if(v1[i]=="+")
				s.push(x + y);
			else if(v1[i]=="-")
				s.push(x - y);
			else if(v1[i] == "*")
				s.push(x * y);
			else if(v1[i] == "/")
				s.push(x / y);
			else
				cout << "error" << endl;
		}
		else
		{
			isFloat = false;
			for(unsigned int j = 0; j < v1[i].length(); ++j)
				if(v1[i][j] == '.')
					isFloat = true;
			if(isFloat)
				s.push(stof(v1[i]));
			else
				s.push(stoi(v1[i]));
		}
	}
	return s.top();
}

bool testForOperator(const string & s)
{
	return (s == "+" || s == "-" || s == "*" || s == "/" || s == "(");
}


int getPrecedence(const string & s)
{
	if(s == "+" || s == "-")
		return 1;
	else if(s == "*" || s == "/")
		return 2;
	else if(s == "(")
		return 3;
	else
		cout << "error";
	return 0;
}