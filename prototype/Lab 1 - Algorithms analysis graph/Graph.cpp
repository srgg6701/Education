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
#include "markers.h"
using namespace std;

// контейнер для сохранения имён сгенерированных файлов
vector<string>glob_files_names;
/*	определяет, показывать ли детали выполнения сортировки;
	может быть присвоено true внутри каждой соответствующей
	функции.	*/
bool show_details=false;

//-----------------------------------------------------------
//-----------------------------------------------------------
// ФУНКЦИИ СОРТИРОВКИ ДАННЫХ:
// Пузырьковая сортировка....................................
void sortBubbling(int);
// Сортировка вставками......................................
void sortByInserts(int);
// Быстрая сортировка........................................
void sortQuick(int);
	/*	рекурсивная функция-обёртка, определяющая, нужно ли
		переставлять элементы массива.	*/
	void quickSort(vector<int>&, int, int, int);
	/*	вызывает функцию (swap()) перестановки элементов местами
		и возвращает новую опорную точку.	*/
	 int pivot(vector<int>&, int, int, int);
	/*	переставляет местами элементы массива и сохраняет новые 
		значения по ссылкам.	*/
	void swap(int&, int&);
//-----------------------------------------------------------
// Сортировка данных:
void sortData();
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
			// glob_alg_analysis_steps[glob_algos][file_index] - индекс алгоритма, файл
			cout<<"Файл "<<file_index+1<<": "<<glob_alg_analysis_steps[algo_index][file_index]<<endl;
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
		float LeftEdge = (copier)? globGraphSpace+globDoubleOffset : 0;	// 400 : 0
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

float getGridTops(float Top=0.0)
{
	float currentTop = globGraphSpace;
	if (Top) currentTop+=globDoubleOffset+Top;
	return currentTop;
}
// СОЗДАНИЕ ГРАФИКОВ .....................................
// построить сетку для графа
void setGrid(int graph_number)
{
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
		ширина сетки предыдущего графа + двойной визуальный отступ */
	Left2	= globGraphSpace + globDoubleOffset;
	/*	правая граница для 1-го и 3-го графов - 
		ширина сетки графа */
	Right1	= globGraphSpace;
	/*	правая граница для 2-го и 4-го графов - 
		левая граница + ширина */
	Right2	= Left2 + globGraphSpace;
	/*	верхняя граница графов в первом (нижнем) ряду */
	Top1	= getGridTops();//globGraphSpace; // 
	/*	верхняя граница графов во втором (верхнем) ряду */
	Top2	= getGridTops(Top1);//Top1+globDoubleOffset+globGraphSpace;
	/*	нижняя граница графов в первом (нижнем) ряду */
	Bottom1	= 0;
	/*	нижняя граница графов во втором (верхнем) ряду */
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

	// назначить x-координаты для горизонтальных линий, генерируемых далее:
	// ЛЕВАЯ
	const float grid_left_start		= GridLeftEdge;
	// ПРАВАЯ
	const float grid_right_finish	= GridRightEdge;
	
	bool test=true;
	//if (test) cout<<endl<<"GRAPH "<<graph_number<<endl<<"........................."<<endl;
	
	/*	Установить индикатор вертикали, пересекающейся с маркером.
		Нужен как инструмент для выделения каждой 4-й вертикали 
		(20 вертикальдных линий / 5 маркеров) цветом, как места, 
		где располагается маркер одного из 5-ти используемых файлов.		*/
	int vCount=0; 
	/*	установить количество вертикалей для каждого отрезка файла как 
		колич. вертикалей одного графа / количество файлов	*/
	int vBunch = glob_grid_value/glob_files;
	//if (test) cout<<"Set verticals:"<<endl;
	// установить по 20 ВЕРТИКАЛЬНЫХ линий для сеток каждого графа
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
		//if (test) cout<<"\t"<<vCount<<": "<<"bottom(x,y) = "<<GridLeftEdge<<", "<<GridBottomEdge<<"\ttop(x,y) = "<<GridLeftEdge<<", "<<GridTopEdge<<endl;
		// линии
		glVertex2f(GridLeftEdge, GridBottomEdge); // 0
		glVertex2f(GridLeftEdge, GridTopEdge);		// 
		GridLeftEdge+=glob_grid_step;
	}
	// установить ГОРИЗОНТАЛИ
	// -------------------------------------------------------------------------------
	// назначить цвет
	glColor3f(0.4,0.4,0.4);
	//if (test) int cnt=0; cout<<"Set horizontals:"<<endl;
	// построить всё
	for ( /* установить начальное нижнее значение горизонтали
			 как эквивалентное нижней точки вертикалей сетки */
		  float offsetBottom  = GridBottomEdge;
				/* значение y-точки коризонтали будет увеличиваться
				   до значения верхней границы сетки текущего графа */
				offsetBottom <= GridTopEdge;
				/* увеличиваем на установленный ранее шаг сетки */
				offsetBottom += glob_grid_step  //
		)
	{   //if (test) cnt++;cout<<"\t"<<cnt<<": "<<"left(x,y) = "<<grid_left_start<<", "<<offsetBottom<<"\tright(x,y) = "<<grid_right_finish<<", "<<offsetBottom<<endl;
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
	// определить режим тестирования (для вывода сообщений)
	bool test=true;
	
	// построить маркеры файлов
	// на левой сетке
	vector<float> xPosLeft1 = setMarkers();
	// на правой сетке
	setMarkers(true);
	
	glEnable(GL_LINE_SMOOTH);
	glHint(GL_LINE_SMOOTH_HINT,GL_NICEST);
	glLineWidth(1.0);
	glBegin(GL_LINES);
		
	/*	Получим максимальное рассчётное значение шагов для калибровки сетки.
		Для этого выберем наибольшее полученное значение (колич. операций/время
		сортировки), ранее сохранённое в массиве glob_alg_analysis_steps (выбираем среди 
		последних элементов вложенных массивов, как естественно наибольших) */
	int biggestNumber;
	/* индекс последнего значения текущего вложенного массива (4)	*/ 
	int lastIndex = glob_files-1;
	/* множитель для установки максимально верхней позиции точки графа;
	   рассчитывается как соотношение максимального значения, полученного
	   в результате анализа текущего алгоритма (сохраняется в массиве glob_alg_analysis_steps)
	   и y-позиции верхней границы сетки графа.	*/
	float yRatio;
	/* базовое значение верхней точки для рассчёта предыдущего показателя - различно для 
	   графов 1-2 и 3-4. В первом случае используются координаты сеток графов первого ряда,
	   во втором, соответственно, - второго. */
	float yRatioCurrentTopBase = globGraphSpace*0.9;
	
	// построить все 4 графа:
	for ( int i = 0, 
			  index_algo = 0,	// индекс алгоритма в globalAlgosColors - нужен для выбора цвета построения кривой анализа текущего алгоритма
			  // получим количество графов, как произведение колич. строк и столбцов сцены
			  grphx = globColsNumber*globRowsNumber; // 4
		  // цикл отрабатывает для каждого из графов
		  i < grphx; 
		  i++
		)
	{
		/* извлечь максимальное значение, полученное в результате анализа текущего алгоритма
		   (см. массив glob_alg_analysis_steps)*/
		biggestNumber = 0; // сбросить предыдущее
		// получить текущее
		for (int b = 0; b < glob_algos; b++)
		{
			if(glob_alg_analysis_steps[b][lastIndex] > biggestNumber)
				biggestNumber = glob_alg_analysis_steps[b][lastIndex];
		}
		/*  если начался второй ряд графов, скорректируем показатель верхней точки 
			для калибровки точек графа, добавив двойнойй оступ и высоту графа
			(см. схему в .xslx-файле)	*/
		if(i==globRowsNumber-1) yRatioCurrentTopBase += globGraphSpace + globDoubleOffset; 
		// откалибровать! 
		if(!biggestNumber) biggestNumber=1; // на случай, если он почему-то оказался нулём.
		yRatio = yRatioCurrentTopBase/float(biggestNumber);
		/*	Далее для построения графа будем уножать все значения 
			массива glob_alg_analysis_steps на калибровочное значение yRatio	*/
		//cout<<endl<<"algorithm #: "<<index_algo+1<<";\nColors: "<<globalAlgosColors[index_algo][0]<<","<<globalAlgosColors[index_algo][1]<<","<<globalAlgosColors[index_algo][2]<<endl;	
		// установить цвет для
		glColor3f(	globalAlgosColors[index_algo][0], // R
					globalAlgosColors[index_algo][1], // G
					globalAlgosColors[index_algo][2]  // B
				 );
		
		for (int index_file = 0; index_file < glob_files; index_file++)
		{
			if(index_file>1) 
				glVertex2d( xPosLeft1[index_file-1], 
							glob_alg_analysis_steps[index_algo][index_file-1]*yRatio);
			
			glVertex2d( /*	позиция текущего маркера, символизирующего
						один из обрабатываемых сгенерированных файлов.
						Также устанавливает помеченной цветом вертикальной
						осли графа.	*/
						xPosLeft1[index_file],
						/*	откалиброванное значение количества шагов, 
						выполненных программой при сортировке файла
						текущим алгоритмом. */
						glob_alg_analysis_steps[index_algo][index_file]*yRatio
					  );
			
			//cout<<"x: "<<xPosLeft1[index_file]<<", y: "<<glob_alg_analysis_steps[index_algo][index_file]*yRatio<<endl;
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
	gluOrtho2D(-globDoubleOffset,					// -50	левый, x	
				/* установить правый край проекции как
				   ширина левого графа +
				   промежуток между графами +
				   визуальный отступ справа от правого графа */
				globSceneWidth+globDoubleOffset+glob_offset,	// 875	= 400 + 50 + 400 + 25 правый, x	
			   -globDoubleOffset,	// -50	нижний, y	
				globSceneHeight		// 875	верхний, y	
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
		/*	рассчитать и установить размер окна (см. установки glOrtho2d())
			50 - отступ влево от начала координат
		*/
		float wSizeX = globDoubleOffset+globSceneWidth+globDoubleOffset+glob_offset;
		float wSizeY = globDoubleOffset+globSceneHeight;
		cout<<"WINDOW size: "<<wSizeX<<" x "<<wSizeY<<endl;
		glutInitWindowSize(wSizeX,wSizeY);
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

// СОРТИРОВКА ............................................
// пузырьковая сортировка
void sortBubbling(int i)
{
	// получить массив строк из файла
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	// установим счётчики шагов и времени:
	int steps=0;
	// шаг 1
	int clipboard;// временная переменная для хранения значения элемента сортируемого массива
	// шаг 2
	/*	the variable that will define the inner loop 
		iterations number; (see the 'while' loop) we 
		need it because constants can't be changed! */
	int lmt;
	// шаг 3
	/*	we need this variable just to avoid keeping to repeat an expression 
		like innerCounter+1	*/
	int nextIndex;	
	/*	it will be used as an element's index to compare the array's elements 
		within an inner loop */
	// шаг 4
	int innerCounter;
		steps+=4;
	// не будем считать вход в цикл шагом
	// пройтись по массиву строк
	for (int cnt=0; cnt<limit; cnt++)
	{
		// шаг 1
		lmt = limit-cnt;
		// шаг 2
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
			// шаг 1
			nextIndex = innerCounter+1;
			// шаг 2
				steps+=2;
			if(nmbrs[innerCounter]>nmbrs[nextIndex]) // 5 < 3
			{
				/*	cout<< "\nA permutation is needed!\ncurrent elemen's value: " 
						<< nmbrs[innerCounter] << "\nnext element's value: "
						<< nmbrs[nextIndex]; */
				// шаг 1
				// store the array's element value
				clipboard = nmbrs[nextIndex];
				/*	cout<< "\nclipboard = nmbrs["<<innerCounter<<"+1] = "
						<< clipboard<<"\n"; */
				/*	here we lost an original value in the array
					but it was stored in the clipboard variable earlier */
				/*	cout<< "\nnmbrs["<<innerCounter<<"+1] = nmbrs["<<innerCounter<<"] = "
						<< nmbrs[innerCounter]<<"\n"; */
				// шаг 2
				nmbrs[nextIndex] = nmbrs[innerCounter]; // 3 -> 5 
				/*	take out the value stored in the clipboard earlier 
					and assign it to the current array's element */
				// шаг 3
				nmbrs[innerCounter] = clipboard;
					steps+=3;
				/*	cout<< "\nnmbrs["<<innerCounter<<"] = clipboard = "
						<< clipboard<<"\n"; */
			}
			// шаг 1,2
			lmt--;
			innerCounter++;
				steps+=2;
		}
	}
	// сохранить в массиве колич. шагов для каждого файла
	glob_alg_analysis_steps[0][i]=steps;
	if (show_details) showSorting(nmbrs,limit);
}
// сортировка вставками
void sortByInserts(int i)
{
	// получить массив строк из файла
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	// установим счётчики шагов и времени:
		int steps=0;
	// шаг 1
	int clipboard; // временная переменная для хранения значения элемента сортируемого массива
	// шаг 2
	int prev_index; // индекс предыдущего элемента
		steps+=2;
	for (int cnt = 1; cnt < limit; cnt++)
    {
        // шаг 1
		clipboard = nmbrs[cnt]; // инициализируем временную переменную текущим значением элемента массива
        // шаг 2
		prev_index = cnt-1; // запоминаем индекс предыдущего элемента массива
        // шаг 3 - считаем условие входа в цикл
			steps+=3;
		while(prev_index >= 0 && nmbrs[prev_index] > clipboard) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
        {
            // шаг 1
			nmbrs[prev_index + 1] = nmbrs[prev_index]; // перестановка элементов массива
            // шаг 2
			nmbrs[prev_index] = clipboard;
			// шаг 3
            prev_index--;
				steps+=3;
        }
    }
	// сохранить в массиве колич. шагов для каждого файла
	glob_alg_analysis_steps[1][i]=steps;
	if (show_details) showSorting(nmbrs,limit);
}
// быстрая сортировка
void sortQuick(int i)
{
	/* получить массив строк из файла
	ВНИМАНИЕ!	В данном случае создаём НЕ массив,
				как таковой, а ссылку на полученные данные,
				т.к. во вложенной функции сортировки работаем
				именно со ссылками на элементы массива	*/
	vector<int> &nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	quickSort(nmbrs, 0, nmbrs.size()-1, i);
	if (show_details) showSorting(nmbrs,limit);
}
// реализация механизма быстрой сортировки
void quickSort(vector<int> &nmbrs, int first, int last, int i)
{
	// установим счётчики шагов и времени:
		int steps=0;
	// шаг 1
	int pivotElement;
	// шаг 2 (условие)
		steps+=2;
    if(first < last)
    {   
        // шаг 1
		pivotElement = pivot(nmbrs, first, last, i); //cout<<"pivotElement = "<<pivotElement<<endl;
        // шаг 2,3
		quickSort(nmbrs, first, pivotElement-1, i);
        quickSort(nmbrs, pivotElement+1, last, i);
		steps+=3;
    }
	// сохранить в массиве колич. шагов для каждого файла
	glob_alg_analysis_steps[2][i]+=steps;
}
// возвращает опорную точку сортировки
int pivot( vector<int> &nmbrs,		// массив значений
		   int first,   // индекс первого элемента массива
		   int last,	// индекс последнего элемента массива
		   int i		// индекс файла для счётчика
		 ) 
{
    // установим счётчики шагов и времени:
		int steps=0;
	// шаг 1
	int  p = first; // "опорная точка" - индекс первого элемента массива
	// шаг 2
	int pivotElement = nmbrs[first];
	/*	шаг 3 - посчитаем условие входа в цикл, т.к. данный шаг 
		специфичен для этого алгоритма */
		steps+=3;
	for(int cnt = first+1 ; cnt <= last ; cnt++)
    {
        // шаг 1
			steps+=1;
		/* Для изменения порядка сортировки заменить "<=" на ">" */
        if(nmbrs[cnt] <= pivotElement)
        {   //cout<<"\tswap "<<nmbrs[cnt]<<" <> "<<pivotElement<<endl;
            // шаг 1
			p++;
			// шаги 2-4 (внутри swap()), 5 - вызов функции
            swap(nmbrs[cnt], nmbrs[p]);			
				steps+=5;
        }
    }
	// шаг 1-3
    swap(nmbrs[p], nmbrs[first]);
		steps+=3;
	// сохранить в массиве колич. шагов для каждого файла
	glob_alg_analysis_steps[2][i]+=steps;
    return p; // возвращает опорную точку
}
// переключает параметры сортировки
void swap( int& a,	// первый параметр 
		   int& b	// последний параметр
		 )
{
    int temp = a;
    a = b;
    b = temp;
}
//-----------------------------------------------------------
// отсортировать всеми указанными способами
void sortData()
{
	setlocale(LC_ALL, "Russian");
	// выбор юзера:
	int choice;
		
	cout<<"Сделайте выбор:"
	<<endl<<"Показать процесс сортировки - введите 8."
	<<endl<<"Перейти к результатам анализа алгоритмов - введите 9."
	<<endl<<"Выход - введите 0."<<endl
	<<"......................................................"<<endl;
	cin>>choice;
	if(choice==9) 
	{
		for (int i = 0; i < glob_algos; i++)
		{
			/*  порядок вызова функций не имеет значения, поскольку 
				для сохранения данных в массиве glob_alg_analysis_steps каждая 
				использует статический индекс своего алгоритма:
				glob_alg_analysis_steps[индекс_алгоритма][индекс_файла] */
			sortBubbling(i);
			sortByInserts(i);
			sortQuick(i);
		}
		// показать статистику
		showResults();
	}
	if(choice==0) exit(0);
	if(choice==8)
	{
		for (unsigned int i = 0; i < glob_files_names.size(); i++)
		{
			cout<<"Итерация "<<i+1<<". Чтобы продолжить, введите "<<i+1
				<<endl<<"Чтобы выйти - введите 0."<<endl
				<<"......................................................"<<endl;
			cin>>choice;
			if(choice==0) exit(0);
			if(choice==(i+1))
			{
				if(i) cout<<endl;
				cout<<"Имя файла: "<<glob_files_names[i]<<endl;
				cout<<endl<<"ПУЗЫРЬКОВАЯ СОРТИРОВКА"<<endl<<"-----------------------"<<endl;
				sortBubbling(i);	// пузырьковая сортировка
				cout<<endl<<"СОРТИРОВКА ВСТАВКАМИ"<<endl<<"-----------------------"<<endl;
				sortByInserts(i);	// сортировка вставками
				cout<<endl<<"БЫСТРАЯ СОРТИРОВКА"<<endl<<"-----------------------"<<endl;
				sortQuick(i);	// быстрая сортировка
			}
			else break;
		}
		cout<<"Перейти к результатам анализа алгоритмов - введите 9."
		<<endl<<"Выход - введите 0."<<endl
		<<"......................................................"<<endl;
		if(choice==9) showResults();
		if(choice==0) exit(0);
	}
}
/*	Материалы:
	- Оценка эффективности алгорима по времени: http://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC#.D0.92.D1.80.D0.B5.D0.BC.D1.8F_.D1.80.D0.B0.D0.B1.D0.BE.D1.82.D1.8B
	- vector: http://ru.cppreference.com/w/cpp/container/vector
	*/