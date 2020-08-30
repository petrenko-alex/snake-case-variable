#pragma once
#include "Structures.h"
//#include "testing.h"

/*!
* ������� ������������ ���� ��������� ������ ���������,� ������� ���������� �������� ����� ����������
*\param [in|out] text     - �����(���) ���������
*\param [in|out] M        - ���������� ����� ������
*\return		 action	  - ��������� �����
*/
int input_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int M);

/*!
* ������� ������������ ����� �� ����� ������ ��������� � ��� ���������� ������ ����������
*\param [in|out] text	- �����(���) ���������
*\param [in]     action - �������� �������
*\param [in|out] M      - ���������� ����� ������
*/
void output_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int action,int M);


/*!
* ������� �������� ������ �� ������� "�����" ������������
*\param [in] *str			  - ������
*\return      white_space     - ������� ������� ��� ���������� ����� ������������
*/
int white_spacers(char str[F]);