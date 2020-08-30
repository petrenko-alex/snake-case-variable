#include "Structures.h"

/*
*Функция сохраняет имя переменной и указатель на начало в массив структур
*\param [in|out] var - указатель на начало переменной
*\param [in|out] our_variables - массив структур,содержащий имя переменной и позицию начала
*/
void save_variable(char* var,struct variables* our_variables);

/*
*Функция вычисляет длину переменной.Коцом имени переменной считается запятая(,) или точка с запятой(;)
*\param [in|out] var - указатель на начало переменной
*\return var_length - длина переменной
*/
int variable_length(char* var);

