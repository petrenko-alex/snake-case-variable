#include "stdafx.h"
#include "ChangingToSnakeCase.h"
#include "string.h"
#include "stdio.h"
#include "ctype.h"



/*!
* Функция запоминает переменные в составе объявлений во всем тексте программы(кроме комментариев) и возвращает их количество
*\param [in]     text          - текст программы для поиска
*\param [in|out] our_variables - массив структур,содержащий имя переменной и позицию начала
*\param [in]     strings	   - количество строк в тексте
*\return					   - количество найденных(добавленных) элементов
*/
int search_variables_in_declarations(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings)
{
	//Инициализируем данные
	char *pos = NULL;								//Указатель на тип данных
	int start_pos = -1;								//Индекс начала типа данных
	int count = 0;									//Счетчик найденных переменных
	int i,j=0;										//Переменные цикла

	//В каждой строке текста
	for(i = 0;i < strings;i++)
	{
		int com_pos = 1000;							//Позиция комментария
		int position[2]={};							//Позиция строковой константы						
		start_pos = 0;
		//Находим позицию комментария
		char *comment_pos = strstr(text[i],"//");	
		if(comment_pos)
			com_pos =  comment_pos - text[i];		

		//Находим тип переменной
		start_pos = find_var(text[i],com_pos);
		//Если найдена потенциальная переменная и она расположена до комментария
		if(start_pos >= 0 && start_pos < com_pos)
		{
			//Ищим строковую константу
			string_const(text[i],position);
		
				//Если найдена переменная,а не функция
				if(is_variable(text[i]+start_pos) == -1)
				{
					//Поиск пока не дойдем до комментария или конца строки
					do
					{
						//Если переменная не находится внутри строковой константы
						if(!(start_pos>position[0] && start_pos<position[1]))
						{
							//Сохраняем переменную
							save_variable(text[i]+start_pos,&our_variables[count],i);
							//Пердвигаем стартовую позицию через сохраненную переменную
							start_pos += strlen(our_variables[count].var_name);
							//Увеличиваем количество найденных переменных
							count++;
						}
						else
							//Иначе передвигаем стартовую позицию за строковую константу
							start_pos = position[1];

						//Ищим запятую на случай многочисленного объявления
						pos = strchr(text[i]+start_pos,',');
						if(pos)
						{//Если найдена

							start_pos = pos - text[i];
							//Поиск имени переменной 
							while(!isalnum(text[i][start_pos]) && text[i][start_pos]!='\0')
								start_pos++;

							//Находим следующую строковую константу
							string_const(text[i],position);
						}
						else
							//Иначе заканчиваем поиск
							start_pos = com_pos;
					}
					while(start_pos < com_pos && start_pos < strlen(text[i]));
				}
				else			
				{//Если найдена функция

					//Заходим в параметры функции
					start_pos +=  is_variable(text[i]+start_pos);

					do
					{//Ищим переменные в параметрах до комментария
						
						if(find_var(text[i]+start_pos,com_pos-start_pos)!=-1)
						{//Сохраянем если найдены,изменяем стартовую позицию и увеличиваем количество найденных переменных
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
	//Возвращаем количетсво найденных переменных
	return count;
}

/*!
* Функция запоминает переменные в составе их использование(т.е. объявленные ранее),в том числе и в комментариях и возвращает их количество
*\param [in]     text          - текст программы для поиска
*\param [in|out] our_variables - массив структур,содержащий имя переменной и позицию начала
*\param [in]     alreadyFound  - количество объявленных переменных
*\param [in]     strings       - количество строк в тексте
*\return					   - количество найденных(добавленных) элементов
*/
int search_variables_in_using(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int alreadyFound,const int strings)
{	
	//Инициализируем данные
	int count = 0;						//Счетчик найденных переменных
	char *pos;							//Указатель на начало переменную
	int intPos = 0;						//Индекс начала переменной

	//Если найдены переменные в объявлениях
	if(alreadyFound != 0)
	{
		//В каждой строке текста
		for(int i = 0;i<strings;i++)
		{
			int position[2]={};
			//Для кажого имени переменной из массива
			for(int j = 0;j<alreadyFound;j++)
			{
				int var_length = strlen(our_variables[j].var_name);
				intPos = 0;

				//Ищим текущую переменную до конца строки
				do
				{
					
					pos = strstr(text[i]+intPos,our_variables[j].var_name);
					if(pos)
						intPos = pos - text[i];
					
					//Если эта переменная еще не сохранена
					if(pos && pos!=our_variables[j].var_start && !isalnum(text[i][intPos+var_length]))
					{
						//Если найдена перменная а не функция
						if(is_variable(pos) == -1)
						{
							string_const(text[i],position);
							//Если переменная находится не внутри строковой константы
							if(!(intPos>position[0] && intPos<position[1]))
							{
								//Сохраняем переменную(учитвая уже сохраненные в массиве)
								save_variable(text[i]+intPos,&our_variables[alreadyFound+count],i);
								//Обновляем указатель для дальнейшего поиска в строке переменных с этим именем
								intPos += strlen(our_variables[alreadyFound+count].var_name);
								//Увеличиваем колличество найденных переменных
								count++;
							}
							else
								//Иначе смещаемся за строковую константу
								intPos += position[0];
						}
						else
							//Иначе смещаемся в параметры функции
							intPos += is_variable(pos);

					}
					else if(pos)
						//Если найдена уже сохраненная переменная,смещаемся за эту переменную
						intPos += strlen(our_variables[j].var_name);
					else
						//Иначе смещаемся в конец строки
						intPos = strlen(text[i]);
				}
				while(intPos < strlen(text[i]));

			}
		}
	}
	//Возвращаем общее количество найденных переменных
	return alreadyFound + count;

}

/*! 
* Функция определяет,переменная или функция "перед нами" и возвращет номер позиции скобки 
*\param [in] identifier - указатель на идентификатор(или переменная или функция)
*\return			    - номер мозиции скобки в случае функции,в противном случчае  - "-1"
*/
int is_variable(const char* identifier)
{
	//Инициализируем данные
	char *bracketPos;									//Указатель на позицию скобки
	int pos=0;											//Индекс позиции скобки

	//Проходим по строке пока буква или пробел,до левой открывающей скобки
	while((isalnum(identifier[pos]) || identifier[pos]==' ') && identifier[pos]!='(')
	{
		pos++;
	}

	//Если не встретилась левая открывающая скобка - результат - "-1" как признак не найденной функции
	if(identifier[pos] != '(')
	{
		pos = -1;
	}
	//Возвращаем номер позиции открывающей скобки, или "-1" если не найдена
	return pos;
}

/*!
* Функция сохраняет имя переменной и указатель на начало в массив структур
*\param [in]     var		    - указатель на начало переменной
*\param [in|out] our_variables  - массив структур,содержащий имя переменной и позицию начала
*\param [in]     string_in_text - строка текста в которой найдена переменная
*/
void save_variable(char* var,struct variables* our_variables,const int string_in_text)
{
	//Инициализируем данные
	const char varEndings[] = ";,[= )<>+-*/";     //Массив символов на которые может оканчиваться переменная
	int varLength = 0;							  //Длина переменной	

	//Сохраняем номер строки текста в которой найдена переменная в массив
	(*our_variables).text_string_number = string_in_text;

	//Сохраняем адрес начала переменной в массив
	(*our_variables).var_start = var;

	//Находим длину имени переменной
	varLength = strcspn(var,varEndings);

	//Сохраняем имя переменной в массив
	strncpy((*our_variables).var_name,var,varLength);

}

/*!
* Функция изменяет все переменные в программе до Snake_Case
*\param [in|out] text		   - изменяемый текст программы
*\param [in]	 our_variables - готовый массив структур,содержащий имена всех переменных и указатели на их начало в тексте программы
*\param [in]	 strings       - количество строк текста
*/
void change_variables_to_snake_case(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings)
{	
	//Инициализируем данные
	int count;							//Счетчик найденных переменных

	//Находим переменные в составе объявлений.
	count = search_variables_in_declarations(text,our_variables,strings);
	//Находим объявленные переменные в использовании.
	count = search_variables_in_using(text,our_variables,count,strings);

	//Для всех элементов массива
	for(int i = 0;i<count;i++)
	{	
		//Если две переменные в одной строке, то обновляем указатель из - за смещения строки
		if(our_variables[i].text_string_number == our_variables[i-1].text_string_number)
		{
			our_variables[i].var_start = strstr(text[our_variables[i].text_string_number],our_variables[i].var_name);
		}
		//Если имя еще не в snake case, приводим стиль к snake case
		if(!is_snake_case(our_variables[i].var_name))
		{
			one_var_to_snake_case(text[our_variables[i].text_string_number],&our_variables[i]);
		}
	}
				
}

/*!
* Функция,проверяет,не находится ли имя переменной УЖЕ в snake case
*\param [in] var_name - имя переменной
*\return	 is_snake - переменная в snake case или нет
*/
bool is_snake_case(const char var_name[MAX_VAR_NAME])
{
	//Инициализируем данные
	bool isSnake = false;											//Признак snake_case
	int i = 0;

	//Если первый символ - большая буква - возвращаем признак - не snake case
	if(isupper(var_name[i]))
	{
		return false;
	}

	i++;
		
	//Поиск большой буквы до конца строки
	while(!isupper(var_name[i]) && var_name[i]!='\0')
	{
		//Если очередной символ является символом нижнего подчеркивания а слева и справа от него строчные буква
		if(var_name[i] == '_' && islower(var_name[i-1] ) && islower(var_name[i+1]))
		{
			//Устанавливаем признак snake case
			isSnake = true;
		}
		i++;
	}
	
	//Если встретилась большая буква
	if(isupper(var_name[i]))
		//Устанавливаем признак не snake case
		isSnake = false;

	
	//Возвращаем признак snake case или нет
	return isSnake == true;
}



/*!
* Функция ищет строковую константу в строке и возвращает номера позиций левой и правой кавычек
*\param [in]	 str	   - строка для поиска
*\param [in|out] positions - номера позиций левой и правой кавычки
*\return				   - кавычки найдены или нет
*/
bool string_const(char* str,int *positions)
{
	//Инициализируем данные
	char *quotePos;								//Указатель на кавычку

	//Если ранее строковых констант не было
	if(positions[0] == 0)
		//Ищем первую открывающую кавычку в строке
		quotePos = strchr(str+positions[1],'\"');
	else
		//Иначе ищем следующую открывающую кавычку в строке
		quotePos = strchr(str+positions[1]+1,'\"');

	if(quotePos)
	{//Если найдена открывающая кавычка
		//Запоминаем новер ее позиции
		positions[0] = quotePos - str;
		//Ищим закрывающаую кавычку
		do
		{
		quotePos = strchr(quotePos+1,'\"');
		positions[1] = quotePos - str;
		}
		while(str[positions[1]-1] == '\\');			
	}

	//Если кавычки найдены возвращаем истину,иначе - ложь
	return positions[0]>0 && positions[1]>0;
	
}


/*!
* Функция приводит имя одной переменной в строке к snake_case стилю
*\param [in|out] str - строка с переменной
*\param [in]     our_variables  - переменная
*/
void one_var_to_snake_case(char *str,const struct variables* our_variables)
{
	//Инициализируес данные
	int name_length = 0;					//Длина имени переменной
	int str_length = 0;						//Длина строки в которой находится переменная
	int start_pos;							//Позиция начала переменной в строке
	int i,j =  0;							//Перменные цикла
	int position = 0;						//Позиция  заглавной буквы

	//Вычисляем длину имени переменной
	name_length = strlen((*our_variables).var_name);

	//Вычисляем длину строки в которой находится переменная
	str_length = strlen(str);

	//Находим позицию начала переменной в строке
	start_pos = (*our_variables).var_start - str;
	//Если нашли
	if(start_pos>=0)
	{
		//Меняем первую букву имени переменной на строчную
		str[start_pos]=(char)tolower(str[start_pos]);

		i = start_pos;
		//По имени переменной
		while(i - start_pos < name_length)
		{
			//Если слева от большой буквы или цифры не символ нижнего подчеркивания
			if((isupper(str[i]) && str[i-1]!='_') || (isdigit(str[i]) && !isdigit(str[i-1])&& str[i-1]!='_'))
			{
				position = i;
				//Сдвигаем строку вправо на один символ
				for(j = str_length;j>position-1;j--)
				{
					str[j+1]=str[j];
				}
				//На место образовавшегося пробела в строке ставим символ нижнего подчеркивания
				str[j+1]='_';
				//Меняем заглавную букву на строчную
				str[j+2]=(char)tolower(str[j+2]);
				name_length++;
				str_length++;
			}
			else if(isupper(str[i]) && str[i-1] == '_')
			{//Если найдена большая буква и слева от нее символ нижнего подчеркивания
				//Меняем заглавную букву на строчную
				str[i]=(char)tolower(str[i]);
			}
			i++;
		}
	}
}

/*!
* Функция ищет переменную в составе объявления
*\param [in] str	   - строка для поиска
*\param [in] com_pos   - индекс позиции комментария в строке
*\return     start_pos - позиция первой буквы в переменной или -1 если не найдена
*/
int find_var(char *str,const int com_pos)
{
	//Инициализируем данные
	//Массив возможных типов данных
	char variable_types[16][30]={{"char"},{"signed long int"},{"unsigned long int"},{"unsigned short int"},{"signed short int"},
	{"unsigned char"},{"signed char"},{"unsigned int"},{"signed int"},{"long int"},{"long double"},{"short int"},
	{"int"},{"bool"},{"float"},{"double"}};					

	char *pos;															//Указатель на начало типа данных
	int j = 0;															//Переменная цикла
	int start_pos = 0;													//Стартовая позиция
	bool isFind = false;												//Признак того,что найдена переменная
	int start_positions[17]={};											//Позиции переменных в строке
	int str_length = strlen(str);										//Длина строки
	int position[2]={};													//Позиция строковой константы

	//Ищим строковую константу
	bool stringConst = string_const(str,position);

	//Для всех типов данных из массива
	for(int i = 0;i < 17;i++)
	{
		int type_length = strlen(variable_types[i]);
		pos = strstr(str,variable_types[i]);
		//Есди найден очередной тип данных в строке
		if(pos)
		{
			int tmp_pos = pos - str;
			//И он находится до комментария, а также не является частью другого слова
			if(tmp_pos < com_pos && str[tmp_pos+type_length] == ' ')
			{
				//И он не внутри строковой константы
				if(!(tmp_pos>position[0] && tmp_pos<position[1]))
				{
					tmp_pos += type_length;
					//Ищем имя переменной
					while((str[tmp_pos] == ' ' || str[tmp_pos] == '_' || str[tmp_pos] == '*') && !isalpha(str[tmp_pos]))
					{
						tmp_pos++;
					}

					//Если дошли до буквы
					if(isalpha(str[tmp_pos]))
					{
						//Сохраняем индекс начала переменной
						start_positions[j] = tmp_pos;
						j++;
						//Выставляем признак того,что найдена переменная
						isFind = true;
					}
				}
			}
		}
	}
	
	//Ищим первую переменную в строке(самую ближнюю к началу)
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
		//Есди в строке не найдены переменные устанавливаем признак отсутствия - "-1"
		start_pos = -1;

	//Возвращаем индекс начала имени переменной или "-1"
	return start_pos;
}


