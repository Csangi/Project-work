//COP 4530 assignment 5
//passserver.h
#ifndef _PASSSERVER_H
#define _PASSSERVER_H
#include "hashtable.h"
#include <iostream>
#include <utility>
#include <unistd.h>
#include <crypt.h>
#include <string>
#include <cstring>


namespace cop4530{

	class PassServer{
		public:
		PassServer(size_t size = 101)
		:ht{size}{}
		~PassServer(); 					//destructor. You need to decide what you should do based on your design of PassServer (how you develop the adaptor class based on the adaptee HashTable). In essence, we do not want to have memory leak.
		bool load(const char *filename);//load a password file into the HashTable object. Each line contains a pair of username and encrypted password.
		bool addUser(std::pair<string,  string> & kv); 	//add a new username and password.  The password passed in is in plaintext, it should be encrypted before insertion.
		bool addUser(std::pair<string, string> && kv); 	//move version of addUser.
		bool removeUser(const string & k); 				//delete an existing user with username k.
		bool changePassword(const std::pair<string, string> &p, const string & newpassword); 	//change an existing user's password. Note that both passwords passed in are in plaintext. They should be encrypted before you interact with the hash table. If the user is not in the hash table, return false. If p.second does not match the current password, return false. Also return false if the new password and the old password are the same (i.e., we cannot update the password).
		bool find(const string & user);					//check if a user exists (if user is in the hash table).
		void dump(); 									//show the structure and contents of the HashTable object to the screen. Same format as the dump() function in the HashTable class template.
		size_t size(); 									//return the size of the HashTable (the number of username/password pairs in the table).
		bool write_to_file(const char *filename); 		//save the username and password combination into a file. Same format as the write_to_file() function in the HashTable class template.

		private:
		string encrypt(const string & str);
		HashTable<string,string> ht;
	};
}
#endif