// 15_Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Yiang Lu
// Date created: 11/Oct/2019

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <ctime>

#include "NCLBoardTraverser.h"

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
	srand((unsigned)time(0));
#if MEMORY_LEAK_CHECK
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif

	{
		/*
		int before[] = 
		{ 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, -1, 12,
		13, 14, 15, 20 };

		int afterBottom[] =
		{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 15, 12,
			13, 14, -1, 20 };
		Board board0(4, before);
		Board board1(4, afterBottom);
		cout << board0 << endl;
		cout << board1 << endl;
		board0.Move(Direction::Bottom);
		cout << board0 << endl;
		cout << board1 << endl;
		bool a = board0.isEqualTo(board1);

		int data[16] =
		{ 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 17, 12,
		13, 14, 15, -1 };

		NCLBoard board3(4, data);
		ContinuousNumber* c = board3.CheckContinuous();
		cout << c->row << endl;
		cout << c->rowReverse << endl;
		cout << c->column << endl;
		cout << c->columnReverse << endl;
		
		delete c;
		*/
		
		int blocks4[] =
		{ 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, -1 };

		NCLBoard *board4 = new NCLBoard(4, blocks4);
		cout << *board4 << endl;
		cout << board4->ToString() << endl;
		
		int blocks3[] =
		{ 1, 2, 3, 4,
		5, 6, 7, 8, -1 };
		NCLBoard *board3 = new NCLBoard(3, blocks3);
		cout << *board3 << endl;
		cout << board3->ToString() << endl;

		int blocks2[] =
		{ 1, 2, 3, -1 };
		NCLBoard *board2 = new NCLBoard(2, blocks2);
		cout << *board2 << endl;
		cout << board2->ToString() << endl;
		
		NCLBoardTraverser traverser;
		ContinuousNumber c = traverser.Travers(board3);
		cout << "row = " << c.row << endl;
		cout << "rowReverse = " << c.rowReverse << endl;
		cout << "column = " << c.column << endl;
		cout << "columnReverse = " << c.columnReverse << endl;
		
		delete board4;
		delete board3;
		delete board2;
	}_CrtDumpMemoryLeaks();

	return 0;

	auto input_number = [](int& input) -> bool
	{
		int inputNumber;

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

#if MEMORY_LEAK_CHECK
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
