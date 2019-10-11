// 15_Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Yiang Lu
// Date created: 11/Oct/2019

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <sstream>

using std::cin;
using std::cout;
using std::endl; 
using std::streamsize;
using std::numeric_limits;
using std::string;

#define MEMORY_LEAK_CHECK true

#if MEMORY_LEAK_CHECK

	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>

#endif



int main()
{
	auto input_number = [](int& input) -> bool
	{
		int inputNumber;

		std::istringstream iss("2 \n");
		cin.rdbuf(iss.rdbuf());

		cin >> inputNumber;
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		if (cin.fail())
		{
			cout << "Please enter a valid integer." << endl;
			cin.clear();
			cin.ignore(numeric_limits<streamsize>::max(), '\n');
			return false;
		}
		else
		{
			input = inputNumber;
			return true;
		}
	};



	int option;
	bool flag = true;
	do
	{
		cout << "\n1 :Manually type in a 15-puzzle configuration "
			<< "\n2: Random create 15-Puzzle configurations  "
			<< "\n3: Produce 15-Puzzle file "
			<< "\n4: Read 15-Puzzle file and output the Solution-File "
			<< endl;
		if (input_number(option))
		{
			int inputNumber;

			switch (option)
			{
			case 1:
				{
					cout << "enter 15 integers: ";
					int counter = 15;
					while (counter >= 0)
					{
						//if(input_number())
						counter--;
					}
				}

				break;
			case 2:
				cout << endl;
				
				cout << "TODO: ";

				cout << endl;
				break;
			case 3:
				// TODO: output file
				break;
			case 4:
				// TODO: read calculate and write
				break;
			default:
				break;
			}
		}
		

	} while (flag);

}

