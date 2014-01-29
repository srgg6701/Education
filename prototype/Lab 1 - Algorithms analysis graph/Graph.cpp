#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <iomanip>
#include <string> // http://en.cppreference.com/w/cpp/string/basic_string/to_string
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime> // ���� ����� �������� ����� ���������� ��������. � ���� �������!
//----------------------------------------------------------------------------------
#include <GL/glut.h>
#include "vars.h"
#include "markers.h"
using namespace std;

// ��������� ��� ���������� ��� ��������������� ������
vector<string>glob_files_names;

//-----------------------------------------------------------
// ������� ���������� ������:
// ����������� ����������....................................
void sortBubbling(vector<int> *,int);
// ���������� ���������......................................
void sortByInserts();
// ������� ����������........................................
void sortQuick();
	/*	����������� �������-������, ������������, ����� ��
		������������ �������� �������.	*/
	void quickSort(vector<int>&, int, int);
	/*	�������� ������� (swap()) ������������ ��������� �������
		� ���������� ����� ������� �����.	*/
	 int pivot(vector<int>&, int, int);
	/*	������������ ������� �������� ������� � ��������� ����� 
		�������� �� �������.	*/
	void swap(int&, int&);
//-----------------------------------------------------------
// ���������� ������:
void sortData();
//-----------------------------------------------------------

// ���������� ������� ����������
void showSorting(vector<int> nmbrs, int limit, int sorting_id=1){

	setlocale(LC_ALL, "Russian");

	cout<<endl<<"����� ����������: "
		<<endl<<"................";
	switch(sorting_id)
	{
		case 1:
			for (int i=0; i<limit; i++){
				if(nmbrs[i]) cout<<endl<<i+1<<" : "<<nmbrs[i];
				else cout<<"������� � �������� "<<i<<" �� ������...";
			}
			break;
		/*	������� ��� ���������, �� ������, ���� ������� �������� 
			������ �� ������� ������������ ����� ��������:	*/
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
	}
}

// �������� �������� ������ ..............................
/*	��������� ����� ������� � ��������� � ������������ 
�������� ��� �������� �������� ���� */
void buildMarkerRow( int &arrayNumbersRow,
					 float Bottom, 
					 float currentLeft
				   )
{
	//cout<<"Bottom: "<<Bottom<<endl;
	for (int col = 1; col <= globMrxCols; col++)
	{   
		// ������� ������� ������ � ������ ����� �������
		float Left		= currentLeft+globMrxColWidth*col;
		float Top		= Bottom+globMrxRowHeight;
		float Right		= currentLeft+globMrxColWidth*col+globMrxColWidth;
		//		Bottom	- �������� � �������� ��������� �������, ����� ������ ������� ������ ����� �������;
		/*cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
			<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
			<<"\tright/top -\t"<<Right<<":"<<Top<<endl
			<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl; */
		// 
		if(globNumbers[arrayNumbersRow][col-1]>0)
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(1.0,1.0,1.0);
		// ������� ������ ����� �������:
		// �����-������
		glVertex2f(Left,Bottom);
		// �����-�������
		glVertex2f(Left,Top);
		// ������-�������
		glVertex2f(Right,Top);
		// ������-������
		glVertex2f(Right,Bottom);
	}
	arrayNumbersRow++;
}
// ������� ������� ����������� ������
void setMarkers(bool copier=false)
{
	// ������� ���������� 2-D ������� ��� ���������� ���� �� 1 �� 5. 
	// ��. ����� �����: http://www.canstockphoto.com/pixel-art-globNumbers-and-mathematical-signs-12800261.html
	// ���������� ������� ������
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		float LeftEdge = (copier)? globSceneWidthHalf+glob_offset*2 : 0;	// 400 : 0
		int files_count=glob_files_names.size();
		for (int i = 1; i <= files_count; i++)
		{	
			// ���������� ����� ������ �������
			float currentX = LeftEdge +		// ����� ���� ����� (0-400)
                             globSceneWidthHalf/files_count	// 400/5 = 80 ����� ������� ��� ������ (����� 5, �� ���������� ������) �������
							 *i				// ����� ������� ����� ��������
							 -15;			// �������� ������� ����� ��� ����������� ������������� � ���������� ���������� �����
			// ��������� ���� � �������� (����� 5�4)
			for (int row = 1; row <= globMrxRows; row++)
			{
				// ��������� �������
				buildMarkerRow( /*	������� ������ ������� � ������� globNumbers
									(������ ������� �� ���� ������������ ������ 
									������� ������ � ����� �������) */
								arrayNumbersRow,
								/*	������ ������� ������� ������ � ����� ������� */
								globMrxTopLine-globMrxRowHeight*row,
								/*	����� ������� ������� ������ � ������ ����� ������� */
								currentX	
							  );
			}
		}
	glEnd();
}

// ��������� ������ ......................................
// c������ �����
void makeFiles()
{
	// �������� ������� ������� �� ������������ ����� �����: http://stackoverflow.com/a/900035/1522479
	string file_full_name;
	
	// http://ru.cppreference.com/w/cpp/numeric/random/rand
	srand(time(NULL));

	bool run  = true;		// ��������� �������� ��������

	setlocale(LC_ALL, "Russian");

	for (int i = 0, len = sizeof(glob_files_volumes)/sizeof(int); i < len; i++)
	{
		stringstream sstm;
		sstm << "file_"<< glob_files_volumes[i]<<".txt";
		file_full_name = sstm.str();
		
		// ��������� ��� ���������������� ����� � �������
		glob_files_names.push_back(file_full_name);
		// ���� �������� � ������, �������� �� -   
		//.insert(glob_files_names.begin(),file_full_name);		
		
		cout<<"������ ��� �����: "<<file_full_name<<endl;
		ofstream f(file_full_name); // �������/����������� ����
		int val;
		int jLen = glob_files_volumes[i];
		// ��� ����� - ���� ���������� �����������, ���������� ���
		if(glob_files_size_decreaser>1) jLen/=glob_files_size_decreaser;
		
		if(run)
		{				
			while(jLen)
			{
				//������������� ��������� ����� �� 0 �� 400000
				val = int(double(rand())/RAND_MAX*400000); 
				//cout<<"val : "<<val<<endl;
				f<<val; // ��������� ��������������� ����� � ������
				jLen--; // ��������������� �������
				if(jLen) f<<endl; // �������� ������� ������, ���� ������� �� ��������
			}
		}	
	}
}

// ������������ ������, �������� ��� ���������� ����� �����
vector<int> getRowsArray(int i=0)
{
	vector<int> rowsArray;
	ifstream text(glob_files_names[i]);
	int count = 0;
	// �������� ���������:
	//setlocale(LC_ALL, "Russian");
	//cout<<endl<<"�� ����������:"<<endl
		//<<"................"<<endl;
	while (text.good())
	{
		int v; text >> v;
		rowsArray.push_back(v);
		//cout<<v<<" ";
	}	//cout<<endl;
	return rowsArray;
}

// �������� �������� .....................................
// ��������� ����� ��� �����
void setGrid(bool copier=false)
{
	/*	���������� ��������� ���������, �������������� � ��������.
		����� ��� ���������� ��� ��������� ������ 4-� ��������� 
		(20 ������������� ����� / 5 ��������) ������, ��� �����, 
		��� ������������� ������ ������ �� 5-�� ������������ ������.		*/
	int vCount=0; 
	/*	������� (� ����� - ����������) ����� � ������ ������� ��� 
		����� ������; ������������ ����� ���� ����� ����������� 
		����������� �����.	*/
	float GridLeftEdge, GridRightEdge;  
	/*	���������� �������� ����� � ������ ������ ����� �����. 
		������������� �������� copier ��������, ��� ������ �����
		��� ������� �����. ���� �������� �� �������, �� - ��� ������. 
		.............................................................
		��. ��������� gluOrtho2D, �� ������ ������� ��������������
		������������ ����� ������ - ������� ����� �� ������ ���������:
		�����:	-50, ������: 875, 
		������: -50, �������: 450	*/
	if(copier)
	{
		/*	�������� �������� ������������ ���� 
			+ ������������ ��� �������� ����������� ������� */
		GridLeftEdge	= globSceneWidthHalf + glob_offset*2;	// 450
		GridRightEdge	= globSceneWidth + glob_offset*2;		// 825
	}
	else
	{
		GridLeftEdge	= 0;				//   0
		GridRightEdge	= globSceneWidthHalf;				// 400
	}
	const float grid_left_start		= GridLeftEdge;
	const float grid_right_finish	= GridRightEdge;
	//cout<<"Start grid"<<endl<<"........................."<<endl;
	// ���������� �� 20 ������������ ����� ��� ����� ������� �����
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// ���������� ���������	
		// ������� ������ ������ 4-� ��������� (���, ��� ����������� ������ ������ �����):
		if( vCount>0 && vCount%4==0 ) 
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;
		// �����
		glVertex2f(GridLeftEdge, 0); // 
		glVertex2f(GridLeftEdge, globSceneHeight);		// 
		GridLeftEdge+=glob_grid_step;
	}
	glColor3f(0.4,0.4,0.4);
	// ���������� �����������
	for ( float offsetBottom  = 0;	// 
				offsetBottom <= globSceneHeight;		// <= 400
				offsetBottom += glob_grid_step )
	{   //cout<<"offsetBottom: "<<offsetBottom<<"\t";
		glVertex2f(grid_left_start,offsetBottom);
		glVertex2f(grid_right_finish,offsetBottom);
	}	//cout<<endl;
}
// ��������� ����
void Draw()
{
	sortData(); // ������������� ���������� ������
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // �������� ������ ���������� �����
	glLineWidth (1.0); // ������� ������� ����� �����
	glLineStipple(1,0xAAAA); // ������� ��� ���������� ����� ��� ����� �����
	glBegin(GL_LINES);
		// ��������� ������ (�����) �����
		setGrid();
		// ��������� ������ (������) �����
		setGrid(true);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
		// ��������� ������� ������
		// �� ����� �����
		setMarkers();
		// �� ������ �����
		setMarkers(true);
	glFlush();
}
// ���������������� �������
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// ����� - left-bottom / right-top
	// ��������� ��������������� ��������
	gluOrtho2D(-glob_offset*2,		// -50	�����, x	
				globSceneWidth+glob_offset*3,	// 875	������, x	
			   -glob_offset*2,		// -50	������, y	
				globSceneHeight+glob_offset		// 450	�������, y	
			  ); 
}
// ���������� ������� ����������
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // ��. ���������� ������������ ����� ASCII �����: http://www.theasciicode.com.ar/
	{
		// ������� ���� �� ������� ��. "������":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // ������������ ����  
}
//
int _tmain(int argc, char** argv)
{
	/*	�������������/������������ ����� � ������� ��������� �����.
		--------------------------------------------------
	��������! 
	� �������� ������ �������������� ��������� ������ 
	������������ ������. ��� ����� ���������� �������
	�������� ���. glob_files_size_decreaser,  
	���������� ��������� ��� ������������ ��� �������� 
	��������� ������� glob_files_volumes � ����� vars.h. */
	makeFiles();
	// ������������� ���������� ������
	sortData(); 
	bool run = false;
	if(run)
	{
		// �������������
		glutInit(&argc, argv); 
		// 3 ����������� ������� ����� ����������� � ����� �������
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
		glutInitWindowSize(globSceneWidth,globSceneHeight);
		glutInitWindowPosition(450,200);
		glutCreateWindow("Grid");
		// �����������
		glutDisplayFunc(Draw);
		glutKeyboardFunc(Keyboard);
		Initialize();
		glutMainLoop();
	}	
	return 0;
}

// ���������� ............................................
// ����������� ����������
void sortBubbling(int i)
{
	// �������� ������ ����� �� �����
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	int clipboard;// ��������� ���������� ��� �������� �������� �������� ������������ �������
	/*	the variable that will define the inner loop 
		iterations number; (see the 'while' loop) we 
		need it because constants can't be changed! */
	int lmt;
	/*	we need this variable just to avoid keeping to repeat an expression 
		like innerCounter+1	*/
	int nextIndex;	
	/*	it will be used as an element's index to compare the array's elements 
		within an inner loop */
	int innerCounter;
	// �������� �� ������� �����
	for (int i=0; i<limit; i++)
	{
		lmt = limit-i;
		innerCounter = 0;
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
			nextIndex = innerCounter+1;
			if(nmbrs[innerCounter]>nmbrs[nextIndex]) // 5 < 3
			{
				/*	cout<< "\nA permutation is needed!\ncurrent elemen's value: " 
						<< nmbrs[innerCounter] << "\nnext element's value: "
						<< nmbrs[nextIndex]; */
				// store the array's element value
				clipboard = nmbrs[nextIndex];
				/*	cout<< "\nclipboard = nmbrs["<<innerCounter<<"+1] = "
						<< clipboard<<"\n"; */
				/*	here we lost an original value in the array
					but it was stored in the clipboard variable earlier */
				/*	cout<< "\nnmbrs["<<innerCounter<<"+1] = nmbrs["<<innerCounter<<"] = "
						<< nmbrs[innerCounter]<<"\n"; */
				nmbrs[nextIndex] = nmbrs[innerCounter]; // 3 -> 5 
				/*	take out the value stored in the clipboard earlier 
					and assign it to the current array's element */
				nmbrs[innerCounter] = clipboard;
				/*	cout<< "\nnmbrs["<<innerCounter<<"] = clipboard = "
						<< clipboard<<"\n"; */
			}
			lmt--;
			innerCounter++;
		}
	}
	showSorting(nmbrs,limit);
	cout<<endl;
}
// ���������� ���������
void sortByInserts(int i)
{
	// �������� ������ ����� �� �����
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	int clipboard; // ��������� ���������� ��� �������� �������� �������� ������������ �������
	int prev_index; // ������ ����������� ��������
	for (int current_index = 1; current_index < limit; current_index++)
    {
        clipboard = nmbrs[current_index]; // �������������� ��������� ���������� ������� ��������� �������� �������
        prev_index = current_index-1; // ���������� ������ ����������� �������� �������
        while(prev_index >= 0 && nmbrs[prev_index] > clipboard) // ���� ������ �� ����� 0 � ���������� ������� ������� ������ ��������
        {
            nmbrs[prev_index + 1] = nmbrs[prev_index]; // ������������ ��������� �������
            nmbrs[prev_index] = clipboard;
            prev_index--;
        }
    }
	showSorting(nmbrs,limit);
	cout<<endl;
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
	quickSort(nmbrs, 0, nmbrs.size()-1);
	showSorting(nmbrs,limit);
	cout<<endl;
}
// ���������� ��������� ������� ����������
void quickSort(vector<int> &nmbrs, int first, int last)
{
	int pivotElement;

    if(first < last)
    {   
        pivotElement = pivot(nmbrs, first, last); //cout<<"pivotElement = "<<pivotElement<<endl;
        quickSort(nmbrs, first, pivotElement-1);
        quickSort(nmbrs, pivotElement+1, last);
    }
}
// ���������� ������� ����� ����������
int pivot( vector<int> &nmbrs,		// ������ ��������
		   int first,   // ������ ������� �������� �������
		   int last		// ������ ���������� �������� �������
		 ) 
{
    int  p = first; // "������� �����" - ������ ������� �������� �������
    int pivotElement = nmbrs[first];
	for(int i = first+1 ; i <= last ; i++)
    {
        /* ��� ��������� ������� ���������� �������� "<=" �� ">" */
        if(nmbrs[i] <= pivotElement)
        {   //cout<<"\tswap "<<nmbrs[i]<<" <> "<<pivotElement<<endl;
            p++;
            swap(nmbrs[i], nmbrs[p]);
        }
    }
 
    swap(nmbrs[p], nmbrs[first]);
 
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
	
	for (int i = 0; i < glob_files_names.size(); i++)
	{
		cout<<"�������� "<<i+1<<". ���� ������ ����������, ������� "<<i+1<<". ����� - 0."<<endl
			<<"......................................................"<<endl;
		int choice;
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
}
/*	���������:
	- ������ ������������� �������� �� �������: http://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC#.D0.92.D1.80.D0.B5.D0.BC.D1.8F_.D1.80.D0.B0.D0.B1.D0.BE.D1.82.D1.8B
	- vector: http://ru.cppreference.com/w/cpp/container/vector
	*/