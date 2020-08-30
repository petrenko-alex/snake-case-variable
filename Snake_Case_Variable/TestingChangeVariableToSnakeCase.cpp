#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"
//#include "Structures.h"
class TestingChangeVariableToSnakeCase : public cfixcc::TestFixture
{
private:
	/*
	*Функция проверяет два массива структур variables на равенство
	*\param [in]     expectable_text - ожидаемый текст программы после изменения
	*\param [in]	 our_text		 - текст программы после обработки функцией
	*\return						 - тексты идентичны или нет
	*/
	bool is_texts_equal(const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING],const char our_text[MAX_OF_STRINGS][MAX_IN_STRING])
	{
		for(int i=0;i<MAX_OF_STRINGS;i++)
		{
			int equal_string=strcmp(expectable_text[i],our_text[i]);
			if(equal_string!=0)
				return false;
		}
		return true;
	}
	

public:
	/////////////////////////////ТЕСТИРОВАНИЕ ФУНКЦИИ change_variable_to_snake_case\\\\\\\\\\\\\\\\\\\\\\\\\\\\/
	void Test_text_has_no_variable_to_change()//В тексте нет переменных,которые требовалось бы изменять
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int variable;"},
				{"char symbol;"},
				{"bool true"},
				{"printf(\"Hello World\");"},
				{"function1(variable,symbol);"},
			{"}"},
			{"void function1(int var,char sym)"},
			{"{"},
				{""},
			{"}"}
		};

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int variable;"},
				{"char symbol;"},
				{"bool true"},
				{"printf(\"Hello World\");"},
				{"function1(variable,symbol);"},
			{"}"},
			{"void function1(int var,char sym)"},
			{"{"},
				{""},
			{"}"}
		};
		
		variables our_variables[F]={'\0'};
	
		//act
		change_variables_to_snake_case(text,our_variables,12);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 1.Do not need to change variables' style");
		CFIX_ASSERT(result==true);
	}

	void Test_text_with_variables_already_in_snake_case()
	{

		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int variable_one;"},
				{"char symbol_number_two;"},
				{"bool is_it_true;"},
				{"unsigned int special_var_123_with_digits;"},
				{"printf(\"Hello World\");"},
			{"}"},
		};

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int variable_one;"},
				{"char symbol_number_two;"},
				{"bool is_it_true;"},
				{"unsigned int special_var_123_with_digits;"},
				{"printf(\"Hello World\");"},
			{"}"},
		};

		variables our_variables[F]={'\0'};
	
		//act
		change_variables_to_snake_case(text,our_variables,8);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 2.All variables is already in snake case,do not need to change.");
		CFIX_ASSERT(result==true);
	}
	
	void Test_text_with_variables_in_camel_case()
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int VariableTwoLong;"},
				{"char symbolAfterString;"},
				{"bool itItRealTrueOrNot"},
				{"double _ExVarOne;"},
				{"printf(\"Hello World\");"},
			{"}"},
		};

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int variable_two_long;"},
				{"char symbol_after_string;"},
				{"bool it_it_real_true_or_not"},
				{"double _ex_var_one;"},
				{"printf(\"Hello World\");"},
			{"}"},
		};

		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,8);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 3.All variables is in camel case.");
		CFIX_ASSERT(result==true);
	}
	
	void Test_declaration_and_using()
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycleVar;"},
				{"char string_to_show[];"},
				{"bool ifClause_variable;"},
				{"float array[7];"},
				{"int operand_one,operandTwo,result;"},
				{""},
				{"printf(\"%s\",string_to_show);"},					
				{"for(cycleVar=3;cycleVar<6;cycleVar++)"},			
				{"scanf(\"%f\",&array);"},					
				{"if(ifClause_variable==true)"},						
				{"result=operand_one+operandTwo;"},					
				{"return 0;"},
			{"}"}
		};//Исходный текст программы

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycle_var;"},
				{"char string_to_show[];"},
				{"bool if_clause_variable;"},
				{"float array[7];"},
				{"int operand_one,operand_two,result;"},
				{""},
				{"printf(\"%s\",string_to_show);"},					
				{"for(cycle_var=3;cycle_var<6;cycle_var++)"},			
				{"scanf(\"%f\",&array);"},					
				{"if(if_clause_variable==true)"},						
				{"result=operand_one+operand_two;"},					
				{"return 0;"},
			{"}"}
		};//Ожидаемый текст,после изменения функцией

		variables our_variables[F]={'\0'};	

		//act
		change_variables_to_snake_case(text,our_variables,15);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 4.Declarations and using.");
		CFIX_ASSERT(result==true);
	}

	void Test_text_with_functions_and_comments()
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int function1(int);"},
			{"bool isTrue(char};"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int actionOne;//actionOne - действие номер один"},
				{"char main_sym;// main_sym - main symbol"},
				{"isTrue(main_sym);"},
				{"//function1(actionOne);"},
				{"return 0;"},
			{"}"},
			{"int function1(int operandOne,int actionOne)//actionOne must be an action one"},
			{"{"},
				{""},
			{"}"},
			{"bool isTrue(char symbolTwo}//symbolTwoisvariable this string just to make a mix up"},
			{"{"},
				{""},
			{"}"}
		};//Исходный текст программы

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int function1(int);"},
			{"bool isTrue(char};"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int action_one;//action_one - действие номер один"},
				{"char main_sym;// main_sym - main symbol"},
				{"isTrue(main_sym);"},
				{"//function1(action_one);"},
				{"return 0;"},
			{"}"},
			{"int function1(int operand_one,int action_one)//action_one must be an action one"},
			{"{"},
				{""},
			{"}"},
			{"bool isTrue(char symbol_two}//symbolTwoisvariable this string just to make a mix up"},
			{"{"},
				{""},
			{"}"}
		};

		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,18);
		result=is_texts_equal(expectable_text,text);

		//assert
		CFIX_LOG("Test 5.Functions and comments.");
		CFIX_ASSERT(result==true);
	}


	void Test_empty_text()//Пустой текст
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{""},{""},{""},{""},{""}};

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]={{""},{""},{""},{""},{""}};
		
		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,5);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 6.Empty text.");
		CFIX_ASSERT(result==true);
	}

	void Test_spacer_text()//Текст состоит только из разделителей
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{"     "},{"  "},{"   "},{"         "},{" "}};

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]={{"     "},{"  "},{"   "},{"         "},{" "}};
		
		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,5);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 7.Spacer text.");
		CFIX_ASSERT(result==true);
	}
	

	void Test_many_vars_in_one_string()
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycleVar;"},
				{"char string_to_show[];"},
				{"bool ifClause_variable;"},
				{"float array[7];"},
				{"int operand_one,operandTwo,result;"},
				{"string_to_show = \"ifClause_variable\""},
				{"printf(\"%s\",string_to_show);"},					
				{"for(cycleVar=3;cycleVar<6;cycleVar++)"},			
				{"scanf(\"%f\",&array);"},					
				{"if(ifClause_variable==true && cycleVar=3 && operand_one && operandTwo)"},											
				{"return 0;"},
			{"}"}
		};//Исходный текст программы

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycle_var;"},
				{"char string_to_show[];"},
				{"bool if_clause_variable;"},
				{"float array[7];"},
				{"int operand_one,operand_two,result;"},
				{"string_to_show = \"ifClause_variable\""},
				{"printf(\"%s\",string_to_show);"},					
				{"for(cycle_var=3;cycle_var<6;cycle_var++)"},			
				{"scanf(\"%f\",&array);"},					
				{"if(if_clause_variable==true && cycle_var=3 && operand_one && operand_two)"},											
				{"return 0;"},
			{"}"}
		};//Ожидаемый текст,после изменения функцией

		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,14);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 8.Multiple using in string.");
		CFIX_ASSERT(result==true);
	}

	void Test_mixed_var_styles()
	{
		bool result = false;
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int Ex_Var_One;"},
				{"char exVarOne[];"},
				{"bool ExVarOne;"},
				{"float Ex_VarOne[7];"},
				{"int Ex_var_one,Ex_var_One123,_ExVar_EXA_Mple1e2;"},
				{"char *Example;"},
				{"unsigned int __varMore"},					
			{"}"}
		};//Исходный текст программы

		const char expectable_text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int ex_var_one;"},
				{"char ex_var_one[];"},
				{"bool ex_var_one;"},
				{"float ex_var_one[7];"},
				{"int ex_var_one,ex_var_one_123,_ex_var_e_x_a_mple_1e_2;"},
				{"char *example;"},
				{"unsigned int __var_more"},					
			{"}"}
		};//Ожидаемый текст,после изменения функцией

		variables our_variables[F]={'\0'};

		//act
		change_variables_to_snake_case(text,our_variables,10);
		result=is_texts_equal(expectable_text,text);
		
		//assert
		CFIX_LOG("Test 9.Special test with mixed up style variables.");
		CFIX_ASSERT(result==true);
	}
};

CFIXCC_BEGIN_CLASS(TestingChangeVariableToSnakeCase)
	CFIXCC_METHOD(Test_text_has_no_variable_to_change)
	CFIXCC_METHOD(Test_text_with_variables_already_in_snake_case)
	CFIXCC_METHOD(Test_text_with_variables_in_camel_case)
	CFIXCC_METHOD(Test_declaration_and_using)
	CFIXCC_METHOD(Test_text_with_functions_and_comments)
	CFIXCC_METHOD(Test_empty_text)
	CFIXCC_METHOD(Test_spacer_text)
	CFIXCC_METHOD(Test_many_vars_in_one_string)
	CFIXCC_METHOD(Test_mixed_var_styles)
CFIXCC_END_CLASS()

