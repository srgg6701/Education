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
#include "vars.h"
#include "markers.h"
using namespace std;

// контейнер для сохранения имён сгенерированных файлов
vector<string>glob_files_names;

//-----------------------------------------------------------
// ФУНКЦИИ СОРТИРОВКИ ДАННЫХ:
// Пузырьковая сортировка....................................
void sortBubbling(vector<int> *,int);
// Сортировка вставками......................................
void sortByInserts();
// Быстрая сортировка........................................
void sortQuick();
	/*	рекурсивная функция-обёртка, определяющая, нужно ли
		переставлять элементы массива.	*/
	void quickSort(vector<int>&, int, int);
	/*	вызывает функцию (swap()) перестановки элементов местами
		и возвращает новую опорную точку.	*/
	 int pivot(vector<int>&, int, int);
	/*	переставляет местами элементы массива и сохраняет новые 
		значения по ссылкам.	*/
	void swap(int&, int&);
//-----------------------------------------------------------
// Сортировка данных:
void sortData();
//-----------------------------------------------------------

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
void setMarkers(bool copier=false)
{
	// создать внутреннюю 2-D матрицу для построения цифр от 1 до 5. 
	// См. схему здесь: http://www.canstockphoto.com/pixel-art-globNumbers-and-mathematical-signs-12800261.html
	// Нарисовать маркеры файлов
	glBegin(GL_QUADS);
		int arrayNumbersRow=0;
		float LeftEdge = (copier)? globSceneWidthHalf+glob_offset*2 : 0;	// 400 : 0
		int files_count=glob_files_names.size();
		for (int i = 1; i <= files_count; i++)
		{	
			// установить левый отступ маркера
			float currentX = LeftEdge +		// левый край сетки (0-400)
                             globSceneWidthHalf/files_count	// 400/5 = 80 длина отрезка для одного (всего 5, по количеству файлов) маркера
							 *i				// общая текущая длина отрезков
							 -15;			// смещение маркера влево для визуального центрирования с выделенной вертикалью сетки
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
void setGrid(bool copier=false)
{
	/*	Установить индикатор вертикали, пересекающейся с маркером.
		Нужен как инструмент для выделения каждой 4-й вертикали 
		(20 вертикальдных линий / 5 маркеров) цветом, как места, 
		где располагается маркер одного из 5-ти используемых файлов.		*/
	int vCount=0; 
	/*	Создать (и далее - установить) левую и правую границы для 
		сеток графов; Пространство между ними будет заполняться 
		вертикалями графа.	*/
	float GridLeftEdge, GridRightEdge;  
	/*	Рассчитать значения левой и правой границ сеток графа. 
		Передавайемый параметр copier означает, что строим сетку
		для правого графа. Если параметр не передан, то - для левого. 
		.............................................................
		См. параметры gluOrtho2D, на основе которых рассчитывается
		расположение сеток графов - отступы углов от начала координат:
		левый:	-50, правый: 875, 
		нижний: -50, верхний: 450	*/
	if(copier)
	{
		/*	Половина рабочего пространства окна 
			+ пространство для создания визуального отступа */
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
	// установить по 20 вертикальных линий для сеток каждого графа
	while(GridLeftEdge<=grid_right_finish)
	{	// cout<<"GridLeftEdge: "<<GridLeftEdge<<endl;
		// установить вертикали	
		// выделим цветом каждую 4-ю вертикаль (там, где размещается маркер нового файла):
		if( vCount>0 && vCount%4==0 ) 
			glColor3f(1.0,0.0,0.5);
		else
			glColor3f(0.4,0.4,0.4);
		vCount++;
		// линии
		glVertex2f(GridLeftEdge, 0); // 
		glVertex2f(GridLeftEdge, globSceneHeight);		// 
		GridLeftEdge+=glob_grid_step;
	}
	glColor3f(0.4,0.4,0.4);
	// установить горизонтали
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
	sortData(); // отсортировать содержание файлов
	glClear(GL_COLOR_BUFFER_BIT);
	glEnable(GL_LINE_STIPPLE); // включить шаблон пунктирной линии
	glLineWidth (1.0); // указать толщину линий сетки
	glLineStipple(1,0xAAAA); // указать тип пунктирной линии для сетки графа
	glBegin(GL_LINES);
		// построить первую (левую) сетку
		setGrid();
		// построить вторую (правую) сетку
		setGrid(true);
	glEnd();
	glDisable(GL_LINE_STIPPLE);
		// построить маркеры файлов
		// на левой сетке
		setMarkers();
		// на правой сетке
		setMarkers(true);
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
	gluOrtho2D(-glob_offset*2,		// -50	левый, x	
				globSceneWidth+glob_offset*3,	// 875	правый, x	
			   -glob_offset*2,		// -50	нижний, y	
				globSceneHeight+glob_offset		// 450	верхний, y	
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
	bool run = false;
	if(run)
	{
		// инициализация
		glutInit(&argc, argv); 
		// 3 нижележащие функции можно располагать в любом порядке
		glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
		glutInitWindowSize(globSceneWidth,globSceneHeight);
		glutInitWindowPosition(450,200);
		glutCreateWindow("Grid");
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
	int clipboard;// временная переменная для хранения значения элемента сортируемого массива
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
	// пройтись по массиву строк
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
// сортировка вставками
void sortByInserts(int i)
{
	// получить массив строк из файла
	vector<int> nmbrs = getRowsArray(i);
	const int limit = nmbrs.size();
	int clipboard; // временная переменная для хранения значения элемента сортируемого массива
	int prev_index; // индекс предыдущего элемента
	for (int current_index = 1; current_index < limit; current_index++)
    {
        clipboard = nmbrs[current_index]; // инициализируем временную переменную текущим значением элемента массива
        prev_index = current_index-1; // запоминаем индекс предыдущего элемента массива
        while(prev_index >= 0 && nmbrs[prev_index] > clipboard) // пока индекс не равен 0 и предыдущий элемент массива больше текущего
        {
            nmbrs[prev_index + 1] = nmbrs[prev_index]; // перестановка элементов массива
            nmbrs[prev_index] = clipboard;
            prev_index--;
        }
    }
	showSorting(nmbrs,limit);
	cout<<endl;
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
	quickSort(nmbrs, 0, nmbrs.size()-1);
	showSorting(nmbrs,limit);
	cout<<endl;
}
// реализация механизма быстрой сортировки
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
// возвращает опорную точку сортировки
int pivot( vector<int> &nmbrs,		// массив значений
		   int first,   // индекс первого элемента массива
		   int last		// индекс последнего элемента массива
		 ) 
{
    int  p = first; // "опорная точка" - индекс первого элемента массива
    int pivotElement = nmbrs[first];
	for(int i = first+1 ; i <= last ; i++)
    {
        /* Для изменения порядка сортировки заменить "<=" на ">" */
        if(nmbrs[i] <= pivotElement)
        {   //cout<<"\tswap "<<nmbrs[i]<<" <> "<<pivotElement<<endl;
            p++;
            swap(nmbrs[i], nmbrs[p]);
        }
    }
 
    swap(nmbrs[p], nmbrs[first]);
 
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
	
	for (int i = 0; i < glob_files_names.size(); i++)
	{
		cout<<"Итерация "<<i+1<<". Если хотите продолжить, введите "<<i+1<<". Выход - 0."<<endl
			<<"......................................................"<<endl;
		int choice;
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
}
/*	Материалы:
	- Оценка эффективности алгорима по времени: http://ru.wikipedia.org/wiki/%D0%90%D0%BB%D0%B3%D0%BE%D1%80%D0%B8%D1%82%D0%BC#.D0.92.D1.80.D0.B5.D0.BC.D1.8F_.D1.80.D0.B0.D0.B1.D0.BE.D1.82.D1.8B
	- vector: http://ru.cppreference.com/w/cpp/container/vector
	*/