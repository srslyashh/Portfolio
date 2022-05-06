/*****************************************************
 ** Program: Assignment 5 - Treasure Chest
 ** Author: Kathleen Ashley
 ** Date: March 8 2020
 ** Description: Taking user input and put it in a 2D allocated array.
 ** 						this program also allows user to modify the input.
 ** Input: String
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

struct books
{
	/* I chose int because it gives out more number than 65,535(short).
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int pages;
	int weight;
	/* I needed string for this because the data type should be a string.
	 */
	string genre;
	/* I needed a float for prices because it could be decimal point.
	 * Min :  1.17549e-038 max: 3.40282e+038
	 */
	float price;
};

/****************** ** Function: checkString ** **********************
 * ** Description: to check the menu choice from user.
 * ** Parameters: string isValueValid
 * ** Pre-conditions: take string isValueValid then turn it into int.
 * ** Post-conditions: return 1 if string consists of non-digit value,
 or if the value is bigger than 6 and less than 1. Otherwise,return 0.
 ******************************************************************/
int checkString(string isValueValid)
{
	/* Chose unsigned int because it suits the variable.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int copy = 0;
	stringstream stringToInt(isValueValid);
	stringToInt >> copy;

	for(int i = 0; i < isValueValid.length(); i++)
	{
		if(isdigit(isValueValid[i]) == false)
		{
			return 1;
		}
	}
	if(copy >= 1 && copy <= 6)
	{
		return 0;
	}
	// if copy is bigger than 6 or less than 1, return 1.
	return 1;
}

/****************** ** Function: errorPrintValue ** **********************
 * ** Description: This prints out the error statement, and prompt the user
 * ** to enter another value if not valid.
 * ** Parameters: string isValueValid, int &destination
 * ** Pre-conditions: check isValueValid, and destination is passed by reference.
 * ** Post-conditions: the correct value is placed in destination.
 ******************************************************************/
void errorPrintValue(string isValueValid, int &destination)
{
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
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
		// if isValValid == 1 (input is invalid).
		else
		{
			cout << "Invalid input. Enter another integer: " << endl;
			cin >> isValueValid;
		}
	}
}

/****************** ** Function: checkValueRowCol** **********************
 * ** Description: This is to make sure that row/col is not less than
 * ** 0 and that it contains only numbers.
 * ** Parameters: string isValueValid
 * ** Pre-conditions: take isValueValid then check if it is 0 or contains
 * ** non-digit characters.
 * ** Post-conditions: return 1 if invalid, return 0 if valid.
 ******************************************************************/
int checkValueRowCol(string isValueValid)
{
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short flagCheck = 0;

	for(int i = 0; i < isValueValid.length(); i++)
	{
		if(isValueValid[0] == '0'|| isdigit(isValueValid[i]) == false)
		{
			flagCheck++;
		}
	}

	if(flagCheck > 0)
	{
		return 1;
	}

	return 0;
}

/****************** ** Function: errorPrintRowCol** **********************
 * ** Description: Error Print. If value is invalid, prompt user to Input
 * ** another value.
 * ** Parameters: string isValueValid, int &destination
 * ** Pre-conditions: pass isValueValid to checkValueRowCol then determine
 * ** whether value is valid or not.
 * ** Post-conditions: put the valid value in destination.
 ******************************************************************/
void errorPrintRowCol(string isValueValid, int &destination)
{
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(checkValueRowCol(isValueValid) == 0)
		{
			loopAgain = 1;
			stringstream stringToInt(isValueValid);
			stringToInt >> destination;
		}
		// value of rowcol is not valid, less than 0 or has non-digit characters.
		else
		{
			cout << "Invalid input. Enter another integer: " << endl;
			cin >> isValueValid;
		}
	}
}

/****************** ** Function: addBook ** **********************
 * ** Description: Add book attributes in the coordinate.
 * ** Parameters: books** dynamic, string genre, float price, int weight,
 * ** int pages,int row, int column
 * ** Pre-conditions: The attributes of the struct
 * ** Post-conditions: Put the attributtes in the determined location.
 ******************************************************************/
void addBook(books** dynamic, string genre, float price, int weight,int pages,
int row, int column)
{
	dynamic[row][column].genre = genre;
	dynamic[row][column].price = price;
	dynamic[row][column].weight = weight;
	dynamic[row][column].pages = pages;
}

/****************** ** Function: randomGenerator ** **********************
 * ** Description: randomize the attributes for the book.
 * ** Parameters: books** dynamic, int row, int column
 * ** Pre-conditions: Randomize the attributes.
 * ** Post-conditions: Pass the attributes to addBook to add it to the location
 * ** determined.
 ******************************************************************/
void randomGenerator(books** dynamic, int row, int column)
{
	string genre[] = {"Romance", "Fiction", "Sci-fi", "Mystery", "Horror"};
	float price[] = {10.20, 11.00, 8.50, 20.00, 15.00};
	int weight[] = {4,5,3,2,6};
	int pages[] = {400,500,300,600,250};

	dynamic[row][column].genre = genre[rand()% 5];
	dynamic[row][column].price = price[rand()% 5];
	dynamic[row][column].weight = weight[rand()% 5];
	dynamic[row][column].pages = pages[rand()% 5];

	addBook(dynamic,genre[rand()% 5], price[rand()% 5], weight[rand()% 5],
	pages[rand()% 5], row, column);
}

/****************** ** Function: printContent ** **********************
 * ** Description: Print the content of the determined location.
 * ** Parameters: books** dynamic, int row, int column
 * ** Pre-conditions: Take in the row and column.
 * ** Post-conditions: Print out the contents of the book
 ******************************************************************/
void printContent(books** dynamic, int row, int column)
{
	cout << "Book genre is: " << dynamic[row][column].genre << ", the book has "
			 << dynamic[row][column].pages << " pages, weight is "
			 << dynamic[row][column].weight << " lbs. The price of the book: $"
			 << dynamic[row][column].price << "." << endl;
}

/****************** ** Function: rowColOutOfBounds ** **********************
 * ** Description: Check if row/column is out of bounds.
 * ** Parameters: int &rowToChange, int &colToChange, int row, int column
 * ** Pre-conditions: Take in the determined row/col, make sure they are more
 * ** than 0 and less than row or column.
 * ** Post-conditions: Print out error if not valid, if valid, pass back the values
 * ** to rowToChange and colToChange.
 ******************************************************************/
int rowColOutOfBounds(int &rowToChange, int &colToChange, int row, int column)
{
	/* I chose int for duplicateRow & duplicateCol because it is needed
	 * for both variables to be int in this function.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int duplicateRow = rowToChange;
	int duplicateCol = colToChange;
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(duplicateRow >= 0 && duplicateCol >= 0 && duplicateCol < column
			&& duplicateRow < row)
		{
			rowToChange = duplicateRow;
			colToChange = duplicateCol;
			loopAgain = 1;
		}
		/* if rowToChange / colToChange is less than 0, or more than row or column,
		 * then it falls on this case.
		 */
		else
		{
			cout << "Invalid coordinate [" << duplicateRow << "][" << duplicateCol << "]."
					 << "Enter another coordinate: " << endl;
			cout << "Row: " << endl;
			cin >> duplicateRow;
			cout << "Column: " << endl;
			cin >> duplicateCol;
		}
	}
	return 0;
}

/****************** ** Function: printPrice ** **********************
 * ** Description: Print the total of price.
 * ** Parameters: books** dynamic, int row, int colum
 * ** Pre-conditions: Go through every row&col, then increment totalPrice.
 * ** Post-conditions: print out amount of books then totalprice.
 ******************************************************************/
void printPrice(books** dynamic, int row, int column)
{
	/* I needed a float for prices because it could be decimal point.
	 * Min :  1.17549e-038 max: 3.40282e+038
	 */
	float totalPrice = 0.0;
	/* Chose unsigned int because it should never be less than 0.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int amountOfBooks = 0;
	for(int i = 0; i < row; i++)
	{
		for(int j= 0; j < column; j++)
		{
			if(dynamic[i][j].price != 0)
			{
				totalPrice += dynamic[i][j].price;
				amountOfBooks++;
			}
			if(dynamic[i][j].price == 0)
			{
				if(dynamic[i][j].genre != "empty")
				{
					amountOfBooks++;
				}
			}
		}
	}
	cout << "Total value of "<< amountOfBooks << " book(s): $ " << totalPrice
			 << endl;
	amountOfBooks = 0;
	totalPrice = 0.0;
}

/****************** ** Function: overallPrint ** **********************
 * ** Description: Print how the 2D array looks like & along with the char.
 * ** Parameters: books** dynamic, int row, int colum
 * ** Pre-conditions: Go through every row&col, then print it.
 * ** Post-conditions: Print out the row and col, along with a character inside
 * ** if [i][j] contains an item.
 ******************************************************************/
void overallPrint(books** dynamic, int row, int column)
{
	for(int i = 0; i < row; i++)
	{
		for(int j = 0; j < column; j++)
		{
			if(dynamic[i][j].genre == "empty")
			{
				cout << "[ ]";
			}
			// if it is not "empty", print out the first char of the genre.
			else
			{
				cout << "[" << dynamic[i][j].genre[0] << "]";
			}
		}
		cout << "\n";
	}
}

/****************** ** Function: isDestinationEmpty ** **********************
 * ** Description: Checking if the destination is empty or if it contains value.
 * ** Parameters: books** dynamic, int rowToChange, int colToChange
 * ** Pre-conditions: Go to [rowToChange][colToChange] see if genre is empty.
 * ** Post-conditions: If there is nothing inside, return 1. If it is not empty,
 * ** return 0.
 ******************************************************************/
int isDestinationEmpty(books** dynamic, int rowToChange, int colToChange)
{
	if(dynamic[rowToChange][colToChange].genre == "empty")
	{
		return 1;
	}
	// if coordinates has something other than "empty", then return 0.
	else
	{
		return 0;
	}
}

/****************** ** Function: emptyErrorPrint ** **********************
 * ** Description: Print out an error statement if coordinates contains nothing.
 * ** Parameters: books** dynamic, int &rowToChange, int &colToChange,
 	int row, int col
 * ** Pre-conditions: rowToChange and colToChange are passed by reference.
 * ** Post-conditions: Keep on prompting the user for a valid value
 * ** if value is not valid.
 ******************************************************************/
void emptyErrorPrint(books** dynamic, int &rowToChange, int &colToChange,
	int row, int col)
{
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;
	/* I chose int for rowduplicate and colduplicate because they are needed to be
	 * int. min -2,147,483,648, max 2,147,483,647
	 */
	int rowduplicate = rowToChange;
	int colduplicate = colToChange;

	while(loopAgain == 0)
	{
		if(isDestinationEmpty(dynamic, rowduplicate, colduplicate) == 0)
		{
			loopAgain = 1;
			rowToChange = rowduplicate;
			colToChange = colduplicate;
		}
		// Coordinates has no item in it if it falls on this case.
		else
		{
			cout << "Coordinates contains no book and attributes. Please input another: "
					 << endl;
			cout << "Row: " << endl;
			cin >> rowduplicate;
			cout << "Column: " << endl;
			cin >> colduplicate;
			rowColOutOfBounds(rowduplicate, colduplicate, row, col);
		}
	}
}

/****************** ** Function: switchingStuff ** **********************
 * ** Description: Switches attributes and items from one place to another.
 * ** Parameters: books** dynamic, int row1, int col1, int row2, int col2
 * ** Pre-conditions: store attributes row2 and col2 somewhere else. So the
 * ** data doesn't get overwritten.
 * ** Post-conditions: Items at [row1][col1] and [row2][col2] are switched.
 ******************************************************************/
void switchingStuff(books** dynamic, int row1, int col1, int row2, int col2)
{
	// It is needed for this to be string.
	string genrecopy = dynamic[row2][col2].genre;
	/* I needed a float for prices because it could be decimal point.
	 * Min :  1.17549e-038 max: 3.40282e+038
	 */
	float pricecopy = dynamic[row2][col2].price;
	/* I chose int because it gives out more number than 65,535(short).
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int weightcopy = dynamic[row2][col2].weight;
	int pagescopy = dynamic[row2][col2].pages;

	cout << "SWITCHING STUFF!" << endl;
	// putting first coordinates' attributes in second coordinates.
	addBook(dynamic, dynamic[row1][col1].genre, dynamic[row1][col1].price,
	dynamic[row1][col1].weight, dynamic[row1][col1].pages, row2, col2);
	// putting second coordinates' attributes in first coordinates.
	addBook(dynamic, genrecopy, pricecopy, weightcopy, pagescopy, row1, col1);
}

/****************** ** Function: removeAttributes ** **********************
 * ** Description: Remove attributes.
 * ** Parameters: books** dynamic, int row1, int col1
 * ** Pre-conditions: go to the coordinates, and empty the item there.
 * ** Post-conditions: the item got removed.
 ******************************************************************/
void removeAttributes(books** dynamic, int row1, int col1)
{
	// row1 and col1 is the coordinate of the item that wants to be removed.
	dynamic[row1][col1].genre = "empty";
	dynamic[row1][col1].price = 0;
	dynamic[row1][col1].weight = 0;
	dynamic[row1][col1].pages = 0;
}

/****************** ** Function: notEmpty ** **********************
 * ** Description: If destination is not empty, keep on prompting user to
 * ** enter a new value.
 * ** Parameters: books** dynamic, int &rowToChange, int &colToChange, int row,
 * ** int col
 * ** Pre-conditions: rowToChange and colToChange are passed by reference.
 * ** Post-conditions: valid values are put inside rowToChange and colToChange
 ******************************************************************/
void notEmpty(books** dynamic, int &rowToChange, int &colToChange, int row, int col)
{
	/* I chose int for rowCopy and colCopy because they should never be 0
	 * and in certain part of the program,it is needed for them to be int.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int rowCopy = rowToChange;
	int colCopy = colToChange;
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(isDestinationEmpty(dynamic, rowCopy, colCopy) == 1)
		{
			rowToChange = rowCopy;
			colToChange = colCopy;
			loopAgain = 1;
		}
		// destination is not empty.
		else
		{
			cout << "Destination is not empty. Please input another coordinate: "
					 << endl;
			cout << "Row: " << endl;
			cin >> rowCopy;
			cout << "Column: " << endl;
			cin >> colCopy;
			rowColOutOfBounds(rowCopy, colCopy, row, col);
		}
	}
}

/****************** ** Function: intCheck ** **********************
 * ** Description: Check if isValValid is within range or not.
 * ** Parameters: int& isValValid
 * ** Pre-conditions: isValValid is passed by reference.
 * ** Post-conditions: valid value is put into isValValid.
 ******************************************************************/
void intCheck(int& isValValid)
{
	/* I chose int because isValValid is an int as well.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int copy = isValValid;
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;
	while(loopAgain == 0)
	{
		if(copy >= 0 && copy <= 2147483647)
		{
			isValValid = copy;
			loopAgain = 1;
		}
		// If value is less than 0 or more than 2147483647, it falls on this case.
		else
		{
			cout << "Value is invalid. Please enter a valid value: " << endl;
			cin >> copy;
		}
	}
}

/****************** ** Function: floatCheck ** **********************
 * ** Description: check if floatCheck is not less than 0.
 * ** Parameters: int& isValValid
 * ** Pre-conditions: isValValid is passed by reference.
 * ** Post-conditions: valid value is put into isValValid.
 ******************************************************************/
void floatCheck(float &isValValid)
{
	/* I needed a float copy because isValValid is a float.
	 * Min :  1.17549e-038 max: 3.40282e+038
	 */
	float copy = isValValid;
	/* I used an unsigned short because i only needed 0/1.
	 *  Min 0, max 65,535.
	 */
	unsigned short loopAgain = 0;
	while(loopAgain == 0)
	{
		if(copy >= 0.0)
		{
			isValValid = copy;
			loopAgain = 1;
		}
		// If value is less than 0.0, then fall on this case.
		else
		{
			cout << "Value is invalid. Please enter a valid value: " << endl;
			cin >> copy;
		}
	}
}


int main()
{
	/* I chose string for three of these variables because they need to take
	 * in spaces, and they are the same type for genre.
	 */
	string choiceAsString;
	string isInputValid;
	string genre;

	/* I needed a float for prices because it could be decimal point.
	 * Min :  1.17549e-038 max: 3.40282e+038
	 */
	float price;

	/* I chose int for these variables because there are certain parts of the
	 * program where they are needed to be an int.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int pages;
	int weight;
	int value;
	int loopAgain = 0;
	int row;
	int column;
	int rowToChange;
	int colToChange;
	// for function 5.
	int rowToSwitch;
	int colToSwitch;


	cout << "Welcome to the Planet Treasure Chest!" << endl;
	cout << "Enter number of rows: " << endl;
	cin >> isInputValid;
	errorPrintRowCol(isInputValid, row);
	cout << "Enter number of columns: " << endl;
	cin >> isInputValid;
	errorPrintRowCol(isInputValid, column);

	// dynamically allocate.
	books** dynamic = new books*[row];
	for(int i = 0; i < row; i++)
	{
		dynamic[i] = new books[column];
	}

	for(int i = 0; i < row; i++)
	{
		for(int j= 0; j < column; j++)
		{
			dynamic[i][j].genre = "empty";
			dynamic[i][j].price = 0;
			dynamic[i][j].weight = 0;
			dynamic[i][j].pages = 0;
		}
	}

	while(loopAgain == 0)
	{
		cout << "Now select an operation!" << endl;
		cout << "(1) Add an item." << endl;
		cout << "(2) Remove an item." << endl;
		cout << "(3) Generate a random item." << endl;
		cout << "(4) Show an individual item." << endl;
		cout << "(5) Switch items." << endl;
		cout << "(6) Quit." << endl;
		cin >> choiceAsString;
		errorPrintValue(choiceAsString, value);

		if(value == 1)
		{
			cout << "Enter row: " << endl;
			cin >> rowToChange;
			cout << "Enter column: " << endl;
			cin >> colToChange;
			rowColOutOfBounds(rowToChange, colToChange, row, column);
			notEmpty(dynamic, rowToChange, colToChange, row, column);
			cin.ignore();

			cout << "Enter genre (string): " << endl;
			getline(cin, genre);

			cout << "Enter price (float): " << endl;
			cin >> price;
			floatCheck(price);

			cout << "Enter weight(int): " << endl;
			cin >> weight;
			intCheck(weight);

			cout << "Enter amount of pages(int): " << endl;
			cin >> pages;
			intCheck(pages);

			addBook(dynamic, genre, price, weight, pages, rowToChange, colToChange);
			overallPrint(dynamic, row, column);
			printPrice(dynamic, row, column);
		}

		else if(value == 2)
		{
			cout << "Enter row: " << endl;
			cin >> rowToChange;

			cout << "Enter column: " << endl;
			cin >> colToChange;
			rowColOutOfBounds(rowToChange, colToChange, row, column);
			emptyErrorPrint(dynamic, rowToChange, colToChange, row, column);
			removeAttributes(dynamic, rowToChange, colToChange);
			overallPrint(dynamic, row, column);
			printPrice(dynamic, row, column);
		}

		else if(value == 3)
		{
			cout << "Enter row: " << endl;
			cin >> rowToChange;

			cout << "Enter column: " << endl;
			cin >> colToChange;
			rowColOutOfBounds(rowToChange, colToChange, row, column);

			randomGenerator(dynamic, rowToChange,colToChange);
			printContent(dynamic, rowToChange, colToChange);
			overallPrint(dynamic, row, column);
			printPrice(dynamic, row, column);
		}

		else if(value == 4)
		{
			cout << "Enter row: " << endl;
			cin >> rowToChange;

			cout << "Enter column: " << endl;
			cin >> colToChange;

			rowColOutOfBounds(rowToChange, colToChange, row, column);
			emptyErrorPrint(dynamic, rowToChange, colToChange, row, column);
			printContent(dynamic, rowToChange, colToChange);
			overallPrint(dynamic, row, column);
			printPrice(dynamic, row, column);
		}

		else if(value == 5)
		{
			cout << "Enter row: " << endl;
			cin >> rowToChange;

			cout << "Enter column: " << endl;
			cin >> colToChange;
			rowColOutOfBounds(rowToChange, colToChange, row, column);
			emptyErrorPrint(dynamic, rowToChange, colToChange, row, column);

			cout << "Enter row you want to switch: " << endl;
			cin >> rowToSwitch;

			cout << "Enter column you want to switch: " << endl;
			cin >> colToSwitch;
			rowColOutOfBounds(rowToSwitch, colToSwitch, row, column);
			emptyErrorPrint(dynamic, rowToChange, colToChange, row, column);

			switchingStuff(dynamic, rowToChange,colToChange,rowToSwitch,colToSwitch);
			overallPrint(dynamic, row, column);
			printPrice(dynamic, row, column);
		}

		else if(value == 6)
		{
			for(int i = 0; i < row; i++)
			{
				delete [] dynamic[i];
				dynamic[i] = NULL;
			}
			delete [] dynamic;
			dynamic = NULL;

			loopAgain = 1;
		}

	}
	return 0;
}
