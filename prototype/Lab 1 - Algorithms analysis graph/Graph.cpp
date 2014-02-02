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
#include "sorting.h"
#include "markers.h"
using namespace std;

// ��������� ��� ���������� ��� ��������������� ������
vector<string>glob_files_names;
/*	����������, ���������� �� ������ ���������� ����������;
	����� ���� ��������� true ������ ������ ���������������
	�������.	*/
bool show_details=false;

//-----------------------------------------------------------

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
			// glob_alg_steps[glob_algos][file_index] - ������ ���������, ����
			cout<<"���� "<<file_index+1<<": "<<glob_alg_steps[algo_index][file_index]<<endl;
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
		float LeftEdge = (copier)? globGraphSpace+glob_offset*2 : 0;	// 400 : 0
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

// �������� �������� .....................................
// ��������� ����� ��� �����
void setGrid(int graph_number)
{
	/*	���������� ��������� ���������, �������������� � ��������.
		����� ��� ���������� ��� ��������� ������ 4-� ��������� 
		(20 ������������� ����� / 5 ��������) ������, ��� �����, 
		��� ������������� ������ ������ �� 5-�� ������������ ������.		*/
	int vCount=0; 
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
		������ ����� ����������� ����� + ���������� ������ */
	Left2	= globGraphSpace + glob_offset*2;
	/*	������ ������� ��� 1-�� � 3-�� ������*/
	Right1	= globGraphSpace;
	/*	������ ������� ��� 2-�� � 4-�� ������ - 
		����� ������� + ������ */
	Right2	= globSceneWidth + glob_offset;
	/*	������� ������� ������ � ������ (������) ���� */
	Top1	= globSceneHeight/globRowsNumber-glob_offset*2; // 
	/*	������� ������� ������ �� ������ (�������) ���� */
	Top2	= globSceneHeight+glob_offset*2;
	/*	������ ������� ������ � ������ (������) ���� */
	Bottom1	= 0;
	/*	������ ������� ������ �� ������ (�������) ���� */
	Bottom2	= Top1+glob_offset*2;

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

	const float grid_left_start		= GridLeftEdge;
	const float grid_right_finish	= GridRightEdge;
	//cout<<"Start grid"<<endl<<"........................."<<endl;
	
	/*	���������� ���������� ���������� ��� ������� ������� ����� ��� 
		�����. ���������� ������ ����� / ���������� ������	*/
	int vBunch = glob_grid_value/glob_files; 
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
		// �����
		glVertex2f(GridLeftEdge, GridBottomEdge); // 0
		glVertex2f(GridLeftEdge, GridTopEdge);		// 
		GridLeftEdge+=glob_grid_step;
	}
	// ���������� �����������
	// -------------------------------------------------------------------------------
	// ��������� ����
	glColor3f(0.4,0.4,0.4);
	// ��������� ��
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

	// ��������� ������� ������
	// �� ����� �����
	vector<float> xPosLeft1 = setMarkers();
	// �� ������ �����
	setMarkers(true);
	/*	������� ������������ ���������� �������� ����� ��� ���������� �����.
		��� ����� ������� ���������� �������� �� glob_alg_steps (�������� 
		����� ��������� ���������, ��� ����������� ����������). */
	int biggestNumber = 0;
	int lastIndex = glob_files-1;
	for (int i = 0; i < glob_algos; i++)
	{
		if(glob_alg_steps[i][lastIndex] > biggestNumber)
			biggestNumber = glob_alg_steps[i][lastIndex];
	}
	// �������������! 
	float yRatio = globSceneHeight*0.9/float(biggestNumber);
	/*	����� ��� ���������� ����� ����� ������� ��� �������� 
		������� glob_alg_steps �� ������������� �������� yRatio	*/
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		
	// ������ ����� ��� ����� ������������� ����������
	float vColors[glob_algos][3]={
			{0.0,0.0,1.0},
			{1.0,0.0,0.0},
			{1.0,0.0,1.0},
			{1.0,0.5,0.0},
			{0.0,1.0,0.0}
	};
	// ��������� ��� 4 �����:
	for ( int i = 0, 
			  index_algo = 0,	// ������ ��������� � vColors - ����� ��� ������ ����� ���������� ������ ������� �������� ���������
			  grphx = globColsNumber*globRowsNumber; // 4
		  i < grphx; 
		  i++
		)
	{
		//cout<<endl<<"algorithm #: "<<index_algo+1<<";\nColors: "<<vColors[index_algo][0]<<","<<vColors[index_algo][1]<<","<<vColors[index_algo][2]<<endl;
		if(i==grphx/2) 
			index_algo = 0; // �������� ������� ���������� ����� ���������� ������ ��� ����������
		
		// ���������� ���� ���
		glColor3f(	vColors[index_algo][0], // R
					vColors[index_algo][1], // G
					vColors[index_algo][2]  // B
				 );
		
		for (int index_file = 0; index_file < glob_files; index_file++)
		{
			if(index_file>1) 
				glVertex2d( xPosLeft1[index_file-1], 
							glob_alg_steps[index_algo][index_file-1]*yRatio);
			
			glVertex2d( /*	������� �������� �������, ����������������
						���� �� �������������� ��������������� ������.
						����� ������������� ���������� ������ ������������
						���� �����.	*/
						xPosLeft1[index_file],
						/*	��������������� �������� ���������� �����, 
						����������� ���������� ��� ���������� �����
						������� ����������. */
						glob_alg_steps[index_algo][index_file]*yRatio
					  );
			
			cout<<"x: "<<xPosLeft1[index_file]<<", y: "<<glob_alg_steps[index_algo][index_file]*yRatio<<endl;
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
	gluOrtho2D(-glob_offset*2,					// -50	�����, x	
				globSceneWidth+glob_offset*3,	// 875	������, x	
			   -glob_offset*2,					// -50	������, y	
				globSceneHeight+glob_offset		// 825	�������, y	
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
		glutInitWindowSize(globSceneWidth,globSceneHeight);
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