//	����� ���������� ��
/*
1.	����� ������� ������������� �������;
2.	���������� ���������� ��������� ���������;
3.	����������� �������� ����������� �������;
4.	�������� ��������� ��������� �������������� �������.
*/
//	��������� ��

//������ 
/*	
	* ������� ��������� ���������
	* ������� ����������������� ������ �����

	������� : = FALSE

	���� �� ������� ���������

	������ // ������� ��������� ������ ���������

		��������� (������_��������� / 2) ��� */
/*		������ // ���� ���������������

			*	������� ��� ����� � ������� ������������������ �� ����������� 
				��������� ��� �����������
			*	��������� ��������� ������ � �������� ���� ��������
			*	������� ����������������� ��������
			*	��������� �������� � ����� ���������

		�����	*/
/*		
		���� ��������� ������� �� ������� : = TRUE

	�����	*/ 
//�����	

#include <iostream>
#include <ctime>
using namespace std;

void main1()
{
	setlocale(LC_ALL, "Russian");

	// ������������ � ����������� ��������� ���������:
	int const cntOrg	= 8,	// ���������� ������
			  cntGen	= 9; // ������ ������ (���������� �����)
	// ������� ��������� ���������
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

	// ����� ���� ������� ���������
	int orgGenomSum[cntOrg];
	
	// ������� ����������������� ������ �����
	for (int i = 0; i<cntOrg; i++)
	{
		orgGenomSum[i] = 0;
		for (int j = 0; j<cntGen; j++)
		{
			orgGenomSum[i]+= population[i][j];
		}
		cout<<"�����["<<i<<"], ���������� �����������������: "<< orgGenomSum[i]<<endl;
	}

	// ������� ������ ���������
	/*	����� ������������ �������� - �� ����� ���������� ������ �������� �������,
		����� ������� ������ ��������� (����� ��������� �����). */
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
	/* �� ����� ������������ ������� � ������� arrayRowSummCopy, �� �� ������ ����.
	������ �� ��������� ����� ���������� ������ �����-�� �� ����� ������� population.
	��� ����� ����� 2 ����� ������� �������� ������� arrayRowSummCopy � �� ���������, �,
	����� �������, ���������� ������ ������� population, ���������� ������� ���������� ������.
	��� ����� � ������� arrayRowSummCopy ����� �������� ��������� ������������ �������, � �����
	��������� ��� ��������� ������ ���������� �� �������� ������������� ��������.*/
	/*�������� ������ arrayRowSummCopy2 � ��������� ���� ��� �������� �� ������� arrayRowSummCopy,
	����� �������������. �� ��� ����� ����� ������ 0. ����� �������� ����� ������� ���������
	��������� ������ ��� ������������� ��������*/
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
	/*�����, ������� 2 ����� ��������������� ����� � ������� population.
	��� ����� � ��������� 2 � 7. �������� ��� ���� ������, � ��������� ���� ���� 2-� ������.
	��� ����� ������������ ����� ���������� ����� ������ �������.
	*/
	cout << "The best individuals: { " << endl;
	int TheBestIndividuals[2][cntGen];
	// �������� 1-� �����:
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

	// �������� 2-� �����:		
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
