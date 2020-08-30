#pragma once
#include "Structures.h"

/*!
* ������� ���������� ���������� � ������� ���������� �� ���� ������ ���������(����� ������������) � ���������� �� ����������
*\param [in]     text          - ����� ��������� ��� ������
*\param [in|out] our_variables - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     strings	   - ���������� ����� � ������
*\return					   - ���������� ���������(�����������) ���������
*/
int search_variables_in_declarations(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings);


/*!
* ������� ���������� ���������� � ������� �� �������������(�.�. ����������� �����),� ��� ����� � � ������������ � ���������� �� ����������
*\param [in]     text          - ����� ��������� ��� ������
*\param [in|out] our_variables - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     alreadyFound  - ���������� ����������� ����������
*\param [in]     strings       - ���������� ����� � ������
*\return					   - ���������� ���������(�����������) ���������
*/
int search_variables_in_using(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int alreadyFound,const int strings);

/*! 
* ������� ����������,���������� ��� ������� "����� ����" � ��������� ����� ������� ������ 
*\param [in] identifier - ��������� �� �������������(��� ���������� ��� �������)
*\return			    - ����� ������� ������ � ������ �������,� ��������� �������  - "-1"
*/
int is_variable(const char* identifier);


/*!
* ������� ��������� ��� ���������� � ��������� �� ������ � ������ ��������
*\param [in]     var		    - ��������� �� ������ ����������
*\param [in|out] our_variables  - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     string_in_text - ������ ������ � ������� ������� ����������
*/
void save_variable(char* var,struct variables* our_variables,const int string_in_text);

/*!
* ������� �������� ��� ���������� � ��������� �� Snake_Case
*\param [in|out] text		   - ���������� ����� ���������
*\param [in]	 our_variables - ������� ������ ��������,���������� ����� ���� ���������� � ��������� �� �� ������ � ������ ���������
*\param [in]	 strings       - ���������� ����� ������
*/
void change_variables_to_snake_case(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings);


/*!
* �������,���������,�� ��������� �� ��� ���������� ��� � snake case
*\param [in] var_name - ��� ����������
*\return	 is_snake - ���������� � snake case ��� ���
*/
bool is_snake_case(const char var_name[MAX_VAR_NAME]);


/*!
* ������� ���� ��������� ��������� � ������ � ���������� ������ ������� ����� � ������ �������
*\param [in]	 str	   - ������ ��� ������
*\param [in|out] positions - ������ ������� ����� � ������ �������
*\return				   - ������� ������� ��� ���
*/
bool string_const(char* str,int positions[2]);

/*!
* ������� �������� ��� ����� ���������� � ������ � snake_case �����
*\param [in|out] str - ������ � ����������
*\param [in]     our_variables  - ����������
*/
void one_var_to_snake_case(char *str,const struct variables* our_variables);


/*!
* ������� ���� ���������� � ������� ����������
*\param [in] str	   - ������ ��� ������
*\param [in] com_pos   - ������ ������� ����������� � ������
*\return     start_pos - ������� ������ ����� � ���������� ��� -1 ���� �� �������
*/
int find_var(char *str,const int com_pos);

