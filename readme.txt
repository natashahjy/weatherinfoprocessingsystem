// To compile file
g++ -std=c++11 csci251_a1.cpp -o csci251_a1.exe

// To execute file
./csci251_a1.exe

// Note that all .txt files are ubuntu based
// Opening in windows might change formatting

// This program works for:
config.txt, citylocation.txt, cloudcover.txt, pressure.txt

// This program will work for:
TestCases_Config.txt, TestCases_CloudCover.txt, TestCases_Pressure.txt

// This program will fail for:
TestCases_CityLocation.txt

// Things to note:
All assignment of values in 2D array for display only runs from 0 to the max limit
(applies to citylocation, cloudcover and pressure)
It does not take into consideration if there are "disruptive values"
Example:
[2 , 8] -> [2 , 2]
