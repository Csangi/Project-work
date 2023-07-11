//Christopher SanGiovanni
//COP 4530 assignment 1
//Tvector.hpp
//Here we are defining all of our functions from tvector.h 
#ifndef _TVECTOR_HPP
#define _TVECTOR_HPP

using namespace std;

//--------------------------------------------------------TVector-----------------------------------------------

template <typename T>
TVector<T> :: TVector()			//default constructor 
{
	size = 0;						//number of elements that are filled with data in terms of the index 
	capacity = SPARECAPACITY;		//total amount that is allocated
	array = new T[capacity];		//creating a new dynamic array 
}

template <typename T>
TVector<T> :: TVector(T val, int num)	//param constructor 
{
	capacity = num + SPARECAPACITY;		//adding the amount of elements that the caller wants to input and adding some extra space
	size = num;							//the current size is the amount of items that have data 
	array = new T[capacity];			//create the dynamically allocated array 
	for(int i = 0; i < size ; i++)		//loop through and add the values for the requested size, but not for the whole capa 
		array[i] = val;
}

template <typename T>
TVector<T> :: ~TVector()			//destructor
{
	if (array != 0)				
      delete [] array;			
}

template <typename T>
TVector<T> :: TVector(const TVector<T>& v)		//copy constructor 
{
	Clone(v);		//calling our deep copy 
}

template <typename T>
TVector<T>& TVector<T>::operator=(const TVector<T>& v)	//copy assignment operator 
{
   if (this != &v)									// if not self-assignment
   {
	   if(array != 0)
			delete[] array;									// delete old data
      Clone(v);										// use clone for deep copy
   }
   return *this;		
}

template <typename T>
TVector<T>::TVector(TVector<T>&& v)		//move constructor 
{
   capacity = v.capacity;
   size = v.size;
   array = v.array;
   v.array = nullptr;				//point away from this' current data   
   v.capacity = v.size = 0;			//set tracking to 0 so it will not try to seg fault
}

template <typename T>
TVector<T>& TVector<T>::operator=(TVector<T>&& v)  //move assignment operator
{
   swap(capacity, v.capacity);	// use swap key word to swap all data from actual to tracking data 
   swap(size, v.size);			
   swap(array, v.array);
   return *this;		
}

template <typename T>
bool TVector<T> :: IsEmpty() const				//Testing to see if array is empty 
{
	if(size == 0)
		return true;
	else	
		return false;
}

template <typename T>
void TVector<T> :: Clear()						//empty array 
{
	capacity = 0 + SPARECAPACITY;				//making new capacity
	size = 0;									
	delete [] array;							//deleting old data
	array = new T[capacity];					//creating new array 
}

template <typename T>
int TVector<T> :: GetSize()const				//getting size 
{
	return size;
}

template <typename T>
void TVector<T> :: InsertBack(const T& d)		//adding to back of array 
{
	if(size == capacity)					//if there is no capacity for new data 
		SetCapacity(capacity + 5);			//add more 
	array[size] = d;						//set new element to the const reference 
	size++;									//increase the size 
}

template <typename T>
void TVector<T> :: RemoveBack()				//remove the last element 
{
	if(!IsEmpty())
		size--;								//the size is the value that we use for everything so subtracting one from there 
}											//makes it as if the element disappeared and will most likely be written over 

template <typename T>
T& TVector<T> :: GetFirst() const			//return the first element 
{
	return array[0];
}

template <typename T>
T& TVector<T> :: GetLast()const				//return the last element 
{
	return array[size - 1];
}

template <typename T>
TVectorIterator<T> TVector<T> :: GetIterator() const //return a iterator pointing to the first element in the array 
{
	TVectorIterator<T> itr;			//nre iterator 
	if(!IsEmpty())
	{
		itr.index = 0;				
		itr.vsize = size;
		itr.ptr = &array[0];			//set pointer to a reference of the first value of the array
	}
	return itr;
}

template <typename T>
TVectorIterator<T> TVector<T> :: GetIteratorEnd() const 		//return the last element of the array
{
	if(!IsEmpty())					//if the array is not empty 
	{
		TVectorIterator<T> itr;		//new iterator
		itr.index = size - 1;		// index is the last spot minus one 
		itr.vsize = size;			
		itr.ptr = &array[size - 1];	//point to a reference of the last element in the array 
		return itr;					//return the iterator 
	}
	else							//if the array is empty
		return GetIterator();		//send to the default get iterator 
}

template <typename T>
TVectorIterator<T> TVector<T> :: Insert(TVectorIterator<T> pos, const T& d)
{	
	if( pos.index + 1 == size && pos.index != 0)
	{
		InsertBack(d);
		pos.index = pos.index + 1;
		pos.vsize = size;
		pos.ptr = &array[pos.index];
	}
	else if( pos.index < pos.vsize && pos.index != 0)			//if the index is in the bounds of the size 
	{
		if(size + 1 >= capacity)				//if the new size out stretches the capacity of the array 
			SetCapacity(capacity * 2);			//set a new capacity 
					//get the size in terms of the index 
		
		
		for(int i = size; i > pos.index ; i--)		//loop through starting at the back as to not over addign any data 
			array[i] = array[i - 1];				//have the last point get the data of the point before it and so one until everything is moved one to the right 
		
		size++;								//add one more to the size 
		array[pos.index] = d;					//then at the new index we add the data that we originally wanted to add
		pos.vsize = size;		//change the size on the iterator 
		pos.ptr = &array[pos.index];
	} 
	else if(pos.index == 0)
	{
		if(size + 1 >= capacity)
			SetCapacity(capacity * 2);
		
		for(int i = size; i > 0; i--)
			array[i] = array[i - 1];
		
		size++;
		array[0] = d;
		pos.vsize = size;		 
		pos.ptr = &array[pos.index];
	}
	else
	{
		TVectorIterator<T> itr;
		return itr; 
	}
	return pos;		//and return the iterator that was passed in 
}

template <typename T>
TVectorIterator<T> TVector<T> :: Remove(TVectorIterator<T> pos)
{
	if(!IsEmpty())
	{
				//set i to the index after the index we are trying to remove 
		for(int i = pos.index; i < size ; i++)		//loop through the whole array 
			array[i] = array[i + 1];		//set the next index to the last previous index
		size--;								//lower the size 
		pos.vsize = size;
		pos.ptr = &array[pos.index];
	}
	else
	{
		TVectorIterator<T> itr;
		return itr;
	}
	return pos;
}

template <typename T>
TVectorIterator<T> TVector<T> :: Remove(TVectorIterator<T> pos1 ,TVectorIterator<T> pos2)
{
	TVectorIterator<T> pos;
	if(!IsEmpty())
	{	//for loop that loops through the array from the index of pos1 to the end using 2 variables moving the data down the array from right to left 
		for(int index1 = pos1.index, index2 = pos2.index; index2 < size  ;index1++, index2++)
			array[index1] = array[index2];
		size -= pos2.index - pos1.index;		//the new size will be the difference in the 2 arrays minus the initial size 
		pos.index = pos1.index;					//the new index will be the index of teh original position which we started the deletion 
		pos.vsize = size;				
		pos.ptr = &array[pos.index];			
		return pos;
	}
	return pos;
}

template <typename T>
void TVector<T>::Clone(const TVector<T>& v)		//Clone deep copy used in both copy constructors 
{
   capacity = v.capacity;
   size = v.size;
   array = new T[capacity];
   for (int i = 0; i < size; i++)
       array[i] = v.array[i];
}

template <typename T>
void TVector<T>::SetCapacity(unsigned int c)
{
   capacity = c;					
   T * temp = new T[capacity];			//create a temp valiable which creates a new dynamic array 
   for (int i=0; i < capacity && i < size; i++)		
      temp[i] = array[i];		//loop through and add all the data from array to the temp array 
   delete [] array;				//delete old data 
   array = temp;				//set new array equal to the temp array 
}

template <typename T>
TVector<T> operator+(const TVector<T>& t1, const TVector<T>& t2)	
{	
	auto t3 = t1;		//create t3 which will be our return variable 
	auto itr = t2.GetIterator();		//make an iterator starting at the begining of t2 
	t3.InsertBack(itr.GetData());		//add the first data to the array so we can increment the loop before we add the data 
	while(itr.HasNext())		//while the iterator has next data 
	{
		itr.Next();						//next down the itr 
		t3.InsertBack(itr.GetData());	//add the data to the back of t3 
	}
	return t3; 		//return t3 
}

template <typename T>
void TVector<T> :: Print(ostream& os, char delim ) const
{
	auto itr = GetIterator();	//use an iterator 
	if(GetSize() == 0)
		os << "List is empty";
	else 
	{
		os << itr.GetData() << delim;	//add the data first to the stream 
		while(itr.HasNext())			// while there is a next in the array 
		{
			itr.Next();					//move to the next element 
			if(itr.HasNext())
				os << itr.GetData() << delim;	//add the data to the stream 
			else
				os << itr.GetData();
		}
	}
}

//----------------------------------------------- TVectorIterator ---------------------------------------------------
template <typename T>
TVectorIterator<T> :: TVectorIterator()
{
	index = 0;
	vsize = 0;
	ptr = nullptr;
}

template <typename T>
bool TVectorIterator<T> :: HasNext() const 
{
	if(index + 1 != vsize) //if the index is not at the end of the size 
		return true;
	else
		return false;
}

template <typename T>
bool TVectorIterator<T> :: HasPrevious() const 
{
	if(index - 1 == -1)		//if the next element to the left of the pointer is -1 
		return false;
	else
		return true;
}

template <typename T>
TVectorIterator<T> TVectorIterator<T> :: Next()
{
	if(HasNext())		//while there is a next 
	{
		index++;		//increment the index 
		ptr++;			//move the pointer to the next element 
	}
	return *this;
}

template <typename T>
TVectorIterator<T> TVectorIterator<T>:: Previous()
{
	if(HasPrevious())	//while it has a previous 
	{
		index--;		//decrement the index 
		ptr--;			//move the pointer down an element 
	}
	return *this;
}

template <typename T>
T& TVectorIterator<T>::GetData() const	
{
	if(ptr != nullptr)
		return *ptr; //return dereferenced pointer 
	else
		return TVector<T>::dummy; 
}
//----------------------------------------------------------------------------------------------------------------------
#endif