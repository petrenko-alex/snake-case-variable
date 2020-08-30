#pragma once
#define MAX_IN_STRING 200
#define MAX_OF_STRINGS 20
#define F 50
#define MAX_VAR_NAME 100


//Структура, содержащая:
//Имя переменной,
//Указатель на начало имени,
//Строка текста,содержащая эту переменную.
struct variables
{
	char var_name[101];				//Имя переменной.
	char* var_start;				//Указатель на начало переменной.
	int text_string_number;			//Строка в тексте.
};



