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
	
	string strs = "2002";
	// включить кириллицу: setlocale(LC_ALL, "Russian");
	string int2str;
	cout<<"strs length = "<<strs.length()<<endl;
	for (unsigned i=0; i<strs.length(); ++i)
		cout<<" :: "<<strs.at(i)<<endl;
	/*while (text.good())
	{
		int v; 
		text >> v;
		int2str = to_string(v);
		cout<<"int2str: "<<int2str<<endl;
		for (unsigned i=0; i<int2str.length(); ++i)
		{
			cout<<"Current character is: "<< int2str.at(i)<<endl;
			if(int2str.at(i)==strs) 
			{
				cout<<endl<<" *found* character "<<int2str.at(i)<<endl;
				break;
			}
		}
	}*/	
	

	/*int i, j;
    int n = (int) rowsArray.size();
    int m = (int) find_str.size();
    i = -1 + _start;
    do
    {
        j = 0;
        i++;
        while( (j < m) && (rowsArray.at(i + j) == find_str.at(j)) ) j++;
    } while( j<m && i<n-m );
 
    if (j == m)
    {
        return i;
    }
    else return -1;*/
	return 0;
}/**/

int _tmain(int argc, _TCHAR* argv[])
{
	int test = 2;
	if(test==1)
	{
		int nmb = 12345;
		string str = to_string(nmb);
		char strs = '4';
		cout<<"My string now is "<<str<<endl;
		for (unsigned i=0; i<str.length(); ++i)
		{
			cout<<"Current character is: "<< str.at(i)<<endl;
			if(str.at(i)==strs) 
			{
				cout<<endl<<" *found* character "<<str.at(i)<<endl;
				break;
			}
		}
	}
	if(test==2)
		straightFind();

	return 0;
}

