//Christopher SanGiovanni
//COP 4530 assignment 3
//stack.hpp
#ifndef _STACK_HPP
#define _STACK_HPP

using namespace std;

//---------------------------stack-----------------------------------
template <typename T>
Stack<T>::Stack()
{}

template <typename T>
Stack<T>::~Stack()
{
	vect.clear();
}

template <typename T>
Stack<T>::Stack (const Stack<T>& copy)
{
	vect = copy.vect;
}

template <typename T>
Stack<T>::Stack(Stack<T> && move)
{
	std::swap(vect,move.vect);
}

template <typename T> 
Stack<T>& Stack<T>::operator= (const Stack <T>& rhs)
{
	auto copy = rhs.vect;			//call copy constructor operator
	swap(vect,copy);		//call move on the new copy given that it will just be deleted afterwards
	return *this;	
}

template <typename T>
Stack<T>& Stack<T>::operator=(Stack<T> && move)
{
	swap(vect,move.vect);
	return *this;
}

template <typename T>
bool Stack<T>::empty() const
{
	return vect.empty();
}

template <typename T>
void Stack<T>::clear()
{
	while(!empty())
		pop();
}

template <typename T>
void Stack<T>::push(const T& x)
{
	vect.push_back(x);
}

template <typename T>
void Stack<T>::push(T && x)
{
	vect.push_back(move(x));
}

template <typename T>
void Stack<T>::pop()
{
	if(!empty())
		vect.pop_back();
}

template <typename T>
T& Stack<T>::top()
{
	return vect.back();
}

template <typename T>
const T& Stack<T>::top() const
{
	return vect.back();
}

template <typename T>
int Stack<T>::size() const
{
	return vect.size();
}

template <typename T>
void Stack<T>::print(std::ostream& os, char ofc = ' ') const
{
	if(!empty())
	{
		for(int i = 0; i < vect.size() - 1; ++i)
			os << vect[i] << ofc;
		os << vect[vect.size() - 1];
	}
}

template <typename T>
T Stack<T>::get(const int& index) const
{
	return vect[index];
}

//------------------------other functions----------------------------
template <typename T>
std::ostream& operator<< (std::ostream& os, const Stack<T>& a)
{
	a.print(os);
	return os;
}

template <typename T> 
bool operator== (const Stack<T>& lhs, const Stack <T>& rhs)
{
	if(lhs.size() != rhs.size())
		return false;
	else 
		for(int i = 0; i < rhs.size(); ++i)
			if(lhs.get(i) != rhs.get(i))
				return false;
	return true;
}

template <typename T>
bool operator!= (const Stack<T>& lhs, const Stack <T>& rhs)
{
	return !(lhs == rhs);
}

template <typename T>
bool operator<= (const Stack<T>& a, const Stack <T>& b)
{
	if(b.size() < a.size())
		return false;
	else 
		for(int i = 0; i < a.size(); ++i)
			if(b.get(i) < a.get(i))
				return false;
	return true;
}

#endif