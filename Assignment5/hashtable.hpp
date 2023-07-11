//Christopher SanGiovanni
//COP 4530 assignment 5
//hashtable.hpp


using namespace std;

template <typename K, typename V>
HashTable<K, V>::~HashTable()
{
	makeEmpty();		//call make empty 
	theLists.clear();	//call clear on the vector 
}

template <typename K, typename V>
bool HashTable<K, V>::contains(const K & k) //important destinction is that this type only uses the key 
{	
	auto & whichList = theLists[myhash(k)];		//find the list 
	for(auto itr = begin(whichList); itr != end(whichList); ++itr)	//use iterators to move through the list 
		if(itr->first == k)		//if the itrs first is the same as the value the it is in the table 
			return true;
	return false;
}

template <typename K, typename V>
bool HashTable<K, V>::match(const pair<K, V> &kv) 
{
	auto & whichList = theLists[myhash(kv.first)];		//this one is much more simple as we can just use the find function on the key/value pair
	for(auto itr = begin(whichList); itr != end(whichList); ++itr)	//use iterators to move through the list 
		if(itr->second == kv.second)
			return true;
	return false;
}
 
template <typename K, typename V>
bool HashTable<K, V>::insert(const pair<K, V> & kv)
{
	if (match(kv))		//first we test to see if the key/value pair is in the table 
		return false;
	else if(contains(kv.first))
	{
		remove(kv.first);
	}
	auto & whichList = theLists[myhash(kv.first)];		//then we find which list it is in 
	whichList.push_back(kv);					//put the new pair into the back of the list 

	if (++currentSize > theLists.size())		//if the current size is larger than the vector 
		rehash();								//make it larger 

	return true;		//finally return true
}

template <typename K, typename V>
bool HashTable<K, V>::insert(pair<K, V> && kv)		//same as before but we use move 
{
	if (match(kv))
		return false;
	else if(contains(kv.first))
	{
		remove(kv.first);
	}
	auto & whichList = theLists[myhash(kv.first)];
	whichList.push_back(move(kv));

	if (++currentSize > theLists.size())
		rehash();

	return true;
}

template <typename K, typename V>
bool HashTable<K, V>::remove(const K & k)
{
	auto & whichList = theLists[myhash(k)];
	auto itr = begin(whichList);
	while(itr != end(whichList))	//use iterators to move through the list 
	{
		if(itr->first == k)	
		{	break;}
		else
		{	++itr;}
	}
	
	if (itr == end(whichList))
		return false;
	
	whichList.erase(itr);
	--currentSize;
	return true;

}

template <typename K, typename V>
void HashTable<K, V>::clear()
{
	makeEmpty();
	currentSize = 0;
}

template <typename K, typename V>
bool HashTable<K, V>::load(const char *filename)
{
	fstream inputfile;
	K key;
	V value;
	string oneline;
	if(inputfile)
	{
		inputfile.open(filename);
		while(getline(inputfile, oneline))
		{
			//Use string stream
			//Does automatic type conversion for us
			stringstream ss(oneline);
			ss>>key;
			ss>>value;
			if(contains(key))
				cout << "Error: Duplicate key '" << key <<"', duplicate key ignored" << endl;
			else
				insert(make_pair(key, value));
		}
		inputfile.close();
		return true;  
	}
	else
	{ 
		return false;
	}
}

template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char *filename)
{
	ofstream out;
	out.open(filename);
	for(auto itr = theLists.begin(); itr != theLists.end(); ++itr)
		for(auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
			out << itr2->first << " " << itr2->second << endl;
	out.close();
	return true;
}

template <typename K, typename V>
void HashTable<K,V>::dump()
{
	int i = 0;
	for(auto itr = theLists.begin(); itr != theLists.end(); ++itr)
	{
		cout << "v[" << i << "] ";
		for(auto itr2 = itr->begin(); itr2 != itr->end(); ++itr2)
		{
			if(itr2 != itr->begin())
				cout << ":";
			cout << itr2->first << " " << itr2->second;
		}
		cout << endl;
		++i;
	} 
}

template <typename K, typename V>
void HashTable<K, V>::makeEmpty() 
{
	for (auto & thisList : theLists) {
		thisList.clear();	
	}
}

template <typename K, typename V>
size_t HashTable<K, V>::myhash(const K &k)
{
	static hash<K> hf;
	return hf(k) % theLists.size();
}

template <typename K, typename V>
size_t HashTable<K,V>::size()
{
	return currentSize;
}

template <typename K, typename V>
void HashTable<K,V>::rehash()
{
	vector<list<pair<K,V>>> oldLists = theLists;

	// create new double-sized, empty table
	theLists.resize(prime_below(2 * theLists.size()));
	for (auto & thisList: theLists)
		thisList.clear();

	// copy table over
	currentSize = 0;
	for (auto & thisList : oldLists)
		for (auto & x : thisList)
			insert(move(x));
}

// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K, V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K, V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}