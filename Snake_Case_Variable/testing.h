///Starting for autotesting - use following environment variables
//testingmode: testing mode
// * blackbox - console standard io streams testing, 
// * unittesting - unit testing
//locale - desired locale (i.e. .866 for russian console or FAR runs, .1251 for russian autotester or visual studio runs)
//testingtime - time of testing in seconds (default 1 second)
#include <conio.h>
#include <string.h>
#include <stdlib.h>
#include <locale.h>
#define _PROGRAM_RUN_FOR_TOO_LONG "Программа выполняется более отведенного лимита в %.2f секунд"
#define _NO_UNIT_TESTS "NUnit-тесты не подключены или подключены неверно"

#ifdef _WIN32
////Start of Microsoft Visual Studio  section
//Please move all Windows/Microsoft Visual Studio - specific code there once it will be discovered
//Look for examples below
#include <crtdbg.h>
#include <windows.h> //Sorry, there is no CRTL equivalent of Sleep function, and _beginthread isn't platform independent too
///INTERFACE: function that redirect all error reports to stdout so they will appear as testing results
void __SendErrorsToStdout(void)
{
	_CrtSetReportMode(_CRT_WARN, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_WARN, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ERROR, _CRTDBG_FILE_STDOUT);
	_CrtSetReportMode(_CRT_ASSERT, _CRTDBG_MODE_FILE);
	_CrtSetReportFile(_CRT_ASSERT, _CRTDBG_FILE_STDOUT);
}
///Thread function to run thread that will stop program after defined time
DWORD WINAPI __TimerThread(LPVOID arg)
{
	
	float *ptr=(float *)arg;
	float sec_to_wait=*ptr;
	free(ptr);
	Sleep((DWORD)sec_to_wait*1000);
	printf(_PROGRAM_RUN_FOR_TOO_LONG,sec_to_wait);
	fflush(stdout);
	exit(1);
}
///INTERFACE: function to start thread to stop program after defined time
void __RunTimerThread(float time)
{
	float *sec_to_wait=(float *)malloc(sizeof(float));
	*sec_to_wait=time;
	CreateThread(NULL,0,__TimerThread,(LPVOID)sec_to_wait,0,0);

}
////End of Microsoft Visual Studio section
#endif


#define TESTING

int __Messages=1;

//Class to run necessary code before main() will get executed
class __RunFirst
{
public:
	__RunFirst(void)
	{
		char * testingmode = getenv("testingmode");
		if (testingmode != NULL && !strcmp(testingmode,"blackbox"))
			__Messages = 0;

		if(testingmode != NULL) //Send errors to stdout in any automatic testing mode
		{
			__SendErrorsToStdout();
		}
		//Setting locale
		//When running from command line (FAR, etc) execute  set locale=.866   before running program.
		char * locale = getenv("locale");
		if(locale != NULL)
			setlocale(LC_ALL, locale);
		else
			setlocale(LC_ALL, ".1251");

		//Set numeric locale to english so period will be used as decimal separator.
		setlocale(LC_NUMERIC,"English");

		if (testingmode != NULL && !strcmp(testingmode,"unittesting"))
		{
			#ifdef STRUNIT_TEST

				//Secure strcat and strcpy macros
				#define strcat secure_strcat
				#define strcpy secure_strcpy


				//1
				_1_selectWords = selectWords;
				_1_findWord = findWord;

				//2
				_2_textToWords = textToWords;
				_2_strToWords = strToWords;

				//3
				_3_crossStrings = crossStrings;
				_3_strToWords = strToWords;

				//4
				_4_delCharacters = delCharacters;
				_4_cutString = cutString;

				//5
				_5_textToWords = textToWords;
				_5_textLength = textLength;

				//6
				_6_getNumbers = getNumbers;
				_6_findInteger = findInteger;

				//7
				_7_sortByStringLength = sortByStringLength;

				//8
				_8_insertString = insertString;
				_8_findCharInText = findCharInText;

				//9
				_9_findPairBrackets = findPairBrackets;

				//10
				_10_markWords = markWords;
				_10_searchWord = searchWord;
				_10_slideString = slideString;

				//11
				_11_deleteBlanks = deleteBlanks;

				//12
				_12_markWords = markWords;

				//13
				_13_searchString = searchString;
				_13_slideStringList = slideStringList;

				//14
				_14_countWordsByLetter = countWordsByLetter;

				//15
				_15_strToWords = strToWords;
				_15_compareByContents = compareByContents;

				//16
				_16_strToWords = strToWords;
				_16_selectWords = selectWords;

				//17
				_17_reverseWords = reverseWords;

				//18
				_18_deleteWords = deleteWords;

				//19
				_19_toMorseCode = toMorseCode;
				_19_strToMorse = strToMorse;

				//20
				_20_searchPhrase = searchPhrase;

				//21
				_21_replaceWords = replaceWords;

				//22
				_22_stringToSubstrings = stringToSubstrings;
				_22_countRepeats = countRepeats;

				//23
				_23_wordMeaning = wordMeaning;
				_23_strToWords = strToWords;

				//24
				_24_stringInText = stringInText;

				//25
				_25_parseSynonym = parseSynonym;
				_25_findSynonym = findSynonym;

				//26
				_26_findString = findString;

				//27
				_27_findWord = findWord;
				_27_divideWord = divideWord;

				//29
				_29_distanceBetweenWords = distanceBetweenWords;

				//30
				_30_censorWords = censorWords;

				//other
				_54ded_spellString = spellString;
				_530ec_textToStr= textToStr;
				_27cd9_divisionOfWordInDictionary = divisionOfWordInDictionary;
				_02b98_insertToStringList = insertToStringList;
				_ce079_insertFirstLineIndent = insertFirstLineIndent;
				_7e880_uniqueStrings = uniqueStrings;
				_aaaa9_insertStringBefore = insertStringBefore;
				_10c6c_distanceBetweenWordsValue = distanceBetweenWordsValue;
				_a120f_startWords = startWords;
				_5d510_censorText = censorText;
				_d26a2_insertEmptyString = insertEmptyString;
				_6ec83_delFromText = delFromText;
				_f8595_equalWords = equalWords;
				_a46a5_minimum = minimum;
				_3643e_sortByStringLength = sortByStringLength;
				_58b3b_findWordFromText = findWordFromText;
				_b4974_getWord = getWord;
				_8f7d2_findFloat = findFloat;
				_a7490_reverseWordsInText = reverseWordsInText;
				_1bec2_cutText = cutText;
				_3eac1_deleteWordsFromText = deleteWordsFromText;
				_0a49d_fixSpelling = fixSpelling;
				_597e4_strToWords = strToWords;
				_f3342_translateText = translateText;
				_25b24_markWordsInText = markWordsInText;
				_fcb68_sentenceLocation = sentenceLocation;
				_6a4eb_searchWordInText = searchWordInText;
				_7a70f_countInvalidBrackets = countInvalidBrackets;
				_024d7_searchWordInText = searchWordInText;
				_04ca43_searchPhrase = searchPhrase;
				_fc6a9_translateSubstrings = translateSubstrings;
				_93be5_countWords = countWords;
				_05789_reversePhraseInText = reversePhraseInText;
				_2ae89_addSynonyms = addSynonyms;
				_d2e14_replaceWordsInText = replaceWordsInText;
				_eb290_deleteBlanksFromText = deleteBlanksFromText;
				_beb12_getNumbersFromText = getNumbersFromText;
				_622d9_findSubstrInText = findSubstrInText;
				_b40a3_distanceBetweenWords = distanceBetweenWords;
				_24cb3_getWords=getWords;
				_2ae70_compositionStrings = compositionStrings;
				_20579_findSynonymAll = findSynonymAll;
				_65b6e_stringInTextAll = stringInTextAll;
				_a4eb3_iterativeWordLocation = iterativeWordLocation;
				_59053_selectPhrases = selectPhrases;
				_c1d1b_uniteStrings = uniteStrings;
				_1f2a9_delSubstring = delSubstring;
				_97af7_delWord = delWord;
				_f579b_isEndOfSentence = isEndOfSentence;
				_8f7d2_getNumbers = getNumbers;
				_ae399_compareString = compareString;
				_1191a_insertStrToText = insertStrToText;
				_c46f2_cutBracketsFromText = cutBracketsFromText;
				_efc2b_duplicateWords = duplicateWords;
				_e18c0_entryCount = entryCount;
				_3ec7d_deleteDelimiters = deleteDelimiters;
				_b37fd_findNextQuote = findNextQuote;
				_64dd0_distanceBeetwenPhrases = distanceBeetwenPhrases;
				_62a5d_compareStringList = compareStringList;
				_05967_strToWords = strToWords;
				_d5d5b_getRating = getRating;
				_69305_packStringList = packStringList;
				_2ffe4_startWords = startWords;
				_0523c_lettersString = lettersString;
				_a77a5_differenceByContents = differenceByContents;
				_142d2_findFIO = findFIO;
				_f3c74_reversePhrase = reversePhrase;
				_1af88_deleteString = deleteString;
				_50b16_deleteDuplicateWordsFromText = deleteDuplicateWordsFromText;
				_fa4a6_translateFromMorseCode = translateFromMorseCode;
				_e3a83_insertStringToText = insertStringToText;
				_235bc_iterativeWordCount = iterativeWordCount;
				_63e44_separateToSentences = separateToSentences;
				_84c95_delRegionOfText = delRegionOfText;
				_8eb83_appendString = appendString;
				_d9542_synonymString = synonymString;
				_e82bb_checkSpelling = checkSpelling;
				_bb159_divideString = divideString;
				_df735_insertString = insertString;
				_5ebf2_fillLettersAndNumbers = fillLettersAndNumbers;
				_454fb_cutString = cutString;
				
			
				UnitTesting();
			#else
				printf(_NO_UNIT_TESTS);
			#endif
			_exit(0);
		}
	
		//The last operation should be runnig the time-limiting thread
		__startTimer();
	}
	//Function that starts time countdown
	void __startTimer()
	{
		if(!__Messages) 
		{
			//By default, program execution time is 1 second
			//You could override it using environment variable "testingtime", specifying time in seconds
			float time=1;
			char * testingtime = getenv("testingtime");
			if(testingtime != NULL)
			{
				float usertime=atof(testingtime);
				if(usertime>0)
					time=usertime;
			}
			__RunTimerThread(time);
		}
	}
};

//Run necessary code using C++ run time library global objects initialisation
__RunFirst __dummy;


#define input_printf if(!__Messages); else printf
#define error_printf if(!__Messages) printf("invalid input data"); else printf
#define WAIT_ANY_KEY if(__Messages) {char c;fflush(stdin);scanf("%c",&c);}