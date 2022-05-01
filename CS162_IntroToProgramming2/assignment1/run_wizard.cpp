/******************************************************
** Program: run_wizard.cpp
** Author: Kathleen Ashley
** Date: 11 October 2020
** Description: [DRIVER FILE FOR ASSIGNMENT 1]
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

int main(int argc, char** argv)
{
	int amountWiz, amountSB, IDholder, option, display, student;
	string password,input;
	filenameGiven(argc);
	ifstream wizardInfo(argv[1], ios::in);
	openFileI(wizardInfo);
	ifstream spellBookInfo(argv[2], ios::in);
	openFileI(spellBookInfo);
	wizardInfo >> amountWiz;
	spellBookInfo >> amountSB;
	wizard* wizList = create_wizardlist(amountWiz);
	spellbook* SBlist = create_spellbook(amountSB);
	get_spellbook_data(SBlist, amountSB, spellBookInfo);
	get_WizardData(wizList,amountWiz,wizardInfo);
	if(checkLogin(IDholder,password,wizList, amountWiz) == 0)
	{
		printLogInData(IDholder,password, wizList, amountWiz, student);
	}
	while(optionSort(option)!=4)
	{
		if(infoDisplayed(display, option, input) == 0)
		{
			displayScreen(wizList, SBlist, amountWiz,amountSB, student, option);
		}
		else
		{
			fstream outputData(input, ios::in | ios::out |ios::app);
			writeToFile(wizList, SBlist, amountWiz, amountSB, student, option, outputData);
			outputData.close();
		}
	}
	delete_info(wizList, amountWiz, SBlist, amountSB);
	wizardInfo.close();
	spellBookInfo.close();
	return 0;
}