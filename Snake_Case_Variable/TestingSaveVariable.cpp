#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"


class saveVariableTesting : public cfixcc::TestFixture
{
private:
	variables our_variables[1];
	variables expected_variables[1];

	/*!
	* Функция проверяет два массива структур variables на равенство
	*\param [in|out] expected_variables - ожидаемый массив структур от теста
	*\param [in|out] our_variables		- массив структур от тестируемой функции
	*\param [in]	 size				- количество элементов массива-размер массива
	*\return							- массивы структур равны или нет
	*/
	bool is_structures_equal(struct variables* expected_variables,struct variables* our_variables,int size)
	{
		size--;
		int name_equal=0;
		int start_equal=0;
		bool string_equal = false;

		for(int i=0;i<=size;i++)
		{
			name_equal = strcmp(our_variables[i].var_name,expected_variables[i].var_name);//Сравниваем имена переменных
			string_equal = our_variables[i].text_string_number == expected_variables[i].text_string_number;
			if(our_variables[i].var_start)
				start_equal = strcmp(our_variables[i].var_start,expected_variables[i].var_start);//Сравниваем указатели на начало
			else
				return false;
			if(name_equal!=0 || start_equal!=0 || !string_equal)
				return false;
		}
		return true;
	}
	

public:
	
	////////////////////////////////ТЕСТЫ ДЛЯ ФУНКЦИИ save_variable\\\\\\\\\\\\\\\\\\\\\\\\/
	void Test_variable_with_initialization()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable=65;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 1.Simple with initialization.");
		CFIX_ASSERT(result==true);
	}

	void Test_variable_array()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="testVarOne[50]={};}";
		
		strcpy(expected_variables[0].var_name,"testVarOne");
		expected_variables[0].var_start=strstr(str,"testVarOne");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 2.Array with initialization.");
		CFIX_ASSERT(result==true);
	}

	void Test_max_length_of_variable()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="specialVariable_for_testing_max_size_of_variable_trying_to_write_one_hundred_symbols_we_already_have = 3;";
	
		strcpy(expected_variables[0].var_name,"specialVariable_for_testing_max_size_of_variable_trying_to_write_one_hundred_symbols_we_already_have");
		expected_variables[0].var_start=strstr(str,"specialVariable_for_testing_max_size_of_variable_trying_to_write_one_hundred_symbols_we_already_have = 3;");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 3.Max length of variable's name.");
		CFIX_ASSERT(result==true);
	}
	
	void Test_save_variable_with_digits()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="tes2rVar53==234;";
		
		strcpy(expected_variables[0].var_name,"tes2rVar53");
		expected_variables[0].var_start=strstr(str,"tes2rVar53==234;");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 4.Variable's name with digits.");
		CFIX_ASSERT(result==true);
	}

	void Test_few_variables()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable,second_var;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 5.Few variable's names in string.");
		CFIX_ASSERT(result==true);
	}

	void Test_just_variable()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 6.Variable's name without initialization.");
		CFIX_ASSERT(result==true);
	}

	void Test_variable_as_function_parameter()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable)";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 7.Variable as function's parameter.");
		CFIX_ASSERT(result==true);
	}

	void Test_within_arithmetic_operation_devision()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable/3;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 8.Variable name within AO - division.");
		CFIX_ASSERT(result==true);
	}

	void Test_within_arithmetic_operation_multiplication()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable*3;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 9.Variable name within AO - multiplication.");
		CFIX_ASSERT(result==true);
	}

	void Test_within_arithmetic_operation_addition()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable+ex2;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 10.Variable name within AO - addition.");
		CFIX_ASSERT(result==true);

	}

	void Test_within_arithmetic_operation_substraction()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable-ex2;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 11.Variable name within AO - substraction.");
		CFIX_ASSERT(result==true);

	}

	void Test_within_arithmetic_operation_comparison()
	{
		//arrange
		bool result = false;
		variables our_variables[1]={};
		variables expected_variables[1]={};
		char str[]="example_variable<=ex2;";
		
		strcpy(expected_variables[0].var_name,"example_variable");
		expected_variables[0].var_start=strstr(str,"example_variable");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 12.Variable name within AO - comparison.");
		CFIX_ASSERT(result==true);
	}

	void Test_min_var_name()
	{
		//arrange
		bool result = false;
		char str[]="a;";
		variables our_variables[1]={};
		variables expected_variables[1]={};

		strcpy(expected_variables[0].var_name,"a");
		expected_variables[0].var_start=strstr(str,"a");

		//act
		save_variable(str,our_variables,0);
		result=is_structures_equal(expected_variables,our_variables,1);

		//assert
		CFIX_LOG("Test 13.Min variable's name.");
		CFIX_ASSERT(result==true);
	}
};

CFIXCC_BEGIN_CLASS(saveVariableTesting)
	CFIXCC_METHOD(Test_variable_with_initialization)
	CFIXCC_METHOD(Test_variable_array)
	CFIXCC_METHOD(Test_max_length_of_variable)
	CFIXCC_METHOD(Test_save_variable_with_digits)
	CFIXCC_METHOD(Test_few_variables)
	CFIXCC_METHOD(Test_just_variable)
	CFIXCC_METHOD(Test_variable_as_function_parameter)
	CFIXCC_METHOD(Test_within_arithmetic_operation_devision)
	CFIXCC_METHOD(Test_within_arithmetic_operation_multiplication)
	CFIXCC_METHOD(Test_within_arithmetic_operation_addition)
	CFIXCC_METHOD(Test_within_arithmetic_operation_substraction)
	CFIXCC_METHOD(Test_within_arithmetic_operation_comparison)
	CFIXCC_METHOD(Test_min_var_name)
CFIXCC_END_CLASS()

