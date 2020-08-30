#include "StdAfx.h"
#include <cfixcc.h>
#include "ChangingToSnakeCase.h"

class TestingSearchVariablesInUsing : public cfixcc::TestFixture
{
private:
	/*
	*Функция проверяет два массива структур variables на равенство
	*\param [in] expected_variables - ожидаемый массив структур от теста
	*\param [in] our_variables		- массив структур от тестируемой функции
	*\param [in] size				- количество элементов массива-размер массива
	*\return						- массивы структур равны или нет
	*/
	bool is_structures_equal(const struct variables* expected_variables,const struct variables* our_variables,int size)
	{
		size--;
		int name_equal=0;
		int start_equal=0;

		for(int i=0;i<=size;i++)
		{
			int name_equal = strcmp(our_variables[i].var_name,expected_variables[i].var_name);//Сравниваем имена переменных
			
			if(our_variables[i].var_start)
				int start_equal = strcmp(our_variables[i].var_start,expected_variables[i].var_start);//Сравниваем указатели на начало
			else
				return false;
			if(name_equal!=0 || start_equal!=0)
				return false;
		}
		return true;
	}
	/*
	*Функция инициализирует массив структур,передаваемыми ей параметрами
	*\param [in|out] array_to_init			  - массив структур,который необходимо инициализировать
	*\param [in]	 name					  - массив имен из для структуры
	*\param [in]	 strings_to_find_pointers - номера строк текста(text) для поиска указателей
	*\param [in]	 text					  - текст содержащий имена(name)
	*\param [in]	 size					  - количество элементов массива структур
	*/
	void structure_initialization(struct variables* array_to_init,const char name[MAX_OF_STRINGS][MAX_VAR_NAME],const int strings_to_find_pointers[MAX_OF_STRINGS],char text[MAX_OF_STRINGS][MAX_IN_STRING],const int size)
	{
		int num_of_string;				//Номер очередной строки в тексте
		int name_length;				//Длина имени переменной
		int offset=0;					//Смещение для поиска одинаковых имен в строке
		char* start;					//Указатель на начало переменной
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
	///////////////////////////////ТЕСТЫ ДЛЯ ФУНКЦИИ search_variable_in_using\\\\\\\\\\\\\\\\\\\\\\\\\\\/
	void Test_empty_text_for_using()
	{
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{""},{""},{""},{""},{""},{""}};
		
		const int strings = 6;
		const int size=0;
		bool result = false;
		variables our_variables[strings]={'\0'};
		variables expected_variables[strings]={'\0'};
		
		//act
		int quantity = search_variables_in_using(text,our_variables,0,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 1.Empty text.");
		CFIX_ASSERT(size==quantity && result==true);
	}

	void Test_spacer_text_for_using()
	{
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]={{"     "},{"    "},{"    "},{"    "},{"   "},{"    "}};
		
		const int strings = 6;
		const int size = 0;
		bool result = false;
		variables our_variables[strings]={'\0'};
		variables expected_variables[strings]={'\0'};
		
		//act
		int quantity = search_variables_in_using(text,our_variables,0,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 2.Spacer text.");
		CFIX_ASSERT(size==quantity && result==true);
	}

	
	void Test_complex_using_after_declaration()
	{
		//arrange
		//Исходный текст программы
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycleVar=1;"},
				{"char stringToShow[]={};"},
				{"bool ifClauseVariable=true;"},
				{"float arrayNumbers[7]={};"},
				{"int operandOne=3,operandTwo=5,result=0;"},
				{""},
				{"printf(\"%s\",stringToShow);"},					//Проверяем использование в функции вывода
				{"for(cycleVar=3;cycleVar<6;cycleVar++)"},			//Проверяем использование в цикле
				{"scanf(\"%f\",&arrayNumbers);"},					//Проверяем использование в функции ввода
				{"if(ifClauseVariable==true)"},						//Проверяем использование в условии
				{"result=operandOne+operandTwo;"},					//Проверяем использование в выражении
				{"return 0;"},
			{"}"}
		};
		
		const int size = 17;
		const int strings = 15;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
		
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"cycleVar"},{"stringToShow"},{"ifClauseVariable"},{"arrayNumbers"},{"operandOne"},{"operandTwo"},{"result"},
		{"stringToShow"},{"cycleVar"},{"cycleVar"},{"cycleVar"},{"arrayNumbers"},{"ifClauseVariable"},{"operandOne"},{"operandTwo"},{"result"}};
		int strings_expected[size]={0,2,3,4,5,6,6,6,8,9,9,9,10,11,12,12,12};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);

		//act
		int quantity = search_variables_in_using(text,our_variables,8,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 3.Complex using after declaration.");
		CFIX_ASSERT(result==true && size==quantity);
	}
	
	void Test_using_in_functions()
	{
		//arrange
		//Исходный текст программы
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int function1(int,int);"},
			{"bool isTrue(char,char};"},
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int actionOne;"},
				{"int actionTwo;"},
				{"char mainSym;"},
				{"char generalTrue;"},
				{"isTrue(mainSym,generalTrue);"},
				{"function1(actionOne,actionTwo);"},
				{"return 0;"},
			{"}"},
			{"int function1(int operandOne,int operandTwo)"},
			{"{"},
				{""},
			{"}"},
			{"bool isTrue(char symbol,char main)"},
			{"{"},
				{""},
			{"}"}
		};
		
		const int strings = 20;
		const int size = 13;
		bool result = false;
		//Массивы переменных
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
			
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"actionOne"},{"actionTwo"},{"mainSym"},{"generalTrue"},{"operandOne"},{"operandTwo"},{"symbol"},{"main"},
		{"mainSym"},{"generalTrue"},{"actionOne"},{"actionTwo"}};
		int strings_expected[size]={2,4,5,6,7,12,12,16,16,8,8,9,9};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);
		
		//act
		int quantity = search_variables_in_using(text,our_variables,9,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 4.Using in functions.");
		CFIX_ASSERT(result==true && size==quantity);
	}

	void Test_using_in_comments()
	{
		//arrange
		//Исходный текст программы
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int actionOne;//int actionOne"},
				{"int actionTwo;//mainSym"},
				{"char mainSym;//generalTrue"},
				{"char generalTrue;//mainSym"},
				{""},
				{"return 0;"},
			{"}"}
		};

		const int size = 9 ;
		const int strings = 9;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
		
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"actionOne"},{"actionTwo"},{"mainSym"},{"generalTrue"},{"actionOne"},{"mainSym"},{"generalTrue"},{"mainSym"}};
		int strings_expected[size]={0,2,3,4,5,2,3,4,5};
		
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);
		expected_variables[5].var_start=strstr(text[2]+12,"actionOne");

		//act
		int quantity = search_variables_in_using(text,our_variables,5,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 5.Using in comments.");
		CFIX_ASSERT(result==true && size==quantity);
	}

	void Test_using_in_cycle()
	{
		//arrange
		//Исходный текст программы
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int cycleVar;"},
				{"int arrayNumbers[5]"},
				{"for(cycleVar=3;cycleVar<6;cycleVar++)"},			
					{"scanf(\"%f\",&arrayNumbers);"},								
				{"return 0;"},
			{"}"}
		};
		
		const int size=7;
		const int strings=8;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
		
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"cycleVar"},{"arrayNumbers"},{"cycleVar"},{"cycleVar"},{"cycleVar"},{"arrayNumbers"}};
		int strings_expected[size]={0,2,3,4,4,4,5};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);

		//act
		int quantity = search_variables_in_using(text,our_variables,3,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 6.Using in cycle.");
		CFIX_ASSERT(result==true && size==quantity);
	}
	
	void Test_using_in_input_and_otput()
	{
		//arrange
		//Исходный текст программы
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"char stringToShow[];"},
				{"scanf(\"%f\",&stringToShow);"},
				{"printf(\"%s\",stringToShow);"},										
				{"return 0;"},
			{"}"}
		};
		
		const int size = 4;
		const int strings = 7;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
		
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"stringToShow"},{"stringToShow"},{"stringToShow"}};
		int strings_expected[size]={0,2,3,4};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);

		//act
		int quantity = search_variables_in_using(text,our_variables,2,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 7.Using in input and output.");
		CFIX_ASSERT(result==true && size==quantity);
	}

	void Test_using_in_if()
	{
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"bool ifClauseVariable;"},
				{""},
				{"if(ifClauseVariable==true)"},						
				{"return 0;"},
			{"}"}
		};//Исходный текст программы
		
		const int size = 3;
		const int strings = 7;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
		
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"ifClauseVariable"},{"ifClauseVariable"}};
		int strings_expected[size]={0,2,4};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);

		//act
		int quantity = search_variables_in_using(text,our_variables,2,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 8.VUsing in IF - clause.");
		CFIX_ASSERT(result==true && size==quantity);
	}

	void Test_using_in_operation()
	{
		//arrange
		char text[MAX_OF_STRINGS][MAX_IN_STRING]=
		{
			{"int _tmain(int argc, _TCHAR* argv[])"},
			{"{"},
				{"int operandOne=5,operandTwo=3,result=0;"},
				{""},
				{"result=operandOne+operandTwo;"},					
				{"return 0;"},
			{"}"}
		};//Исходный текст программы
	
		const int size = 7;
		const int strings = 7;
		bool result = false;
		variables our_variables[size]={'\0'};
		variables expected_variables[size]={'\0'};
			
		//Подготавливаем массив перед использованием в функции
		search_variables_in_declarations(text,our_variables,strings);
		
		char var_names_expected[size][MAX_VAR_NAME]={{"argc"},{"operandOne"},{"operandTwo"},{"result"},{"operandOne"},{"operandTwo"},{"result"}};
		int strings_expected[size]={0,2,2,2,4,4,4};
		structure_initialization(expected_variables,var_names_expected,strings_expected,text,size);

		//act
		int quantity = search_variables_in_using(text,our_variables,4,strings);
		result=is_structures_equal(expected_variables,our_variables,size);

		//assert
		CFIX_LOG("Test 9.Using in operations.");
		CFIX_ASSERT(result==true && size==quantity);
	}
};

CFIXCC_BEGIN_CLASS(TestingSearchVariablesInUsing)
	CFIXCC_METHOD(Test_empty_text_for_using)
	CFIXCC_METHOD(Test_spacer_text_for_using)
	CFIXCC_METHOD(Test_complex_using_after_declaration)
	CFIXCC_METHOD(Test_using_in_functions)
	CFIXCC_METHOD(Test_using_in_comments)
	CFIXCC_METHOD(Test_using_in_cycle)
	CFIXCC_METHOD(Test_using_in_input_and_otput)
	CFIXCC_METHOD(Test_using_in_if)
	CFIXCC_METHOD(Test_using_in_operation)
CFIXCC_END_CLASS()

