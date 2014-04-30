/* fitness function*/
int F(int i)
{
  int fitness = 0;
  /*	вычисление значения fitness */ 
  return fitness;
}
/* элитная селекция 

FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
  for i = m to 0 do
    for j = 0 to m do
      if F(arrPopulation[j]) < F(arrPopulation[j + 1]) then
        Temp = arrPopulation[j];
        arrPopulation[j] = arrPopulation[j + 1];
        arrPopulation[j + 1] = Temp;
      j = j + 1;
    i = i - 1;
    for j = 0 to n do
      arrPopulationN[j] = arrPopulation[j];
}*/
void elite_selection(int arrPopulation[/*m*/], int m, int n)
{
	int Temp = 0;
	int i = m;
	while (i)
	{
		for (size_t j = 0; j < m; j++)
		{
			if (F(arrPopulation[j])<F(arrPopulation[j+1]))
			{
				Temp = arrPopulation[j];
			}
		}
	}
}
/*  Турнирная селекция
FunkSelection(arrPopulation[m], n)
{
  do
    TempCol = random(m);
    if TempCol = m OR TemCol = 0 then
      TempCol = m/2;
  while n > TempCol
  for i =0 to TempCol do
    arrTempMsv[i] = arrPorulation[random(m)]
  Temp = 0;
  for i = m to 0 do
    for j = 0 to m do
      if F(arrTempMsv[j])<F(arrTempMsv[j+1]) then
        Temp = arrTempMsv[j];
        arrTempMsv[j] = arrTempMsv[j+1];
        arrTempMsv[j+1] = Temp;
      j = j+1;
    i = i-1;
  for j = 0 to n do
    arrPopulation[j] = arrTempMsv[j];
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/

/*  
FunkSelection(arrPopulation[m], n)
{
  Temp = 0;
}
*/