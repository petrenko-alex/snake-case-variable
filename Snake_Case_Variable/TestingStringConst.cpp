#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"


class TestingStringConst : public cfixcc::TestFixture
{
private:

public:
	void Test_string_intialization()
	{
		//arrange
		char str[]="char string=\"This is an example text\"";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 1.Single sting const.");
		CFIX_ASSERT(positions[0]==12 && positions[1]==36);
	}
	
	void Test_array_intialization()
	{
		//arrange
		char str[]="char array[3]={{\"one\"},{\"two\"},{\"three\"}};";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 2.Array of string consts.");
		CFIX_ASSERT(positions[0]==16 && positions[1]==20);
	}

	void Test_printf()
	{
		//arrange
		char str[]="printf(\"This is an example text\");";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 3.String const inside printf.");
		CFIX_ASSERT(positions[0]==7 && positions[1]==31);
	}

	void Test_printf_with_format()
	{
		//arrange
		char str[]="printf(\"%d or %f\",integer,real);";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 4.String const inside formated prntf.");
		CFIX_ASSERT(positions[0]==7 && positions[1]==16);
	}
	
	void Test_commas_inside()
	{
		//arrange
		char str[]="char string=\"example-\\\"various\\\" is right\";";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 5.String const with commas inside.");
		CFIX_ASSERT(positions[0]==12 && positions[1]==41);
	}
	
	void Test_comment()
	{
		//arrange
		char str[]="int number;//because \"number\" is correct";
		int positions[2]={};

		//act
		string_const(str,positions);
		
		//assert
		CFIX_LOG("Test 6.String const in comment.");
		CFIX_ASSERT(positions[0]==21 && positions[1]==28);
	}


	void Test_no_commas()
	{
		//arrange
		char str[] = "int number,number_one,number_two;";
		int positions[2]={};
		
		//act
		string_const(str,positions);

		//assert
		CFIX_LOG("Test 7.There is no string const.");
		CFIX_ASSERT(positions[0] == 0 && positions[1] == 0);
	}

};

CFIXCC_BEGIN_CLASS(TestingStringConst)
	CFIXCC_METHOD(Test_string_intialization)
	CFIXCC_METHOD(Test_array_intialization)
	CFIXCC_METHOD(Test_printf)
	CFIXCC_METHOD(Test_printf_with_format)
	CFIXCC_METHOD(Test_commas_inside)
	CFIXCC_METHOD(Test_comment)
	CFIXCC_METHOD(Test_no_commas)
CFIXCC_END_CLASS()

