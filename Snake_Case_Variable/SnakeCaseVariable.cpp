#include "stdafx.h"
#include "Structures.h"
#include "ChangingToSnakeCase.h"
#include "testing.h"
#include <iostream>
#include "dataio.h"


int _tmain(int argc, _TCHAR* argv[])
{	
	setlocale(LC_ALL,"RUS");
	input_printf("**************************************************************************\n");
	input_printf("*************  �������� ����� ���������� � ����� Snake Case  *************\n");
	input_printf("**************************************************************************\n\n");

	//�������������� ������
	int M=0;																				//���������� ����� ������
	char text[MAX_OF_STRINGS][MAX_IN_STRING]={};										//����� ���������
	struct variables our_variables[F]={};												//������ ����������
	int empty_strings=0;																//������� ������ �����
	
	//�������� ����� ���������
	input_printf("������� ���������� ����� ������ M = ");
	scanf("%d",&M);
	
	if(M < 1 || M > 20)
	{
		error_printf("\n������������ ���������� �����\n");
		WAIT_ANY_KEY;
		return 0;
	}
	getchar();

	input_printf("\n������� ������������� ������ ����� ��������� �� ��\n\n");
	for(int i = 0; i < M; i++ )
	{
		gets(text[i]);
		if(strlen(text[i])==0)
			empty_strings++;
	}
	
	

	//�������� ���������� � snake case
	change_variables_to_snake_case(text,our_variables,M);

	//������� ����� ��������� � ������������ ������������

	input_printf("\n");
	if(empty_strings == M)
	{
		input_printf("��� ��������� ������ �����!");
	}
	else
	{
		input_printf("���������� ������� ��������.��� ��� �����:\n");
		for(int i = 0;i < M; i++)
			printf("%s\n",text[i]);
	}

	WAIT_ANY_KEY;
	return 0;
}

