//COP 4530 assignment 5
//passserver.cpp
#include "hashtable.h"
#include "passserver.h"

namespace cop4530{//fairly short implementation, mostly just calling all the functions that we were using in hashtable 

PassServer::~PassServer()
{
	ht.clear();
} 	

bool PassServer::load(const char *filename)
{
	if(ht.load(filename))
		return true; 
	else
		return false;
}

bool PassServer::addUser(std::pair<string,  string> & kv)
{
	if(ht.insert(make_pair(kv.first,encrypt(kv.second).substr(12,31))))
		return true;
	else
		return false;
}

bool PassServer::addUser(std::pair<string, string> && kv)
{
	if(ht.insert(std::move(make_pair(kv.first,encrypt(kv.second).substr(12,31)))))
		return true;
	else
		return false;
}	

bool PassServer::removeUser(const string & k)
{
	if(ht.remove(k))
		return true;
	else
		return false;
} 				
bool PassServer::changePassword(const std::pair<string, string> &p, const string & newpassword)
{
	
	if(ht.match(make_pair(p.first,encrypt(p.second).substr(12,31))))
	{
		auto newPair = make_pair(p.first,encrypt(newpassword).substr(12,31));
		ht.remove(p.first);
		ht.insert(newPair);
		return true;
	}
	else
	{
		return false;
	}
}	

bool PassServer::find(const string & user)
{
	if(ht.contains(user))
		return true;
	else
		return false;
}	

void PassServer::dump()
{
	ht.dump();
}	

size_t PassServer::size()
{
	return ht.size();
}

bool PassServer::write_to_file(const char *filename)
{
	if(ht.write_to_file(filename))
		return true;
	else
		return false;
}

string PassServer::encrypt(const string & str)
{		//similar to the algorithm that we were given. 
	char salt[] = "$1$########";
	char * password = new char [100];
	strcpy ( password, crypt(str.c_str(), salt));
	return password;
}
}//end of namespace cop4530 