#ifndef API_H
#define API_H
/*	����� �����������: 
	* ���������������� ��������� ����� - 
		 - ������ 
		 - ������
	* ��� ����� ��� ������
	* ��������� ���������� ��������
	* ���������� ������������ ���������� ������, ��������� ����������_��������/������_�_����������
	  ������� ����� ��������������� ����������.	*/
// ������ �������� ������������ (�����)
const float globSceneWidth=800.0;
// ���������� ������� (�.�., ������ � ����� ����)
const int globColsNumber = 2;
// ���������� ����� (�.�., ����� � �������)
const int globRowsNumber = 2;

// ������� ������������ ��� ������ �����
const float globGraphSpace=globSceneWidth/float(globColsNumber);
/*	������ ����� ��������������� ����, ����� ����������� �������� 
	������� (glob_offset), ��������������� �����������  */
// ���������� ������������ ����� � ����� �����
const int glob_grid_value = 20;
/*	��� �������� ���� ����� � ������� ����������� ������� ����� ������������� 
	�� ����� ����������������� �������� ������ �������� ������������ � 
	���������� ���������� ��� ������ �����:
	������ �������� ������������ / 2 (���������� ������ � ����� ���� �����) / ���������� ���������� 
	��������� ������� � ���������� ���������� ������� ����������� ����� ������. */
//	��� ����� (� ��������)
const float glob_grid_step = globSceneWidth/globColsNumber/float(glob_grid_value);
//	������� ����������� �������
/*	������������ ���������� - ��� ����� ������ �������� ������������	*/
const float glob_offset = globSceneWidth/32.0;
const float globDoubleOffset = glob_offset*2;
/*	������ �����, ������� �� 0 �� ��� Y 
	(400+50+400+25) */
const float globSceneHeight=globSceneWidth+globDoubleOffset+glob_offset;

/*	����� (�����. �����) ������������ ������ 
	��������! 
	� �������� ������ �������������� ��������� ������ 
	������������ ������. ��� ����� ���������� �������
	�������� ���. glob_files_size_decreaser (��. �����). */
const int glob_files_volumes[]={
	1000, 20000, 100000, 250000, 380000
};
const int glob_algos = 5; // ���������� ����������
const int glob_files = 5; // ���������� ������
/*	���� ������� ��������� ���������� �����, �������� �������� �������
	glob_files_volumes �� ����������� ��������. ���� ����� �������� ���
	������ �������������� ������, ��������� �������� 1*/
const int glob_files_size_decreaser = 100;	
/*	������ ��� ���������� �����. ����� ��� ����������/������ ������:
	{�������� ����������{ ����1, ����2, ����3, ����4, ����5 }}	*/
int glob_alg_steps[glob_algos][glob_files]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};
/*	������ ��� ���������� �������, ������������ �� ����������/������ ������:
	{�������� ������{ ����1, ����2, ����3, ����4, ����5 }}	*/
int glob_alg_time[glob_algos][glob_files]={
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0},
	{0,0,0,0,0}
};

#endif;