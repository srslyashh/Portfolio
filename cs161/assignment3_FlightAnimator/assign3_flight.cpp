/*****************************************************
 ** Program: Assignment 3 - Flight Simulator
 ** Author: Kathleen Ashley
 ** Date: February 9 2020
 ** Description: Taking the user input for the game
 ** Input: Integer, one could be negative (windSpeed) and the others cannot be 0.
 ** Output: The output depends on the user's choice, and the output will
 ** come with how long the flight will take, and how much it is gonna cost,
 ** along with animator.
 *****************************************************/

#include <iostream>
#include <math.h>
#include <unistd.h>
#include <iomanip>
#include <cctype>
#include <cstring>
#include <sstream>

using namespace std;

/****************** ** Function: getValue ** **********************
 * ** Description: to check whether input is valid or not.
 * ** Parameters: isValueValid, counter.
 * ** Pre-conditions: check if the value is valid.
 * ** Post-conditions: return 1 or return 0.
 ******************************************************************/
int getValue(string isValueValid, int counter)
{
	/* I chose unsigned int because i should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short i;

	for(i = 0; i < isValueValid.length(); i++)
	{
		/* if counter is 3, the value is taken for windSpeed. so it is OK to be
		 * a negative number.
		 */
		if(counter == 3  && isValueValid[0] == '-' )
		{
			i++;
		}
		if(isValueValid[0] == '0' || isdigit(isValueValid[i]) == false)
		{
			return 1;
		}
	}
	return 0;
}

/****************** ** Function: errorPrintForInt ** **********************
 * ** Description: print error / no if the value destination is int.
 * ** Parameters: value, isValueValid, counter.
 * ** Pre-conditions: check if the value is valid if not, keep on prompting.
 * ** Post-conditions:turn the string into int, and plug it into the value
 * ** destinated.
 ******************************************************************/
void errorPrintForInt(int& value, string isValueValid, int counter)
{
	/* I chose unsigned short because it should never be less than 0.
	 * min 0, max 65535.
	 */
 	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(getValue(isValueValid, counter) == 0)
		{
			loopAgain = 1;
			// turn the string into int.
			stringstream stringToInt(isValueValid);
			// plug the int into the value destinated.
			stringToInt >> value;
		}
		else
		{
			cout << "Invalid input. Enter another integer: " << endl;
			cin >> isValueValid;
		}
	}
}

/****************** ** Function: errorPrintForUnsigned ** **********************
 * ** Description: print error/ no for unsigned int destination.
 * ** Parameters: int&value, isValueValid, counter.
 * ** Pre-conditions: check if the value is valid if not, keep on prompting.
 * ** Post-conditions: turn the string into int, and plug it into the value
 * ** destinated.
 ******************************************************************/
void errorPrintForUnsigned(unsigned int& value, string isValueValid, int counter)
{
	/* I chose unsigned short because it should never be less than 0.
	 * min 0, max 65535.
	 */
 	unsigned short loopAgain = 0;

	while(loopAgain == 0)
	{
		if(getValue(isValueValid, counter) == 0)
		{
			loopAgain = 1;
			// turn the string into int.
			stringstream stringToInt(isValueValid);
			// plug the int into the value destinated.
			stringToInt >> value;
		}
		else
		{
			cout << "Invalid input. Enter another integer: " << endl;
			cin >> isValueValid;
		}
	}
}

/****************** ** Function: duration ** **********************
 * ** Description: to count the duration of flight, and print out the statement.
 * ** Parameters: distance, windSpeed, airSpeed, &flightDuration, &returnFlight.
 * ** Pre-conditions: count the duration.
 * ** Post-conditions: print out how long the flight will take, depending
 * ** whether it is the firstflight or returningflight.
 ******************************************************************/

void duration(int distance, int windSpeed, int airSpeed, int& flightDuration,
int& returnFlight)
{
	/* I assume the number of hour will be more than 0, and never be negative.
	 * Hence, an unsigned short would be perfect. (min 0, max 65,535)
	 */
	unsigned short hour;
	/* I assume the number of minutes will be more than 0 and less than 60,
	 * and never be negative. Therefore, an unsigned short would be perfect.
	 * (min 0, max 65,535)
	 */
	unsigned short minutes;
	/* The remainder of minutes will never be more than 60, and never be less
	 * than zero. An unsigned short would be perfect. (min 0, max 65,535)
	 */
	unsigned short remainderOfMinutes;

	hour = distance / (airSpeed - windSpeed);
	remainderOfMinutes = distance % (airSpeed - windSpeed);
	minutes = (remainderOfMinutes * 60 / (airSpeed - windSpeed));
	flightDuration = hour * 60 + minutes;

	// this is to check if this is returnFlight or not.
	if (returnFlight == 0)
	{
		cout << "Your flight will take " << hour << " hour(s) and " << minutes
			 << " minutes ";
		returnFlight = 1;
	}
	else if(returnFlight == 1)
	{
		cout << "Your return flight will take " << hour << " hour(s) and "
			 << minutes << " minutes ";
	}
}

/****************** ** Function: durationInFloat ** **********************
 * ** Description: to count the duration of flight as a floating point.
 * ** Parameters: distance, windSpeed, airSpeed, &durationAsAFloat
 * ** Pre-conditions: do a calculation.
 * ** Post-conditions: change the value of durationAsAFloat in floating point.
 ******************************************************************/
void durationInFloat(float distance, float windSpeed, float airSpeed,
	float& durationAsAFloat)
{
	durationAsAFloat = distance / (airSpeed - windSpeed);
}

/****************** ** Function: ticketPrice ** **********************
 * ** Description: to count the cost of the flight.
 * ** Parameters: durationAsAFloat, fuelBurnRate, fuelPrice, passengers
 * ** Pre-conditions: count the price of a ticket.
 * ** Post-conditions: print out the ticket price.
 ******************************************************************/
void ticketPrice(float durationAsAFloat, float fuelBurnRate, int fuelPrice,
	int passengers)
{
	/* I chose float for the price so that it holds a floating point.
	 * (min : 1.2e-38, max: 3.4e38)
	 */
	float price;
	price = durationAsAFloat * fuelBurnRate * fuelPrice / passengers;

	cout << "and cost $ " << fixed << setprecision(2) << price << " per person."
			 << endl;
}

/****************** ** Function: animation ** **********************
 * ** Description: print out animation for the first flight.
 * ** Parameters: duration, secOfAnimation, minsInAnHour
 * ** Pre-conditions: duration counted and rounded up.
 * ** Post-conditions: print out animation as many as the rounded duration.
 ******************************************************************/

void animation(float duration, int secOfAnimation, int minsInAnHour = 60)
{
	/* I chose float so that it holds a decimal point.
	 * (min : 1.2e-38, max: 3.4e38)
	 */
	float durationRoundedUp = duration / minsInAnHour;
	/* I chose int for this so that it will round up as an int.
	 * (min -2.147,483,648, max 2147483647).
	 */
	int roundedUp = ceil(durationRoundedUp);

	for(int i = 0; i < roundedUp; i++)
	{
		cout << "*" << flush;
		sleep(secOfAnimation);
	}
	cout << endl;
}

/****************** ** Function: returnAnimation ** *****************
 * ** Description: to count the duration of flight, and print out the statement.
 * ** Parameters: distance, windSpeed, airSpeed, &flightDuration, &returnFlight.
 * ** Pre-conditions: duration counted and rounded up.
 * ** Post-conditions: print out animation from right to left
 * ** as many as the rounded duration.
 ******************************************************************/

void returnAnimation(float duration, int secOfAnimation)
{
	/* I chose float so that it holds a decimal point.
	 * (min : 1.2e-38, max: 3.4e38)
	 */
	float durationRoundedUp = duration / 60;
	/* I chose int for this so that it will round up as an int.
	 * (min -2.147,483,648, max 2147483647).
	 */
	int roundedUp = ceil(durationRoundedUp);
	/* I chose unsigned short because the variable should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short num_u = 1;
	/* I chose unsigned short because the variable should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short num_spaces = roundedUp;
	/* I chose unsigned short because the variable should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short flag = 1;
	/* I chose unsigned short because the variable should never be less than 0.
	 * min 0, max 65535.
	 */
	unsigned short x = 0;

	while(flag <= roundedUp)
	{
		for(int i = 1; i < num_spaces; i++)
		{
			cout << " ";
		}
		num_spaces--;

		cout << "*" << flush;
		sleep(secOfAnimation);
		cout << "\r";

		flag++;
	}
}

/****************** ** Function: intToFloat ** *****************
 * ** Description: take an int and turn it into a float.
 * ** Parameters: int value
 * ** Pre-conditions: int value
 * ** Post-conditions: float value
 ******************************************************************/
float intToFloat(int value)
{
	return float(value);
}

int main()
{
	/* I chose unsigned int because the variable should never be less than 0.
	 * and it is an int so that it can hold large input.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int distance;
	/* I chose unsigned int because the variable should never be less than 0.
	 * min 0, max 4,249,967,295.
	 */
	unsigned int airSpeed;
	/* I chose an int so that windSpeed can be negative numbers,
	 *  min -2,147,483,648, max 2,147,483,647
	 */
	int windSpeed;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int fuelBurnRate;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int fuelPrice;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int passengers;
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int secOfAnimation;
	/* I chose int for this variable because in certain part of the codes,
	 * it is needed for this variable to be an int.
	 * min -2,147,483,648, max 2,147,483,647
	 */
	int flightDuration;
	/* I chose an int for this variable because the returnFlight flag
	 * has to be an unsigned int. (min -2,147,483,648, max 2,147,483,647)
	 */
	int returnFlight = 0;
	/* I chose float so that it holds a decimal point.
	 * (min : 1.2e-38, max: 3.4e38)
	 */
	float durationAsAFloat;
	/* Using string for the input from the user.
	 */
	string isValueValid = "";
	/* I chose unsigned int because the variable should never be less than 0.
	 * and should be able to handle large input. min 0, max 4,249,967,295.
	 */
	unsigned int counter = 1;

	cout << "Welcome to flight animator!" << endl;
	cout << "Please provide the following flight information as desired!"
		 << endl;
	cout << "(1) Flight distance (miles) : " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(distance, isValueValid, counter);
	counter++;

	cout << "(2) Airplane speed (miles per hour): " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(airSpeed, isValueValid, counter);
	counter++;

	cout << "(3) Wind speed (miles per hour): " << endl;
	cin >> isValueValid;
	errorPrintForInt(windSpeed, isValueValid, counter);
	counter++;

	cout << "(4) Fuel burn rate (gallons per hour): " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(fuelBurnRate, isValueValid, counter);
	counter++;

	cout << "(5) Fuel price (dollars per gallon): " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(fuelPrice, isValueValid, counter);
	counter++;

	cout << "(6) Number of people onboard: " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(passengers, isValueValid, counter);
	counter++;

	cout << "(7) Second of animation per flight hour: " << endl;
	cin >> isValueValid;
	errorPrintForUnsigned(secOfAnimation, isValueValid, counter);

	// calling functions for the first flight.
	duration(distance, windSpeed, airSpeed, flightDuration, returnFlight);
	durationInFloat(intToFloat(distance), intToFloat(windSpeed),
					intToFloat(airSpeed), durationAsAFloat);
	ticketPrice(durationAsAFloat, fuelBurnRate, fuelPrice, passengers);
	animation(intToFloat(flightDuration),secOfAnimation);

	// calling functions for the return flight.
	duration(distance, -windSpeed, airSpeed, flightDuration, returnFlight);
	durationInFloat(intToFloat(distance), intToFloat(-windSpeed),
				    intToFloat(airSpeed), durationAsAFloat);
	ticketPrice(durationAsAFloat, fuelBurnRate, fuelPrice, passengers);
	returnAnimation(intToFloat(flightDuration),secOfAnimation);

	return 0;
}
