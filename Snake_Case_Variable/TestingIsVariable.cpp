#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"


class isVariableTesting : public cfixcc::TestFixture
{
private:

public:
	/////////////////////“≈—“€ ƒÀﬂ ‘”Õ ÷»» is_variable\\\\\\\\\\\\\\\\\\\\\\\\\\\/
	void Test_not_variable_but_typical_function_name()
	{
		//arrange
		const char str[]="exampleFunction(int a,char b,bool isIt)";
		
		//act
		int result = is_variable(str);

		//asser
		CFIX_LOG("Test 1.Typical function's name.");
		CFIX_ASSERT(result==15);
	}

	void Test_not_variable_but_function_name_without_parametres()
	{
		//arrange
		const char str[]="exampleFunction()";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 2.Function's name without parametres.");
		CFIX_ASSERT(result==15);
	}

	void Test_not_variable_but_function_name_as_prototype()
	{
		//arrange
		const char str[]="exampleFunction(int,char,long double);";
		
		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 3.Function's name as prototype.");
		CFIX_ASSERT(result==15);
	}


	void Test_one_word_variable()
	{
		//arrange
		const char str[]="variable";
		
		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 4.One word variable's name.");
		CFIX_ASSERT(result<0);
	}

	void Test_one_word_variable_with_digits()
	{
		//arrange
		const char str[]="var853";
		
		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 5.One word variable's name withdigits.");
		CFIX_ASSERT(result<0);
	}

	void Test_variable_in_snake_case()
	{
		//arrange
		const char str[]="example_variable_one";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 6.Variable's name in snake case.");
		CFIX_ASSERT(result<0);
	}

	void Test_variable_in_camel_case()
	{
		//arrange
		const char str[]="exampleVariableOne";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 7.Variable's name in camel case.");
		CFIX_ASSERT(result<0);
	}

	void Test_mix_style_variable()
	{
		//arrange
		const char str[]="exampleVariable_one";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 8.Variable's name in mixed style.");
		CFIX_ASSERT(result<0);
	}

	void Test_variable_with_digits()
	{
		//arrange
		const char str[]="exVar94";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 9.Variable's name in mixed style with digits.");
		CFIX_ASSERT(result<0);
	}

	void Test_inside_function()
	{
		//arrange
		const char str[] = "int a,int f,bool isStr)";

		//act
		int result = is_variable(str);

		//assert
		CFIX_LOG("Test 10.Variable's name as function's parameter.");
		CFIX_ASSERT(result<0);
	}
};

CFIXCC_BEGIN_CLASS(isVariableTesting)
	CFIXCC_METHOD(Test_not_variable_but_typical_function_name)
	CFIXCC_METHOD(Test_not_variable_but_function_name_without_parametres)
	CFIXCC_METHOD(Test_not_variable_but_function_name_as_prototype)
	CFIXCC_METHOD(Test_one_word_variable)
	CFIXCC_METHOD(Test_one_word_variable_with_digits)
	CFIXCC_METHOD(Test_variable_in_snake_case)
	CFIXCC_METHOD(Test_variable_in_camel_case)
	CFIXCC_METHOD(Test_mix_style_variable)
	CFIXCC_METHOD(Test_variable_with_digits)
	CFIXCC_METHOD(Test_inside_function)
CFIXCC_END_CLASS()

