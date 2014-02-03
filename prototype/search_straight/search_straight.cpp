#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

using namespace std;

/*int straightFind()
{
    vector<int> rowsArray;
	ifstream text("file_1000.txt");
	int count = 0;
	// включить кириллицу:
	//setlocale(LC_ALL, "Russian");
	//cout<<endl<<"До сортировки:"<<endl
		//<<"................"<<endl;
	while (text.good())
	{
		int v; text >> v;
		rowsArray.push_back(v);
		//cout<<v<<" ";
	}	//cout<<endl;
	

	int i, j;
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
    else return -1;
}*/

int _tmain(int argc, _TCHAR* argv[])
{
	int nmb = 12345;
	string str = to_string(nmb);
	cout<<"My string now is "<<str<<endl;
	return 0;
}

