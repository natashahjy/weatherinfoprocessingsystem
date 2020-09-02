/*
Done By: Natasha Jeng Yee Heng
Student Number: 6959684
Subject: CSCI251 Assignment 1
*/

#include <fstream>
#include <string>
#include <iostream>
#include <vector>
#include <iomanip>
#include <algorithm>

using namespace std;

struct Citylocation {
	string coord;
	int cityid;
	string cityname;
};

// function prototype of readConfigfile
vector <string> readConfigFile();

// function prototype of readCityFile
void readCityFile(string, int, int);

// function prototype of readCloudFile
void readCloudFile(string, int, int, int);

// function prototype of readPressureFile
void readPressureFile(string, int, int, int);

// function prototype of printmenu
void printMenu();

// function prototype of promptUserChoice
int promptUserChoice();

// function prototype of choiceOutcome
int choiceOutcome(int, int, int, string, string, string);

// function prototype of splitString
vector<string> splitString (string, string);

// function prototype of find max x and find max y values
int findMaxValue(string);

// format gridRange
string formatGridRange(string);

// processing citylocation.txt
void initialiseCity(int, int, int, string*, string*);

void displayCity(string **, int, int);

// filtering for cloud and pressure values
string getSymbol(int);

string getIndex(int);

// processing cloudcover.txt
void initialiseCloud(int, int, int, string*, string*, int);

void displayCloud(string **, int, int);

// processing pressure.txt
void initialisePressure(int, int, int, string*, string*, int);

void displayPressure(string **, int, int);

// choice 7
void processReportValues(int xMax, int yMax, string cityLocationFileName, string cloudCoverFileName, string pressureFileName);

vector <Citylocation> storeCityLocation(string, int, int);

vector <int> findUniqueCityId(vector<Citylocation>);

vector <string> findUniqueCityName(vector<Citylocation>);

vector <int> findOccurences(vector<int>, vector<Citylocation>);

vector <string> defineColumns(vector<int>, vector<int>);

vector<vector<string> > init2dVector(vector<int>, vector<Citylocation>);

vector<vector<string> > findPoint(vector<vector<string> >, vector<int>, vector<string>, vector<int>, int, int);

vector <string> findFourCornersCoordinates(string, string, int, int);

int findXCoordinate(string);

int findYCoordinate(string);

vector <string> storeCorner(int, int);

int findNumberOfPointsBetween(int, int);

vector <string> findSideLeftPerimeter(int, int, int, int);

vector <string> findSideTopPerimeter(int, int, int, int);

vector <string> findSideRightPerimeter(int, int, int, int);

vector <string> findSideBottomPerimeter(int, int, int, int);

vector <string> findPerimeter(vector <string>, vector <string>, vector <string>, vector <string>, vector <string>);

vector<vector<string> > findPerimeterById(vector<string>, vector<int>, vector<int>);

void extractXYFromCoordinates(vector<vector<string> >, vector<int>);

// find ACC and AP
void findAverage(vector<int>, vector <string>, vector<vector<string> >, vector<vector<string> >, int, int, string, string);

// cloud:
int readCloudFile(string, int, int, vector<int>, vector<int>);
string ** findCloudArray(int, int, int, string*, string*);
int findCloudValue(string **, vector<int>, vector<int>, int, int);

// pressure: 
int readPressureFile(string, int, int, vector<int>, vector<int>);
string ** findPressureArray(int, int, int, string*, string*);
int findPressureValue(string **, vector<int>, vector<int>, int, int);

void displayReport(vector<int>, vector <string>, double [], double []);

int getProbability(string, string);

void displayGraphics(int);

// check if xCoordinate/yCoordinate are inside grid
bool is_valid(int check, int max)
{
	if (check >=0  && check <= max)
		return true;
	else
		return false;
}

// sort by city id
bool sortbyId(const Citylocation &lhs, const Citylocation &rhs){return lhs.cityid < rhs.cityid;}
//--------------------------------------------

int main() {

	// variables to initialise
	string gridXRange;
	string gridYRange;
	string cityLocationFileName;
	string cloudCoverFileName;
	string pressureFileName;
	
	int xMax;
	int yMax;
	
	int choice;

	// vector that stores values of variables to initialise
	vector <string> configVar;

	// calls function printMenu to display menu
	PRINTMENU:printMenu();
	
	// calls function promptUserChoice to ask for user's choice
	choice = promptUserChoice();

	if (choice == 8)
		exit(0);
		
	else if (choice != 1)
	{ 	
		cout << "Please choose option 1 to enter configuration file before choosing choices 2-7" << endl;
		cout << endl;
		goto PRINTMENU;
	}
	
	if (choice == 1)
	{
		cout << endl;
		cout << "[ Read in and process a configuration file ]" << endl;
			
		// calls readConfigFile function
		configVar = readConfigFile();
	
		// initialise variables
		gridXRange = configVar[0];
		gridYRange = configVar[1];
		cityLocationFileName = configVar[2];
		cloudCoverFileName = configVar[3];
		pressureFileName = configVar[4];

		cout << "Reading in GridX_IdxRange : " << configVar[0] << " ... done!" << endl;
		cout << "Reading in GridY_IdxRange : " << configVar[1] << " ... done!" << endl;
		cout << endl;
		cout << "Storing data from input file : " << endl; 
		cout << configVar[2] << " ... done!" << endl;
		cout << configVar[3] << " ... done!" << endl;
		cout << configVar[4] << " ... done!" << endl;
		cout << endl;

		cout << "All records successfully stored. Going back to main menu ..." << endl;
		cout << endl;
	}

	// after choice 1 has been processed
	printMenu();
	choice = promptUserChoice();
	// Find size of grid
	xMax = findMaxValue(gridXRange);
	yMax = findMaxValue(gridYRange);

	// calls choiceOutcome() function to process choices 2-7
	while (choice >1 && choice <8)
	{
		choice = choiceOutcome(choice, xMax, yMax, cityLocationFileName, cloudCoverFileName, pressureFileName);
	}
	return 0;
}

// prompts for user's choice
int promptUserChoice() 
{
	int choice;
	// prompt user to enter your choice
	cout << "Please enter your choice : ";
	cin >> choice;
	// check for valid input
	if (cin.good())
		return choice;
	
}

// choiceOutcome()
int choiceOutcome(int choice, int xMax, int yMax, string cityLocationFileName, string cloudCoverFileName, string pressureFileName)
{
	switch (choice)
	{
		case 2:
		{
			readCityFile(cityLocationFileName, xMax, yMax);
			
			// wait for user input
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			}
			break;	
		}
		case 3: 
		{
			readCloudFile(cloudCoverFileName, xMax, yMax, choice);

			// wait for user input
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			}
			break;			
		}
		case 4:
		{
			readCloudFile(cloudCoverFileName, xMax, yMax, choice);

			// wait for user input
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			} 
			break;	
		}
		case 5: 
		{
			readPressureFile(pressureFileName, xMax, yMax, choice);

			// wait for user input
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			}
			break;
		}
		case 6:
		{
			readPressureFile(pressureFileName, xMax, yMax, choice);
	
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			}
			break;
		}
		case 7:
		{
			processReportValues(xMax, yMax, cityLocationFileName, cloudCoverFileName, pressureFileName);
			
			do {
				cout << '\n' << "Press <enter> to go back to main menu..." <<endl;
			} while (cin.get()!='\n');
			if (cin.get() == '\n')
			{
				printMenu();
				choice = promptUserChoice();
				return choice;
			}
			break;
		}
		case 8:
			exit(0);
	}
}

// splitString
// takes in two strings input and delimiter
// loops input to find delimiter and splits
// stores into a vector string result
// returns a vector string result
vector<string> splitString (string input, string delimiter)
{
	size_t pos = 0;
	string token;
	vector<string> result;

	while ((pos = input.find(delimiter)) != string::npos) 
	{
    		token = input.substr(0, pos);
    		result.push_back (token);
		input.erase(0, pos + delimiter.length());
	}

	result.push_back (input);

	return (result);
}

// format grid range
string formatGridRange(string gridRange){
	vector<string> tokenStringVector = splitString (gridRange, "=");
	string gridVal;	
	
	cout << endl;
	for (int i=0; i<tokenStringVector.size(); i++)
	{
		//cout << tokenStringVector [i] << endl;
		gridVal = tokenStringVector[i];
	}		

	tokenStringVector.clear();
	
	return gridVal;	
}


int findMaxValue(string rangeValues){
	int max;
	vector <string> tokenStringVector = splitString (rangeValues, "-");
	for (int i=0; i<tokenStringVector.size(); i++)
	{
		// xMax is the end range of grid x
		// yMax is the end range of grid y
		max = stoi(tokenStringVector[i]);
		
	}
	return max;
}


// readConfigFile reads contents in fileName
vector <string> readConfigFile() {
	string fileName;
	
	// prompt user for configuration filename	
	cout << "Please enter config filename: ";
	cin >> fileName;

	ifstream readFile (fileName);
	string content;
	string gridXRange;
	string gridYRange;
	string cityLocationFileName;
	string cloudCoverFileName;
	string pressureFileName;

	// xMax is the end range of grid x
	int xMax;

	// yMax is the end range of grid y
	int yMax;
	

	if (readFile.is_open())
	{
		int counter = 0;
	
		while (getline(readFile,content))
		{
			// ignore comments and empty lines
			if (content[0] != '/' && content[1] != '/' && !content.empty())
			{
				// display output for debugging
				//cout << content << endl;

				// store variables
				switch (counter)
				{
				case 0:
					gridXRange = content;
					break;
				case 1:
					gridYRange = content;
					break;
				case 2:
					cityLocationFileName = content;
					break;
				case 3:
					cloudCoverFileName = content;
					break;
				case 4:
					pressureFileName = content;
					break;
				
				}
				
				counter++;	
			}	
		}
		readFile.close();
	
		////////////////////////////////////////////////////////
		// extracting range value of grid x range
		string gridXVal;
		
		gridXVal = formatGridRange(gridXRange);
		////////////////////////////////////////	
	
		// extracting range val of grid y range
		string gridyval;

		gridyval = formatGridRange(gridYRange);
		////////////////////////////////////////////////////////

		// return to int main()
		vector <string> result;
		result.push_back(gridXVal);
		result.push_back(gridyval);
		result.push_back(cityLocationFileName);
		result.push_back(cloudCoverFileName);
		result.push_back(pressureFileName);
		return result;
	}
	else
		cout << "Unable to open file";
}

// readCityFile
void readCityFile(string fileName, int xMax, int yMax)
{
	ifstream readFile (fileName);
	string content;
	
	if (readFile.is_open())
	{
		vector <string> city;
	
		while (getline(readFile,content)) 
		{
			// store citylocation values into vector city			
			if (content.size() > 0) 
				city.push_back(content);
		}
		
		// dynamically create arrays for coordinates, Id, name
		string *cityCoordinates = nullptr;
		cityCoordinates = new string[city.size()];

		string *cityId = nullptr;
		cityId = new string[city.size()];

		string *cityName = nullptr;
		cityName = new string[city.size()];

		for (int i=0; i<city.size(); i++)
		{
			string data = city[i];
			// split string in city vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				cityCoordinates[i] = tokenStringVector[0];
				cityId[i] = tokenStringVector[1];
				cityName[i] = tokenStringVector[2];
			}	
		}
		
		readFile.close();

		// delete to free memory
		delete [] cityName;

		// initialise
		initialiseCity(city.size(), xMax, yMax, cityCoordinates, cityId);		
	}

	else
		cout << "Unable to open file";	
}

void initialiseCity(int size, int xMax, int yMax, string* cityCoordinates, string* cityId)
{
	// finding x and y coordinates to display city map
	int * xCoordArrayPtr = nullptr;
	int * yCoordArrayPtr = nullptr;

	xCoordArrayPtr = new int[size];
	yCoordArrayPtr = new int[size];

	//cout << "before " << cityCoordinates[0] << endl;
	// remove [ ] from cityCoordinates
	for (int index =0; index < size; index++)
	{
		// remove '[' and ']' characters
		string temp = cityCoordinates[index].substr(1, cityCoordinates[index].size()-2);
		cityCoordinates[index] = temp;
		
		//storing into int arrays xCoord and yCoord
		string data = cityCoordinates[index];
		// split string of cityCoordinates 
		vector<string> tokenStringVector = splitString (data, ", ");

		for (int k=0; k<tokenStringVector.size(); k++)
		{
			// store split strings in various int arrays
			xCoordArrayPtr[index] = stoi(tokenStringVector[0]);
			yCoordArrayPtr[index] = stoi(tokenStringVector[1]);
		}
		
	}
	//cout << "after "<< cityCoordinates[0] << endl;
	//cout << "x coord" << xCoord[0] << endl;
	//cout << "y coord" << yCoord[0] << endl;
		
	// populate grid array after matching with values in city location
	// create grid array 
	
	// map formatting
	int x=xMax+3;
	int y=yMax+2;
	int count = 0;
	
	////////////////////////////////////////
	// init cityArray
	////////////////////////////////////////
	string ** cityArray = nullptr;
	cityArray = new string * [y];
	for (int m=0; m<y; m++)
		cityArray[m] = new string[x];

	////////////////////////////////////////	
	// populate cityArray
	////////////////////////////////////////
	for (int row = 0; row < y; row++)
	{
		for (int col = 0; col < x; col++)
		{
			// TODO in the case that it doesn't start in sequence
			// note that this applies for cloud, pressure values
			// City1 [2, 8] --> City2 [2, 2]
			// this code does not handle inputs of lower value
			// the code only increments, after it passed the higher values it will return to 
			// check smaller values
			if(row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
			{
				cityArray[row][col] = cityId[count];
				count++;
			}
			else
			{
				cityArray[row][col] = " ";
			}
		}
	}

	// delete to free memory
	delete [] cityCoordinates;
	delete [] cityId;
	
	// delete to free memory
	delete [] xCoordArrayPtr;
	delete [] yCoordArrayPtr;

	// displayCity
	displayCity(cityArray, x, y);


}

void displayCity(string ** cityArray, int x, int y) 
{
	////////////////////////////////////////////////
	// display cityMap
	////////////////////////////////////////////////		
	int height;
	int width;
	height = y;
	width = x;
	int yAxis = y-2;
	//int yAxis = y;	
	
	for (int p=height; p>=0; p--)
	{
		cout << endl;
		if (p == 0 || p == height)
			cout << setw(3) << " ";
		// print the y axis labels
		else
		{
			if (yAxis > 9)
			{
				cout << setw(1) << " ";
				cout << yAxis;
			}
			else 
			{
				cout << setw(2) << " ";
				cout << yAxis;
			}
			yAxis--;
		}
		for (int q=0; q< width; q++)
		{
			if(p==0 || p == height || q ==0 || q == width-1)
				cout << setw(3) << "#";

			else
				//cout << "  ";
				cout << setw(3) << cityArray[q-1][p-1];		
		}
	}
	// print x axis labels
	cout << endl;
	for (int xAxis=0; xAxis < width-1; xAxis++)
	{
		if (xAxis==0)			
			cout << setw(6) << " ";
		else
			cout << setw(3) << xAxis-1;
		
	}
	cout << endl;

	// deallocate memory for cityArray
	for (int s=0; s<y; s++)
		delete [] cityArray[s];
 
	delete [] cityArray;
}

// readCloudFile
void readCloudFile(string fileName, int xMax, int yMax, int choice) 
{
	//cout << fileName;
	ifstream readFile (fileName);
	string content;
	if (readFile.is_open())
	{
		vector <string> cloud;

		while (getline(readFile,content)) 
		{
			// store cloudcover values into vector cloud			
			if (content.size() > 0) 
				cloud.push_back(content);
		}
		
		// dynamically create array for coordinates and cloudcover
		string *cloudCoordinates = nullptr;
		cloudCoordinates = new string[cloud.size()];

		string *cloudCover = nullptr;
		cloudCover = new string[cloud.size()];

		for (int i=0; i<cloud.size(); i++)
		{
			string data = cloud[i];
			// split string in cloud vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				cloudCoordinates[i] = tokenStringVector[0];
				cloudCover[i] = tokenStringVector[1];
			}
		}
		readFile.close();
		
		// initialise
		initialiseCloud(cloud.size(), xMax, yMax, cloudCoordinates, cloudCover, choice);
	}
	else
		cout << "Unable to open file";	
}

// initialises array based on choice
void initialiseCloud(int size, int xMax, int yMax, string* cloudCoordinates, string* cloudCover, int choice)
{
	int * xCoordArrayPtr = nullptr;
	int * yCoordArrayPtr = nullptr;

	xCoordArrayPtr = new int[size];
	yCoordArrayPtr = new int[size];

	for (int index = 0; index < size; index++)
	{
		// remove '[' and ']' characters
		string temp = cloudCoordinates[index].substr(1, cloudCoordinates[index].size()-2);
		cloudCoordinates[index] = temp;
		
		// storing into int arrays xCoord and yCoord
		string data = cloudCoordinates[index];
		// split string of cityCoordinates 
		vector<string> tokenStringVector = splitString (data, ", ");

		for (int m=0; m<tokenStringVector.size(); m++)
		{
			// store split strings in various int arrays
			xCoordArrayPtr[index] = stoi(tokenStringVector[0]);
			yCoordArrayPtr[index] = stoi(tokenStringVector[1]);
		}
	}
	
	// storing int version of cloudCover array		
	int cloudCoverVal[size];
	
	// create cloud grid array 
	int x = xMax + 3;
	int y = yMax + 2;
	int count = 0;

	////////////////////////////////////////
	// init cloudArray
	////////////////////////////////////////
	string ** cloudArray = nullptr;
	cloudArray = new string * [y];
	for (int m=0; m<y; m++)
		cloudArray[m] = new string[x];
 
	// cloudinessIndex
	if (choice == 3)
	{
		//////////////////////////////////////////
		// Extracting cloud value from cloud cover array
		// Categorising cloudiness index
		//////////////////////////////////////////

		// storing categorised values of cloud 
		string cloudinessIndex[size];

		for (int i=0; i < size; i++)
		{
			string cloudVal = cloudCover[i];
			int cloudValues = stoi(cloudVal);
			cloudCoverVal[i] = cloudValues;

			cloudinessIndex[i] = getIndex(cloudCoverVal[i]);
		}

		// populate cloud grid array after matching with values in cloud location
	
		////////////////////////////////////////	
		// populate cloudArray
		////////////////////////////////////////
		for (int row = 0; row < y; row++)
		{
			for (int col = 0; col < x; col++)
			{	
				if (row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
				{
					cloudArray[row][col] = cloudinessIndex[count];					
					count++;
				}
				else
				{
					cloudArray[row][col] = " ";
				}
			}
		}
		
		// delete to free memory
		delete [] xCoordArrayPtr;
		delete [] yCoordArrayPtr;

		// delete to free memory
		delete [] cloudCoordinates;
		delete [] cloudCover;

		// display cloudiness Index
		displayCloud(cloudArray, x, y);
	}

	// cloudinessSymbol (LMH)
	if (choice == 4)
	{
		//////////////////////////////////////////
		// Extracting cloud value from cloud cover array
		// Categorising cloudiness symbol
		//////////////////////////////////////////
		// storing categorised values of cloud 
		string cloudinessSymbol[size]; 

		for (int i=0; i < size; i++)
		{
			string cloudVal = cloudCover[i];
			int cloudValues = stoi(cloudVal);
			cloudCoverVal[i] = cloudValues;

			cloudinessSymbol[i] = getSymbol(cloudCoverVal[i]);
		}
		
		// populate cloud grid array after matching with values in cloud location

		////////////////////////////////////////	
		// populate cloudArray
		////////////////////////////////////////
		for (int row = 0; row < y; row++)
		{
			for (int col = 0; col < x; col++)
			{	
				if (row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
				{
					cloudArray[row][col] = cloudinessSymbol[count];					
					count++;
				}
				else
				{
					cloudArray[row][col] = " ";
				}
			}
		}
		
		// delete to free memory
		delete [] xCoordArrayPtr;
		delete [] yCoordArrayPtr;

		// delete to free memory
		delete [] cloudCoordinates;
		delete [] cloudCover;

		// display cloudiness Symbols (LMH)
		displayCloud(cloudArray, x, y);
	}
}

void displayCloud(string ** cloudArray, int x, int y) 
{
	// display cloud map
	int height;
	int width;
	height = y;
	width = x;
	int yAxis = y-2;
	
	for (int p=height; p>=0; p--)
	{
		cout << endl;
		if (p == 0 || p == height)
			cout << setw(3) << " ";
		// print the y axis labels
		else
		{
			if (yAxis > 9)
			{
				cout << setw(1) << " ";
				cout << yAxis;
			}
			else 
			{
				cout << setw(2) << " ";
				cout << yAxis;
			}
			yAxis--;
		}
		for (int q=0; q< width; q++)
		{
			if(p==0 || p == height || q ==0 || q == width-1)
				cout << setw(3) << "#";

			else
				//cout << "  ";
				cout << setw(3) << cloudArray[q-1][p-1];		
		}
	}
	// print x axis labels
	cout << endl;
	for (int xAxis=0; xAxis < width-1; xAxis++)
	{
		if (xAxis==0)			
			cout << setw(6) << " ";
		else
			cout << setw(3) << xAxis-1;
			
	}
	cout << endl;

	// deallocate memory for cloudArray
	for (int s=0; s<y; s++)
		delete [] cloudArray[s];
 
	delete [] cloudArray;

}

// readPressureFile
void readPressureFile(string fileName, int xMax, int yMax, int choice)
{
	ifstream readFile (fileName);
	string content;

	if (readFile.is_open())
	{
		vector <string> pressure;

		while (getline(readFile,content)) 
		{
			// store pressure values into vector pressure		
			if (content.size() > 0) 
				pressure.push_back(content);
		}
	
		// dynamically create array for coordinates and atmosphericPressure
		string *pressureCoordinates = nullptr;
		pressureCoordinates = new string[pressure.size()];

		string *atmosphericPressure = nullptr;
		atmosphericPressure = new string[pressure.size()];

		for (int i=0; i<pressure.size(); i++)
		{
			string data = pressure[i];
			// split string in cloud vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				pressureCoordinates[i] = tokenStringVector[0];
				atmosphericPressure[i] = tokenStringVector[1];
			}
		}
		readFile.close();

		// initialise
		initialisePressure(pressure.size(), xMax, yMax, pressureCoordinates, atmosphericPressure, choice);
	}
	else 
		cout << "Unable to open file";
}

void initialisePressure(int size, int xMax, int yMax, string* pressureCoordinates, string* atmosphericPressure, int choice)
{
	int * xCoordArrayPtr = nullptr;
	int * yCoordArrayPtr = nullptr;

	xCoordArrayPtr = new int[size];
	yCoordArrayPtr = new int[size];


	for (int index = 0; index < size; index++)
	{
		
		// remove '[' and ']' characters
		string temp = pressureCoordinates[index].substr(1, pressureCoordinates[index].size()-2);
		pressureCoordinates[index] = temp;
		
		//storing into int arrays xCoord and yCoord
		string data = pressureCoordinates[index];
		// split string of cityCoordinates 
		vector<string> tokenStringVector = splitString (data, ", ");

		for (int i=0; i<tokenStringVector.size(); i++)
		{
			// store split strings in various int arrays
			xCoordArrayPtr[index] = stoi(tokenStringVector[0]);
			yCoordArrayPtr[index] = stoi(tokenStringVector[1]);
		}
	}
	
	// storing int version of atmosphericPressure array		
	int atmosphericPressureVal[size];

	// create pressure grid array 
	int x = xMax + 3;
	int y= yMax + 2;
	int count = 0;

	////////////////////////////////////////
	// init pressureArray
	////////////////////////////////////////
	string ** pressureArray = nullptr;
	pressureArray = new string * [y];
	for (int m=0; m<y; m++)
		pressureArray[m] = new string[x];

	// pressureIndex
	if (choice == 5)
	{
		//////////////////////////////////////////
		// Extracting pressure value from atmospheric pressure array
		// Categorising pressure index
		//////////////////////////////////////////

		// storing categorised values of pressure 
		string pressureIndex[size];

		for (int idx=0; idx < size; idx++)
		{
			string pressureVal = atmosphericPressure[idx];
			int pressureValues = stoi(pressureVal);
			atmosphericPressureVal[idx] = pressureValues;

			pressureIndex[idx] = getIndex(atmosphericPressureVal[idx]);
		}

		// populate pressure grid array after matching with values in pressure location
	
		////////////////////////////////////////
		// populate pressurearray
		////////////////////////////////////////
		for (int row = 0; row < y; row++)
		{
			for (int col = 0; col < x; col++)
			{	
				if(row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
				{
					pressureArray[row][col] = pressureIndex[count];					
					count++;
				}
				else
				{
					pressureArray[row][col] = " ";
				}
			}
		}
		// delete to free memory
		delete [] pressureCoordinates;
		delete [] atmosphericPressure;

		// delete to free memory
		delete [] xCoordArrayPtr;
		delete [] yCoordArrayPtr;

		// display pressure Index
		displayPressure(pressureArray, x, y);
	}
	
	// pressure Symbol (LMH)
	if (choice == 6)
	{
		//////////////////////////////////////////
		// Extracting pressure value from atmospheric pressure array
		// Categorising pressure symbol
		//////////////////////////////////////////

		// storing categorised values of pressure 
		string pressureSymbol[size];

		for (int idx=0; idx < size; idx++)
		{
			string pressureVal = atmosphericPressure[idx];
			int pressureValues = stoi(pressureVal);
			atmosphericPressureVal[idx] = pressureValues;

			pressureSymbol[idx] = getSymbol(atmosphericPressureVal[idx]);
		}

		// populate pressure grid array after matching with values in pressure location
	
		////////////////////////////////////////
		// populate pressurearray
		////////////////////////////////////////
		for (int row = 0; row < y; row++)
		{
			for (int col = 0; col < x; col++)
			{	
				if(row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
				{
					pressureArray[row][col] = pressureSymbol[count];					
					count++;
				}
				else
				{
					pressureArray[row][col] = " ";
				}
			}
		}

		// delete to free memory
		delete [] pressureCoordinates;
		delete [] atmosphericPressure;

		// delete to free memory
		delete [] xCoordArrayPtr;
		delete [] yCoordArrayPtr;

		// display pressure Index
		displayPressure(pressureArray, x, y);
	}
}


void displayPressure(string ** pressureArray, int x, int y) 
{
	// display cloud map
	int height;
	int width;
	height = y;
	width = x;
	int yAxis = y-2;
	
	for (int p=height; p>=0; p--)
	{
		cout << endl;
		if (p == 0 || p == height)
			cout << setw(3) << " ";
		// print the y axis labels
		else
		{
			if (yAxis > 9)
			{
				cout << setw(1) << " ";
				cout << yAxis;
			}
			else 
			{
				cout << setw(2) << " ";
				cout << yAxis;
			}
			yAxis--;
		}
		for (int q=0; q< width; q++)
		{
			if(p==0 || p == height || q ==0 || q == width-1)
				cout << setw(3) << "#";

			else
				//cout << "  ";
				cout << setw(3) << pressureArray[q-1][p-1];		
		}
	}
	// print x axis labels
	cout << endl;
	for (int xAxis=0; xAxis < width-1; xAxis++)
	{
		if (xAxis==0)			
			cout << setw(6) << " ";
		else
			cout << setw(3) << xAxis-1;
	}
	cout << endl;

	// deallocate memory for pressureArray
	for (int s=0; s<y; s++)
		delete [] pressureArray[s];
 
	delete [] pressureArray;

}

// getSymbol
string getSymbol(int value){
	if (value >=0 && value < 35)
	{
		return "L";
	}
	else if (value >= 35 && value < 65)
	{
		return "M";
	}
	else if (value >= 65 && value < 100)
	{
		return "H";
	}
}

// getIndex
string getIndex(int value){
	if (value >= 0 && value < 10)
	{
		return "0";
	} 
	else if (value >= 10 && value < 20)
	{
		return "1";
	}
	else if (value >= 20 && value < 30)
	{
		return "2";
	}
	else if (value >= 30 && value < 40)
	{
		return "3";
	}
	else if (value >= 40 && value < 50)
	{
		return "4";
	}
	else if (value >= 50 && value < 60)
	{
		return "5";
	}
	else if (value >= 60 && value < 70)
	{
		return "6";
	}
	else if (value >= 70 && value < 80)
	{
		return "7";
	}
	else if (value >= 80 && value < 90)
	{
		return "8";
	}
	else if (value >= 90 && value < 100)
	{
		return "9";
	}
}

void processReportValues(int xMax, int yMax, string cityLocationFileName, string cloudCoverFileName, string pressureFileName)
{
	/*
		1. Find city location values and store
		2. Filter by city id and store city area coordinates
		3. Filter by city id and store city perimeter coordinates
			3a. Find perimeter by identifying the first point of city area 
			3b. Find perimeter by identifying the last point of city area
			3c. Find the 4 corners, find the number of points between each corner
			3d. Sides that are out of grid range are filtered out
		4. Find average after matching with cloudFile and pressureFile
		5. Display values
	*/

	vector <Citylocation> cityLocation;
	cityLocation = storeCityLocation(cityLocationFileName, xMax, yMax);

	// sort the vector by id
	sort(cityLocation.begin(), cityLocation.end(), sortbyId);

	// find unique city id
	vector <int> uniqueCityId = findUniqueCityId(cityLocation);

	// find unique city name
	vector <string> uniqueCityName = findUniqueCityName(cityLocation);

	// find city occurences
	vector<int> cityOccurences = findOccurences(uniqueCityId,cityLocation);

	// define and initialise columns
	vector<string> cityCol = defineColumns(uniqueCityId, cityOccurences);

	// initialise and populate 2d vector for city area values
	vector<vector<string> > citylocationById = init2dVector(uniqueCityId, cityLocation);

	// findPoint
	vector<vector<string> > cityPerimeterById;
	cityPerimeterById = findPoint(citylocationById, cityOccurences, cityCol, uniqueCityId, xMax, yMax);	
	// find average values of cloud and pressure
	findAverage(uniqueCityId, uniqueCityName, citylocationById, cityPerimeterById, xMax, yMax, cloudCoverFileName, pressureFileName);
}
//////////////////////////////////////////////////////////////////////////////////////////////////////

// reads and storeCityLocation in vector type Citylocation struct
vector <Citylocation> storeCityLocation(string fileName, int xMax, int yMax)
{
	ifstream readFile (fileName);
	string content;
	
	vector <Citylocation> cityLocation;

	if (readFile.is_open())
	{
		vector <string> city;	
		Citylocation cl;
	
		while (getline(readFile,content)) 
		{
			// store cityLocation values into vector city			
			if (content.size() > 0) 
				city.push_back(content);
		}

		for (int i=0; i<city.size(); i++)
		{
			//cout << city[i] << endl;
			string data = city[i];
			// split string in city vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				cl.coord = tokenStringVector[0];
				cl.cityid = stoi(tokenStringVector[1]);
				cl.cityname = tokenStringVector[2];
				
			}
			// add to vector cityLocation using cl struct
			cityLocation.push_back(cl);	
		}
		readFile.close();	
	}

	else
		cout << "Unable to open file";	

	return cityLocation;
}

// identify unique city ids
vector <int> findUniqueCityId(vector<Citylocation> cityLocation)
{
	vector <int> uniqueCityId;
	vector <int>::iterator uc;

	for(int i=0; i<cityLocation.size(); i++)
	{
		uniqueCityId.push_back(cityLocation[i].cityid);
	}

	// use unique algorithm (filter)
	// removes repeated values
	uc = unique(uniqueCityId.begin(), uniqueCityId.end());

	// resize vector, remove undefined terms
	uniqueCityId.resize(distance(uniqueCityId.begin(), uc));

	return uniqueCityId;
}

// identify unique city names
vector <string> findUniqueCityName(vector<Citylocation> cityLocation)
{
	vector <string> uniqueCityName;
	vector <string>::iterator uc;

	for(int i=0; i<cityLocation.size(); i++)
	{
		uniqueCityName.push_back(cityLocation[i].cityname);
	}

	// use unique algorithm (filter)
	// removes repeated values
	uc = unique(uniqueCityName.begin(), uniqueCityName.end());

	// resize vector, remove undefined terms
	uniqueCityName.resize(distance(uniqueCityName.begin(), uc));

	return uniqueCityName;
}

// find the occurences of city from file
vector <int> findOccurences(vector<int> uniquecityid, vector<Citylocation> cityLocation) 
{
	int size = uniquecityid.size();
	vector<int> cityOccurences;

	for (int i = 0; i < size; i++) {
			
		// using lambdas to find frequency of element (cityid) in vector(cityLocation)
		int condition = uniquecityid.at(i);
			
		int count = count_if(cityLocation.begin(), cityLocation.end(), 
			[&](const Citylocation& c1) {
				return c1.cityid == condition;
			});
		cityOccurences.push_back(count);
		//cout << "count: "<< cityOccurences[i] << endl;
	}
	return cityOccurences;
}

// create columns for 2d vector citylocationById
vector <string> defineColumns(vector<int> uniquecityid, vector<int> cityOccurences)
{
	int size = uniquecityid.size();
	// define cols
	vector<string> citycol;

	// input number of columns in (i+1)th row
	// store into vector cityidcol
	for (int i = 0; i < size; i++){
		citycol.push_back(to_string(cityOccurences[i]));
	}
	
	return citycol;
}

// store area coordinates for each city by city id
vector<vector<string> > init2dVector(vector<int> uniquecityid, vector<Citylocation> cityLocation)
{
	// define 2d vector
	vector<vector<string> > citylocationById;

	for (int i = 0; i < uniquecityid.size(); i++) {
		int ucidval = uniquecityid.at(i);
		
		// define temp vector
		vector <string> tempvect;
		
		for (int j =0; j<=cityLocation.size();j++)
		{	
			int citylocationidval = cityLocation[j].cityid;

			// if cityId in cityLocation matches uniquecity
			if (citylocationidval == ucidval){
				// fill temp vector with values for (i+1)th row from top
				tempvect.push_back(cityLocation[j].coord);
			}
		}				
		// save created row into citylocationById
		citylocationById.push_back(tempvect);
	}
	return citylocationById;
}

// store perimeter coordinates for each city by city id

// for each city find the first point & last point coordinates
// return 2d vector that has each city's coordinates (perimeter)
vector<vector<string> > findPoint(vector<vector<string> > citylocationById, vector<int> cityOccurences, vector<string> cityCol, vector<int> uniquecityid, int xMax, int yMax)
{
	vector <string> tempCity;
	vector <string> allCity;
	int size;
	// number of perimeter coordinates in a city
	vector <int> cityPerimeterSize;

	for (int i=0;i < citylocationById.size();++i)
	{
		for (int j=0; j<cityCol[i].size();++j)
		{
			// size of city is 1
			if (cityOccurences[i] < 2)
			{
				string firstPoint = citylocationById[i][j];

				tempCity = findFourCornersCoordinates(firstPoint, " ", xMax, yMax);
				size = tempCity.size();
				cityPerimeterSize.insert(cityPerimeterSize.begin(), size);
				allCity.insert(allCity.begin(), tempCity.begin(), tempCity.end());
			} 
			// size of city is > 1
			else 
			{
				string firstPoint = citylocationById[i].front();

				string lastPoint = citylocationById[i][citylocationById[i].size()-1]; 

				tempCity = findFourCornersCoordinates(firstPoint, lastPoint, xMax, yMax);
				size = tempCity.size();
				cityPerimeterSize.insert(cityPerimeterSize.end(), size);
				allCity.insert(allCity.end(), tempCity.begin(), tempCity.end());

			}
		}
	}
	vector<vector<string> > cityPerimeterById;
	cityPerimeterById = findPerimeterById(allCity, uniquecityid, cityPerimeterSize);
	return cityPerimeterById;
}

// for each city find the surrounding coordinates (perimeter)
vector<vector<string> > findPerimeterById(vector<string> tempCity, vector<int> uniquecityid, vector<int> cityPerimeterSize)
{
	// define 2d vector
	vector<vector<string> > cityPerimeterById;

	for (int i = 0; i < uniquecityid.size(); i++) {
		// define temp vector
		vector <string> tempvect;

		int size = cityPerimeterSize[i];
		//cout << size << endl;

		int count = size;
		
		//for (int j =0; j<tempCity.size();j++)
		for (int j =0; j<cityPerimeterSize[i];j++)
		{	
			if (i == 0)
				tempvect.push_back(tempCity[j]);
			else
			{
				while (count > 0)
				{
					tempCity.erase(tempCity.begin());
					count--;
				}
				tempvect.push_back(tempCity[j]);
			}
			
		}				
		// save created row into citylocationById
		cityPerimeterById.push_back(tempvect);
	}

	return cityPerimeterById;
}

// returns a vector containing coordinates of the perimeter sides that are in the grid
vector <string> findFourCornersCoordinates(string firstPoint, string lastPoint, int xMax, int yMax)
{
	int xCoordinate = findXCoordinate(firstPoint);
	int yCoordinate = findYCoordinate(firstPoint);

	int bottomLeftX = xCoordinate - 1;
	int bottomLeftY = yCoordinate - 1;

	int topRightX;
	int topRightY;
	
	if (lastPoint == " ")
	{
		topRightX = xCoordinate + 1;
		topRightY = yCoordinate + 1;
	} 
	else 
	{
		xCoordinate = findXCoordinate(lastPoint);
		yCoordinate = findYCoordinate(lastPoint);
		
		topRightX = xCoordinate + 1;
		topRightY = yCoordinate + 1;
	}

	int topLeftX = bottomLeftX;
	int topLeftY = topRightY;
	
	int bottomRightX = topRightX; 
	int bottomRightY = bottomLeftY;

	//-----------------------------------------------------------
	// number of points between two corners
	// **********************************************************
	vector <string> leftPerimeter;
	
	// num of left between points
	int numLeft = findNumberOfPointsBetween(topLeftY, bottomLeftY);

	int limit = xMax;

	leftPerimeter = findSideLeftPerimeter(numLeft, bottomLeftX, bottomLeftY, limit);
	// **********************************************************
	vector <string> topPerimeter;
	
	// num of top between points
	int numTop = findNumberOfPointsBetween(topRightX, topLeftX);

	limit = yMax;	
	topPerimeter = findSideTopPerimeter(numTop, topLeftY, topLeftX, limit);
	// **********************************************************
	vector <string> rightPerimeter;

	// num of right between points
	int numRight = findNumberOfPointsBetween(topRightY, bottomRightY);

	limit = xMax;
	rightPerimeter = findSideRightPerimeter(numRight, topRightX, topRightY, limit);
	// **********************************************************
	vector <string> bottomPerimeter;
	
	// num of bottom between points
	int numBottom = findNumberOfPointsBetween(bottomRightX, bottomLeftX);

	limit = yMax;	
	bottomPerimeter = findSideBottomPerimeter(numBottom, bottomRightY, bottomRightX, limit);
	// **********************************************************
	
	// vector - 4 corners + 4 sides (between points)
	// store 4 corners
	vector <string> bottomLeftCorner;
	vector <string> topLeftCorner; 
	vector <string> topRightCorner; 
	vector <string> bottomRightCorner;  

	// vector to store four corners into one vector
	vector <string> fourCorners;

	// xCoordinate and yCoordinate must be within grid
	// if either xCoordinate/yCoordinate are not in grid then don't store corner
	// conditions like 1&0 or 0&1 or 0&0 (must be 1&1 to store)	
	if ((is_valid(bottomLeftX, xMax)==1) && (is_valid(bottomLeftY, yMax)==1))
	{
		bottomLeftCorner = storeCorner(bottomLeftX, bottomLeftY);
		fourCorners.insert(fourCorners.begin(), bottomLeftCorner.begin(), bottomLeftCorner.end());
	}

	if ((is_valid(topLeftX, xMax)==1) && (is_valid(topLeftY, yMax)==1))
	{
		topLeftCorner = storeCorner(topLeftX, topLeftY);
		fourCorners.insert(fourCorners.end(), topLeftCorner.begin(), topLeftCorner.end());

	}
	
	if ((is_valid(topRightX, xMax)==1) && (is_valid(topRightY, yMax)==1))	
	{
		topRightCorner = storeCorner(topRightX,topRightY);
		fourCorners.insert(fourCorners.end(), topRightCorner.begin(), topRightCorner.end());
	}

	if ((is_valid(bottomRightX, xMax)==1) && (is_valid(bottomRightY, yMax)==1))	
	{
		bottomRightCorner = storeCorner(bottomRightX, bottomRightY);
		fourCorners.insert(fourCorners.end(), bottomRightCorner.begin(), bottomRightCorner.end());
	}
	
	vector <string> perimeterValues;
	perimeterValues = findPerimeter(fourCorners, leftPerimeter, topPerimeter, rightPerimeter, bottomPerimeter);

	return perimeterValues;
	
}

vector <string> findPerimeter(vector <string> corner, vector <string> leftPerimeter, vector <string> topPerimeter, vector <string> rightPerimeter, vector <string> bottomPerimeter)
{
	// store into vector
	vector <string> perimeter;
	perimeter.insert(perimeter.begin(), corner.begin(), corner.end());
	perimeter.insert(perimeter.end(), leftPerimeter.begin(), leftPerimeter.end());
	perimeter.insert(perimeter.end(), topPerimeter.begin(), topPerimeter.end());
	perimeter.insert(perimeter.end(), rightPerimeter.begin(), rightPerimeter.end());
	perimeter.insert(perimeter.end(), bottomPerimeter.begin(), bottomPerimeter.end());

	return perimeter;
}

int findXCoordinate(string point)
{
	// removes '[' and ']'
	string temp = point.substr(1, point.size()-2);
	string data = temp;

	int pointX;

	vector<string> tokenStringVector = splitString (data, ", ");

	// store 'x' 
	pointX = stoi(tokenStringVector[0]);

	return pointX;
}

int findYCoordinate(string point)
{
	// removes '[' and ']'
	string temp = point.substr(1, point.size()-2);
	string data = temp;

	int pointY;

	vector<string> tokenStringVector = splitString (data, ", ");

	// store 'y'
	pointY = stoi(tokenStringVector[1]);

	return pointY;
}

void printCorner(int xCoordinate, int yCoordinate)
{
	string point;
	point = "[" + to_string(xCoordinate) + ", " + to_string(yCoordinate) + "]";

	cout << point << endl;
}

vector <string> storeCorner(int xCoordinate, int yCoordinate)
{
	string point;
	point = "[" + to_string(xCoordinate) + ", " + to_string(yCoordinate) + "]";

	vector <string> corner;
	corner.push_back(point);
	
	return corner;
}

int findNumberOfPointsBetween(int corner1, int corner2)
{
	int numOfPoints = corner1 - corner2 - 1;
	return numOfPoints;
}

// size, fixed x/y coordinate, starting x/y coordinate
vector <string> findSideLeftPerimeter(int size, int fixedCoordinate, int startingCoordinate, int limit)
{
	vector <string> sidePerimeter;

	int changingAxisCoordinate;
	
	for (int i=0; i<size; i++)
	{
		if (fixedCoordinate > -1 && fixedCoordinate <= limit)
		{
			changingAxisCoordinate = startingCoordinate + i + 1;
			sidePerimeter.push_back("["+to_string(fixedCoordinate)+", "+to_string(changingAxisCoordinate)+"]");
			//cout << sidePerimeter[i];
		}		
	}
	//cout << endl;

	return sidePerimeter;
}

// size, fixed x/y coordinate, starting x/y coordinate
vector <string> findSideTopPerimeter(int size, int fixedCoordinate, int startingCoordinate, int limit)
{
	vector <string> sidePerimeter;

	int changingAxisCoordinate;
	
	for (int i=0; i<size; i++)
	{
		
		if (fixedCoordinate > -1 && fixedCoordinate <= limit)
		{	
			changingAxisCoordinate = startingCoordinate + i + 1;			
			sidePerimeter.push_back("["+to_string(changingAxisCoordinate)+", "+to_string(fixedCoordinate)+"]");			
			//cout << sidePerimeter[i];
		}
	}
	//cout << endl;
	
	return sidePerimeter;
	
}

// size, fixed x/y coordinate, starting x/y coordinate
vector <string> findSideRightPerimeter(int size, int fixedCoordinate, int startingCoordinate, int limit)
{
	vector <string> sidePerimeter;

	int changingAxisCoordinate;
	
	for (int i=0; i<size; i++)
	{
		if (fixedCoordinate > -1 && fixedCoordinate <= limit)
		{
			changingAxisCoordinate = startingCoordinate - i - 1;
			sidePerimeter.push_back("["+to_string(fixedCoordinate)+", "+to_string(changingAxisCoordinate)+"]");
			//cout << sidePerimeter[i];
		}
	}
	//cout << endl;

	return sidePerimeter;
	
}

// size, fixed x/y coordinate, starting x/y coordinate
vector <string> findSideBottomPerimeter(int size, int fixedCoordinate, int startingCoordinate, int limit)
{
	vector <string> sidePerimeter;

	int changingAxisCoordinate;
	
	for (int i=0; i<size; i++)
	{
		if (fixedCoordinate > -1 && fixedCoordinate <= limit)
		{
			changingAxisCoordinate = startingCoordinate - i - 1;
			sidePerimeter.push_back("["+to_string(changingAxisCoordinate)+", "+to_string(fixedCoordinate)+"]");
			//cout << sidePerimeter[i];
		}
	}
	//cout << endl;
	
	return sidePerimeter;
}



//////////////////////////////////////////////////////////////////////////////////////////////////////
//****************************************************************************************************
//=======================================================
int readCloudFile(string fileName, int xMax, int yMax, vector<int> xCoord, vector<int> yCoord) 
{
	ifstream readFile (fileName);
	string content;
	if (readFile.is_open())
	{
		vector <string> cloud;

		while (getline(readFile,content)) 
		{
			// store cloudcover values into vector cloud			
			if (content.size() > 0) 
				cloud.push_back(content);
		}
		
		// dynamically create array for coordinates and cloudcover
		string *cloudCoordinates = nullptr;
		cloudCoordinates = new string[cloud.size()];

		string *cloudCover = nullptr;
		cloudCover = new string[cloud.size()];

		for (int i=0; i<cloud.size(); i++)
		{
			string data = cloud[i];
			// split string in cloud vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				cloudCoordinates[i] = tokenStringVector[0];
				cloudCover[i] = tokenStringVector[1];
			}
		}
		readFile.close();
		
		// find cloudArray
		string ** cloudArray = findCloudArray(cloud.size(), xMax, yMax, cloudCoordinates, cloudCover);
		
		// find cloudValue
		int cloudValue = findCloudValue(cloudArray, xCoord, yCoord, xMax, yMax);
		

		// deallocate memory for cloudArray
		// for (int s=0; s<yMax+2; s++)
		for (int s=0; s<yMax+2; s++)
			delete [] cloudArray[s];
	 
		delete [] cloudArray;

		return cloudValue;
	}
	else
		cout << "Unable to open file";	
}

string ** findCloudArray(int size, int xMax, int yMax, string* cloudCoordinates, string* cloudCover)
{
	int * xCoordArrayPtr = nullptr;
	int * yCoordArrayPtr = nullptr;

	xCoordArrayPtr = new int[size];
	yCoordArrayPtr = new int[size];

	for (int index = 0; index < size; index++)
	{
		// remove '[' and ']' characters
		string temp = cloudCoordinates[index].substr(1, cloudCoordinates[index].size()-2);
		cloudCoordinates[index] = temp;
		
		// storing into int arrays xCoord and yCoord
		string data = cloudCoordinates[index];
		// split string of cityCoordinates 
		vector<string> tokenStringVector = splitString (data, ", ");

		for (int m=0; m<tokenStringVector.size(); m++)
		{
			// store split strings in various int arrays
			xCoordArrayPtr[index] = stoi(tokenStringVector[0]);
			yCoordArrayPtr[index] = stoi(tokenStringVector[1]);
		}
	}
	
	// storing int version of cloudCover array		
	int cloudCoverVal[size];
	
	// create cloud grid array 
	int x = xMax + 3;
	int y = yMax + 2;
	int count = 0;

	////////////////////////////////////////
	// init cloudArray
	////////////////////////////////////////
	string ** cloudArray = nullptr;
	cloudArray = new string * [y];
	for (int m=0; m<y; m++)
		cloudArray[m] = new string[x];
 

	//////////////////////////////////////////
	// Extracting cloud value from cloud cover array
	//////////////////////////////////////////
	// storing categorised values of cloud 
	string cloudinessIndex[size];

	for (int i=0; i < size; i++)
	{
		cloudinessIndex[i] = cloudCover[i];
	}

	// populate cloud grid array after matching with values in cloud location

	////////////////////////////////////////	
	// populate cloudArray
	////////////////////////////////////////
	for (int row = 0; row < y; row++)
	{
		for (int col = 0; col < x; col++)
		{	
			if (row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
			{
				cloudArray[row][col] = cloudinessIndex[count];					
				count++;
			}
			else
			{
				cloudArray[row][col] = " ";
			}
		}
	}
	// delete to free memory
	delete [] xCoordArrayPtr;
	delete [] yCoordArrayPtr;

	// delete to free memory
	delete [] cloudCoordinates;
	delete [] cloudCover;

	return cloudArray;	
}

// matches with xCoord, yCoord values of coordinates with cloudArray 
// to identify the cloudiness Value of the xCoord and yCoord value passed into function
// returns the cloudiness value of the point

int findCloudValue(string ** cloudArray, vector<int> xCoord, vector<int> yCoord, int xMax, int yMax)
{
	int cloudValue;
	// values in cloud array
	//cout << "Values in cloud array: " << endl;
	int count = 0;

	for (int row = 0; row < yMax+2; row++)
	{
		for (int col = 0; col < xMax+3; col++)
		{	
			if (row == xCoord[count] && col == yCoord[count])
			{
				//cout << cloudArray[row][col] << endl;
				cloudValue = stoi(cloudArray[row][col]);
				return cloudValue;
			}
		}	
	}
}
//============================================================

//************************************************************
int readPressureFile(string fileName, int xMax, int yMax, vector<int> xCoord, vector<int> yCoord)
{
	ifstream readFile (fileName);
	string content;

	if (readFile.is_open())
	{
		vector <string> pressure;

		while (getline(readFile,content)) 
		{
			// store pressure values into vector pressure		
			if (content.size() > 0) 
				pressure.push_back(content);
		}
	
		// dynamically create array for coordinates and atmosphericPressure
		string *pressureCoordinates = nullptr;
		pressureCoordinates = new string[pressure.size()];

		string *atmosphericPressure = nullptr;
		atmosphericPressure = new string[pressure.size()];

		for (int i=0; i<pressure.size(); i++)
		{
			string data = pressure[i];
			// split string in cloud vector
			vector<string> tokenStringVector = splitString (data, "-");

			for (int j=0; j<tokenStringVector.size(); j++)
			{
				// store split strings in various string arrays
				pressureCoordinates[i] = tokenStringVector[0];
				atmosphericPressure[i] = tokenStringVector[1];
			}
		}
		readFile.close();

		// find pressureArray
		string ** pressureArray = findPressureArray(pressure.size(), xMax, yMax, pressureCoordinates, atmosphericPressure);
		
		// find pressureValue
		int pressureValue = findPressureValue(pressureArray, xCoord, yCoord, xMax, yMax);
		

		// deallocate memory for pressureArray
		for (int s=0; s<yMax+2; s++)
			delete [] pressureArray[s];
	 
		delete [] pressureArray;

		return pressureValue;
	}
	else 
		cout << "Unable to open file";
}

string ** findPressureArray(int size, int xMax, int yMax, string* pressureCoordinates, string* atmosphericPressure)
{
	int * xCoordArrayPtr = nullptr;
	int * yCoordArrayPtr = nullptr;

	xCoordArrayPtr = new int[size];
	yCoordArrayPtr = new int[size];


	for (int index = 0; index < size; index++)
	{
		
		// remove '[' and ']' characters
		string temp = pressureCoordinates[index].substr(1, pressureCoordinates[index].size()-2);
		pressureCoordinates[index] = temp;
		
		//storing into int arrays xCoord and yCoord
		string data = pressureCoordinates[index];
		// split string of cityCoordinates 
		vector<string> tokenStringVector = splitString (data, ", ");

		for (int i=0; i<tokenStringVector.size(); i++)
		{
			// store split strings in various int arrays
			xCoordArrayPtr[index] = stoi(tokenStringVector[0]);
			yCoordArrayPtr[index] = stoi(tokenStringVector[1]);
		}
	}
	
	// storing int version of atmosphericPressure array		
	int atmosphericPressureVal[size];

	// create pressure grid array 
	int x = xMax + 3;
	int y= yMax + 2;
	int count = 0;

	////////////////////////////////////////
	// init pressureArray
	////////////////////////////////////////
	string ** pressureArray = nullptr;
	pressureArray = new string * [y];
	for (int m=0; m<y; m++)
		pressureArray[m] = new string[x];


	// storing categorised values of pressure 
	string pressureIndex[size];

	for (int idx=0; idx < size; idx++)
	{
		pressureIndex[idx] = atmosphericPressure[idx];
	}

	// populate pressure grid array after matching with values in pressure location

	////////////////////////////////////////
	// populate pressurearray
	////////////////////////////////////////
	for (int row = 0; row < y; row++)
	{
		for (int col = 0; col < x; col++)
		{	
			if(row == xCoordArrayPtr[count] && col == yCoordArrayPtr[count])
			{
				pressureArray[row][col] = pressureIndex[count];					
				count++;
			}
			else
			{
				pressureArray[row][col] = " ";
			}
		}
	}
	// delete to free memory
	delete [] pressureCoordinates;
	delete [] atmosphericPressure;

	// delete to free memory
	delete [] xCoordArrayPtr;
	delete [] yCoordArrayPtr;
	
	return pressureArray;
}

// matches with xCoord, yCoord values of coordinates with pressureArray 
// to identify the pressureValue of the xCoord and yCoord value passed into function
// returns the pressure value of the point
int findPressureValue(string ** pressureArray, vector<int> xCoord, vector<int> yCoord, int xMax, int yMax)
{
	int pressureValue;
	int count = 0;

	for (int row = 0; row < yMax+2; row++)
	{
		for (int col = 0; col < xMax+3; col++)
		{	
			if (row == xCoord[count] && col == yCoord[count])
			{
				//cout << pressureArray[row][col] << endl;
				pressureValue = stoi(pressureArray[row][col]);
				return pressureValue;
			}
		}	
	}
}
//************************************************************
// find ACC, AP
void findAverage(vector<int> uniqueCityId, vector <string> uniqueCityName, vector<vector<string> > citylocationById, vector<vector<string> > cityPerimeterById, int xMax, int yMax, string cloudCoverFileName, string pressureFileName)
{
	int size = uniqueCityId.size();

	/* cloud */
	vector<int> cloudAreaValues;
	vector<int> cloudPerimeterValues;
	// store cloud total values by ID
	int cloudAreaTotal[size];
	int cloudPerimeterTotal[size];
	// store cloud count values
	int cloudAreaCount[size];
	int cloudPerimeterCount[size];
	// starting positions
	int cloudAreaPosition = 0;
	int cloudPerimeterPosition = 0;
	// calculating sum
	int sumCloudArea = 0;
	int sumCloudPerimeter = 0;

	/* pressure */	
	vector<int> pressureAreaValues;
	vector<int> pressurePerimeterValues;
	// store pressure total values by ID
	int pressureAreaTotal[size];
	int pressurePerimeterTotal[size];
	// store pressure count values
	int pressureAreaCount[size];
	int pressurePerimeterCount[size];
	// starting positions
	int pressureAreaPosition = 0;
	int pressurePerimeterPosition = 0;
	// calculating sum
	int sumPressureArea = 0;
	int sumPressurePerimeter = 0;
	
	// using locations found, loop through array to match with values (cloud, pressure) in their files
	
	for (int i = 0; i < size; i++)
	{
		// city area coordinates (inside)
		for (int j=0; j<citylocationById[i].size();++j)
		{
			vector<int> xCoord;
			vector<int> yCoord;
	
			// remove '[' ']'
			string temp = citylocationById[i][j].substr(1, citylocationById[i][j].size()-2);
			citylocationById[i][j] = temp;

			// storing into int arrays xCoord and yCoord
			string data = citylocationById[i][j];
			vector<string> tokenStringVector = splitString (data, ", ");

			xCoord.push_back(stoi(tokenStringVector[0]));
			yCoord.push_back(stoi(tokenStringVector[1]));
			
			
			if (j == 0)
			{
				cloudAreaValues.push_back(i+1);
				pressureAreaValues.push_back(i+1);
			}
			// cloud values
			cloudAreaValues.push_back(readCloudFile(cloudCoverFileName, xMax, yMax, xCoord, yCoord));
			// pressure values
			pressureAreaValues.push_back(readPressureFile(pressureFileName, xMax, yMax, xCoord, yCoord));
		}
		
		// city perimeter coordinates (outside)
		for (int k=0; k<cityPerimeterById[i].size();++k)
		{
			vector<int> xCoord;
			vector<int> yCoord;
	
			// remove '[' ']'
			string temp = cityPerimeterById[i][k].substr(1, cityPerimeterById[i][k].size()-2);
			cityPerimeterById[i][k] = temp;

			// storing into int arrays xCoord and yCoord
			string data = cityPerimeterById[i][k];
			vector<string> tokenStringVector = splitString (data, ", ");

			xCoord.push_back(stoi(tokenStringVector[0]));
			yCoord.push_back(stoi(tokenStringVector[1]));
			
			if (k == 0)
			{
				cloudPerimeterValues.push_back(i+1);
				pressurePerimeterValues.push_back(i+1);
			}

			// cloud values
			cloudPerimeterValues.push_back(readCloudFile(cloudCoverFileName, xMax, yMax, xCoord, yCoord));
			// pressure values
			pressurePerimeterValues.push_back(readPressureFile(pressureFileName, xMax, yMax, xCoord, yCoord));
		}
		
		// find cloudArea sum and count
		for (int l = 0; l < cloudAreaValues.size(); l++)
		{	
			if (cloudAreaValues[l] == i+1)
			{
				for (int count=l+1; count < cloudAreaValues.size(); count++)
				{
					sumCloudArea = sumCloudArea + cloudAreaValues[count];
					if (count == cloudAreaValues.size()-1)
					{
						cloudAreaCount[cloudAreaPosition] = count;
						cloudAreaTotal[cloudAreaPosition] = sumCloudArea;
						cloudAreaPosition++;
						sumCloudArea = 0;
					}
				}
			}
		}

		// find cloudPerimeter sum and count
		for (int m = 0; m < cloudPerimeterValues.size(); m++)
		{	
			if (cloudPerimeterValues[m] == i+1)
			{
				for (int count=m+1; count < cloudPerimeterValues.size(); count++)
				{
					sumCloudPerimeter = sumCloudPerimeter + cloudPerimeterValues[count];
					if (count == cloudPerimeterValues.size()-1)
					{
						cloudPerimeterCount[cloudPerimeterPosition] = count;
						cloudPerimeterTotal[cloudPerimeterPosition] = sumCloudPerimeter;
						cloudPerimeterPosition++;
						sumCloudPerimeter = 0;
					}
				}
			}
			
		}

		// find pressureArea sum and count
		for (int n = 0; n < pressureAreaValues.size(); n++)
		{	
			if (pressureAreaValues[n] == i+1)
			{
				for (int count=n+1; count < pressureAreaValues.size(); count++)
				{
					sumPressureArea = sumPressureArea + pressureAreaValues[count];
					if (count == pressureAreaValues.size()-1)
					{
						pressureAreaCount[pressureAreaPosition] = count;
						pressureAreaTotal[pressureAreaPosition] = sumPressureArea;
						pressureAreaPosition++;
						sumPressureArea = 0;
					}
				}
			}
		}
		
		// find pressurePerimeter sum and count
		for (int p = 0; p < pressurePerimeterValues.size(); p++)
		{	
			if (pressurePerimeterValues[p] == i+1)
			{
				for (int count=p+1; count < pressurePerimeterValues.size(); count++)
				{
					
					sumPressurePerimeter = sumPressurePerimeter + pressurePerimeterValues[count];
					
					if (count == pressurePerimeterValues.size()-1)
					{
						pressurePerimeterCount[pressurePerimeterPosition] = count;
						pressurePerimeterTotal[pressurePerimeterPosition] = sumPressurePerimeter;
						pressurePerimeterPosition++;
						sumPressurePerimeter = 0;
					}
				}
			}
			
		}
	}
	
	// find Count for each cities
	// removing duplicate counts
	for (int a = size; a > 0; a--)
	{
		cloudAreaCount[a] = cloudAreaCount[a] - cloudAreaCount[a-1] -1;
		cloudPerimeterCount[a] = cloudPerimeterCount[a] - cloudPerimeterCount[a-1] -1;

		pressureAreaCount[a] = pressureAreaCount[a] - pressureAreaCount[a-1] -1;
		pressurePerimeterCount[a] = pressurePerimeterCount[a] - pressurePerimeterCount[a-1] -1;
	}
	
	double sumCloud = 0.0;
	double sumAverage = 0.0;
	double averageCloudArr[size];
	for (int c = 0; c < size; c++)
	{
		int totalCount;
		sumCloud = cloudAreaTotal[c] + cloudPerimeterTotal[c];
		totalCount = cloudAreaCount[c] + cloudPerimeterCount[c];
		sumAverage = sumCloud/totalCount;
		averageCloudArr[c] = sumAverage;
	}

	double sumPressure = 0.0;
	double averagePressure = 0.0;
	double averagePressureArr[size];
	for (int d = 0; d < size; d++)
	{
		int totalCount;
		sumPressure = pressureAreaTotal[d] + pressurePerimeterTotal[d];
		totalCount = pressureAreaCount[d] + pressurePerimeterCount[d];
		averagePressure = sumPressure/totalCount;
		averagePressureArr[d] = averagePressure;
	}
	
	// displayReport
	displayReport(uniqueCityId, uniqueCityName, averageCloudArr, averagePressureArr);
	
}

//*****************************************************************************************************
void displayReport(vector<int> uniqueCityId, vector <string> uniqueCityName, double averageCloudArr[], double averagePressureArr[]) 
{
	int size = uniqueCityId.size();

	cout << endl;
	cout << "Weather Forecast Summary Report" << endl;
	cout << "-------------------------------" << endl;

	string cloudSymbol;
	string pressureSymbol;
	int probabilityRain;

	for (int i = size-1; i > -1; i--) 
	{
		cloudSymbol = getSymbol(averageCloudArr[i]);
		pressureSymbol = getSymbol(averagePressureArr[i]);
		probabilityRain = getProbability(pressureSymbol, cloudSymbol);

		cout << "City Name : " << uniqueCityName[i] << endl;
		cout << "City ID   : " << uniqueCityId[i] << endl;
		cout << "Ave. Cloud Cover (ACC)   : " << setprecision(2) << fixed << averageCloudArr[i] << "  ";
		cout << "(" << cloudSymbol << ")" << endl;
		cout << "Ave. Pressure    (AP)    : " << setprecision(2) << fixed << averagePressureArr[i] << "  ";
		cout << "(" << pressureSymbol << ")" << endl;
		cout << "Probability of Rain (%)  : " << setprecision(2) << fixed << double(probabilityRain) << endl;
		displayGraphics(probabilityRain);
		cout << endl;
	}
	
}
//*****************************************************************************************************
// value1 -- average pressure value symbol
// value2 -- average cloud cover value symbol
int getProbability(string value1, string value2)
{
	if (value1 == "L" && value2 == "H")
	{
		return 90;
	}
	else if (value1 == "L" && value2 == "M")
	{
		return 80;
	}
	else if (value1 == "L" && value2 == "L")
	{
		return 70;
	}
	else if (value1 == "M" && value2 == "H")
	{
		return 60;
	}
	else if (value1 == "M" && value2 == "M")
	{
		return 50;
	}
	else if (value1 == "M" && value2 == "L")
	{
		return 40;
	}
	else if (value1 == "H" && value2 == "H")
	{
		return 30;
	}
	else if (value1 == "H" && value2 == "M")
	{
		return 20;
	}
	else if (value1 == "H" && value2 == "L")
	{
		return 10;
	}
}
////////////////////////////////////////////////////////////////////////////
// value -- getProbability return value
// Print ASCII
void displayGraphics(int value)
{
	if (value == 90){
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		// cout backslash "\\" (only print 1)
		cout << "\\\\\\\\\\" << endl;
	}
	else if (value == 80) {
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << setw(5) << "\\\\\\\\" << endl;
	}
	else if (value == 70) {
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << setw(5) << "\\\\\\" << endl;
	}
	else if (value == 60) {
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << setw(5) << "\\\\" << endl;
	}
	else if (value == 50) {
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
		cout << setw(5) << "\\" << endl;
	}
	else if (value == 40) {
		cout << "~~~~" << endl;
		cout << "~~~~~" << endl;
	}
	else if (value == 30) {
		cout << "~~~" << endl;
		cout << "~~~~" << endl;
	}
	else if (value == 20) {
		cout << "~~" << endl;
		cout << "~~~" << endl;
	}
	else if (value == 10) {
		cout << "~" << endl;
		cout << "~~" << endl;
	}
}

//-----------------------------------------------------------------------------------------------------
// printMenu displays main menu
void printMenu() {
	cout << "Student ID	: 6959684" << endl;
	cout << "Student Name	: Natasha Jeng Yee Heng" << endl;
	cout << "-----------------------------------------" << endl;
	cout << "Welcome to Weather Information Processing System!" << endl;
	cout << endl;
	cout << "1)	Read in and process a configuration file" << endl;
	cout << "2)	Display city map" << endl;
	cout << "3)	Display cloud coverage map (cloudiness index)" << endl;
	cout << "4)	Display cloud coverage map (LMH symbols)" << endl;
	cout << "5)	Display atmospheric pressure map (pressure index)" << endl;
	cout << "6)	Display atmospheric pressure map (LMH symbols)" << endl;
	cout << "7)	Show weather forecast summary report" << endl;
	cout << "8)	Quit" << endl;
	cout << endl;
}


