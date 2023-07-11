//Christopher SanGiovanni
//COP 4530 assignment 2
//List.hpp
//Here we are defining all of our functions from List.h
#ifndef _LIST_HPP
#define _LIST_HPP

//---------const_iterator-------------
template <typename T>
List<T> :: const_iterator :: const_iterator()
{
	current = nullptr; 						//default constructor just points to null pointer 
}

template <typename T>
const T& List<T> :: const_iterator :: operator*() const
{
	return retrieve();						//star operator returns the data stored in the pointer 
}

template <typename T>
typename List<T> :: const_iterator& List<T> :: const_iterator :: operator++()		//prefix 
{
	current = current->next;				//prefix returns the next node 
	return *this;
}

template <typename T>
typename List<T> :: const_iterator List<T> :: const_iterator :: operator++(int i)	//postfix 
{
	const_iterator old = *this;				//postfix returns the old location, but still increments the node 
	++(*this);
	return old;
}

template <typename T>
typename List<T> :: const_iterator& List<T> :: const_iterator :: operator--()			//prefix
{
	current->prev;
	return *this;
}

template <typename T>
typename List<T> :: const_iterator List<T> :: const_iterator :: operator--(int i)	//postfix 
{
	const_iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
bool List<T> :: const_iterator :: operator==(const const_iterator & rhs) const
{
	return current == rhs.current;							//if the current pointer is pointing to the same location as the rhs 
}															//this is great for for loops 

template <typename T>
bool List<T> :: const_iterator :: operator!=(const const_iterator & rhs) const
{
	return !(*this == rhs);						//just use the equal to operator not 
}

template <typename T>
T& List<T> :: const_iterator :: retrieve() const
{
	return current->data;						//use the arrow operator to dereference current and return the data 
}

template <typename T>
List<T> :: const_iterator :: const_iterator(Node *p)	//parameterized constructor with node pointer p 
{
	current = p;								
}

//-----------iterator--------------------
template <typename T>
List<T> :: iterator :: iterator()			//default constructor 
{ }

template <typename T>
T& List<T> :: iterator :: operator* ()	
{
	return const_iterator::retrieve();
}

template <typename T>
const T & List<T> :: iterator :: operator*() const 
{
	return const_iterator :: operator*();
}

template <typename T>
typename List<T> :: iterator & List<T> :: iterator :: operator++()
{
	this->current = this->current->next;
	return *this;
}

template <typename T>
typename List<T> :: iterator List<T> :: iterator :: operator++(int i)
{
	iterator old = *this;
	++(*this);
	return old;
}

template <typename T>
typename List<T> :: iterator& List<T> :: iterator :: operator--()
{
	this->current = this->current->prev;
	return *this;
}

template <typename T>
typename List<T> :: iterator List<T> :: iterator :: operator--(int i)
{
	iterator old = *this;
	--(*this);
	return old;
}

template <typename T>
List<T> :: iterator :: iterator(Node *p) : const_iterator{p}
{ }

//---------------------------------------List------------------------------------------
template <typename T>
List<T> :: List()
{
	init();			//call in it 
}

template <typename T>
List<T> :: List(const List<T> &rhs)   // copy constructor
{
	init();						//clear the current function essentially calling default constructor 
	for(auto & x : rhs)			//loop through all of the right hand side 
		push_back(x);			//add it to this 
}

template <typename T>//const in the front so it can be called by const objects
const List<T>& List<T> :: operator=(const List<T> &rhs)      // copy assignment operator
{
	List copy = rhs;			//call copy constructor operator
	std::swap(*this,copy);		//call move on the new copy given that it will just be deleted afterwards
	return *this;				//return this
}

template <typename T>
List<T> :: List(List<T> && rhs)  // move constructor
{						//in the header we just give the new object the head and tail and size
	theSize= rhs.theSize; 
	head = rhs.head;
	tail = rhs.tail;
	rhs.theSize = 0;	//then we set the current size and head and tail to 0 so it is no longer poining
    rhs.head = nullptr;	//to the same location in memory 
    rhs.tail = nullptr;
}

template <typename T>
List<T>& List<T> :: operator=(List<T> && rhs) // move assignment operator 
{
	std::swap( theSize, rhs.theSize );		//basic move assignment operator 
    std::swap( head, rhs.head );			//very similar to Tvector HW 
    std::swap( tail, rhs.tail );
    return *this;
}

template <typename T>
List<T> :: List(int num, const T& val)
{
	init();
	for(int i = 0; i < num; ++i)
		push_back(val);
}

template <typename T>
List<T> :: ~List()
{
	clear();
	delete head;			//have to call delete on head and tail because they take up space in memory
	delete tail;
}

template <typename T>
List<T> :: List(const_iterator start, const_iterator end)
{
	init();								//call default init 
	for(auto i = start; i != end; ++i)	//for loop from the start iterator to the end 
		push_back(*i);					//add to the list 
}

template <typename T>
List<T> :: List (std::initializer_list<T> iList)	//copy constructor from initializer list 
{
	init();
	for(auto x: iList)			//loop through iList and pushback to new object 
		push_back(x);
}

template <typename T>
List<T>& List<T> :: operator= (std::initializer_list<T> iList)	//copy assignment operator for initializer list 
{
	clear();					//clear instead of init because we are not initializing. 
	for(auto x: iList)			//loop through iList and pushback to new object 
		push_back(x);
	return *this;
}

template <typename T>
int List<T> :: size() const
{
	return theSize;
}

template <typename T>
bool List<T> :: empty() const
{
	return (theSize == 0);
}

template <typename T>
void List<T> :: clear()
{
	while(!empty())
		pop_front();
}

template <typename T>
void List<T> :: reverse()
{
	if(!empty())
	{
		List<T> newList;			//make a new list to hold all of the data reversed
		for(auto start = --end(); start != begin(); --start)	//loop through the list using iterators 
			newList.push_back(*start);				//add everything to the new list in reversed order 
		newList.push_back(*begin());		//add begin because the loop goes until != to begin so we have to add it again
		std::swap(*this, newList);			//use move semantics
	}
}

template <typename T>
T& List<T> :: front()
{
	return *begin();		//return a dereferenced begin iterator
}

template <typename T>
const T& List<T> :: front() const
{
	return *begin();		//return a dereferenced begin iterator
}

template <typename T>
T& List<T> :: back()
{
	return *--end();		//given that the end iterator is pointing to the last dummy and not the last node 
}							//we return --end() to get the last element

template <typename T>
const T& List<T> :: back() const
{
	return *--end();
}

template <typename T>
void List<T> :: push_front(const T & val)
{
	insert( begin( ), val ); 	//pushfront just inserts the value at teh begining iterator 
}

template <typename T>
void List<T> :: push_back(const T & val)
{
	insert( end(), val);		//push_back inserts before the last function 
}

template <typename T>
void List<T> :: push_front(T && val)
{
	insert( begin(), std::move(val));		//same but uses move semantics 
}

template <typename T>
void List<T> :: push_back(T && val)
{
	insert( end(), std::move(val));			//same but uses move semantics 
}

template <typename T>
void List<T> :: pop_front()
{
	if(!empty())
		erase(begin());							//deletes the first element 
}

template <typename T>
void List<T> :: pop_back()
{	
	if(!empty())
		erase(--end());							//deletes the element before the last 
}

template <typename T>
void List<T> :: remove(const T &val)
{
	if(!empty())
		for(auto start = begin(); start != end(); ++start)		//loop through using iterators 
			if(*start == val)			//if teh data stored in the iterator is equal to the value 
			{
				start = erase(start);					//erase the iterator from the list 
				--start;						//decrement the iterator because the erase will return the next iterator 
			}									//and the loop will automatically increment the iterator 
}

template <typename T>
template <typename PREDICATE>
void List<T> :: remove_if(PREDICATE pred)
{
	if(!empty())
		for(auto start = begin(); start != end(); ++start)	//loop through using iterators
			if(pred(*start))		//when the data satisfies the predicate operator 
			{
				start = erase(start);			//same as before
				--start;
			}
}

template <typename T>
void List<T> :: print(std::ostream& os, char ofc) const
{
	if(empty())
		os<<"The List is empty";
	else
		for( auto itr = begin(); itr != end(); ++itr)
		{	
			if(itr.current->next->next != nullptr)		//if the next is nullptr 
				os << *itr << ofc;
			else
				os << *itr;
		}
}

template <typename T>
typename List<T> :: iterator List<T> :: begin()
{
	return iterator( head->next ); 
}

template <typename T>
typename List<T> :: const_iterator List<T> :: begin() const
{
	return const_iterator( head->next ); 
}

template <typename T>
typename List<T> :: iterator List<T> :: end()
{
	return iterator( tail ); 
}

template <typename T>
typename List<T> :: const_iterator List<T> :: end() const
{
	return const_iterator( tail ); 
}

template <typename T>
typename List<T> :: iterator List<T> :: insert(iterator itr, const T& val)
{
	Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node{ val, p->prev, p } );
}

template <typename T>
typename List<T> :: iterator List<T> :: insert(iterator itr, T && val)
{
	Node *p = itr.current;
    ++theSize;
    return iterator( p->prev = p->prev->next = new Node{ std::move( val ), p->prev, p } );
}

template <typename T>
typename List<T> :: iterator List<T> :: erase(iterator itr)
{
		Node *p = itr.current;
		iterator retVal( p->next );
		p->prev->next = p->next;
		p->next->prev = p->prev;
		delete p;
		--theSize;
		return retVal;
}

template <typename T>
typename List<T> :: iterator List<T> :: erase(iterator start, iterator end)
{
	while(start != end)
        start = erase( start );

    return end;
}

template <typename T>
void List<T> :: init()
{
	theSize = 0;
    head = new Node;
    tail = new Node;
    head->next = tail;
    tail->prev = head;
}

template <typename T>
bool operator==(const List<T> &lhs, const List<T> &rhs)
{
	if(lhs.size() != rhs.size())
		return false;
	else
	{
		auto itr1 = lhs.begin();
		auto itr2 = rhs.begin();
		while(itr1 != lhs.end())
		{
			if(*itr1 != *itr2)
				return false;
			++itr1;
			++itr2;
		}
			return true; 
	}
}

template <typename T>
bool operator!=(const List<T> & lhs, const List<T> &rhs)
{
	return !(lhs == rhs);
}

template <typename T>
std::ostream & operator<<(std::ostream &os, const List<T> &l)
{
	l.print(os);
	return os;
}

#endif