#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <iomanip>
#include <string> // http://en.cppreference.com/w/cpp/string/basic_string/to_string
#include <sstream>
#include <fstream>
#include <vector>
#include <ctime> // если будем измерять время выполнения процедур. А ведь придётся!
//----------------------------------------------------------------------------------
#include <GL/glut.h>
#include "api.h"
#include "sorting.h"
#include "markers.h"
using namespace std;

// контейнер для сохранения имён сгенерированных файлов
vector<string>glob_files_names;
/*	определяет, показывать ли детали выполнения сортировки;
	может быть присвоено true внутри каждой соответствующей
	функции.	*/
bool show_details=false;

//-----------------------------------------------------------

// вывести информацию по каждому выполненному алгоритму 
void showResults()
{
	setlocale(LC_ALL, "Russian");
	cout<<"Количество шагов."<<endl;
	for (int algo_index = 0; algo_index < glob_algos; algo_index++)
	{
		cout<<algo_index+1<<". "; // 1(-5). Имя_алгоритма 
		switch(algo_index)
		{
			case 0:
				cout<<"Пузырьковая сортировка"; //cout<<"1. Пузырьковая сортировка:"<<endl;
				break;
			case 1:
				cout<<"Сортировка вставками";
				break;
			case 2:
				cout<<"Быстрая сортировка";
				break;
			default: 
				return;
		}		
		cout<<":"<<endl;
		for (int file_index = 0; file_index < glob_files; file_index++)
		{   // 
			// glob_alg_steps[glob_algos][file_index] - индекс алгоритма, файл
			cout<<"Файл "<<file_index+1<<": "<<glob_alg_steps[algo_index][file_index]<<endl;
		}
		cout<<"---------------------"<<endl;
	}
}
// отобразить процесс сортировки
void showSorting(vector<int> nmbrs, int limit, int sorting_id=1){

	setlocale(LC_ALL, "Russian");
	cout<<endl<<"После сортировки: "
		<<endl<<"................";
	switch(sorting_id)
	{
		case 1:
			for (int i=0; i<limit; i++){
				if(nmbrs[i]) cout<<endl<<i+1<<" : "<<nmbrs[i];
				else cout<<"Элемент с индексом "<<i<<" не найден...";
			}
			break;
		/*	оставим как заготовку, на случай, если захотим выводить 
			данные по каждому сортируемому файлу отдельно:	*/
		case 2: break;
		case 3: break;
		case 4: break;
		case 5: break;
	}
	cout<<endl;
}

// СОЗДАНИЕ МАРКЕРОВ ФАЙЛОВ ..............................
/*	построить сетку маркера и заполнить её закрашенными 
ячейками для создания контуров цифр */
void buildMarkerRow( int &arrayNumbersRow,
					 float Bottom, 
					 float currentLeft
				   )
{
	//cout<<"Bottom: "<<Bottom<<endl;
	for (int col = 1; col <= globMrxCols; col++)
	{   
		// Позиции текущей ячейки в строке сетки маркера
		float Left		= currentLeft+globMrxColWidth*col;
		float Top		= Bottom+globMrxRowHeight;
		float Right		= currentLeft+globMrxColWidth*col+globMrxColWidth;
		//		Bottom	- получена в качестве аргумента функции, равна нижней позиции строки сетки маркера;
		/*cout<<"\tleft/bottom -\t"<<Left<<":"<<Bottom<<endl
			<<"\tleft/top -\t"<<Left<<":"<<Top<<endl
			<<"\tright/top -\t"<<Right<<":"<<Top<<endl
			<<"\tright/bottom -\t"<<Right<<":"<<Bottom<<endl<<endl; */
		// 
		if(globNumbers[arrayNumbersRow][col-1]>0)
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(1.0,1.0,1.0);
		// создать ячейки сетки маркера:
		// левая-нижняя
		glVertex2f(Left,Bottom);
		// левая-верхняя
		glVertex2f(Left,Top);
		// правая-верхняя
		glVertex2f(Right,Top);
		// правая-нижняя
		glVertex2f(Right,Bottom);
	}
	arrayNumbersRow++;
}
// создать маркеры загружаемых файлов
vector<float> setMarkers(bool copier=false)
{
	/*	создать векторный массив для сохраненения x-координат 
		(вертикали для откладывания данных с резульататами 
		анализов алгоритмов).	*/
	vector<float> xPos;
	// создать внутреннюю 2-D матрицу для построения цифр от 1 до 5. 
	// См. схему здесь: http://www.canstockphoto.com/pixel-art-globNumbers-and-mathematical-signs-12800261.html
	// Нарисовать маркеры файлов
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		float LeftEdge = (copier)? globGraphSpace+glob_offset*2 : 0;	// 400 : 0
		int files_count=glob_files_names.size();
		
		for (int i = 1; i <= files_count; i++)
		{	
			// установить левый отступ маркера
			float currentX = LeftEdge +		// левый край сетки (0-400)
                             globGraphSpace/files_count	// 400/5 = 80 длина отрезка для одного (всего 5, по количеству файлов) маркера
							 *i				// общая текущая длина отрезков
							 -15;			// смещение маркера влево для визуального центрирования с выделенной вертикалью сетки
			/*	добавить x-координату в векторный массив.
				Далее будем использовать её для установки
				горизонтальной координаты вершины, визуализирующей
				значение параметра анализируемого алгоритма.	*/
			xPos.push_back(currentX+15);
			// построить блок с маркером (сетка 5х4)
			for (int row = 1; row <= globMrxRows; row++)
			{
				// построить маркеры
				buildMarkerRow( /*	текущий индекс массива с цифрами globNumbers
									(внутри функции по нему определяется индекс 
									текущей строки в сетке маркера) */
								arrayNumbersRow,
								/*	нижняя позиция текущей строки в сетке маркера */
								globMrxTopLine-globMrxRowHeight*row,
								/*	левая граница текущей ячейки в строке блока маркера */
								currentX	
							  );
			}
		}
	glEnd();
	return xPos;
}

// ГЕНЕРАЦИЯ ФАЙЛОВ ......................................
// cоздать файлы
void makeFiles()
{
	// отличный сборник решений по канкатенации строк здесь: http://stackoverflow.com/a/900035/1522479
	string file_full_name;
	
	// http://ru.cppreference.com/w/cpp/numeric/random/rand
	srand(time(NULL));

	bool run  = true;		// позволить процессу начаться

	setlocale(LC_ALL, "Russian");

	for (int i = 0, len = sizeof(glob_files_volumes)/sizeof(int); i < len; i++)
	{
		stringstream sstm;
		sstm << "file_"<< glob_files_volumes[i]<<".txt";
		file_full_name = sstm.str();
		
		// сохранить имя сгенерированного файла в векторе
		glob_files_names.push_back(file_full_name);
		// если добавить в начало, заменить на -   
		//.insert(glob_files_names.begin(),file_full_name);		
		
		cout<<"Полное имя файла: "<<file_full_name<<endl;
		ofstream f(file_full_name); // создать/пересоздать файл
		int val;
		int jLen = glob_files_volumes[i];
		// для теста - если установили уменьшитель, используем его
		if(glob_files_size_decreaser>1) jLen/=glob_files_size_decreaser;
		
		if(run)
		{				
			while(jLen)
			{
				//сгенерировать случайное число от 0 до 400000
				val = int(double(rand())/RAND_MAX*400000); 
				//cout<<"val : "<<val<<endl;
				f<<val; // сохранить сгенерированный номер в строке
				jLen--; // декременировать счётчик
				if(jLen) f<<endl; // добавить перенос строки, если счётчик не кончился
			}
		}	
	}
}

// сформировать массив, заполнив его значениями строк файла
vector<int> getRowsArray(int i=0)
{
	vector<int> rowsArray;
	ifstream text(glob_files_names[i]);
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
	return rowsArray;
}

// СОЗДАНИЕ ГРАФИКОВ .....................................
// построить сетку для графа
void setGrid(int graph_number)
{
	/*	Установить индикатор вертикали, пересекающейся с маркером.
		Нужен как инструмент для выделения каждой 4-й вертикали 
		(20 вертикальдных линий / 5 маркеров) цветом, как места, 
		где располагается маркер одного из 5-ти используемых файлов.		*/
	int vCount=0; 
	/*	Создать (и далее - установить) левую и правую границы для 
		сеток графов; Пространство между ними будет заполняться 
		вертикалями графа.	*/
	float GridLeftEdge, GridRightEdge, GridTopEdge, GridBottomEdge;  
	/*	Рассчитать значения координат сеток графа. 
		.............................................................
		См. параметры gluOrtho2D, на основе которых рассчитывается
		расположение сеток графов - отступы углов от начала координат:	
		Left:	-50
		Right:	875
		Bottom	-50
		Top		825	
		.................................................................
		ВНИМАНИЕ!
		1. НИЖНЯЯ/ЛЕВАЯ граница графов соответствует началу координат;
		2. МАРКЕРЫ ФАЙЛОВ располагаются ПОД нижними линиями сеток графов.
		См. схему в .xslx-файле.		*/
	/*	установим абсолютные значения углов, которые будут использоваться 
		различными графами, чтобы избежать повторений рассчётов	*/
	float Left1,Left2,Right1,Right2,Top1,Top2,Bottom1,Bottom2;
	/*	левая граница для 1-го и 3-го графов */
	Left1	= 0;
	/*	левая граница для 2-го и 4-го графов - 
		ширина сетки предыдущего графа + визуальный отступ */
	Left2	= globGraphSpace + glob_offset*2;
	/*	правая граница для 1-го и 3-го графов*/
	Right1	= globGraphSpace;
	/*	правая граница для 2-го и 4-го графов - 
		левая граница + ширина */
	Right2	= globSceneWidth + glob_offset;
	/*	верхняя граница графов в первом (нижнем) ряду */
	Top1	= globSceneHeight/globRowsNumber-glob_offset*2; // 
	/*	верхняя граница графов во втором (верхнем) ряду */
	Top2	= globSceneHeight+glob_offset*2;
	/*	нижняя граница графов в первом (нижнем) ряду */
	Bottom1	= 0;
	/*	нижняя граница графов во втором (верхнем) ряду */
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
	
	/*	установить количество вертикалей для каждого отрезка файла как 
		колич. вертикалей одного графа / количество файлов	*/
	int vBunch = glob_grid_value/glob_files; 
	// установить по 20 вертикальных линий для сеток каждого графа
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// установить вертикали	
		// -------------------------------------------------------------------------------
		// выделим цветом каждую 4-ю вертикаль (там, где размещается маркер нового файла):
		if( vCount>0 
			&& vCount%vBunch==0 // если нет остатка от деления, значит - номер вертикали кратен 4
		  ) 
			glColor3f(1.0,0.0,0.5); // установить специфический цвет для вертикали файла
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;
		// линии
		glVertex2f(GridLeftEdge, GridBottomEdge); // 0
		glVertex2f(GridLeftEdge, GridTopEdge);		// 
		GridLeftEdge+=glob_grid_step;
	}
	// установить горизонтали
	// -------------------------------------------------------------------------------
	// назначить цвет
	glColor3f(0.4,0.4,0.4);
	// построить всё
	for ( float offsetBottom  = 0;	// 
				offsetBottom <= globSceneHeight;		// <= 400
				offsetBottom += glob_grid_step )
	{   //cout<<"offsetBottom: "<<offsetBottom<<"\t";
		glVertex2f(grid_left_start,offsetBottom);
		glVertex2f(grid_right_finish,offsetBottom);
	}	//cout<<endl;
}
// построить граф
void Draw()
{
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // включить шаблон пунктирной линии
	glLineWidth (1.0); // указать толщину линий сетки
	glLineStipple(1,0xAAAA); // указать тип пунктирной линии для сетки графа
	glBegin(GL_LINES);	
	/*	построить сетки графов. i определяет номер графа.
		Порядок: 
		1. нижний-левый 
		2. нижний-правый
		3. верхний-левый
		4. верхний-правый
		*/
	for (int i = 1; i <= 4; i++)
		setGrid(i);
	glEnd();
	glDisable(GL_LINE_STIPPLE);

	// построить маркеры файлов
	// на левой сетке
	vector<float> xPosLeft1 = setMarkers();
	// на правой сетке
	setMarkers(true);
	/*	Получим максимальное рассчётное значение шагов для калибровки сетки.
		Для этого выберем наибольшее значение из glob_alg_steps (выбираем 
		среди последних элементов, как естественно наибольших). */
	int biggestNumber = 0;
	int lastIndex = glob_files-1;
	for (int i = 0; i < glob_algos; i++)
	{
		if(glob_alg_steps[i][lastIndex] > biggestNumber)
			biggestNumber = glob_alg_steps[i][lastIndex];
	}
	// откалибровать! 
	float yRatio = globSceneHeight*0.9/float(biggestNumber);
	/*	Далее для построения графа будем уножать все значения 
		массива glob_alg_steps на калибровочное значение yRatio	*/
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		
	// задать цвета для линий анализируемых алгоритмов
	float vColors[glob_algos][3]={
			{0.0,0.0,1.0},
			{1.0,0.0,0.0},
			{1.0,0.0,1.0},
			{1.0,0.5,0.0},
			{0.0,1.0,0.0}
	};
	// построить все 4 графа:
	for ( int i = 0, 
			  index_algo = 0,	// индекс алгоритма в vColors - нужен для выбора цвета построения кривой анализа текущего алгоритма
			  grphx = globColsNumber*globRowsNumber; // 4
		  i < grphx; 
		  i++
		)
	{
		//cout<<endl<<"algorithm #: "<<index_algo+1<<";\nColors: "<<vColors[index_algo][0]<<","<<vColors[index_algo][1]<<","<<vColors[index_algo][2]<<endl;
		if(i==grphx/2) 
			index_algo = 0; // сбросить счётчик алгоритмов после построения графов для сортировки
		
		// установить цвет для
		glColor3f(	vColors[index_algo][0], // R
					vColors[index_algo][1], // G
					vColors[index_algo][2]  // B
				 );
		
		for (int index_file = 0; index_file < glob_files; index_file++)
		{
			if(index_file>1) 
				glVertex2d( xPosLeft1[index_file-1], 
							glob_alg_steps[index_algo][index_file-1]*yRatio);
			
			glVertex2d( /*	позиция текущего маркера, символизирующего
						один из обрабатываемых сгенерированных файлов.
						Также устанавливает помеченной цветом вертикальной
						осли графа.	*/
						xPosLeft1[index_file],
						/*	откалиброванное значение количества шагов, 
						выполненных программой при сортировке файла
						текущим алгоритмом. */
						glob_alg_steps[index_algo][index_file]*yRatio
					  );
			
			cout<<"x: "<<xPosLeft1[index_file]<<", y: "<<glob_alg_steps[index_algo][index_file]*yRatio<<endl;
		}
		index_algo++;
	}
	glEnd();
	glFlush();
}
// инициализировать процесс
void Initialize()
{
	glClearColor(1.0,1.0,1.0,1.0);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	// сетка - left-bottom / right-top
	// построить ортографическую проекцию
	gluOrtho2D(-glob_offset*2,					// -50	левый, x	
				globSceneWidth+glob_offset*3,	// 875	правый, x	
			   -glob_offset*2,					// -50	нижний, y	
				globSceneHeight+glob_offset		// 825	верхний, y	
			  ); 
}
// обработать события клавиатуры
void Keyboard(unsigned char key, int x, int y)
{
	switch(key) // см. справочник клавиатурных кодов ASCII здесь: http://www.theasciicode.com.ar/
	{
		// Закрыть окно по нажатию кл. "Пробел":
		case 32: exit(0);
			break;
	}
	if(key!=32) glutPostRedisplay(); // перерисовать окно  
}
//
int _tmain(int argc, char** argv)
{
	/*	Сгенерировать/перезаписать файлы с набором случайных чисел.
		--------------------------------------------------
	ВНИМАНИЕ! 
	В тестовом режиме целесооборазно уменьшить размер 
	генерируемых файлов. Для этого достаточно указать
	значение пер. glob_files_size_decreaser,  
	являющееся делителем для определяющих его значений 
	элементов массива glob_files_volumes в файле vars.h. */
	makeFiles();
	// отсортировать содержание файлов
	sortData(); 
	bool run = true;
	if(run)
	{
		// инициализация
		glutInit(&argc, argv); 
		// 3 нижележащие функции можно располагать в любом порядке
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
		glutInitWindowSize(globSceneWidth,globSceneHeight);
		glutInitWindowPosition(450,100);
		glutCreateWindow("Graph");
		// регистрация
		glutDisplayFunc(Draw);
		glutKeyboardFunc(Keyboard);
		Initialize();
		glutMainLoop();
	}	
	return 0;
}