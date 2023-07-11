//COP 4530 assignment 5
//proj5.cpp
//implementation without hiding text 
#include "hashtable.h"
#include "passserver.h"
#include "passserver.cpp"
#include <cstring>
#include <string>

using namespace std;
using namespace cop4530;

void Write(PassServer&);
void Menu();
void AddUser(PassServer&);
void Load(PassServer&);
void RemoveUser(PassServer&);
void ChangePassword(PassServer&);
void FindUser( PassServer&);
void DUMP( PassServer&);
void GetSize( PassServer&);


int main()
{
	int size = 101;
	cout << "Enter preferred hash table capacity\t: ";
	cin >> size; 
	PassServer PS(size);
	char input = ' ';
	do{
		Menu();
		cin >> input; 
		switch(input){		//simple switch statement which passes PassServer to each of the functions by reference
			case 'l':
				Load(PS);
				break;
			case 'a':
				AddUser(PS);
				break;
			case 'r':
				RemoveUser(PS);
				break;
			case 'c':
				ChangePassword(PS);
				break;
			case 'f':
				FindUser(PS);
				break;
			case 'd':
				DUMP(PS);
				break;
			case 's':
				GetSize(PS);
				break;
			case 'w':
				Write(PS);
				break;
			case 'x':
				break;
			default:
				cout << "*****Error: Invalid entry.  Try again." << endl;
		}
	}while(input != 'x' && input != 'X');
	return 0;
}
void Menu() 
{
  cout << "\n\n";
  cout << "l - Load From File" << endl;
  cout << "a - Add User" << endl;
  cout << "r - Remove User" << endl;
  cout << "c - Change User Password" << endl;
  cout << "f - Find User" << endl;
  cout << "d - Dump HashTable" << endl;
  cout << "s - HashTable Size" << endl;
  cout << "w - Write to Password File" << endl;
  cout << "x - Exit program" << endl;
  cout << "\nEnter choice : ";
}

//each function deals with IO and calls functions inside of PassServer which will return a true or false
//which will indicate what the output should be from the program 

void AddUser(PassServer& PS)
{
	string name, password;
	cout << "Enter username: ";
	cin >> name;
	cout << "Enter password: ";
	cin >> password;
	if(PS.addUser(make_pair(name, password)))
		cout << "\nUser " << name << " added." << endl;
	else 
		cout << "*****Error: User already exists. Could not add user." << endl;
}

void Load(PassServer& PS)
{
	char input[100];
	cout << "Enter password file name to load from: ";
	cin >> input;
	if(!PS.load(input))
		cout << "Cannot open file " << input << endl;
}

void Write(PassServer& PS)
{
	char input[100];
	cout << "Enter password file name to write to: ";
	cin >> input;
	PS.write_to_file(input);
}

void RemoveUser(PassServer& PS)
{
	string name;
	cout << "Enter username\t: ";
	cin >> name;
	if(PS.removeUser(name))
		cout << "User " << name << " deleted." << endl;
	else
		cerr << "*****Error: User not found.  Could not delete user" << endl;
}

void ChangePassword(PassServer& PS)
{
	string name, oldpassword, newpassword;
	cout << "Enter username\t: ";
	cin >> name;

	cout << "Enter password\t: ";
	cin >> oldpassword;
	cout << "\nEnter new password\t: ";
	cin >> newpassword;
	if(PS.changePassword(make_pair(name, oldpassword), newpassword))
		cout << "\nPassword changed for user " << name << endl; 
	else
		cerr << "\n*****Error: Could not change user password" << endl;
}

void FindUser( PassServer& PS)
{
	string name;
	cout << "Enter username\t: ";
	cin >> name;
	if(PS.find(name))
		cout << "\nUser '" << name << "' found." << endl;
	else
		cout << "\nUser '" << name << "' not found." << endl; 
}

void DUMP( PassServer& PS)
{
	PS.dump();
}

void GetSize( PassServer& PS)
{
	cout << "Size of hashtable\t: " << PS.size() << endl; 
}