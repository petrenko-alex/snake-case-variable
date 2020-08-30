#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"
#include <string.h>
class TestingIsSnakeCase : public cfixcc::TestFixture
{
private:

public:
	//////////////////////////“≈—“€ ƒÀﬂ ‘”Õ ÷»» is_snake_case\\\\\\\\\\\\\\\\\\\\\\\\\\\/
	void Test_already_snake_case()
	{
		//arrange
		const char str[MAX_VAR_NAME]="testing_var_one";
		bool result = false;

		//act
		result = is_snake_case(str);

		//assert
		CFIX_LOG("Test 1.Variable is already in snake case.");
		CFIX_ASSERT(result==true);
	}

	void Test_not_snake_case()
	{
		//arrange
		const char str[MAX_VAR_NAME]="testingVarOne";
		bool result = false;

		//act
		result = is_snake_case(str);

		//assert
		CFIX_LOG("Test 2.Variable is in camel case.");
		CFIX_ASSERT(result==false);
	}

	void Test_not_snake_case_but_mixed_style()
	{
		//arrange
		const char str[MAX_VAR_NAME]="specialVariable_for_testing";
		bool result = false;

		//act
		result = is_snake_case(str);

		//assert
		CFIX_LOG("Test 3.Variable is in mixed style.");
		CFIX_ASSERT(result==false);
	}

	void Test_check_variable_with_digits()
	{
		//arrange
		const char str[MAX_VAR_NAME]="exampleVarNumber123";
		bool result = false;

		//act
		result = is_snake_case(str);

		//assert
		CFIX_LOG("Test 4.Variable is in camel case with digits.");
		CFIX_ASSERT(result==false);
	}

	void Test_starts_with_upper()
	{
		//arrange
		const char str[MAX_VAR_NAME]="ExampleVar";
		bool result = false;

		//act
		result = is_snake_case(str);

		//assert
		CFIX_LOG("Test 5.Variable's name starts with upper.");
		CFIX_ASSERT(result==false);
	}


};

CFIXCC_BEGIN_CLASS(TestingIsSnakeCase)
	CFIXCC_METHOD(Test_already_snake_case)
	CFIXCC_METHOD(Test_not_snake_case)
	CFIXCC_METHOD(Test_not_snake_case_but_mixed_style)
	CFIXCC_METHOD(Test_check_variable_with_digits)
	CFIXCC_METHOD(Test_starts_with_upper)
CFIXCC_END_CLASS()

