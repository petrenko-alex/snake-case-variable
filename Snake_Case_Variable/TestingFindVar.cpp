#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"

class TestingFindVar : public cfixcc::TestFixture
{
private:

public:
	void Test_number_one()
	{
		//arrange
		char str[]="bool isRight;//int varOne";
		int start_pos = -100;
		const int com_pos = 13;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 1.Var type - +int+ will be finded first.But need to find +bool+.");
		CFIX_ASSERT(start_pos == 5);
	}


	void Test_number_two()
	{
		//arrange
		char str[]="int isRight;//bool varOne";
		int start_pos = -100;
		const int com_pos = 12;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 2.Var type - +int+ will be finded first.And dont need to find +bool+.");
		CFIX_ASSERT(start_pos == 4);
	}
	
	void Test_no_start_pos()
	{
		//arrange
		char str[]="//bool varOne,int varTwo,char string[5]={};";
		int start_pos = -100;
		const int com_pos = 0;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 3.The sting is commented,so function must return -1.");
		CFIX_ASSERT(start_pos == -1);
	}
	
	void Test_string_const()
	{
		//arrange
		char str[]="char string = \"int varOne\"";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 4.String const in string.Dont need to find it.");
		CFIX_ASSERT(start_pos == 5);
	}

	void Test_string_array()
	{
		//arrange
		char str[]="char string[5][15] = {{\"varieto\"},{\"signed long int varOne\"},{\"int varTwo\"}};";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 5.Array of string const.Need to find only +char+.");
		CFIX_ASSERT(start_pos == 5);
	}

	void Test_simple_var()
	{
		//arrange
		char str[]="int varOne;";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 6.Simple declaration.");
		CFIX_ASSERT(start_pos == 4);
	}

	void Test_simple_func()
	{
		//arrange
		char str[]="bool func1(int air,int boom)";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 7.Simple function.Need to find min - +bool+.");
		CFIX_ASSERT(start_pos == 5);
	}


	void Test_multiple_declaration()
	{
		//arrange
		char str[]="signed int arrangeOne,arrangeTwo,array,stringConst.";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 8.Multiple declaration.Need to find first var name.");
		CFIX_ASSERT(start_pos == 11);
	}

	void Test_func_with_unnamed_param()
	{
		//arrange
		char str[]="bool func1(char,int );";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 9.Function with unnamed parametres.Need to find +bool+.");
		CFIX_ASSERT(start_pos == 5);
	}

	void Test_var_name_starts_with_()
	{
		//arrange
		char str[]="signed int _srecialVar;";
		int start_pos = -100;
		const int com_pos = 1000;

		//act
		start_pos = find_var(str,com_pos);
		
		//assert
		CFIX_LOG("Test 10.Var name starts with symbol +_+.Need to find letter after this symbol.");
		CFIX_ASSERT(start_pos == 12);
	}
};

CFIXCC_BEGIN_CLASS(TestingFindVar)
	CFIXCC_METHOD(Test_number_one)
	CFIXCC_METHOD(Test_number_two)
	CFIXCC_METHOD(Test_no_start_pos)
	CFIXCC_METHOD(Test_string_const)
	CFIXCC_METHOD(Test_string_array)
	CFIXCC_METHOD(Test_simple_var)
	CFIXCC_METHOD(Test_simple_func)
	CFIXCC_METHOD(Test_multiple_declaration)
	CFIXCC_METHOD(Test_func_with_unnamed_param)
	CFIXCC_METHOD(Test_var_name_starts_with_)
CFIXCC_END_CLASS()

