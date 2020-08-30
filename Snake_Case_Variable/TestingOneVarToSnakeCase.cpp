#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"

class TestingOneVarToSnakeCase : public cfixcc::TestFixture
{
private:
	
	/*
	*Функция инициализирует массив структур,передаваемыми ей параметрами
	*\param [in[     str		   - строка для поиска указателся
	*\param [in]	 name		   - имя переменной
	*\param [in]     string		   - номера строк текста в которой находится переменная
	*\param [in|out] our_variables - массив структур,который необходимо инициализировать
	*/
	void structure_initialization(char *str,char *name,int string,struct variables* our_variables)
	{
		strcpy((*our_variables).var_name,name);
		(*our_variables).var_start = strstr(str,name);
		(*our_variables).text_string_number = string;
	}

public:
	void Test_var_not_in_snake_case()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int VariableTwoLong;";
		char exp_str[MAX_IN_STRING] = "int variable_two_long;";
		struct variables our_variables[1]={};
		structure_initialization(str,"VariableTwoLong",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 1.Variable is not in snake case yet.");
		CFIX_ASSERT(result == 0);
	}


	void Test_no_variable_to_change()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variable;";
		char exp_str[MAX_IN_STRING] = "int variable;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variable",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 2.Do not need to change variable.");
		CFIX_ASSERT(result == 0);
	}
	
	void Test_already_in_snake_case()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variable_number_one;";
		char exp_str[MAX_IN_STRING] = "int variable_number_one;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variable_number_one",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 3.Variable is already in snake case.");
		CFIX_ASSERT(result == 0);
	}

	void Test_already_in_snake_case_with_digits()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variable_number_one_124;";
		char exp_str[MAX_IN_STRING] = "int variable_number_one_124;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variable_number_one_124",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 4.Variable is already in snake case with digits.");
		CFIX_ASSERT(result == 0);
	}
	
	void Test_var_with_digits()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variableNumber124;";
		char exp_str[MAX_IN_STRING] = "int variable_number_124;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variableNumber124",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 5.Variable is in camel case with digits.");
		CFIX_ASSERT(result == 0);
	}


	void Test_mix_style_var()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variable_numberTwo;";
		char exp_str[MAX_IN_STRING] = "int variable_number_two;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variable_numberTwo",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 6.Variable is in mixed style.");
		CFIX_ASSERT(result == 0);
	}
	

	void Test_mix_style_var_with_digits()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int variable_number124;";
		char exp_str[MAX_IN_STRING] = "int variable_number_124;";
		struct variables our_variables[1]={};
		structure_initialization(str,"variable_number124",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 7.Variable is in mixed style with digits.");
		CFIX_ASSERT(result == 0);
	}
	
	void Test_var_min_length()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int a;";
		char exp_str[MAX_IN_STRING] = "int a;";
		struct variables our_variables[1]={};
		structure_initialization(str,"a",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 8.Min var name length.");
		CFIX_ASSERT(result == 0);
	}

	void Test_string_with_two_vars()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int varExample_two,varExampleOne = 4;";
		char exp_str[MAX_IN_STRING] = "int var_example_two,varExampleOne = 4;";
		struct variables our_variables[1]={};
		structure_initialization(str,"varExample_two",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 9.Two variables in string.");
		CFIX_ASSERT(result == 0);
	}


	void Test_string_with_var_using()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "for(cycleVar=3;cycleVar<6;cycleVar++)";
		char exp_str[MAX_IN_STRING] = "for(cycle_var=3;cycleVar<6;cycleVar++)";
		struct variables our_variables[1]={};
		structure_initialization(str,"cycleVar",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 10.Variable's name in using.");
		CFIX_ASSERT(result == 0);
	}

	void Test_change_second_var_in_string()
	{
		//arrange
		int result = 1;
		char str[MAX_IN_STRING] = "int varExample_two,varExampleOne = 4;";
		char exp_str[MAX_IN_STRING] = "int varExample_two,var_example_one = 4;";
		struct variables our_variables[1]={};
		structure_initialization(str,"varExampleOne",0,our_variables);

		//act
		one_var_to_snake_case(str,our_variables);
		result = strcmp(str,exp_str);

		//assert
		CFIX_LOG("Test 11.Change second var in string.");
		CFIX_ASSERT(result == 0);
	}
};

CFIXCC_BEGIN_CLASS(TestingOneVarToSnakeCase)
	CFIXCC_METHOD(Test_var_not_in_snake_case)
	CFIXCC_METHOD(Test_no_variable_to_change)
	CFIXCC_METHOD(Test_already_in_snake_case)
	CFIXCC_METHOD(Test_already_in_snake_case_with_digits)
	CFIXCC_METHOD(Test_var_with_digits)
	CFIXCC_METHOD(Test_mix_style_var)
	CFIXCC_METHOD(Test_mix_style_var_with_digits)
	CFIXCC_METHOD(Test_var_min_length)
	CFIXCC_METHOD(Test_string_with_two_vars)
	CFIXCC_METHOD(Test_string_with_var_using)
	CFIXCC_METHOD(Test_change_second_var_in_string)
CFIXCC_END_CLASS()

