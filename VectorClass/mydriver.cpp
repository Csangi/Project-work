#include <iostream>
#include <string>

#include "tvector.h"

using namespace std;

template <typename T> 
void PrintList(const TVector<T>& v, string label)
{
   cout << label << " size is: " << v.GetSize() << "\n"
        << label << " = "; 
   v.Print(cout);
   cout << "\n\n";
}

int main()
{
   TVector<int> v1;		// integer list

   for (int i = 0; i < 10; i++)
	v1.InsertBack(i*3);


   for (int i = 0; i < 8; i++)
        v1.Insert( v1.GetIterator(), (i+1) * 50 );

   v1.RemoveBack();

   v1.RemoveBack();

   v1.Remove(v1.GetIterator());

   v1.Remove(v1.GetIterator());

   // try an iterator, and some middle inserts/deletes

   TVectorIterator<int> itr = v1.GetIterator();
   itr = v1.Insert(itr, 999);
   itr.Next();
   itr.Next();				// advance two spots
   itr = v1.Insert(itr, 888);
   itr.Next();				
   itr.Next();				
   itr.Next();				// advance three spots
   itr = v1.Insert(itr, 777);

   itr.Next();   
   itr.Next();   			// advance two spots
   itr = v1.Remove(itr);		// delete current item

   for (int i = 0; i < 5; i++)
      itr.Previous();			// back 5 spots

   itr = v1.Remove(itr);		// delete current item
   
   // building another list

   TVector<int> v2;
   for (int i = 0; i < 10; i++)
      v2.InsertBack(i * 3 + 1);

   // Testing + overload:
   TVector<int> v3 = v1 + TVector<int>(100, 7);

   TVector<int> v4;
   v4 = v2 + v1;

   TVectorIterator<int> itr1 = v4.GetIterator();
   TVectorIterator<int> itr2 = v4.GetIterator();

   itr1.Next();
   itr1.Next();
   for (int i = 0; i < 8; i++)
      itr2.Next();
   
   v4.Remove(itr1, itr2);   


	cout << "----------------------------Personal Testing--------------------------------------" << endl;
	cout << "Testing Clear::" << endl; 
	v1.Clear();
	PrintList(v1, "v1");
	v2.Clear();
	PrintList(v2, "v2");
	cout << "Swapping vectors 3 and 4" << endl << "Before" << endl;
	PrintList(v3, "v3");
	PrintList(v4, "v4");
	swap(v3, v4);
	cout << " after :: " << endl;
	PrintList(v3, "v3");
	PrintList(v4, "v4");
	cout << "Testing move constructor ::" << endl << "Making vector v5 and moving v4 into it" << endl;
	TVector<int> v5 = move(v4);
	PrintList(v4, "v4");
	PrintList(v5, "v5");
	cout << "removing every other from v5 using iterators" << endl;
	TVectorIterator<int> itr3 = v5.GetIterator();
	for (int i = 0; i < v5.GetSize(); i++)
	{
		itr3 = v5.Remove(itr3);
		itr3.Next();
	}
	PrintList(v5, "v5");
	cout << "Moving backwards using the has previous and get previous functions in iterators" << endl;
	TVectorIterator<int> itr6 = v5.GetIteratorEnd();
	cout << itr6.GetData() << " ";
	while(itr6.HasPrevious())
	{
		itr6.Previous();
		cout << itr6.GetData() << " ";
	}
	cout << endl << "Testing Get first and Get last with v5" << endl;
	cout << "First element is " << v5.GetFirst() << endl;
	cout << "Last element is " << v5.GetLast() << endl;
	cout << "Testing get iterator end and deleting all but one element from v5" << endl;
	TVectorIterator<int> itr4 = v5.GetIterator();
	itr3 = v5.GetIteratorEnd();
	v5.Remove(itr4, itr3);
	PrintList(v5, "v5");
	cout << "Now time for a stress test" << endl;
	cout << "I will create an int array with 1,000 elements" << endl;

	for(int i = 0; i < 1000; i++)
		v5.Insert( v1.GetIterator(), (i+1) );

	PrintList(v5, "v5");
	cout << "Now time to remove all the 1,000 elements" << endl;
	itr4 = v5.GetIterator();
	itr3 = v5.GetIteratorEnd();
	v5.Remove(itr4, itr3);
	PrintList(v5, "v5");
	cout << "testing param constructor" << endl;
	TVector<int> v6(7, 42);
	PrintList(v6, "v6");
/*
   
*/




}


