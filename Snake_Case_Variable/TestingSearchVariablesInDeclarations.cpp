#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"


class TestingSearchVariablesInDeclarations : public cfixcc::TestFixture
{
private:
	/*
	*Функция проверяет два массива структур variables на равенство
	*\param [in] expected_variables - ожидаемый массив структур от теста
	*\param [in] our_variables	    - массив структур от тестируемой функции
	*\param [in] size				- количество элементов массива-размер массива
	*\return						- массивы структур равны или нет
	*/
	bool is_structures_equal(const struct variables* expected_variables,const struct variables* our_variables,int size)
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
	/*
	*Функция инициализирует массив структур,передаваемыми ей параметрами
	*\param [in|out] array_to_init			  - массив структур,который необходимо инициализировать
	*\param [in]	 name					  - массив имен из для структуры
	*\param [in]	 strings_to_find_pointers - номера строк текста(text) для поиска указателей
	*\param [in]	 text				      - текст содержащий имена(name)
	*\param [in]	 size					  - количество элементов массива структур
	*/
	void structure_initialization(struct variables* array_to_init,const char name[MAX_OF_STRINGS][MAX_VAR_NAME],const int strings_to_find_pointers[MAX_OF_STRINGS],char text[MAX_OF_STRINGS][MAX_IN_STRING],const int size)
	{
		int num_of_string;//Номер очередной строки в тексте
		int name_length;//Длина имени переменной
		int offset=0;//Смещение для поиска одинаковых имен в строке
		char* start;//Указатель на начало переменной
		for(int i=0;i<size;i++)
		{
			num_of_string=strings_to_find_pointers[i];//Задаем очередной номер строки
			array_to_init[i].text_string_number=num_of_string;
			strcpy(array_to_init[i].var_name,name[i]);//Копируем очередное имя в массив структур
			array_to_init[i].var_start=strstr(text[num_of_string],name[i]);//Копируем очередной указатель на переменную в массив структур
			if(strcmp(name[i-1],name[i])==0 && strings_to_find_pointers[i-1] == strings_to_find_pointers[i])//Если в одной строке несколько одинаковых имен переменных
			{
				name_length = strlen(name[i]);//Вычисляем длину имени
				start=strstr(text[num_of_string],name[i]);//Находим указатель на начало
				offset+=(start-array_to_init[i].var_start)+name_length;//Задаем смещение для поиска указателя
				array_to_init[i].var_start=strstr(text[num_of_string]+offset,name[i]);//Заносим указатель в массив структур
			}
		}
	}

public:
	///////////////////////////ТЕСТЫ ДЛЯ ФУНКЦИИ search_variables_in_declarations\\\\\\\\\\\\\/
	void Test_empty_text_for_declarations()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{""},{""},{""},{""},{""},{""}};
		
		variables our_variables[6]={'\0'};
		variables expected_variables[6]={'\0'};
		int size=0;

		//act
		int quantity = search_variables_in_declarations(text,our_variables,6);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 1.Empty text.");
		CFIX_ASSERT(size == quantity && result == true);
	}

	void Test_spacer_text_for_declarations()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{"     "},{"    "},{"    "},{"    "},{"   "},{"    "}};
		

		variables our_variables[6]={'\0'};
		variables expected_variables[6]={'\0'};
		int size=0;

		//act
		int quantity = search_variables_in_declarations(text,our_variables,6);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 2.Spacer text.");
		CFIX_ASSERT(size==quantity);
	}

	void Test_one_declaration_in_one_string()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int spareLineIndex;"},
				{"char separatorsNumbers[5];"},
				{" "},
				{"printf(\"Hello World\");"},
				{"bool isTrue;"},
				{"return 0;"},
			{"}"}
		};
		
		variables our_variables[4]={'\0'};
		variables expected_variables[4]={'\0'};
		int size=4;

		char var_names[4][MAX_VAR_NAME]={{"argc"},{"spareLineIndex"},{"separatorsNumbers"},{"isTrue"}};
		int strings[4]={0,2,3,6};
		structure_initialization(expected_variables,var_names,strings,text,size);
		
		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);
		

		//assert
		CFIX_LOG("Test 3.One declaration in one string.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_many_declarations_in_one_string()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"float twoDimensional,threeDimensional,secondLongTwo;"},
				{"double firstNum,secondNum;"},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};

		variables our_variables[6]={'\0'};
		variables expected_variables[6]={'\0'};
		int size=6;
		
		char var_names[6][MAX_VAR_NAME]={{"argc"},{"twoDimensional"},{"threeDimensional"},{"secondLongTwo"},{"firstNum"},{"secondNum"}};
		int strings[6]={0,2,2,2,3,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 4.Multiple declarations.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_declaration_with_simple_initialization()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"float twoDimensional=32.3,threeDimensional=12.5,secondLongTwo;"},
				{"char firstSring[]=\"Hello\""},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};

		variables our_variables[5]={'\0'};
		variables expected_variables[5]={'\0'};
		int size=5;
		
		char var_names[5][MAX_VAR_NAME]={{"argc"},{"twoDimensional"},{"threeDimensional"},{"secondLongTwo"},{"firstSring"}};
		int strings[5]={0,2,2,2,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 5.Declaration with simple initialization.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_commented_declaration()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"//signed int whatIsIt;"},
				{"//long double firstLongValue;"},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};

		variables our_variables[1]={'\0'};
		variables expected_variables[1]={'\0'};
		int size=1;
		
		char var_names[1][MAX_VAR_NAME]={{"argc"}};
		int strings[1]={0};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 6.Commented declaration.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_function_in_text()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int sampleFunction(int ,char );"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"signed short int verySmall;"},
				{"unsigned short int longValue;"},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"},
			{""},
			{"int sampleFunction(int firstNum,char spacer)"},
			{"{"},
			{""},
			{"}"}
		};

		variables our_variables[5]={'\0'};
		variables expected_variables[5]={'\0'};
		int size=5;

		char var_names[5][MAX_VAR_NAME]={{"argc"},{"verySmall"},{"longValue"},{"firstNum"},{"spacer"}};
		int strings[5]={1,3,4,11,11};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,15);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 7.Declaration in function.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_same_name_of_function_and_variable()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int doOperation(int ,char );"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"long int superLong;"},
				{"unsigned int longestValue;"},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"},
			{""},
			{"int doOperation(int doOperation,char spacer)"},
			{"{"},
			{""},
			{"}"}
		};

		variables our_variables[5]={'\0'};
		variables expected_variables[5]={'\0'};
		int size=5;
		
		char var_names[5][MAX_VAR_NAME]={{"argc"},{"superLong"},{"longestValue"},{"doOperation"},{"spacer"}};
		int strings[5]={1,3,4,11,11};
		structure_initialization(expected_variables,var_names,strings,text,size);
		expected_variables[3].var_start=strstr(text[11]+12,"doOperation");

		//act
		int quantity = search_variables_in_declarations(text,our_variables,15);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 8.Same name of function and variable.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_spacers_between_type_and_name()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"unsigned long int      shortValue;"},
				{"signed long int   shortValueTwo;"},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};
							
		variables our_variables[3]={'\0'};
		variables expected_variables[3]={'\0'};
		int size=3;

		char var_names[3][MAX_VAR_NAME]={{"argc"},{"shortValue"},{"shortValueTwo"}};
		int strings[3]={0,2,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,8);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 9.Spacers between type and name.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_declaration_and_using()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycleVar;"},
				{"char stringToShow[];"},
				{"bool ifClauseVariable;"},
				{"float arrayNumbers[7];"},
				{"int operandOne,operandTwo,result;"},
				{""},
				{"printf(\"%s\",stringToShow);"},					//Проверяем использование в функции вывода
				{"for(cycleVar=3;cycleVar<6;cycleVar++)"},			//Проверяем использование в цикле
				{"scanf(\"%f\",&arrayNumbers);"},					//Проверяем использование в функции ввода
				{"if(ifClauseVariable==true)"},						//Проверяем использование в условии
				{"result=operandOne+operandTwo;"},					//Проверяем использование в выражении
				{"return 0;"},
			{"}"}
		};//Исходный текст программы

		variables our_variables[8]={'\0'};
		variables expected_variables[8]={'\0'};
		int size=8;

		char var_names[8][MAX_VAR_NAME]={{"argc"},{"cycleVar"},{"stringToShow"},{"ifClauseVariable"},{"arrayNumbers"},{"operandOne"},{"operandTwo"},{"result"}};
		int strings[8]={0,2,3,4,5,6,6,6};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,15);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 10.Declaration and using.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_declaration_with_complicated_initialization()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int sampleFunction(int ,char );"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int array_of_numbers[5]={};"},
				{"int twoDimensional=array_of_numbers[3];"},
				{"int threeDimensional=sampleFunction(3,' ');"},
				{"int secondLongTwo=twoDimensional+threeDimensional;"},
				{""},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"},
			{""},
			{"int sampleFunction(int firstNum,char spacer)"},
			{"{"},
			{""},
			{"}"}
		};

		variables our_variables[7]={'\0'};
		variables expected_variables[7]={'\0'};
		int size=7;
		
		char var_names[7][MAX_VAR_NAME]={{"argc"},{"array_of_numbers"},{"twoDimensional"},{"threeDimensional"},{"secondLongTwo"},{"firstNum"},{"spacer"}};
		int strings[7]={1,3,4,5,6,13,13};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,17);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 11.Declaration with complicated initialization.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_tabulation_between_type_and_name()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"float      shortValue;"},
				{"short int      shortValueTwo;"},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};
							
		variables our_variables[3]={'\0'};
		variables expected_variables[3]={'\0'};
		int size=3;
		
		char var_names[3][MAX_VAR_NAME]={{"argc"},{"shortValue"},{"shortValueTwo"}};
		int strings[3]={0,2,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,8);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 12.Tabulation between type and name.");
		CFIX_ASSERT(result==true && size == quantity);
	}
	void Test_spacers_before_var_type()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"   float shortValue;"},
				{"		long int   shortValueTwo;"},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};
							
		variables our_variables[3]={'\0'};
		variables expected_variables[3]={'\0'};
		int size=3;
		
		char var_names[3][MAX_VAR_NAME]={{"argc"},{"shortValue"},{"shortValueTwo"}};
		int strings[3]={0,2,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,8);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 13.Spacers before var type.");
		CFIX_ASSERT(result==true && size == quantity);
	}

	void Test_declaration_in_cycle()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"bool ifClauseVariable[5];"},
				{""},					
				{"for(int cycleVar=3;cycleVar<6;cycleVar++)"},			
					{"scanf(\"%f\",&ifClauseVariable);"},										
				{"return 0;"},
			{"}"}
		};//Исходный текст программы

		variables our_variables[3]={'\0'};
		variables expected_variables[3]={'\0'};
		int size=3;

		char var_names[3][MAX_VAR_NAME]={{"argc"},{"ifClauseVariable"},{"cycleVar"}};
		int strings[3]={0,2,4};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,8);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 14.Declaration in cycle.");
		CFIX_ASSERT(result==true && size == quantity);
	}


	void Test_declaration_with_string_const()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"char verySmall[5][7] = {{\"toughVar\"},{\"int\"},{\"int one\"},{\"213\"},{\" \"}};"},
				{"char oneString[] = \"bool templateVar\";"},
				{"char *stringVar;"},
				{"printf(\"Hello World\");"},
				{""},
				{"return 0;"},
			{"}"}
		};

		variables our_variables[4]={'\0'};
		variables expected_variables[4]={'\0'};
		int size=4;

		char var_names[4][MAX_VAR_NAME]={{"argc"},{"verySmall"},{"oneString"},{"stringVar"}};
		int strings[4]={0,2,3,4};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 15.Declaration with string const.");
		CFIX_ASSERT(result==true && size == quantity);
	}


	void Test_special_test_for_comments()
	{
		//arrange
		bool result = false;
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int  whatIsIt;//int varOne"},
				{"char firstLongValue;//double fight,toDo"},
				{""},
				{"printf(\"Hello World\");//int varOne"},
				{"int func(int,char)//bool focusLeft"},
				{"return 0;"},
			{"}"}
		};

		variables our_variables[3]={'\0'};
		variables expected_variables[3]={'\0'};
		int size=3;
		
		char var_names[3][MAX_VAR_NAME]={{"argc"},{"whatIsIt"},{"firstLongValue"}};
		int strings[3]={0,2,3};
		structure_initialization(expected_variables,var_names,strings,text,size);

		//act
		int quantity = search_variables_in_declarations(text,our_variables,9);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 16.Special test for comments.");
		CFIX_ASSERT(result==true && size == quantity);
	}
	

};

CFIXCC_BEGIN_CLASS(TestingSearchVariablesInDeclarations)
	CFIXCC_METHOD(Test_empty_text_for_declarations)
	CFIXCC_METHOD(Test_spacer_text_for_declarations)
	CFIXCC_METHOD(Test_one_declaration_in_one_string)
	CFIXCC_METHOD(Test_many_declarations_in_one_string)
	CFIXCC_METHOD(Test_declaration_with_simple_initialization)
	CFIXCC_METHOD(Test_commented_declaration)
	CFIXCC_METHOD(Test_function_in_text)
	CFIXCC_METHOD(Test_same_name_of_function_and_variable)
	CFIXCC_METHOD(Test_spacers_between_type_and_name)
	CFIXCC_METHOD(Test_declaration_and_using)
	CFIXCC_METHOD(Test_declaration_with_complicated_initialization)
	CFIXCC_METHOD(Test_tabulation_between_type_and_name)
	CFIXCC_METHOD(Test_spacers_before_var_type)
	CFIXCC_METHOD(Test_declaration_in_cycle)
	CFIXCC_METHOD(Test_declaration_with_string_const)
	CFIXCC_METHOD(Test_special_test_for_comments)
CFIXCC_END_CLASS()

