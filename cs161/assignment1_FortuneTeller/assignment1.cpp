#include <iostream>

using namespace std;

int main()
{
	unsigned short n_dogs;
	unsigned short n_days;
	short temperature;
	unsigned int milestravelled;
	unsigned short age;

	cout << "Please enter a number between 0 and 65535: ";
	cin >> n_dogs; 

	cout << "Please enter the amount of days you would like spending in bed: ";
	cin >> n_days;
	
	cout << "Please enter your desired value from -100 to 100: ";
	cin >> temperature;
	
	cout << "Please enter a value between 0 and 4,249,967,295(without commas): ";
	cin >> milestravelled;
	
	cout << "Please enter the age of the oldest person you know: ";
	cin >> age;

	cout << "You will have " << n_dogs << " dogs to take care of you." << endl;

	cout << "You will experience " << n_days << " days at " << temperature
	<< " F." << endl;

	cout << "You will have travelled " << milestravelled
	<< " miles by the time you are " << age << " years old." << endl;

	return 0;
}
