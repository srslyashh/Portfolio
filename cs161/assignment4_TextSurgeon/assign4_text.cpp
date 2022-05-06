/*****************************************************
 ** Program: Assignment 4 - Text Surgeon
 ** Author: Kathleen Ashley
 ** Date: February 23 2020
 ** Description: Taking the user input for the game
 ** Input: c string
 ** Output: The output depends on the user's choice, and the output will
 ** reflect on each function given.
 *****************************************************/

#include <iostream>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <sstream>

using namespace std;

/****************** ** Function: getInput ** **********************
 * ** Description: to take input of the user.
 * ** Parameters: char *input
 * ** Pre-conditions: store value in input.
 * ** Post-conditions: manipulate what's stored in input.
 ******************************************************************/
void getInput(char *input)
{
	cout << "Please enter a string or a paragraph: " << endl;
	cin.getline(input, 1027);
}

/****************** ** Function: check_vowel_cons ** **********************
 * ** Description: to check whether consonants == vowels.
 * ** Parameters: char* s
 * ** Pre-conditions: count each consonants and vowels.
 * ** Post-conditions: return 0 if consonants equal vowels, else return 1.
 ******************************************************************/
 // function 1.
bool check_vowel_cons(const char* s)
{
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int vowels = 0;
	/* Unsigned int is suitable for consonants.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int consonants = 0;
	/* Chose unsigned int because it suits the variable.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int flag = 0;

	for(int i = 0; i < strlen(s); i++)
	{
		flag = 0;
		if(s[i] == ' ')
		{
			i++;
		}
		if(s[i] == 'a' || s[i] == 'i' || s[i] == 'u' || s[i] == 'e' || s[i] == 'o')
		{
			vowels++;
			flag = 1;
		}
		else if(s[i] == 'A' || s[i] == 'I' || s[i] == 'U' || s[i] == 'E' || s[i] == 'O')
		{
			vowels++;
			flag = 1;
		}
		// isalpha should be consonant if it gets into this function.
		else if(isalpha(s[i]) && flag == 0)
		{
			consonants++;
		}
		// if it is not an alphabet, skip to the next char.
		else if(!(isalpha(s[i])))
		{
			i++;
		}
	}

	if(consonants == vowels)
	{
		return true;
	}

	return false;
}

/****************** ** Function: errorPrintForLetter ** **********************
 * ** Description: check whether char is more than 1, and if it is not an alpha.
 * ** Parameters: char *a, char& destination
 * ** Pre-conditions: check if a is valid.
 * ** Post-conditions: if so, put a into destination.
 ******************************************************************/
void errorPrintForLetter(char* a, char& destination)
{
	/* I chose int for this variable because in certain part of the codes,
	 * it is needed for this variable to be an int.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int loopAgain = 0;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int counterOfChar = 0;

	while(loopAgain == 0)
	{
			// if a is not an alphabet or more than 2 chars, loop again.
			for(int i = 0; i < strlen(a); i++)
			{
				if(!(isalpha(a[i])) || strlen(a) > 1)
				{
					cout << "Invalid input. Enter another character: " << endl;
					cin >> a;
					break;
				}
				else if(isalpha(a[i]) && strlen(a) == 1)
				{
					loopAgain = 1;
					destination = *a;
				}
			}
	}
}

/****************** ** Function: letter_swap ** **********************
 * ** Description: to swap the letters and plug it into s.
 * ** Parameters: char* s, const char a, const char b
 * ** Pre-conditions: if s[i] is a, change it to b.
 * ** Post-conditions: manipulated string is in s.
 ******************************************************************/
// function 2.
void letter_swap(char* s, const char a, const char b)
{
	for(int i = 0; i < strlen(s); i++)
	{
		if(s[i] != a)
		{
			i++;
		}
		if(s[i] == a)
		{
			s[i] = b;
		}
	}

	cout <<"The modified string is: "<< endl;
	cout << s << endl;
}

/****************** ** Function: flip_str ** **********************
 * ** Description: flip the string of s.
 * ** Parameters: char* s, const char* s2
 * ** Pre-conditions: flip s and put it into s2.
 * ** Post-conditions: manipulated string is in s2.
 ******************************************************************/
// function 3.
void flip_str(const char *s, char *s2)
{
	strcpy(s2, s);
	/* I chose int for lengthOfS2 because it should never be 0,
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int lengthOfS2 = strlen(s) - 1;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int lengthOfS = 0;

	while(lengthOfS < strlen(s))
	{
		if(s[lengthOfS] == ' ')
		{
			s2[lengthOfS2] = ' ';
			lengthOfS2--;
			lengthOfS++;
		}
		s2[lengthOfS2] = s[lengthOfS];
		lengthOfS2--;
		lengthOfS++;
	}
}

/****************** ** Function: count_chars ** **********************
 * ** Description: count occurences in string
 * ** Parameters: char* s, const char a, const char* chars
 * ** Pre-conditions: count the occurences, put it into int* occurences.
 * ** Post-conditions: return occurences.
 ******************************************************************/
// function 4.
int* count_chars(const char* s, const char* chars)
{
	// int pointer.
	int* occurences = new int[strlen(chars) + 1];
	/* I chose int because it is suitable for this case.
	 *  min -2,147,483,648, max 2,147,483,647
	 */
	int lengthOfChars = strlen(chars);

	while(lengthOfChars >= 0)
	{
		for(int i = 0; i < strlen(s); i++)
		{
			if(s[i] == chars[lengthOfChars])
			{
				occurences[lengthOfChars] += 1;
			}
		}
		lengthOfChars--;
	}
	return occurences;
}

/****************** ** Function: lowerUpperCase ** **********************
 * ** Description: turn the lowercase to uppercase, and vice versa.
 * ** if there are non-alphabets, leave them be.
 * ** Parameters: char* s
 * ** Pre-conditions: check if s[i] is lowercase or uppercase.
 * ** Post-conditions: manipulated string is in s.
 ******************************************************************/
// function 5.
void lowerUpperCase(char* s)
{
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int letterValue = 0;

	for(int i = 0; i < strlen(s); i++)
	{
		// put the int value of s[i] inside letterValue.
		letterValue = (int)s[i];

		if(s[i] == ' ')
		{
			s[i] = ' ';
		}
		else if(!(isalpha(s[i])))
		{
			i++;
		}
		else if(isalpha(s[i]))
		{
			if(s[i] >= 'a' && s[i] <= 'z')
			{
				s[i] = char(letterValue - 32);
			}
			else if(s[i] >= 'A' && s[i] <= 'Z')
			{
				s[i] = char(letterValue + 32);
			}
		}
	}
}

/****************** ** Function: checkString ** **********************
 * ** Description: check if the string input is valid.
 * ** Parameters: string isValueValid
 * ** Pre-conditions: Check if length is more than 1, or other than isdigit.
 * ** Post-conditions: return 0 if isValueValid valid. else, return 1.
 ******************************************************************/
int checkString(string isValueValid)
{
	/* I chose unsigned short because it should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short i;

	for(i = 0; i < isValueValid.length(); i++)
	{
		if(isValueValid.length() > 1 || isdigit(isValueValid[i]) == false)
		{
			return 1;
		}
		else if(isdigit(isValueValid[i]))
		{
			if(isValueValid[i] == '1' || isValueValid[i] == '2')
			{
				return 0;
			}
			else if(isValueValid[i] == '3' || isValueValid[i] == '4')
			{
				return 0;
			}
			else if(isValueValid[i] == '5' || isValueValid[i] == '6')
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	return 0;
}

/****************** ** Function: errorPrintForString ** **********************
 * ** Description: error print for string.
 * ** Parameters: string isValueValid, int &destination
 * ** Pre-conditions: check isValueValid valid.
 * ** Post-conditions: if string is invalid, keep on checking. if not, copy
 * ** value to destination.
 ******************************************************************/
void errorPrintForString(string isValueValid, int &destination)
{
	/* I chose unsigned short because it should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(checkString(isValueValid) == 0)
		{
			loopAgain = 1;
			stringstream stringToInt(isValueValid);
			stringToInt >> destination;
		}
		else
		{
			cout << "Invalid input. Enter another integer: " << endl;
			cin >> isValueValid;
		}
	}
}

int main()
{
	char input[1027];
	/* I chose int for this because there are certain area in the code
	 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
	 */
	int lengthOfStr = 0;
	// string.
	string choiceAsString;
	/* I chose int for this variable because it is suitable.
	 * (min -2.147,483,648, max 2147483647).
	 */
	int choice;
	/* I chose int for this because there are certain area in the code
	 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
	 */
	int loopAgain = 0;
	/* I chose int for this because there are certain area in the code
	 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
	 */
	int counter = 0;
	/* I chose int for this because there are certain area in the code
	 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
	 */
	int playAgain = 0;
	/* I chose int for this because there are certain area in the code
	 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
	 */
	int valid = 0;

	while(loopAgain == 0)
	{
		cout << "Please choose an operation: " << endl;
		cout << "(1) Check if the number of vowels equals the number of consonants."
				 << endl;
		cout << "(2) Letter swap." << endl;
		cout << "(3) Temporarily flip (reverse) the C-style string." << endl;
		cout << "(4) Compute character frequency distribution." << endl;
		cout << "(5) Upper-lower case function." << endl;
		cout << "(6) Quit the program." << endl;
		cin >> choiceAsString;
		errorPrintForString(choiceAsString, choice);

		cin.ignore();

		// (1) Check if vowels equals consonants.
		if(choice == 1)
		{
			getInput(input);

			if(check_vowel_cons(input))
			{
				cout << "# vowels = # consonants." << endl;
			}
			else
			{
				cout << "# vowels != # consonants." << endl;
			}
		}
		// (2) Letter swap function.
		else if(choice == 2)
		{
			// Using C-string for input check from user.
			char firstChar[1027];
			// Using C-string for input check from user.
			char secondChar[1027];
			// Character destination after gone through the check.
			char bereplaced;
			// Character destination after gone through the check.
			char replacement;

			getInput(input);

			cout << "Enter the character you want to replace: " << endl;
			cin >> firstChar;
			errorPrintForLetter(firstChar, bereplaced);

			cout << "Enter the character you want to replace it with: " << endl;
			cin >> secondChar;
			errorPrintForLetter(secondChar, replacement);

			letter_swap(input, bereplaced, replacement);
		}
		// 3. Temporarily flip (reverse) the C-style string.
		else if(choice == 3)
		{
			getInput(input);

			char* flipped = new char[strlen(input) + 1];

			flip_str(input, flipped);

			cout << "Your modified string is: " << flipped << endl;
			delete [] flipped;
			flipped = NULL;
		}
		// 4. Compute character frequency distribution.
		else if(choice == 4)
		{
			// Using C-string to input the charsOfInterest.
			char charsOfInterest[11];
			getInput(input);

			cout << "Please enter another string containing 1 to 10 characters "
					 << "of interest: " << endl;
			cin >> charsOfInterest;

			int* occurencesPointer = count_chars(input, charsOfInterest);

			for(int i = 0; i < strlen(charsOfInterest); i++)
			{
				cout << charsOfInterest[i] << ")" << occurencesPointer[i] << endl;
			}

			delete [] occurencesPointer;
			occurencesPointer = NULL;
		}

		// 5. Upper-lower case function
		else if(choice == 5)
		{
			/* I chose int for this because there are certain area in the code
			 *  where it is needed to be an int. (min -2.147,483,648, max 2147483647)
			 */
			int length = 0;

			getInput(input);
			lowerUpperCase(input);

			cout << "Your modified string is: " << input << endl;
		}
		else if(choice == 6)
		{
			loopAgain = 1;
		}
	}
	return 0;
}
