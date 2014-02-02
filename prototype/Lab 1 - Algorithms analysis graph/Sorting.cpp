#include "stdafx.h"
#include "sorting.h"
#include <vector>
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
	glob_alg_steps[0][i]=steps;
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
	glob_alg_steps[1][i]=steps;
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
	glob_alg_steps[2][i]+=steps;
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
	glob_alg_steps[2][i]+=steps;
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
				для сохранения данных в массиве glob_alg_steps каждая 
				использует статический индекс своего алгоритма:
				glob_alg_steps[индекс_алгоритма][индекс_файла] */
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
		for (int i = 0; i < glob_files_names.size(); i++)
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