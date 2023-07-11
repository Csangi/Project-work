/*Assignment 6
 *COP 4530
 *Christopher SanGiovanni
 *Objective: take input from standard input and organize it into a stl container and output the 10 
 *most common words, numbers, and letters
 */
#include <istream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <algorithm>
#include <vector>
#include <cctype>
#include <ctime> 
#include <iomanip>

using namespace std;

struct valueHolder{		//for holding both a number of things and the position for comparison
int count;
int position;
};
 
struct vectorValueHolder{		//for the vector in the print function
	int count;
	int position;
	string content;
};

struct sorting	//functor class for sorting algorithm
{
	bool operator() (const vectorValueHolder& v1, const vectorValueHolder& v2)
	{
		if(v1.count == v2.count)	//if the values are equal 
		{
			if(v1.content.length() == 1 && !isdigit(v1.content[0]))		//if it is a letter and not a number
			{
				char a,b;
				a = v1.content[0];
				b = v2.content[0]; 
				
				return a < b;
			}
			else		//if it is a number 
				return v1.position < v2.position; 
		}
		else		//normal
			return v1.count > v2.count;
	}
}myobject;

void printMap(unordered_map<string, valueHolder> & map);	
void inputIntoMap(unordered_map<string, valueHolder> & map, const string& input,const int &counter);	

int main(){
	//clock_t start, stop;
	//start = clock();
	unordered_map<string, valueHolder> wordMap;		//everything stored in a hashtable 
	unordered_map<string, valueHolder> numMap;
	unordered_map<string, valueHolder> charMap;
	char a;		//our input character
	bool wasNum = false, wasChar = false;		//out booleans
	string lastIn;				//a string which will build numbers and words from the last characters that were input 
	int counter;				//counter for positioning
	string holder;				//holder for convering char input to a string for counting characrers
	while(cin.get(a))			//loop through input character by character
	{
		++counter;		//increment
		holder += a;								//convert char to string
		inputIntoMap(charMap, holder, counter);		//input via a helper function 
		holder.clear();								//clear string holder
			
		if(isdigit(a))			//for numbers 
		{
			if(wasChar)			//if the last input was a character 
			{
				if(lastIn.length() > 1 || lastIn[0] == 'a' || lastIn[0] == 'I' || lastIn[0] == 'A')	//make sure it was longer than length 1
				{						//exccept for a and I 
					inputIntoMap(wordMap, lastIn, counter);		//use our insert
				}
				lastIn.clear();		//clear the last in 
				lastIn += a;		//add new input 
				wasChar = false;	//was not a character 
				wasNum = true;		//was a number 
			}
			else if(wasNum)			//if the last in was a number 
			{
				lastIn += a;		//add to string last in 
				wasNum = true;		//last in was a number 
				wasChar = false;	//and was not a character 
			}
			else					//if previous were not a number or a character than 
			{
				lastIn += a;		//add to last in 
				wasNum = true;		//set num to true 
			}
		}
		else if(isalpha(a))			//if character was a letter 
		{
			if(wasNum)				//see if the last input was a number 
			{
				inputIntoMap(numMap, lastIn, counter);	//if so insert into the map 
				lastIn.clear();			//clear the last in 
				lastIn += tolower(a);	//add new letter
				wasChar = true;			//current input was a character 
				wasNum = false;	
			}
			else if(wasChar)			//if the last input was a character 
			{
				lastIn += tolower(a);	//add lastin to lower 
				wasChar = true;			//was a character 
				wasNum = false;
			} 
			else						//if nothing than 
			{
				wasChar = true;			//set char to true 
				lastIn += tolower(a);	//and it is lower 
			}
		}
		else		//if the input was not a number or a letter 
		{
			if(wasNum)		//add the last inputs into their respective maps 
			{
				inputIntoMap(numMap, lastIn, counter);
				lastIn.clear();
				wasChar = false;
				wasNum = false;
			}
			else if(wasChar)
			{
				if(lastIn.length() > 1 || lastIn[0] == 'a' || lastIn[0] == 'I' || lastIn[0] == 'A')
				{
					inputIntoMap(wordMap, lastIn, counter);
				}
				lastIn.clear();
				wasChar = false;
				wasNum = false;
			}
		}
	}
	if(wasNum)		//then add the final last in into their maps 
	{
		inputIntoMap(numMap, lastIn, counter);
		lastIn.clear();
		lastIn += tolower(a);
		wasChar = true;
		wasNum = false;
	}
	else if(wasChar)
	{
		if(lastIn.length() > 1 || lastIn[0] == 'a' || lastIn[0] == 'I'|| lastIn[0] == 'A')
		{
			inputIntoMap(wordMap, lastIn, counter);
		}
		lastIn.clear();
		lastIn += a;
		wasChar = false;
		wasNum = true;
	}
	
				//and then print everything out 
	
	cout << "Total " << charMap.size() << " different characters, ";
	if(charMap.size() >= 10)
		cout << "10 most used characters:" << endl;
	else
		cout << charMap.size() << " most used characters: " << endl;
	printMap(charMap);
	
	
	cout << "Total " << wordMap.size() << " different words, ";
	if(wordMap.size() >= 10)
		cout << "10 most used words:" << endl;
	else
		cout << wordMap.size() << " most used words: " << endl;
	printMap(wordMap);
	
	
	cout << "Total " << numMap.size() << " different numbers, ";
	if(numMap.size() >= 10)
		cout << "10 most used numbers:" << endl;
	else
		cout << numMap.size() << " most used numbers: " << endl;
	printMap(numMap);
	//stop = clock();
	//cout << "Runtime = " << fixed << setprecision(4) << (stop - start) / (double)CLOCKS_PER_SEC << endl;
	return 0; 
}

void printMap(unordered_map<string, valueHolder> &map)		//print map function for well you know
{
	vector<vectorValueHolder> output; 		//make a holder vector for our output
	auto itr = map.begin();					//make an iterator to the beginning of the map
	vectorValueHolder v1;					//make a holder for converting everything 
	for(int i = 0; i < 10 && map.size() != 0; ++i)		//add the first 10 items to the vector 
	{
		v1.content = itr->first;
		v1.count = itr->second.count;
		v1.position = itr->second.position; 
		output.push_back(v1);
		itr = map.erase(itr);			//will return next iterator 
	}
	sort(output.begin(), output.end(), myobject);		//sort the vector 
	
	while(itr != map.end())		//if there are still more 
	{	
		v1.content = itr->first;
		v1.count = itr->second.count;
		v1.position = itr->second.position; 
		output.push_back(v1);				//add to the vector
		
		sort(output.begin(), output.end(), myobject);			//sort complexity would only be 11log11 given that the
		output.pop_back();										//size will never be larger than 11 because we pop_back
		itr = map.erase(itr);
	}			//this will be O(11nlog11) but once we get rid of constants it is just O(n)
	int i = 0;
	for(auto itr: output)		//then print the vector
	{
		if(itr.content == "\n")	//if the character is a tab or newline than set them as so 
			itr.content = "\\n";
		else if(itr.content == "\t")
			itr.content = "\\t";
		cout << "No. " << i << ": " << itr.content << "\t\t" << itr.count << endl;
		++i;
	}
		cout << endl;
}


void inputIntoMap(unordered_map<string, valueHolder> & map, const string& input, const int &counter)	//input function
{
	auto itr = map.find(input);	//O(1) because I used a hashtable 
	if(itr == map.end())		//if the find is at the end then it is not in the map yet 
	{
		valueHolder v1;
		v1.count = 1;
		v1.position = counter;
		map.insert(make_pair(input, v1));		//insert into the map which will be O(1) 
	}
	else
		++(itr->second.count);			//else just increment the count on the iterator 
}