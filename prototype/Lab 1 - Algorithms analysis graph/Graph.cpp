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
#include "api.h"
#include "markers.h"
using namespace std;

// ��������� ��� ���������� ��� ��������������� ������
vector<string>glob_files_names;
/*	����������, ���������� �� ������ ���������� ����������;
	����� ���� ��������� true ������ ������ ���������������
	�������.	*/
bool show_details=false;

//-----------------------------------------------------------
//-----------------------------------------------------------
// ������� ���������� ������:
// ����������� ����������....................................
void sortBubbling(int);
// ���������� ���������......................................
void sortByInserts(int);
// ������� ����������........................................
void sortQuick(int);
	/*	����������� �������-������, ������������, ����� ��
		������������ �������� �������.	*/
	void quickSort(vector<int>&, int, int, int);
	/*	�������� ������� (swap()) ������������ ��������� �������
		� ���������� ����� ������� �����.	*/
	 int pivot(vector<int>&, int, int, int);
	/*	������������ ������� �������� ������� � ��������� ����� 
		�������� �� �������.	*/
	void swap(int&, int&);
//-----------------------------------------------------------
// ���������� ������:
void sortData();
// ������� ���������� �� ������� ������������ ��������� 
void showResults()
{
	setlocale(LC_ALL, "Russian");
	cout<<"���������� �����."<<endl;
	for (int algo_index = 0; algo_index < glob_algos; algo_index++)
	{
		cout<<algo_index+1<<". "; // 1(-5). ���_��������� 
		switch(algo_index)
		{
			case 0:
				cout<<"����������� ����������"; //cout<<"1. ����������� ����������:"<<endl;
				break;
			case 1:
				cout<<"���������� ���������";
				break;
			case 2:
				cout<<"������� ����������";
				break;
			default: 
				return;
		}		
		cout<<":"<<endl;
		for (int file_index = 0; file_index < glob_files; file_index++)
		{   // 
			// glob_alg_analysis_steps[glob_algos][file_index] - ������ ���������, ����
			cout<<"���� "<<file_index+1<<": "<<glob_alg_analysis_steps[algo_index][file_index]<<endl;
		}
		cout<<"---------------------"<<endl;
	}
}
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
	cout<<endl;
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
vector<float> setMarkers(bool copier=false)
{
	/*	������� ��������� ������ ��� ������������ x-��������� 
		(��������� ��� ������������ ������ � ������������� 
		�������� ����������).	*/
	vector<float> xPos;
	// ������� ���������� 2-D ������� ��� ���������� ���� �� 1 �� 5. 
	// ��. ����� �����: http://www.canstockphoto.com/pixel-art-globNumbers-and-mathematical-signs-12800261.html
	// ���������� ������� ������
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		float LeftEdge = (copier)? globGraphSpace+globDoubleOffset : 0;	// 400 : 0
		int files_count=glob_files_names.size();
		
		for (int i = 1; i <= files_count; i++)
		{	
			// ���������� ����� ������ �������
			float currentX = LeftEdge +		// ����� ���� ����� (0-400)
                             globGraphSpace/files_count	// 400/5 = 80 ����� ������� ��� ������ (����� 5, �� ���������� ������) �������
							 *i				// ����� ������� ����� ��������
							 -15;			// �������� ������� ����� ��� ����������� ������������� � ���������� ���������� �����
			/*	�������� x-���������� � ��������� ������.
				����� ����� ������������ � ��� ���������
				�������������� ���������� �������, ���������������
				�������� ��������� �������������� ���������.	*/
			xPos.push_back(currentX+15);
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
	return xPos;
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

float getGridTops(float Top=0.0)
{
	float currentTop = globGraphSpace;
	if (Top) currentTop+=globDoubleOffset+Top;
	return currentTop;
}
// �������� �������� .....................................
// ��������� ����� ��� �����
void setGrid(int graph_number)
{
	/*	������� (� ����� - ����������) ����� � ������ ������� ��� 
		����� ������; ������������ ����� ���� ����� ����������� 
		����������� �����.	*/
	float GridLeftEdge, GridRightEdge, GridTopEdge, GridBottomEdge;  
	/*	���������� �������� ��������� ����� �����. 
		.............................................................
		��. ��������� gluOrtho2D, �� ������ ������� ��������������
		������������ ����� ������ - ������� ����� �� ������ ���������:	
		Left:	-50
		Right:	875
		Bottom	-50
		Top		825	
		.................................................................
		��������!
		1. ������/����� ������� ������ ������������� ������ ���������;
		2. ������� ������ ������������� ��� ������� ������� ����� ������.
		��. ����� � .xslx-�����.		*/
	/*	��������� ���������� �������� �����, ������� ����� �������������� 
		���������� �������, ����� �������� ���������� ���������	*/
	float Left1,Left2,Right1,Right2,Top1,Top2,Bottom1,Bottom2;
	/*	����� ������� ��� 1-�� � 3-�� ������ */
	Left1	= 0;
	/*	����� ������� ��� 2-�� � 4-�� ������ - 
		������ ����� ����������� ����� + ������� ���������� ������ */
	Left2	= globGraphSpace + globDoubleOffset;
	/*	������ ������� ��� 1-�� � 3-�� ������ - 
		������ ����� ����� */
	Right1	= globGraphSpace;
	/*	������ ������� ��� 2-�� � 4-�� ������ - 
		����� ������� + ������ */
	Right2	= Left2 + globGraphSpace;
	/*	������� ������� ������ � ������ (������) ���� */
	Top1	= getGridTops();//globGraphSpace; // 
	/*	������� ������� ������ �� ������ (�������) ���� */
	Top2	= getGridTops(Top1);//Top1+globDoubleOffset+globGraphSpace;
	/*	������ ������� ������ � ������ (������) ���� */
	Bottom1	= 0;
	/*	������ ������� ������ �� ������ (�������) ���� */
	Bottom2	= Top1+globDoubleOffset;

	switch(graph_number)
	{
		case 1:
			GridLeftEdge	= Left1;
			GridRightEdge	= Right1;
			GridTopEdge		= Top1;
			GridBottomEdge	= Bottom1;
			break;
		case 2:
			GridLeftEdge	= Left2; 
			GridRightEdge	= Right2;
			GridTopEdge		= Top1;
			GridBottomEdge	= Bottom1;
			break;
		case 3:
			GridLeftEdge	= Left1;
			GridRightEdge	= Right1;
			GridTopEdge		= Top2;
			GridBottomEdge	= Bottom2;
			break;
		case 4:
			GridLeftEdge	= Left2;
			GridRightEdge	= Right2;
			GridTopEdge		= Top2;
			GridBottomEdge	= Bottom2;
			break;
	}

	// ��������� x-���������� ��� �������������� �����, ������������ �����:
	// �����
	const float grid_left_start		= GridLeftEdge;
	// ������
	const float grid_right_finish	= GridRightEdge;
	
	bool test=true;
	//if (test) cout<<endl<<"GRAPH "<<graph_number<<endl<<"........................."<<endl;
	
	/*	���������� ��������� ���������, �������������� � ��������.
		����� ��� ���������� ��� ��������� ������ 4-� ��������� 
		(20 ������������� ����� / 5 ��������) ������, ��� �����, 
		��� ������������� ������ ������ �� 5-�� ������������ ������.		*/
	int vCount=0; 
	/*	���������� ���������� ���������� ��� ������� ������� ����� ��� 
		�����. ���������� ������ ����� / ���������� ������	*/
	int vBunch = glob_grid_value/glob_files;
	//if (test) cout<<"Set verticals:"<<endl;
	// ���������� �� 20 ������������ ����� ��� ����� ������� �����
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// ���������� ���������	
		// -------------------------------------------------------------------------------
		// ������� ������ ������ 4-� ��������� (���, ��� ����������� ������ ������ �����):
		if( vCount>0 
			&& vCount%vBunch==0 // ���� ��� ������� �� �������, ������ - ����� ��������� ������ 4
		  ) 
			glColor3f(1.0,0.0,0.5); // ���������� ������������� ���� ��� ��������� �����
		else
			glColor3f(0.4,0.4,0.4);
		vCount++; 
		//if (test) cout<<"\t"<<vCount<<": "<<"bottom(x,y) = "<<GridLeftEdge<<", "<<GridBottomEdge<<"\ttop(x,y) = "<<GridLeftEdge<<", "<<GridTopEdge<<endl;
		// �����
		glVertex2f(GridLeftEdge, GridBottomEdge); // 0
		glVertex2f(GridLeftEdge, GridTopEdge);		// 
		GridLeftEdge+=glob_grid_step;
	}
	// ���������� �����������
	// -------------------------------------------------------------------------------
	// ��������� ����
	glColor3f(0.4,0.4,0.4);
	//if (test) int cnt=0; cout<<"Set horizontals:"<<endl;
	// ��������� ��
	for ( /* ���������� ��������� ������ �������� �����������
			 ��� ������������� ������ ����� ���������� ����� */
		  float offsetBottom  = GridBottomEdge;
				/* �������� y-����� ����������� ����� �������������
				   �� �������� ������� ������� ����� �������� ����� */
				offsetBottom <= GridTopEdge;
				/* ����������� �� ������������� ����� ��� ����� */
				offsetBottom += glob_grid_step  //
		)
	{   //if (test) cnt++;cout<<"\t"<<cnt<<": "<<"left(x,y) = "<<grid_left_start<<", "<<offsetBottom<<"\tright(x,y) = "<<grid_right_finish<<", "<<offsetBottom<<endl;
		glVertex2f(grid_left_start,offsetBottom);
		glVertex2f(grid_right_finish,offsetBottom);
	}	//cout<<endl;
}
// ��������� ����
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // �������� ������ ���������� �����
	glLineWidth (1.0); // ������� ������� ����� �����
	glLineStipple(1,0xAAAA); // ������� ��� ���������� ����� ��� ����� �����
	glBegin(GL_LINES);	
	/*	��������� ����� ������. i ���������� ����� �����.
		�������: 
		1. ������-����� 
		2. ������-������
		3. �������-�����
		4. �������-������
		*/
	for (int i = 1; i <= 4; i++)
		setGrid(i);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
	// ���������� ����� ������������ (��� ������ ���������)
	bool test=true;
	
	// ��������� ������� ������
	// �� ����� �����
	vector<float> xPosLeft1 = setMarkers();
	// �� ������ �����
	setMarkers(true);
	
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		
	/*	������� ������������ ���������� �������� ����� ��� ���������� �����.
		��� ����� ������� ���������� ���������� �������� (�����. ��������/�����
		����������), ����� ���������� � ������� glob_alg_analysis_steps (�������� ����� 
		��������� ��������� ��������� ��������, ��� ����������� ����������) */
	int biggestNumber;
	/* ������ ���������� �������� �������� ���������� ������� (4)	*/ 
	int lastIndex = glob_files-1;
	/* ��������� ��� ��������� ����������� ������� ������� ����� �����;
	   �������������� ��� ����������� ������������� ��������, �����������
	   � ���������� ������� �������� ��������� (����������� � ������� glob_alg_analysis_steps)
	   � y-������� ������� ������� ����� �����.	*/
	float yRatio;
	/* ������� �������� ������� ����� ��� �������� ����������� ���������� - �������� ��� 
	   ������ 1-2 � 3-4. � ������ ������ ������������ ���������� ����� ������ ������� ����,
	   �� ������, ��������������, - �������. */
	float yRatioCurrentTopBase = globGraphSpace*0.9;
	
	// ��������� ��� 4 �����:
	for ( int i = 0, 
			  index_algo = 0,	// ������ ��������� � globalAlgosColors - ����� ��� ������ ����� ���������� ������ ������� �������� ���������
			  // ������� ���������� ������, ��� ������������ �����. ����� � �������� �����
			  grphx = globColsNumber*globRowsNumber; // 4
		  // ���� ������������ ��� ������� �� ������
		  i < grphx; 
		  i++
		)
	{
		/* ������� ������������ ��������, ���������� � ���������� ������� �������� ���������
		   (��. ������ glob_alg_analysis_steps)*/
		biggestNumber = 0; // �������� ����������
		// �������� �������
		for (int b = 0; b < glob_algos; b++)
		{
			if(glob_alg_analysis_steps[b][lastIndex] > biggestNumber)
				biggestNumber = glob_alg_analysis_steps[b][lastIndex];
		}
		/*  ���� ������� ������ ��� ������, ������������� ���������� ������� ����� 
			��� ���������� ����� �����, ������� �������� ����� � ������ �����
			(��. ����� � .xslx-�����)	*/
		if(i==globRowsNumber-1) yRatioCurrentTopBase += globGraphSpace + globDoubleOffset; 
		// �������������! 
		if(!biggestNumber) biggestNumber=1; // �� ������, ���� �� ������-�� �������� ����.
		yRatio = yRatioCurrentTopBase/float(biggestNumber);
		/*	����� ��� ���������� ����� ����� ������� ��� �������� 
			������� glob_alg_analysis_steps �� ������������� �������� yRatio	*/
		//cout<<endl<<"algorithm #: "<<index_algo+1<<";\nColors: "<<globalAlgosColors[index_algo][0]<<","<<globalAlgosColors[index_algo][1]<<","<<globalAlgosColors[index_algo][2]<<endl;	
		// ���������� ���� ���
		glColor3f(	globalAlgosColors[index_algo][0], // R
					globalAlgosColors[index_algo][1], // G
					globalAlgosColors[index_algo][2]  // B
				 );
		
		for (int index_file = 0; index_file < glob_files; index_file++)
		{
			if(index_file>1) 
				glVertex2d( xPosLeft1[index_file-1], 
							glob_alg_analysis_steps[index_algo][index_file-1]*yRatio);
			
			glVertex2d( /*	������� �������� �������, ����������������
						���� �� �������������� ��������������� ������.
						����� ������������� ���������� ������ ������������
						���� �����.	*/
						xPosLeft1[index_file],
						/*	��������������� �������� ���������� �����, 
						����������� ���������� ��� ���������� �����
						������� ����������. */
						glob_alg_analysis_steps[index_algo][index_file]*yRatio
					  );
			
			//cout<<"x: "<<xPosLeft1[index_file]<<", y: "<<glob_alg_analysis_steps[index_algo][index_file]*yRatio<<endl;
		}
		index_algo++;
	}
	glEnd();
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
	gluOrtho2D(-globDoubleOffset,					// -50	�����, x	
				/* ���������� ������ ���� �������� ���
				   ������ ������ ����� +
				   ���������� ����� ������� +
				   ���������� ������ ������ �� ������� ����� */
				globSceneWidth+globDoubleOffset+glob_offset,	// 875	= 400 + 50 + 400 + 25 ������, x	
			   -globDoubleOffset,	// -50	������, y	
				globSceneHeight		// 875	�������, y	
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
	bool run = true;
	if(run)
	{
		// �������������
		glutInit(&argc, argv); 
		// 3 ����������� ������� ����� ����������� � ����� �������
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
		/*	���������� � ���������� ������ ���� (��. ��������� glOrtho2d())
			50 - ������ ����� �� ������ ���������
		*/
		float wSizeX = globDoubleOffset+globSceneWidth+globDoubleOffset+glob_offset;
		float wSizeY = globDoubleOffset+globSceneHeight;
		cout<<"WINDOW size: "<<wSizeX<<" x "<<wSizeY<<endl;
		glutInitWindowSize(wSizeX,wSizeY);
		glutInitWindowPosition(450,100);
		glutCreateWindow("Graph");
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
	glob_alg_analysis_steps[0][i]=steps;
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
	glob_alg_analysis_steps[1][i]=steps;
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
	glob_alg_analysis_steps[2][i]+=steps;
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
	glob_alg_analysis_steps[2][i]+=steps;
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
				��� ���������� ������ � ������� glob_alg_analysis_steps ������ 
				���������� ����������� ������ ������ ���������:
				glob_alg_analysis_steps[������_���������][������_�����] */
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
		for (unsigned int i = 0; i < glob_files_names.size(); i++)
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