#include "stdafx.h"
#include "ChangingToSnakeCase.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"



/*!
* ������� ���������� ���������� � ������� ���������� �� ���� ������ ���������(����� ������������) � ���������� �� ����������
*\param [in]     text          - ����� ��������� ��� ������
*\param [in|out] our_variables - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     strings	   - ���������� ����� � ������
*\return					   - ���������� ���������(�����������) ���������
*/
int search_variables_in_declarations(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings)
{
	//�������������� ������
	char *pos = NULL;								//��������� �� ��� ������
	int start_pos = -1;								//������ ������ ���� ������
	int count = 0;									//������� ��������� ����������
	int i,j=0;										//���������� �����

	//� ������ ������ ������
	for(i = 0;i < strings;i++)
	{
		int com_pos = 1000;							//������� �����������
		int position[2]={};							//������� ��������� ���������						
		start_pos = 0;
		//������� ������� �����������
		char *comment_pos = strstr(text[i],"//");	
		if(comment_pos)
			com_pos =  comment_pos - text[i];		

		//������� ��� ����������
		start_pos = find_var(text[i],com_pos);
		//���� ������� ������������� ���������� � ��� ����������� �� �����������
		if(start_pos >= 0 && start_pos < com_pos)
		{
			//���� ��������� ���������
			string_const(text[i],position);
		
				//���� ������� ����������,� �� �������
				if(is_variable(text[i]+start_pos) == -1)
				{
					//����� ���� �� ������ �� ����������� ��� ����� ������
					do
					{
						//���� ���������� �� ��������� ������ ��������� ���������
						if(!(start_pos>position[0] && start_pos<position[1]))
						{
							//��������� ����������
							save_variable(text[i]+start_pos,&our_variables[count],i);
							//���������� ��������� ������� ����� ����������� ����������
							start_pos += strlen(our_variables[count].var_name);
							//����������� ���������� ��������� ����������
							count++;
						}
						else
							//����� ����������� ��������� ������� �� ��������� ���������
							start_pos = position[1];

						//���� ������� �� ������ ��������������� ����������
						pos = strchr(text[i]+start_pos,',');
						if(pos)
						{//���� �������

							start_pos = pos - text[i];
							//����� ����� ���������� 
							while(!isalnum(text[i][start_pos]) && text[i][start_pos]!='\0')
								start_pos++;

							//������� ��������� ��������� ���������
							string_const(text[i],position);
						}
						else
							//����� ����������� �����
							start_pos = com_pos;
					}
					while(start_pos < com_pos && start_pos < strlen(text[i]));
				}
				else			
				{//���� ������� �������

					//������� � ��������� �������
					start_pos +=  is_variable(text[i]+start_pos);

					do
					{//���� ���������� � ���������� �� �����������
						
						if(find_var(text[i]+start_pos,com_pos-start_pos)!=-1)
						{//��������� ���� �������,�������� ��������� ������� � ����������� ���������� ��������� ����������
							start_pos += find_var(text[i]+start_pos,com_pos-start_pos);
							save_variable(text[i]+start_pos,&our_variables[count],i);
							start_pos += strlen(our_variables[count].var_name);
							count++;
						}
						else
							start_pos = com_pos;
					}
					while(start_pos<com_pos);
				}
		}
	}
	//���������� ���������� ��������� ����������
	return count;
}

/*!
* ������� ���������� ���������� � ������� �� �������������(�.�. ����������� �����),� ��� ����� � � ������������ � ���������� �� ����������
*\param [in]     text          - ����� ��������� ��� ������
*\param [in|out] our_variables - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     alreadyFound  - ���������� ����������� ����������
*\param [in]     strings       - ���������� ����� � ������
*\return					   - ���������� ���������(�����������) ���������
*/
int search_variables_in_using(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int alreadyFound,const int strings)
{	
	//�������������� ������
	int count = 0;						//������� ��������� ����������
	char *pos;							//��������� �� ������ ����������
	int intPos = 0;						//������ ������ ����������

	//���� ������� ���������� � �����������
	if(alreadyFound != 0)
	{
		//� ������ ������ ������
		for(int i = 0;i<strings;i++)
		{
			int position[2]={};
			//��� ������ ����� ���������� �� �������
			for(int j = 0;j<alreadyFound;j++)
			{
				int var_length = strlen(our_variables[j].var_name);
				intPos = 0;

				//���� ������� ���������� �� ����� ������
				do
				{
					
					pos = strstr(text[i]+intPos,our_variables[j].var_name);
					if(pos)
						intPos = pos - text[i];
					
					//���� ��� ���������� ��� �� ���������
					if(pos && pos!=our_variables[j].var_start && !isalnum(text[i][intPos+var_length]))
					{
						//���� ������� ��������� � �� �������
						if(is_variable(pos) == -1)
						{
							string_const(text[i],position);
							//���� ���������� ��������� �� ������ ��������� ���������
							if(!(intPos>position[0] && intPos<position[1]))
							{
								//��������� ����������(������� ��� ����������� � �������)
								save_variable(text[i]+intPos,&our_variables[alreadyFound+count],i);
								//��������� ��������� ��� ����������� ������ � ������ ���������� � ���� ������
								intPos += strlen(our_variables[alreadyFound+count].var_name);
								//����������� ����������� ��������� ����������
								count++;
							}
							else
								//����� ��������� �� ��������� ���������
								intPos += position[0];
						}
						else
							//����� ��������� � ��������� �������
							intPos += is_variable(pos);

					}
					else if(pos)
						//���� ������� ��� ����������� ����������,��������� �� ��� ����������
						intPos += strlen(our_variables[j].var_name);
					else
						//����� ��������� � ����� ������
						intPos = strlen(text[i]);
				}
				while(intPos < strlen(text[i]));

			}
		}
	}
	//���������� ����� ���������� ��������� ����������
	return alreadyFound + count;

}

/*! 
* ������� ����������,���������� ��� ������� "����� ����" � ��������� ����� ������� ������ 
*\param [in] identifier - ��������� �� �������������(��� ���������� ��� �������)
*\return			    - ����� ������� ������ � ������ �������,� ��������� �������  - "-1"
*/
int is_variable(const char* identifier)
{
	//�������������� ������
	char *bracketPos;									//��������� �� ������� ������
	int pos=0;											//������ ������� ������

	//�������� �� ������ ���� ����� ��� ������,�� ����� ����������� ������
	while((isalnum(identifier[pos]) || identifier[pos]==' ') && identifier[pos]!='(')
	{
		pos++;
	}

	//���� �� ����������� ����� ����������� ������ - ��������� - "-1" ��� ������� �� ��������� �������
	if(identifier[pos] != '(')
	{
		pos = -1;
	}
	//���������� ����� ������� ����������� ������, ��� "-1" ���� �� �������
	return pos;
}

/*!
* ������� ��������� ��� ���������� � ��������� �� ������ � ������ ��������
*\param [in]     var		    - ��������� �� ������ ����������
*\param [in|out] our_variables  - ������ ��������,���������� ��� ���������� � ������� ������
*\param [in]     string_in_text - ������ ������ � ������� ������� ����������
*/
void save_variable(char* var,struct variables* our_variables,const int string_in_text)
{
	//�������������� ������
	const char varEndings[] = ";,[= )<>+-*/";     //������ �������� �� ������� ����� ������������ ����������
	int varLength = 0;							  //����� ����������	

	//��������� ����� ������ ������ � ������� ������� ���������� � ������
	(*our_variables).text_string_number = string_in_text;

	//��������� ����� ������ ���������� � ������
	(*our_variables).var_start = var;

	//������� ����� ����� ����������
	varLength = strcspn(var,varEndings);

	//��������� ��� ���������� � ������
	strncpy((*our_variables).var_name,var,varLength);

}

/*!
* ������� �������� ��� ���������� � ��������� �� Snake_Case
*\param [in|out] text		   - ���������� ����� ���������
*\param [in]	 our_variables - ������� ������ ��������,���������� ����� ���� ���������� � ��������� �� �� ������ � ������ ���������
*\param [in]	 strings       - ���������� ����� ������
*/
void change_variables_to_snake_case(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings)
{	
	//�������������� ������
	int count;							//������� ��������� ����������

	//������� ���������� � ������� ����������.
	count = search_variables_in_declarations(text,our_variables,strings);
	//������� ����������� ���������� � �������������.
	count = search_variables_in_using(text,our_variables,count,strings);

	//��� ���� ��������� �������
	for(int i = 0;i<count;i++)
	{	
		//���� ��� ���������� � ����� ������, �� ��������� ��������� �� - �� �������� ������
		if(our_variables[i].text_string_number == our_variables[i-1].text_string_number)
		{
			our_variables[i].var_start = strstr(text[our_variables[i].text_string_number],our_variables[i].var_name);
		}
		//���� ��� ��� �� � snake case, �������� ����� � snake case
		if(!is_snake_case(our_variables[i].var_name))
		{
			one_var_to_snake_case(text[our_variables[i].text_string_number],&our_variables[i]);
		}
	}
				
}

/*!
* �������,���������,�� ��������� �� ��� ���������� ��� � snake case
*\param [in] var_name - ��� ����������
*\return	 is_snake - ���������� � snake case ��� ���
*/
bool is_snake_case(const char var_name[MAX_VAR_NAME])
{
	//�������������� ������
	bool isSnake = false;											//������� snake_case
	int i = 0;

	//���� ������ ������ - ������� ����� - ���������� ������� - �� snake case
	if(isupper(var_name[i]))
	{
		return false;
	}

	i++;
		
	//����� ������� ����� �� ����� ������
	while(!isupper(var_name[i]) && var_name[i]!='\0')
	{
		//���� ��������� ������ �������� �������� ������� ������������� � ����� � ������ �� ���� �������� �����
		if(var_name[i] == '_' && islower(var_name[i-1] ) && islower(var_name[i+1]))
		{
			//������������� ������� snake case
			isSnake = true;
		}
		i++;
	}
	
	//���� ����������� ������� �����
	if(isupper(var_name[i]))
		//������������� ������� �� snake case
		isSnake = false;

	
	//���������� ������� snake case ��� ���
	return isSnake == true;
}



/*!
* ������� ���� ��������� ��������� � ������ � ���������� ������ ������� ����� � ������ �������
*\param [in]	 str	   - ������ ��� ������
*\param [in|out] positions - ������ ������� ����� � ������ �������
*\return				   - ������� ������� ��� ���
*/
bool string_const(char* str,int *positions)
{
	//�������������� ������
	char *quotePos;								//��������� �� �������

	//���� ����� ��������� �������� �� ����
	if(positions[0] == 0)
		//���� ������ ����������� ������� � ������
		quotePos = strchr(str+positions[1],'\"');
	else
		//����� ���� ��������� ����������� ������� � ������
		quotePos = strchr(str+positions[1]+1,'\"');

	if(quotePos)
	{//���� ������� ����������� �������
		//���������� ����� �� �������
		positions[0] = quotePos - str;
		//���� ������������ �������
		do
		{
		quotePos = strchr(quotePos+1,'\"');
		positions[1] = quotePos - str;
		}
		while(str[positions[1]-1] == '\\');			
	}

	//���� ������� ������� ���������� ������,����� - ����
	return positions[0]>0 && positions[1]>0;
	
}


/*!
* ������� �������� ��� ����� ���������� � ������ � snake_case �����
*\param [in|out] str - ������ � ����������
*\param [in]     our_variables  - ����������
*/
void one_var_to_snake_case(char *str,const struct variables* our_variables)
{
	//�������������� ������
	int name_length = 0;					//����� ����� ����������
	int str_length = 0;						//����� ������ � ������� ��������� ����������
	int start_pos;							//������� ������ ���������� � ������
	int i,j =  0;							//��������� �����
	int position = 0;						//�������  ��������� �����

	//��������� ����� ����� ����������
	name_length = strlen((*our_variables).var_name);

	//��������� ����� ������ � ������� ��������� ����������
	str_length = strlen(str);

	//������� ������� ������ ���������� � ������
	start_pos = (*our_variables).var_start - str;
	//���� �����
	if(start_pos>=0)
	{
		//������ ������ ����� ����� ���������� �� ��������
		str[start_pos]=(char)tolower(str[start_pos]);

		i = start_pos;
		//�� ����� ����������
		while(i - start_pos < name_length)
		{
			//���� ����� �� ������� ����� ��� ����� �� ������ ������� �������������
			if((isupper(str[i]) && str[i-1]!='_') || (isdigit(str[i]) && !isdigit(str[i-1])&& str[i-1]!='_'))
			{
				position = i;
				//�������� ������ ������ �� ���� ������
				for(j = str_length;j>position-1;j--)
				{
					str[j+1]=str[j];
				}
				//�� ����� ��������������� ������� � ������ ������ ������ ������� �������������
				str[j+1]='_';
				//������ ��������� ����� �� ��������
				str[j+2]=(char)tolower(str[j+2]);
				name_length++;
				str_length++;
			}
			else if(isupper(str[i]) && str[i-1] == '_')
			{//���� ������� ������� ����� � ����� �� ��� ������ ������� �������������
				//������ ��������� ����� �� ��������
				str[i]=(char)tolower(str[i]);
			}
			i++;
		}
	}
}

/*!
* ������� ���� ���������� � ������� ����������
*\param [in] str	   - ������ ��� ������
*\param [in] com_pos   - ������ ������� ����������� � ������
*\return     start_pos - ������� ������ ����� � ���������� ��� -1 ���� �� �������
*/
int find_var(char *str,const int com_pos)
{
	//�������������� ������
	//������ ��������� ����� ������
	char variable_types[16][30]={{"char"},{"signed long int"},{"unsigned long int"},{"unsigned short int"},{"signed short int"},
	{"unsigned char"},{"signed char"},{"unsigned int"},{"signed int"},{"long int"},{"long double"},{"short int"},
	{"int"},{"bool"},{"float"},{"double"}};					

	char *pos;															//��������� �� ������ ���� ������
	int j = 0;															//���������� �����
	int start_pos = 0;													//��������� �������
	bool isFind = false;												//������� ����,��� ������� ����������
	int start_positions[17]={};											//������� ���������� � ������
	int str_length = strlen(str);										//����� ������
	int position[2]={};													//������� ��������� ���������

	//���� ��������� ���������
	bool stringConst = string_const(str,position);

	//��� ���� ����� ������ �� �������
	for(int i = 0;i < 17;i++)
	{
		int type_length = strlen(variable_types[i]);
		pos = strstr(str,variable_types[i]);
		//���� ������ ��������� ��� ������ � ������
		if(pos)
		{
			int tmp_pos = pos - str;
			//� �� ��������� �� �����������, � ����� �� �������� ������ ������� �����
			if(tmp_pos < com_pos && str[tmp_pos+type_length] == ' ')
			{
				//� �� �� ������ ��������� ���������
				if(!(tmp_pos>position[0] && tmp_pos<position[1]))
				{
					tmp_pos += type_length;
					//���� ��� ����������
					while((str[tmp_pos] == ' ' || str[tmp_pos] == '_' || str[tmp_pos] == '*') && !isalpha(str[tmp_pos]))
					{
						tmp_pos++;
					}

					//���� ����� �� �����
					if(isalpha(str[tmp_pos]))
					{
						//��������� ������ ������ ����������
						start_positions[j] = tmp_pos;
						j++;
						//���������� ������� ����,��� ������� ����������
						isFind = true;
					}
				}
			}
		}
	}
	
	//���� ������ ���������� � ������(����� ������� � ������)
	if(isFind)
	{
		start_pos = 1000;
		for(int i = 0;i<j;i++)
		{
			if(start_positions[i] < start_pos)
				start_pos = start_positions[i];
		}
	}
	else
		//���� � ������ �� ������� ���������� ������������� ������� ���������� - "-1"
		start_pos = -1;

	//���������� ������ ������ ����� ���������� ��� "-1"
	return start_pos;
}


