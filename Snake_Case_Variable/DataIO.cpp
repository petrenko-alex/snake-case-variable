#include "stdafx.h"
#include "DataIO.h"
#include "ctype.h"


/*!
* ������� ������������ ���� ��������� ������ ���������,� ������� ���������� �������� ����� ����������
*\param [in|out] text     - �����(���) ���������
*\param [in|out] M        - ���������� ����� ������
*\return		 action	  - ��������� �����
*/
int input_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int M)
{
	int empty_strings=0;			//����������� ������ �����
	int action=0;					//���� - ��������� �����

	printf("������� ���������� ����� ������ M = ");
	scanf("%d",&M);
	
	if(M < 1 || M > 20)
	{
		action = 1;
		return action;
	}
	getchar();

	printf("\n������� ������������� ������ ����� ��������� �� ��\n\n");

	for(int i = 0; i < M; i++ )
	{
		gets(text[i]);
		if(strlen(text[i]) == 0 || white_spacers(text[i]) == 1)
			empty_strings++;
	}

	if(empty_strings == M)
		action = 2;
	
	return action;
}


/*!
* ������� ������������ ����� �� ����� ������ ��������� � ��� ���������� ������ ����������
*\param [in|out] text	- �����(���) ���������
*\param [in]     action - �������� �������
*\param [in|out] M      - ���������� ����� ������
*/
void output_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int action,int M)
{

	if(action == 0)
	{
		printf("���������� ������� ��������.��� ��� �����:\n");
		for(int i = 0;i < M; i++)
			printf("%s\n",text[i]);
	}
	else if(action == 1)
	{
		printf("\n�������� ���������� �����\n");
	}
	else if(action == 2)
	{
		printf("��� ��������� ������ �����!");
	}
}



/*!
* ������� �������� ������ �� ������� "�����" ������������
*\param [in] *str			  - ������
*\return      white_space     - ������� ������� ��� ���������� ����� ������������
*/
int white_spacers(char *str)
{
	int white_space_count=0;							//C������ ����� ������������
	int length = strlen(str);						    //����� ������
	int white_space = 0;								//����
	
	//���� ����� ������ �� ����
	if (length > 0)
		//�� ���� ������
		for (int i = 0; i < length; i++)
			//���� ������ ����� �����������
			if (isspace(str[i]) != 0)
				//����������� �������
				white_space_count++;

	//���� ������ ������� ������ �� ����� ������������
	if(white_space_count == length)
		white_space = 1;
	
	return white_space;
}
