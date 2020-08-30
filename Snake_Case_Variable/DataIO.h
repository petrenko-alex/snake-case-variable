#pragma once
#include "Structures.h"
//#include "testing.h"

/*!
* Функция осуществляет ввод исходного текста программы,в котором необходимо изменить стиль переменных
*\param [in|out] text     - текст(код) программы
*\param [in|out] M        - количество строк текста
*\return		 action	  - результат ввода
*/
int input_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int M);

/*!
* Функция осуществляет вывод на экран текста программы с уже измененным стилем переменных
*\param [in|out] text	- текст(код) программы
*\param [in]     action - действие функции
*\param [in|out] M      - количество строк текста
*/
void output_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int action,int M);


/*!
* Функция проверки строки на наличие "белых" разделителей
*\param [in] *str			  - строка
*\return      white_space     - признак наличия или отсутствия белых разделителей
*/
int white_spacers(char str[F]);