/******************************************************
** Program: catalog.h
** Author: Kathleen Ashley
** Date: 11 October 2020
** Description: [HEADER FILE FOR RUN_WIZARD.CPP / ASSIGNMENT1]
** sorting data by their pages, spell effects, and average success rate.
** Input: 2 txt files from command line and some sort options
** Output: write to a file/ print to screen the data that was produced
** from the sort functions
******************************************************/

#ifndef CATALOG_H
#define CATALOG_H

#include <fstream>
#include <iostream>
#include <string>
#include <cstdlib>
#include <cctype>
#include <string>
#include <cstring>
#include <sstream>


using namespace std;

struct wizard
{
	string name;
	int id;
	string password;
	string position_title;
	float beard_length;
};

struct spell
{
	string name;
	float success_rate;
	string effect;
};

struct spellbook
{
	string title;
	string author;
	int num_pages;
	int edition;
	int num_spells;
	float avg_success_rate;
	struct spell *s;
};

void swap(spellbook* SB1, spellbook* SB2);

wizard* create_wizardlist(int num);

spellbook* create_spellbook(int num);

spell* create_spells(int num);

void get_WizardData(wizard* list, int num, ifstream& inputWiz);

void get_spell_data(spell* list, int num, ifstream& input);

float success_rate_SB(spell* list, int numSpells);

void get_spellbook_data(spellbook* list, int num, ifstream& input);

void delete_info(wizard* wizList, int wiz, spellbook* SBlist,int SB);

int filenameGiven(int argc);

int openFileI(ifstream &input);

int logInCheck(int& id, string& passwordH, wizard* list, int numWiz);

int checkID(string isValValid);

void printError(string& id, string& password);

int logInID(string isIDvalid, int& IDdestination, string &passwordH);

int checkLogin(int &ID, string& password, wizard* list, int num);

int isStudent(wizard* wizlist, int id, int i, string password);

void printLogInData(int IDholder, string password, wizard* list, int numWiz, int& student);

int checkOption(string isOptValid);

int isOptionValid(string& optHolder, int& destination);

int optionSort(int &numOption);

int infoDisplayed(int &display, int option, string &input);

// (1) First function - Sort by Number of Pages. Printing function for students.
void printForStudentNP(spellbook* SBlist, int numSB);

void PrintToScreenNP(spellbook* SBlist, int numSB, int student);

//(1)- First function - Sort by Number of Pages. Write to File.
void writeNPStudent(spellbook* SBlist, int numSB, fstream &output);

void writeToFileNP(spellbook* SBlist, int numSB, int student, fstream &output);

// (3) Third sorting function by average. Print to screen
void printForStudentAVG(spellbook* SBlist, int numSB);

void PrintToScreenAVG(spellbook* SBlist, int numSB, int student);

// (3). Sort by average success rate - write to file.
void writeStudentAVG(spellbook* SBlist, int numSB, fstream &output);

void writeToFileAVG(spellbook* SBlist, int numSB, int student, fstream &output);

// the bubbleSort for numPages.
spellbook* sortNumPages(spellbook* SBlist, int numSB);

// the bubbleSort for average number of pages
spellbook* sortAVG(spellbook* SBlist, int numSB);

// this function was made to count the total of spells.
int totalSpell(spellbook* SBlist, int numSB);

// this function will sort the array depending on their spell effects.
void Effect(spell* listbyE, spellbook *SBlist, int numSB, int& start, string spellE);

spell* sortEffect(spellbook* SBlist, int numSB);

// (2) SORT BY EFFECTS, print to screen.
void printForStudentSpell(spell* Slist, int totalSpell);

void printToScreenSpell(spell *list, int totalSpell, int student);

// (2) SORT BY EFFECTS, WRITE TO FILE.
void writeStudentSpell(spell* Slist, int totalSpell, fstream &output);

void writeToFileSpell(spell *list, int totalSpell, int student, fstream &output);

// print to screen options (from 1st to 3rd sort)
void displayScreen(wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
    int student, int option);

// write to file options (from 1st to 3rd sort)
void writeToFile(wizard* wizList, spellbook* SBlist, int numWiz, int numSB,
    int student, int option, fstream& output);

#endif