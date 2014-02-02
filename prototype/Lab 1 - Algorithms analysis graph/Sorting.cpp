#include "stdafx.h"
#include "sorting.h"
#include <vector>
// ���������� ............................................
// ����������� ����������
void sortBubbling(int i)
{
	// �������� ������ ����� �� �����
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	// ��������� �������� ����� � �������:
	int steps=0;
	// ��� 1
	int clipboard;// ��������� ���������� ��� �������� �������� �������� ������������ �������
	// ��� 2
	/*	the variable that will define the inner loop 
		iterations number; (see the 'while' loop) we 
		need it because constants can't be changed! */
	int lmt;
	// ��� 3
	/*	we need this variable just to avoid keeping to repeat an expression 
		like innerCounter+1	*/
	int nextIndex;	
	/*	it will be used as an element's index to compare the array's elements 
		within an inner loop */
	// ��� 4
	int innerCounter;
		steps+=4;
	// �� ����� ������� ���� � ���� �����
	// �������� �� ������� �����
	for (int cnt=0; cnt<limit; cnt++)
	{
		// ��� 1
		lmt = limit-cnt;
		// ��� 2
		innerCounter = 0;
			steps+=2;
		/*	Go to the inner loop;
			its length should be decreased while every 
			new iteration (see video).
			It starts from the maximal value which is:
			array length (6) minus 1 (see a definition
			of 'lmt' variable); 
			every outer iteration decreases it 
			(see in the end of the 'while' loop):
			- the first iteration:	lmt = 5
			- the second iteration: lmt = 4 
			- etc...
			*/
		while(lmt>1)
		{ 
			// ��� 1
			nextIndex = innerCounter+1;
			// ��� 2
				steps+=2;
			if(nmbrs[innerCounter]>nmbrs[nextIndex]) // 5 < 3
			{
				/*	cout<< "\nA permutation is needed!\ncurrent elemen's value: " 
						<< nmbrs[innerCounter] << "\nnext element's value: "
						<< nmbrs[nextIndex]; */
				// ��� 1
				// store the array's element value
				clipboard = nmbrs[nextIndex];
				/*	cout<< "\nclipboard = nmbrs["<<innerCounter<<"+1] = "
						<< clipboard<<"\n"; */
				/*	here we lost an original value in the array
					but it was stored in the clipboard variable earlier */
				/*	cout<< "\nnmbrs["<<innerCounter<<"+1] = nmbrs["<<innerCounter<<"] = "
						<< nmbrs[innerCounter]<<"\n"; */
				// ��� 2
				nmbrs[nextIndex] = nmbrs[innerCounter]; // 3 -> 5 
				/*	take out the value stored in the clipboard earlier 
					and assign it to the current array's element */
				// ��� 3
				nmbrs[innerCounter] = clipboard;
					steps+=3;
				/*	cout<< "\nnmbrs["<<innerCounter<<"] = clipboard = "
						<< clipboard<<"\n"; */
			}
			// ��� 1,2
			lmt--;
			innerCounter++;
				steps+=2;
		}
	}
	// ��������� � ������� �����. ����� ��� ������� �����
	glob_alg_steps[0][i]=steps;
	if (show_details) showSorting(nmbrs,limit);
}
// ���������� ���������
void sortByInserts(int i)
{
	// �������� ������ ����� �� �����
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	// ��������� �������� ����� � �������:
		int steps=0;
	// ��� 1
	int clipboard; // ��������� ���������� ��� �������� �������� �������� ������������ �������
	// ��� 2
	int prev_index; // ������ ����������� ��������
		steps+=2;
	for (int cnt = 1; cnt < limit; cnt++)
    {
        // ��� 1
		clipboard = nmbrs[cnt]; // �������������� ��������� ���������� ������� ��������� �������� �������
        // ��� 2
		prev_index = cnt-1; // ���������� ������ ����������� �������� �������
        // ��� 3 - ������� ������� ����� � ����
			steps+=3;
		while(prev_index >= 0 && nmbrs[prev_index] > clipboard) // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
        {
            // ��� 1
			nmbrs[prev_index + 1] = nmbrs[prev_index]; // ������������ ��������� �������
            // ��� 2
			nmbrs[prev_index] = clipboard;
			// ��� 3
            prev_index--;
				steps+=3;
        }
    }
	// ��������� � ������� �����. ����� ��� ������� �����
	glob_alg_steps[1][i]=steps;
	if (show_details) showSorting(nmbrs,limit);
}
// ������� ����������
void sortQuick(int i)
{
	/* �������� ������ ����� �� �����
	��������!	� ������ ������ ������ �� ������,
				��� �������, � ������ �� ���������� ������,
				�.�. �� ��������� ������� ���������� ��������
				������ �� �������� �� �������� �������	*/
	vector<int> &nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	quickSort(nmbrs, 0, nmbrs.size()-1, i);
	if (show_details) showSorting(nmbrs,limit);
}
// ���������� ��������� ������� ����������
void quickSort(vector<int> &nmbrs, int first, int last, int i)
{
	// ��������� �������� ����� � �������:
		int steps=0;
	// ��� 1
	int pivotElement;
	// ��� 2 (�������)
		steps+=2;
    if(first < last)
    {   
        // ��� 1
		pivotElement = pivot(nmbrs, first, last, i); //cout<<"pivotElement = "<<pivotElement<<endl;
        // ��� 2,3
		quickSort(nmbrs, first, pivotElement-1, i);
        quickSort(nmbrs, pivotElement+1, last, i);
		steps+=3;
    }
	// ��������� � ������� �����. ����� ��� ������� �����
	glob_alg_steps[2][i]+=steps;
}
// ���������� ������� ����� ����������
int pivot( vector<int> &nmbrs,		// ������ ��������
		   int first,   // ������ ������� �������� �������
		   int last,	// ������ ���������� �������� �������
		   int i		// ������ ����� ��� ��������
		 ) 
{
    // ��������� �������� ����� � �������:
		int steps=0;
	// ��� 1
	int  p = first; // "������� �����" - ������ ������� �������� �������
	// ��� 2
	int pivotElement = nmbrs[first];
	/*	��� 3 - ��������� ������� ����� � ����, �.�. ������ ��� 
		���������� ��� ����� ��������� */
		steps+=3;
	for(int cnt = first+1 ; cnt <= last ; cnt++)
    {
        // ��� 1
			steps+=1;
		/* ��� ��������� ������� ���������� �������� "<=" �� ">" */
        if(nmbrs[cnt] <= pivotElement)
        {   //cout<<"\tswap "<<nmbrs[cnt]<<" <> "<<pivotElement<<endl;
            // ��� 1
			p++;
			// ���� 2-4 (������ swap()), 5 - ����� �������
            swap(nmbrs[cnt], nmbrs[p]);			
				steps+=5;
        }
    }
	// ��� 1-3
    swap(nmbrs[p], nmbrs[first]);
		steps+=3;
	// ��������� � ������� �����. ����� ��� ������� �����
	glob_alg_steps[2][i]+=steps;
    return p; // ���������� ������� �����
}
// ����������� ��������� ����������
void swap( int& a,	// ������ �������� 
		   int& b	// ��������� ��������
		 )
{
    int temp = a;
    a = b;
    b = temp;
}
//-----------------------------------------------------------
// ������������� ����� ���������� ���������
void sortData()
{
	setlocale(LC_ALL, "Russian");
	// ����� �����:
	int choice;
		
	cout<<"�������� �����:"
	<<endl<<"�������� ������� ���������� - ������� 8."
	<<endl<<"������� � ����������� ������� ���������� - ������� 9."
	<<endl<<"����� - ������� 0."<<endl
	<<"......................................................"<<endl;
	cin>>choice;
	if(choice==9) 
	{
		for (int i = 0; i < glob_algos; i++)
		{
			/*  ������� ������ ������� �� ����� ��������, ��������� 
				��� ���������� ������ � ������� glob_alg_steps ������ 
				���������� ����������� ������ ������ ���������:
				glob_alg_steps[������_���������][������_�����] */
			sortBubbling(i);
			sortByInserts(i);
			sortQuick(i);
		}
		// �������� ����������
		showResults();
	}
	if(choice==0) exit(0);
	if(choice==8)
	{
		for (int i = 0; i < glob_files_names.size(); i++)
		{
			cout<<"�������� "<<i+1<<". ����� ����������, ������� "<<i+1
				<<endl<<"����� ����� - ������� 0."<<endl
				<<"......................................................"<<endl;
			cin>>choice;
			if(choice==0) exit(0);
			if(choice==(i+1))
			{
				if(i) cout<<endl;
				cout<<"��� �����: "<<glob_files_names[i]<<endl;
				cout<<endl<<"����������� ����������"<<endl<<"-----------------------"<<endl;
				sortBubbling(i);	// ����������� ����������
				cout<<endl<<"���������� ���������"<<endl<<"-----------------------"<<endl;
				sortByInserts(i);	// ���������� ���������
				cout<<endl<<"������� ����������"<<endl<<"-----------------------"<<endl;
				sortQuick(i);	// ������� ����������
			}
			else break;
		}
		cout<<"������� � ����������� ������� ���������� - ������� 9."
		<<endl<<"����� - ������� 0."<<endl
		<<"......................................................"<<endl;
		if(choice==9) showResults();
		if(choice==0) exit(0);
	}
}
/*	���������:
	- ������ ������������� �������� �� �������: http://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC#.D0.92.D1.80.D0.B5.D0.BC.D1.8F_.D1.80.D0.B0.D0.B1.D0.BE.D1.82.D1.8B
	- vector: http://ru.cppreference.com/w/cpp/container/vector
	*/