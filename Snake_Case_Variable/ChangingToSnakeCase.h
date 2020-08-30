#pragma once
#include "Structures.h"

/*!
* Функция запоминает переменные в составе объявлений во всем тексте программы(кроме комментариев) и возвращает их количество
*\param [in]     text          - текст программы для поиска
*\param [in|out] our_variables - массив структур,содержащий имя переменной и позицию начала
*\param [in]     strings	   - количество строк в тексте
*\return					   - количество найденных(добавленных) элементов
*/
int search_variables_in_declarations(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings);


/*!
* Функция запоминает переменные в составе их использование(т.е. объявленные ранее),в том числе и в комментариях и возвращает их количество
*\param [in]     text          - текст программы для поиска
*\param [in|out] our_variables - массив структур,содержащий имя переменной и позицию начала
*\param [in]     alreadyFound  - количество объявленных переменных
*\param [in]     strings       - количество строк в тексте
*\return					   - количество найденных(добавленных) элементов
*/
int search_variables_in_using(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int alreadyFound,const int strings);

/*! 
* Функция определяет,переменная или функция "перед нами" и возвращет номер позиции скобки 
*\param [in] identifier - указатель на идентификатор(или переменная или функция)
*\return			    - номер мозиции скобки в случае функции,в противном случчае  - "-1"
*/
int is_variable(const char* identifier);


/*!
* Функция сохраняет имя переменной и указатель на начало в массив структур
*\param [in]     var		    - указатель на начало переменной
*\param [in|out] our_variables  - массив структур,содержащий имя переменной и позицию начала
*\param [in]     string_in_text - строка текста в которой найдена переменная
*/
void save_variable(char* var,struct variables* our_variables,const int string_in_text);

/*!
* Функция изменяет все переменные в программе до Snake_Case
*\param [in|out] text		   - изменяемый текст программы
*\param [in]	 our_variables - готовый массив структур,содержащий имена всех переменных и указатели на их начало в тексте программы
*\param [in]	 strings       - количество строк текста
*/
void change_variables_to_snake_case(char text[MAX_OF_STRINGS][MAX_IN_STRING],struct variables* our_variables,const int strings);


/*!
* Функция,проверяет,не находится ли имя переменной УЖЕ в snake case
*\param [in] var_name - имя переменной
*\return	 is_snake - переменная в snake case или нет
*/
bool is_snake_case(const char var_name[MAX_VAR_NAME]);


/*!
* Функция ищет строковую константу в строке и возвращает номера позиций левой и правой кавычек
*\param [in]	 str	   - строка для поиска
*\param [in|out] positions - номера позиций левой и правой кавычки
*\return				   - кавычки найдены или нет
*/
bool string_const(char* str,int positions[2]);

/*!
* Функция приводит имя одной переменной в строке к snake_case стилю
*\param [in|out] str - строка с переменной
*\param [in]     our_variables  - переменная
*/
void one_var_to_snake_case(char *str,const struct variables* our_variables);


/*!
* Функция ищет переменную в составе объявления
*\param [in] str	   - строка для поиска
*\param [in] com_pos   - индекс позиции комментария в строке
*\return     start_pos - позиция первой буквы в переменной или -1 если не найдена
*/
int find_var(char *str,const int com_pos);

