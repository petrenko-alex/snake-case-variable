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
	input_printf("*************  Привести имена переменных к стилю Snake Case  *************\n");
	input_printf("**************************************************************************\n\n");

	//Инициализируем данные
	int M=0;																				//Количество строк текста
	char text[MAX_OF_STRINGS][MAX_IN_STRING]={};										//Текст программы
	struct variables our_variables[F]={};												//Массив переменных
	int empty_strings=0;																//Счетчик пустых строк
	
	//Получаем текст программы
	input_printf("Введите количество строк текста M = ");
	scanf("%d",&M);
	
	if(M < 1 || M > 20)
	{
		error_printf("\nНедопустимое количество строк\n");
		WAIT_ANY_KEY;
		return 0;
	}
	getchar();

	input_printf("\nВведите синтаксически верный текст программы на Си\n\n");
	for(int i = 0; i < M; i++ )
	{
		gets(text[i]);
		if(strlen(text[i])==0)
			empty_strings++;
	}
	
	

	//Изменяем переменные в snake case
	change_variables_to_snake_case(text,our_variables,M);

	//Выводим текст программы с измененнными переменнными

	input_printf("\n");
	if(empty_strings == M)
	{
		input_printf("Все введенные строки пусты!");
	}
	else
	{
		input_printf("Переменные успешно изменены.Вот ваш текст:\n");
		for(int i = 0;i < M; i++)
			printf("%s\n",text[i]);
	}

	WAIT_ANY_KEY;
	return 0;
}

