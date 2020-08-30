#include "stdafx.h"
#include "DataIO.h"
#include "ctype.h"


/*!
* Функция осуществляет ввод исходного текста программы,в котором необходимо изменить стиль переменных
*\param [in|out] text     - текст(код) программы
*\param [in|out] M        - количество строк текста
*\return		 action	  - результат ввода
*/
int input_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int M)
{
	int empty_strings=0;			//Колличество пустых строк
	int action=0;					//Флаг - результат ввода

	printf("Введите количество строк текста M = ");
	scanf("%d",&M);
	
	if(M < 1 || M > 20)
	{
		action = 1;
		return action;
	}
	getchar();

	printf("\nВведите синтаксически верный текст программы на Си\n\n");

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
* Функция осуществляет вывод на экран текста программы с уже измененным стилем переменных
*\param [in|out] text	- текст(код) программы
*\param [in]     action - действие функции
*\param [in|out] M      - количество строк текста
*/
void output_text(char text[MAX_OF_STRINGS][MAX_IN_STRING],int action,int M)
{

	if(action == 0)
	{
		printf("Переменные успешно изменены.Вот ваш текст:\n");
		for(int i = 0;i < M; i++)
			printf("%s\n",text[i]);
	}
	else if(action == 1)
	{
		printf("\nНеверное количество строк\n");
	}
	else if(action == 2)
	{
		printf("Все введенные строки пусты!");
	}
}



/*!
* Функция проверки строки на наличие "белых" разделителей
*\param [in] *str			  - строка
*\return      white_space     - признак наличия или отсутствия белых разделителей
*/
int white_spacers(char *str)
{
	int white_space_count=0;							//Cчетчик белых разделителей
	int length = strlen(str);						    //Длина строки
	int white_space = 0;								//Флаг
	
	//Если длина строки не ноль
	if (length > 0)
		//Во всей строке
		for (int i = 0; i < length; i++)
			//Если найден белый разделитель
			if (isspace(str[i]) != 0)
				//Увеличиваем счетчик
				white_space_count++;

	//Если строка состоит только из булых разделителей
	if(white_space_count == length)
		white_space = 1;
	
	return white_space;
}
