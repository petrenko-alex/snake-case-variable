#include "Structures.h"

/*
*������� ��������� ��� ���������� � ��������� �� ������ � ������ ��������
*\param [in|out] var - ��������� �� ������ ����������
*\param [in|out] our_variables - ������ ��������,���������� ��� ���������� � ������� ������
*/
void save_variable(char* var,struct variables* our_variables);

/*
*������� ��������� ����� ����������.����� ����� ���������� ��������� �������(,) ��� ����� � �������(;)
*\param [in|out] var - ��������� �� ������ ����������
*\return var_length - ����� ����������
*/
int variable_length(char* var);

