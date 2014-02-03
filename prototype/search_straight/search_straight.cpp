#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

int straightFind()
{
    //vector<int> rowsArray;
	ifstream text("file_10.txt");
	
	string str_to_find = "2002";
	int l = str_to_find.length();
	// включить кириллицу: setlocale(LC_ALL, "Russian");
	string word_from_array;
	int steps = 0;
	int v;
	int w_counter=0;
	//cout<<"str_to_find length = "<<str_to_find.length()<<endl;
	while (text.good())
	{		
		w_counter++; 
		text >> v;
		word_from_array = to_string(v);	
		//cout<<endl<<"WORD word_from_array is: "<<word_from_array<<endl;
		// ABXD
		for (unsigned i=0, wl=word_from_array.length(); i<wl; ++i)
		{
			// A
			// B
			// X
			// D
			//cout<<"Current character of the word from the ARRAY is: "<< word_from_array.at(i)<<endl;
			steps++;
			//cout<<"Current character of the searching word is "<<str_to_find.at(i)<<endl;
			// A : <ABXD>
			if(word_from_array.at(i)==str_to_find.at(i)) // A == A
			{
				steps++;
				//cout<<endl<<"("<<i<<")The same characters: "<<word_from_array.at(i)<<" | "<<str_to_find.at(i)<<endl;
				if(i==wl-1)
				{   
					steps++;
					if(wl==l) 
					{	
						steps++;
						cout<<endl<<" coincides (word_from_array/str_to_find) on step "<<steps<<": "<<word_from_array<<" | "<<str_to_find<<endl;
						cout<<endl<<"i = "<<i<<", l = "<<l<<endl<<"string # "<<w_counter<<endl;
						return steps;
					}
				}
			}else 
				break;
			steps++;
		}
	}
	return 0;
}

int _tmain(int argc, _TCHAR* argv[])
{
	int test = 0;
	if(test==1)
	{
		int nmb = 12345;
		string str = to_string(nmb);
		char str_to_find = '4';
		cout<<"My string now is "<<str<<endl;
		for (unsigned i=0; i<str.length(); ++i)
		{
			cout<<"Current character is: "<< str.at(i)<<endl;
			if(str.at(i)==str_to_find) 
			{
				cout<<endl<<" *found* character "<<str.at(i)<<endl;
				break;
			}
		}
	}
	if(test==2)
		cout<<endl<<"Steps summary: "<<straightFind()<<endl;

	int biggestNumber = 0;
	double minNum = 0.03;
	cout<<(double)biggestNumber<<", doubled biggestNumber is now "<<biggestNumber<<endl;
	cout<<endl<<"compare them: "<<(minNum>biggestNumber)<<endl;
	return 0;
}

