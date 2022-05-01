******************************************************
** Program: run_wizard.cpp
** Author: Kathleen Ashley
** Date: 11 October 2020
** Description: [IMPLEMENTATION FILE FOR ASSIGNMENT1]
** sorting data by their pages, spell effects, and average success rate.
** Input: 2 txt files from command line and some sort options
** Output: write to a file/ print to screen the data that was produced
** from the sort functions
******************************************************/

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <sstream>
#include "catalog.h"

using namespace std;

/******************************************************
** Function: swap
** Description: swaps the data from SB1 to SB2, and SB2 to SB1
** Input: spellbook* SB1 (Spellbook1) & SB2 (spellbook2)
** Output: both values are changed
******************************************************/
void swap(spellbook* SB1, spellbook* SB2)
{
	spellbook* hold = SB1;
	SB1 = SB2;
	SB2 = hold;
}

/******************************************************
** Function: create_wizardlist
** Description: create a dynamically allocated wizardlist
** Input: int num
** Output: the address of pointer
******************************************************/
wizard* create_wizardlist(int num)
{
	wizard* wizardlist = new wizard[num];
	return wizardlist;
}

/******************************************************
** Function: create_spellbook
** Description: create a dynamically allocated spellbooklist
** Input: int num
** Output: the address of pointer
******************************************************/
spellbook* create_spellbook(int num)
{
	spellbook* spellbooklist = new spellbook[num];
		return spellbooklist;
}

/******************************************************
** Function: create_Spells
** Description:  create a dynamically allocated spell list
** Input: int num
** Output: the address of pointer
******************************************************/
spell* create_spells(int num)
{
	spell* spellList = new spell[num];
	return spellList;
}

/******************************************************
** Function: get_WizardData
** Description:  get the data for wizard, from txt file
** Input: wizard* list, int num, ifstream& inputWiz
** Output: list gets data from .txt file
******************************************************/
void get_WizardData(wizard* list, int num, ifstream& inputWiz)
{
	int counter = 0;
	while(inputWiz)
	{
		inputWiz >> list[counter].name;
		inputWiz >> list[counter].id;
		inputWiz >> list[counter].password;
		inputWiz >> list[counter].position_title;
		inputWiz >> list[counter].beard_length;
		counter++;
	}
}

/******************************************************
** Function: get_Spell_Data
** Description: get data for spell struct from .txt file
** Input: spell* list, int num, ifstream& input
** Output: list gets data from .txt file
******************************************************/
void get_spell_data(spell* list, int num, ifstream& input)
{
	for(int i = 0; i < num; i++)
	{
		input >> list[i].name;
		input >> list[i].success_rate;
		input >> list[i].effect;
	}
}

/******************************************************
** Function: success_rate_SB
** Description: count the average success rate of a spellbook
** Input: spell* list, int numSpells
** Output: float avg success rate
******************************************************/
float success_rate_SB(spell* list, int numSpells)
{
	float totalOfSuccess = 0;
	for(int i = 0; i < numSpells; i++)
	{
		totalOfSuccess += list[i].success_rate;
	}
	return totalOfSuccess/numSpells;
}

/******************************************************
** Function: get_spellbook_data
** Description:  get spellbook data from a .txt file
** Input: spellbook* list, int num, ifstream& input
** Output: list gets data from .txt file
******************************************************/
void get_spellbook_data(spellbook* list, int num, ifstream& input)
{
	int counter = 0, numSpells = 0;
	while(input)
	{
		input >> list[counter].title;
		input >> list[counter].author;
		input >> list[counter].num_pages;
		input >> list[counter].edition;
		input >> numSpells;
		list[counter].num_spells = numSpells;
		list[counter].s = create_spells(numSpells);
		get_spell_data(list[counter].s, numSpells, input);
		list[counter].avg_success_rate = success_rate_SB(list[counter].s,numSpells);
		numSpells = 0;
		counter++;
	}
}

/******************************************************
** Function: delete_info
** Description:  free the dynamically allocated memory
** Input: wizard* wizList, int wiz, spellbook* SBlist,int SB
** Output: wizlist and SBlist get freed
******************************************************/
void delete_info(wizard* wizList, int wiz, spellbook* SBlist,int SB)
{
	delete [] wizList;
	wizList = NULL;

	delete[] SBlist;
	SBlist = NULL;
}

/******************************************************
** Function: filenameGiven
** Description: if the user didnt give 2 filenames, exit.
** Input: argc
** Output: return or exit
******************************************************/
int filenameGiven(int argc)
{
	if(argc!= 3)
	{
		cout << "Error: Please provide a filename." << endl;
		exit(1);
	}
	return 0;
}

/******************************************************
** Function: openFileI
** Description:  if the user gave a non-existent file, exit.
** Input: ifstream &input
** Output: exit or return 0
******************************************************/
int openFileI(ifstream &input)
{
	if(input.fail())
	{
		cout << "Oops! Failed to open file. " << endl;
		exit (1);
	}
	return 0;
}

/******************************************************
** Function: logInCheck
** Description:  if there's a match for the password and ID with the list, return 0. if not,
** return 1.
** Input: int& id, string& passwordH, wizard* list, int numWiz
** Output: return values (0/1)
******************************************************/
int logInCheck(int& id, string& passwordH, wizard* list, int numWiz)
{
	for(int i = 0; i < numWiz; i++)
	{
		if(list[i].id == id)
		{
			if(list[i].password == passwordH)
			{
				return 0;
			}
			else
			{
				return 1;
			}
		}
	}
	return 1;
}

/******************************************************
** Function: checkID
** Description: if ID is not a digit, return 1.
** Input: string isValValid
** Output: return values
******************************************************/
int checkID(string isValValid)
{
	for(int i = 0; i < isValValid.length(); i++)
	{
		if(isdigit(isValValid[i]) == false)
		{
			return 1;
		}
	}
	return 0;
}

/******************************************************
** Function: printError
** Description: to print error messages for id/password
** Input: id, password
** Output: changed values for id and password
******************************************************/
void printError(string& id, string& password)
{
	cout << "Please enter your id :";
	cin >> id;
	cout << "Please enter your password: ";
	cin >> password;
}

/******************************************************
** Function: logInID
** Description: keep on prompting user to enter a valid ID.
** Input: string isIDvalid, int& IDdestination, string &passwordH
** Output: put a new value to IDdestination. return 0
******************************************************/
int logInID(string isIDvalid, int& IDdestination, string &passwordH)
{
	int loopAgain = 0;
	while(loopAgain == 0)
	{
		if(checkID(isIDvalid) == 0)
		{
			loopAgain = 1;
			stringstream changeToInt(isIDvalid);
			changeToInt >> IDdestination;
		}
		else
		{
			printError(isIDvalid, passwordH);
		}
	}
	return 0;
}

/******************************************************
** Function: checkLogin
** Description: make sure that id is right before checking that id and passwordholder
** match the information in wizard list
** Input: int &ID, string& password, wizard* list, int num
** Output: exit(1) or return 0;
******************************************************/
int checkLogin(int &ID, string& password, wizard* list, int num)
{
	int i = 0, falseI = 0;
	string idholder, passwordholder;
	for(i = 0; i < 3; i++)
	{
		if(i == 0 || falseI == 1)
		{
 			printError(idholder, passwordholder);
			falseI = 0;
		}
		if(logInID(idholder, ID, passwordholder) == 0)
		{
			if(logInCheck(ID, passwordholder, list, num) == 1)
			{
				cout << "Incorrect ID or password" << endl;
				falseI = 1;
			}
			else
			{
				password = passwordholder;
				return 0;
			}
		}
	}
    exit (1);
}

/******************************************************
** Function: isStudent
** Description: check whether the one trying to access information
** is a student or not
** Input: wizard* wizlist, int id, int i, string password
** Output: return 1 if not student, otherwise 0.
******************************************************/
int isStudent(wizard* wizlist, int id, int i, string password)
{
	string s1 = ("Student");
	if(wizlist[i].position_title.compare(s1) == 0)
	{
		return 0;
	}
	else
	{
		return 1;
	}
}

/******************************************************
** Function: printLogInData
** Description:  print information after logging in
** Input: int IDholder, string password, wizard* list, int numWiz, int& student
** Output: print to screen information
******************************************************/
void printLogInData(int IDholder, string password, wizard* list, int numWiz, int& student)
{
	for(int i = 0; i < numWiz; i++)
	{
		if(list[i].id == IDholder)
		{
			if(list[i].password == password)
			{
				cout << endl << "Welcome " << list[i].name << endl;
				cout << "ID: " << list[i].id << endl;
				cout << "Status: " << list[i].position_title << endl;
				cout << "Beard length: " << list[i].beard_length << endl << endl;
				student = isStudent(list,IDholder,i, password);
			}
		}
	}
}

/******************************************************
** Function: checkOption
** Description:  check whether option is valid.
** Input:string isOptValid
** Output: return 1 if not right, 0 elsewise.
******************************************************/
int checkOption(string isOptValid)
{
	for(int i = 0; i < isOptValid.length(); i++)
	{
		if(isOptValid.length() == 1)
		{
			if(isOptValid[i] == '1' || isOptValid[i] == '2')
			{
				return 0;
			}
			if(isOptValid[i] == '3' || isOptValid[i] == '4')
			{
				return 0;
			}
			else
 			{
				return 1;
			}
		}
 }
	return 1;
}

/******************************************************
** Function: isOptionValid
** Description: keep on prompting user for the right option
** Input: string& optHolder, int& destination
** Output: the right value will be updated to destination.
******************************************************/
int isOptionValid(string& optHolder, int& destination)
{
	int loopAgain = 0;
	while(loopAgain == 0)
	{
		if(checkOption(optHolder) == 0)
		{
			loopAgain = 1;
			stringstream changeToInt(optHolder);
			changeToInt >> destination;
		}
		else
		{
			cout << "Not an option. Enter a valid option from 1-4: " << endl;
			cin >> optHolder;
		}
	}
	return 0;
}

/******************************************************
** Function: optionSort
** Description: Print option for user
** Input: int &numoption
** Output: return numOption
******************************************************/
int optionSort(int &numOption)
{
	string optHolder;
	cout << endl << "Which option would you like to choose?" << endl;
	cout << "(1) Sort spellbooks by number of pages." << endl;
	cout << "(2) Group spells by their effect." << endl;
	cout << "(3) Sort Spellbooks by average success rate." << endl;
	cout << "(4) Quit. " << endl;
	cin >> optHolder;
	isOptionValid(optHolder, numOption);
	return numOption;
}

/******************************************************
** Function: infoDisplayed
** Description:  How would the user like the information to be displayed
** Input: int &display, int option, string &input
** Output: return 0 if print to screen, 1 if write to file.
******************************************************/
int infoDisplayed(int &display, int option, string &input)
{
	cout << "How would you like the information displayed?" << endl;
	cout << "(1) Print to screen." << endl;
	cout << "(2) Print to file." << endl;
	cin >> display;
	if(display == 1)
	{
		return 0;
	}
	else if(display == 2)
	{
		cout << "Please provide filename: ";
		cin >> input;
		return 1;
	}
	return 0;
}

/******************************************************
** Function: printForStudentNP
** Description:  print for student (no forbidden spells/books)
** Input: spellbook* SBlist, int numSB
** Output: print to screen the information
******************************************************/
// (1) First function - Sort by Number of Pages. Printing function for students.
void printForStudentNP(spellbook* SBlist, int numSB)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < numSB ; i++)
 	{
		for(int j = 0; j < SBlist[i].num_spells; j++)
		{
			if(SBlist[i].s[j].effect.compare(s1) == 0 || SBlist[i].s[j].effect.compare(s2) == 0)
			{
				forbidden++;
			}
		}
		if(forbidden == 0)
		{
			cout << SBlist[i].title << " ";
			cout << SBlist[i].num_pages << endl;
		}
		forbidden = 0;
	}
}

/******************************************************
** Function: PrintToScreenNP
** Description:  print to screen information based on sort pages
** Input: spellbook* SBlist, int numSB, int student
** Output: print to screen
******************************************************/
void PrintToScreenNP(spellbook* SBlist, int numSB, int student)
{
	if(student == 0)
	{
		printForStudentNP(SBlist, numSB);
	}
	else
	{
		for(int i = 0; i < numSB; i++)
		{
			cout << SBlist[i].title << " ";
			cout << SBlist[i].num_pages << endl;
		}
	}
}

/******************************************************
** Function: writeNPStudent
** Description:  write data for students to files, based on
** sorting by number of pages
** Input: spellbook* SBlist, int numSB, fstream &output
** Output: print to file
******************************************************/
//(1)- First function - Sort by Number of Pages. Write to File.
void writeNPStudent(spellbook* SBlist, int numSB, fstream &output)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < numSB ; i++)
	{
		for(int j = 0; j < SBlist[i].num_spells; j++)
		{
			if(SBlist[i].s[j].effect.compare(s1) == 0 || SBlist[i].s[j].effect.compare(s2) == 0)
			{
				forbidden++;
			}
		}
		if(forbidden == 0)
		{
			output << SBlist[i].title << " ";
			output << SBlist[i].num_pages << endl;
		}
		forbidden = 0;
	}
}

/******************************************************
** Function: writeToFileNP
** Description: write to file based on sorting by num of pages
** Input: spellbook* SBlist, int numSB, int student, fstream &output
** Output: write to file
******************************************************/
void writeToFileNP(spellbook* SBlist, int numSB, int student, fstream &output)
{
	if(student == 0)
	{
		writeNPStudent(SBlist, numSB, output);
	}
	else
	{
		for(int i = 0; i < numSB; i++)
		{
			output << SBlist[i].title << " ";
			output << SBlist[i].num_pages << endl;
		}
	}
}

/******************************************************
** Function: printForStudentAVG
** Description: print to screen the data based on sorting by average
** success rate, for student.
** Input: spellbook* SBlist, int numSB
** Output: print to screen data
******************************************************/
// (3) Third sorting function by average. Print to screen
void printForStudentAVG(spellbook* SBlist, int numSB)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < numSB ; i++)
	{
		for(int j = 0; j < SBlist[i].num_spells; j++)
		{
			if(SBlist[i].s[j].effect.compare(s1) == 0 || SBlist[i].s[j].effect.compare(s2) == 0)
			{
				forbidden++;
			}
		}
		if(forbidden == 0)
		{
			cout << SBlist[i].title << " ";
			cout << SBlist[i].avg_success_rate << endl;
		}
		forbidden = 0;
	}
}

/******************************************************
** Function: PrintToScreenAVG
** Description: print to screen the data based on sorting by average
** success rate, for student.
** Input: spellbook* SBlist, int numSB, int student
** Output: print to screen
******************************************************/
void PrintToScreenAVG(spellbook* SBlist, int numSB, int student)
{
	if(student == 0)
	{
		printForStudentAVG(SBlist, numSB);
	}
	else
	{
		for(int i = 0; i < numSB; i++)
		{
			cout << SBlist[i].title << " ";
			cout << SBlist[i].avg_success_rate << endl;
		}
	}
}

/******************************************************
** Function: writeStudentAVG
** Description: write to file the data based on sorting by average
** success rate, for student.
** Input: spellbook* SBlist, int numSB, fstream &output
** Output: write to file
******************************************************/
// (3). Sort by average success rate - write to file.
void writeStudentAVG(spellbook* SBlist, int numSB, fstream &output)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < numSB ; i++)
	{
		for(int j = 0; j < SBlist[i].num_spells; j++)
		{
			if(SBlist[i].s[j].effect.compare(s1) == 0 || SBlist[i].s[j].effect.compare(s2) == 0)
			{
				forbidden++;
			}
		}
		if(forbidden == 0)
		{
			output << SBlist[i].title << " ";
			output << SBlist[i].avg_success_rate << endl;
		}
		forbidden = 0;
	}
}

/******************************************************
** Function: writeToFileAVG
** Description: write to file the data based on sorting by average
** success rate.
** Input: spellbook* SBlist, int numSB, int student, fstream &output
** Output: write to file
******************************************************/
void writeToFileAVG(spellbook* SBlist, int numSB, int student, fstream &output)
{
	if(student == 0)
	{
		writeStudentAVG(SBlist, numSB, output);
	}
	else
	{
		for(int i = 0; i < numSB; i++)
		{
			output << SBlist[i].title << " ";
			output << SBlist[i].avg_success_rate << endl;
		}
	}
}

/******************************************************
** Function: sortNumPages
** Description: bubblesort for Number of pages sort
** Input: spellbook* SBlist, int numSB
** Output:return the address of SBlist
******************************************************/
spellbook* sortNumPages(spellbook* SBlist, int numSB)
{
	int i, flag = 1;
	while(flag)
	{
		flag = 0;
		for(i = 0; i < numSB - 1; i++)
		{
			if(SBlist[i].num_pages > SBlist[i+1].num_pages)
			{
				swap(SBlist[i], SBlist[i+1]);
				flag = 1;
			}
		}
	}
	return SBlist;
}

/******************************************************
** Function: sortAVG
** Description: bubbleSort for average number of pages
** Input: spellbook* SBlist, int numSB
** Output: SBlist
******************************************************/
spellbook* sortAVG(spellbook* SBlist, int numSB)
{
	int i, flag = 1;
	while(flag)
	{
		flag = 0;
		for(i = 0; i < numSB - 1; i++)
		{
			if(SBlist[i].avg_success_rate > SBlist[i+1].avg_success_rate)
			{
				swap(SBlist[i], SBlist[i+1]);
				flag = 1;
			}
		}
	}
	return SBlist;
}

/******************************************************
** Function: totalSpell
** Description: count the total spell
** Input: spellbook* SBlist, int numSB
** Output: int totalSpell
******************************************************/
// this function was made to count the total of spells.
int totalSpell(spellbook* SBlist, int numSB)
{
	int totalSpell = 0;
	for(int i = 0; i < numSB; i++)
	{
		totalSpell += SBlist[i].num_spells;
	}
	return totalSpell;
}

/******************************************************
** Function: Effect
** Description: sort the spells by effect in listbyE
** Input: spell* listbyE, spellbook *SBlist, int numSB, int& start, string spellE
** Output: listbyE will be sorted
******************************************************/
// this function will sort the array depending on their spell effects.
void Effect(spell* listbyE, spellbook *SBlist, int numSB, int& start, string spellE)
{
	for(int i = 0; i < numSB; i++)
	{
		for(int j = 0; j < SBlist[i].num_spells ; j++)
		{
			if(SBlist[i].s[j].effect.compare(spellE) == 0)
			{
				listbyE[start].name = SBlist[i].s[j].name;
				listbyE[start].success_rate = SBlist[i].s[j].success_rate;
				listbyE[start].effect = SBlist[i].s[j].effect;
				start++;
			}
		}
	}
}

/******************************************************
** Function: sortEffect
** Description: to pass the listbyEffect and the effects and arrange
** them in Effect
** Input: spellbook* SBlist, int numSB
** Output: listbyEffect
******************************************************/
spell* sortEffect(spellbook* SBlist, int numSB)
{
	spell* listbyEffect = new spell[totalSpell(SBlist, numSB)];
	int start = 0;

	Effect(listbyEffect, SBlist, numSB, start, "bubble");
	Effect(listbyEffect, SBlist, numSB, start, "memory_loss");
	Effect(listbyEffect, SBlist, numSB, start, "fire");
	Effect(listbyEffect, SBlist, numSB, start, "poison");
	Effect(listbyEffect, SBlist, numSB, start, "death");

	return listbyEffect;
}

/******************************************************
** Function: printForStudentSpell
** Description:  print to screen for student based on effect
** Input: spell* Slist, int totalSpell
** Output: print info to screen
******************************************************/
// (2) SORT BY EFFECTS, print to screen.
void printForStudentSpell(spell* Slist, int totalSpell)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < totalSpell ; i++)
	{
		if(Slist[i].effect.compare(s1) == 0 || Slist[i].effect.compare(s2) == 0)
		{
			forbidden++;
		}
		if(forbidden == 0)
		{
			cout << Slist[i].effect << " ";
			cout << Slist[i].name << endl;
		}
		forbidden = 0;
	}
	delete [] Slist;
	Slist = NULL;
}

/******************************************************
** Function:printToScreenSpell
** Description: print to screen based on sorting by effect
** Input: spell *list, int totalSpell, int student
** Output:print info to screen
******************************************************/
void printToScreenSpell(spell *list, int totalSpell, int student)
{
	if(student == 0)
	{
		printForStudentSpell(list, totalSpell);
	}
	else
	{
		for(int i = 0; i < totalSpell; i++)
		{
			cout << list[i].effect << " ";
			cout << list[i].name << endl;
		}
		delete[] list;
		list = NULL;
	}
}

/******************************************************
** Function: writeStudentSpell
** Description:  write to file the info based on sorting function 2.
** Input: spell* Slist, int totalSpell, fstream &output
** Output: write to file for student based on effect
******************************************************/
// (2) SORT BY EFFECTS, WRITE TO FILE.
void writeStudentSpell(spell* Slist, int totalSpell, fstream &output)
{
	int forbidden = 0;
	string s1 = ("death");
	string s2 = ("poison");
	for(int i= 0; i < totalSpell ; i++)
	{
		if(Slist[i].effect.compare(s1) == 0 || Slist[i].effect.compare(s2) == 0)
		{
			forbidden++;
		}
		if(forbidden == 0)
		{
			output << Slist[i].effect << " ";
			output << Slist[i].name << endl;
		}
		forbidden = 0;
	}
}

/******************************************************
** Function: writeToFileSpell
** Description: write to file the info based on sorting function 2.
** Input: spell *list, int totalSpell, int student, fstream &output
** Output: write to file based on effect
******************************************************/
void writeToFileSpell(spell *list, int totalSpell, int student, fstream &output)
{
	if(student == 0)
	{
		writeStudentSpell(list, totalSpell, output);
	}
	else
	{
		for(int i = 0; i < totalSpell; i++)
		{
			output << list[i].effect << " ";
			output << list[i].name << endl;
		}
	}
}

/******************************************************
** Function: displayScreen
** Description: call 3 sorting functions based on the user's option
** to print info to screen
** Input: wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
** int student, int option
** Output: different info based on sort function chosen
******************************************************/
// print to screen options (from 1st to 3rd sort)
void displayScreen(wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
    int student, int option)
{
	if(option == 1)
	{
		PrintToScreenNP(sortNumPages(SBlist, numSB),numSB,student);
	}
	else if (option == 2)
	{
		printToScreenSpell(sortEffect(SBlist,numSB),totalSpell(SBlist,numSB),student);
	}
	else if(option == 3)
	{
		PrintToScreenAVG(sortAVG(SBlist, numSB),numSB,student);
	}
}

/******************************************************
** Function: writeToFile
** Description:call 3 sorting functions based on the user's option
** to write to file
** Input: wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
** int student, int option, fstream& output
** Output: different info appended/written to files based on sort function chosen
******************************************************/
// write to file options (from 1st to 3rd sort)
void writeToFile(wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
    int student, int option, fstream& output)
{
	if(option == 1)
	{
		writeToFileNP(sortNumPages(SBlist,numSB),numSB,student, output);
		cout << "Appended requested information to file." << endl;
	}
	else if(option == 2)
	{
		writeToFileSpell(sortEffect(SBlist,numSB),totalSpell(SBlist,numSB),student,output);
		cout << "Appended requested information to file." << endl;
	}
	else if (option == 3)
	{
		writeToFileAVG(sortAVG(SBlist, numSB), numSB, student, output);
		cout << "Appended requested information to file." << endl;
	}
}
