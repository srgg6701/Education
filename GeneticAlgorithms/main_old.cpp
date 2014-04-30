//	этапы выполнения ГА
/*
1.	выбор способа представления решения;
2.	разработка операторов случайных изменений;
3.	определение способов «выживания» решений;
4.	создание начальной популяции альтернативных решений.
*/
//	псевдокод ГА

//НАЧАЛО 
/*	
	* Создать начальную популяцию
	* Оценить приспособленность каждой особи

	останов : = FALSE

	ПОКА НЕ останов ВЫПОЛНЯТЬ

	НАЧАЛО // создать популяцию нового поколения

		ПОВТОРИТЬ (размер_популяции / 2) РАЗ */
/*		НАЧАЛО // цикл воспроизводства

			*	Выбрать две особи с высокой приспособленностью из предыдущего 
				поколения для скрещивания
			*	Скрестить выбранных особей и получить двух потомков
			*	Оценить приспособленности потомков
			*	Поместить потомков в новое поколение

		КОНЕЦ	*/
/*		
		ЕСЛИ популяция сошлась ТО останов : = TRUE

	КОНЕЦ	*/ 
//КОНЕЦ	

#include <iostream>
#include <ctime>
using namespace std;

void main1()
{
	setlocale(LC_ALL, "Russian");

	// определиться с параметрами начальной популяции:
	int const cntOrg	= 8,	// количество особей
			  cntGen	= 9; // размер генома (количество генов)
	// Создать начальную популяцию
	int population[cntOrg][cntGen] = {
		{ 1, 0, 1, 0, 1, 1, 0, 0, 0 },
		{ 0, 0, 0, 0, 1, 1, 1, 1, 1 },
		{ 1, 0, 1, 1, 1, 1, 1, 1, 1 },
		{ 1, 0, 0, 0, 0, 0, 1, 0, 0 },
		{ 1, 0, 1, 0, 1, 1, 1, 0, 1 },
		{ 0, 0, 0, 1, 0, 0, 1, 0, 1 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 0 },
		{ 1, 0, 1, 0, 1, 1, 1, 1, 1 }
	};

	// набор сумм геномов популяции
	int orgGenomSum[cntOrg];
	
	// Оценить приспособленность каждой особи
	for (int i = 0; i<cntOrg; i++)
	{
		orgGenomSum[i] = 0;
		for (int j = 0; j<cntGen; j++)
		{
			orgGenomSum[i]+= population[i][j];
		}
		cout<<"Особь["<<i<<"], показатель приспособленности: "<< orgGenomSum[i]<<endl;
	}

	// Создать вторую популяцию
	/*	Здесь неправильная методика - не нужно копировать массив значений геномов,
		нужно создать вторую популяцию (будет выполнено потом). */
	int arrayRowSummCopy[cntOrg];

	for (int i = 0; i<cntOrg; i++)
	{
		arrayRowSummCopy[i] = orgGenomSum[i];
	}
	
	int dif, max, indexMaxElement;

	for (int i = 0; i<cntOrg; i++)
	{
		dif = orgGenomSum[i] - orgGenomSum[i - 1];
		if (dif>0)
		{
			max = orgGenomSum[i];
		}
		else
		{
			if (dif<0)
			{
				orgGenomSum[i] = orgGenomSum[i - 1];
				max = orgGenomSum[i - 1];
			}
		}
	}
	cout << "max= " << max << endl;
	cout << "Max element has the index: " << endl;
	for (int i = 0; i<cntOrg; i++)
	{
		if (arrayRowSummCopy[i] == max)
		{
			indexMaxElement = i;
			cout << indexMaxElement << " " << endl;
		}
	}
	//cout <<". We must to tern max element into 0 and found an element which is on the second place in decreasing order."<<endl;
	/* Мы нашли максимальный элемент в массиве arrayRowSummCopy, но он только один.
	Каждый из элементов равен количеству единиц какой-то из строк массива population.
	Нам нужно найти 2 самых больших элемента массива arrayRowSummCopy с их индексами, и,
	таким образом, определить строки массива population, содержащие большее количество единиц.
	Для этого в массиве arrayRowSummCopy нужно обнулить найденный максимальный элемент, а затем
	повторить все процедуры поиска следующего по величине максимального элемента.*/
	/*Создадим массив arrayRowSummCopy2 и скопируем туда все значения из массива arrayRowSummCopy,
	кроме максимального. На его месте будет стоять 0. После создания этого массива проделаем
	процедуры поиска его максимального элемента*/
	int max2, indexMaxElement2;
	int arrayRowSummCopy2[cntOrg];
	for (int i = 0; i<cntOrg; i++)
	{

		arrayRowSummCopy2[i] = arrayRowSummCopy[i];
		if (i == 2)
		{
			arrayRowSummCopy2[i] = 0;
		}
	}
	for (int i = 0; i<cntOrg; i++)
	{
		dif = arrayRowSummCopy2[i] - arrayRowSummCopy2[i - 1];
		if (dif>0)
		{
			max2 = arrayRowSummCopy2[i];
		}
		else
		{
			if (dif<0)
			{
				arrayRowSummCopy2[i] = arrayRowSummCopy2[i - 1];
				max2 = arrayRowSummCopy2[i - 1];
			}
		}
	}
	cout << "max2= " << max2 << endl;
	for (int i = 0; i<cntOrg; i++)
	{
		if (arrayRowSummCopy2[i] == max2)
		{
			indexMaxElement2 = i;
			cout << "The second max element has the index: " << indexMaxElement2 << endl;
		}
	}
	/*Итого, найдены 2 самых приспособленных особи в массиве population.
	Это особи с индексами 2 и 7. Создадим еще один массив, и скопируем туда этих 2-х особей.
	Они будут представлять собой содержимое этого нового массива.
	*/
	cout << "The best individuals: { " << endl;
	int TheBestIndividuals[2][cntGen];
	// Внесение 1-й особи:
	for (int i = 0; i<indexMaxElement2; i++)
	{
		if (i == indexMaxElement)
		{
			for (int j = 0; j<cntGen; j++)
			{
				TheBestIndividuals[0][j] = population[2][j];
				cout << TheBestIndividuals[0][j] << " " << endl;
			}
		}
	}

	// Внесение 2-й особи:		
	for (int i = 0; i<cntGen; i++)
	{
		TheBestIndividuals[1][i] = population[7][i];
		cout << TheBestIndividuals[1][i] << " " << endl;
	}

	cout << "}" << endl;
	int rand_max = cntGen;
	srand(time(0));
	cout << "random number=" << rand() % 9 << endl;
	int const a = 5;
	int kid[cntGen];
	int kid2[cntGen];
	int i = 0;
	cout << " kid 1 = " << endl;
	cout << " kid 2 = " << endl;
	while (i<a)
	{
		kid[i] = TheBestIndividuals[0][i];
		kid2[i] = TheBestIndividuals[1][i];
		i++;
		cout << kid[i] << endl;
		cout << kid2[i] << endl;
	}
	while (i<cntGen)
	{
		kid[i] = TheBestIndividuals[1][i];
		kid2[i] = TheBestIndividuals[0][i];
		i++;
		cout << kid[i] << endl;
		cout << kid2[i] << endl;
	}
}
