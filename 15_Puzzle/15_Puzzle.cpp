// 15_Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Yiang Lu
// Date created: 11/Oct/2019

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <string>
#include <unordered_set>
#include "NCLBoardTraverser.h"

using namespace std;

#define MEMORY_LEAK_CHECK true

#if MEMORY_LEAK_CHECK
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif




inline void WritePuzzleFile(const vector<NCLBoard*>& boards, const string& fileName)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size;
	fileOutput.open(fileName.c_str);

	if(fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << boards[j];
	}
	fileOutput.close();
}

// length: length of each puzzle 
inline void ReadPuzzleFile(const int& length, vector<NCLBoard*> boards, const string& fileName) throw (invalid_argument)
{
	ifstream fileInput;
	int numberOfPuzzles;

	fileInput.open(fileName.c_str());

	if (fileInput.fail())
		throw invalid_argument("Fail to read the file \""+ fileName + "\".");
	fileInput >> numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		int *inputArray = new int[length + 1];
		for (int i = 0; i < length; i++)
		{
			fileInput >> inputArray[i];
		}
		inputArray[length] = -1;
		boards.push_back(new NCLBoard(4, inputArray));
		delete inputArray;
		inputArray = nullptr;
	}

	fileInput.close();
}

inline void WriteSolutionFile(const vector<NCLBoard*>& boards, const vector<int>& results, const string& fileName) throw (invalid_argument)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size;
	fileOutput.open(fileName.c_str);

	if (fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << boards[j];
		fileOutput << "row = " << results[j] << endl;
		fileOutput << "column = " << results[j] << endl;
		fileOutput << "reverse row = " << results[j] << endl;
		fileOutput << "reverse column = " << results[j] << endl;
	}
	fileOutput.close();
}

inline int* inputBoardConfiguration(const int& length)
{
	unordered_set<int> hashTable;
	int* array = new int[length];
	int inputNumber;
	for (int i = 0; i < length; i++)
	{
		do
		{
			InputInteger(inputNumber, 1, INT_MAX);
			if (hashTable.count(inputNumber) != 0)
			{
				std::cout << "Number " << inputNumber << " is already exist." << endl;
				continue;
			}
			hashTable.insert(inputNumber);
		} while (true);
		
	}
}

inline bool InputInteger(int& input, const int& min, const int& max)
{
	int inputNumber;

	cin >> inputNumber;
	cin.clear();
	cin.ignore(numeric_limits<streamsize>::max(), '\n');
	if (cin.fail() || inputNumber < min || inputNumber > max)
	{
		std::cout << "Please enter a valid integer in Range (" << min << ", " << max << "): ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
		return false;
	}
	else
	{
		input = inputNumber;
		return true;
	}
}

int main()
{
	srand((unsigned)time(0));
#if MEMORY_LEAK_CHECK
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
#if false
	{

		int blocks4[] =
		{ 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, 11, 12,
		13, 14, 15, -1 };

		NCLBoard *board4 = new NCLBoard(4, blocks4);
		cout << *board4 << endl;
		cout << board4->ToString() << endl;
		
		//int blocks3[] =
		//{ 1, 2, 3, 15,
		//205, 7, 18, 4, -1 };
		int blocks3[] =
		{ 1, 2, 3, 4,
		5, 6, -1, 8, 9 };
		NCLBoard *board3 = new NCLBoard(3, blocks3);
		cout << *board3 << endl;
		cout << board3->ToString() << endl;
		
		int blocks2[] =
		{ 1, 2, 3, -1 };
		NCLBoard *board2 = new NCLBoard(2, blocks2);
		cout << *board2 << endl;
		cout << board2->ToString() << endl;
		
		
		NCLBoard* board0 = board4;
		cout << "Continuous = " << board0->GetTotalContinuousNumber(false) << endl;
		/*
		NCLBoardTraverser traverser(board0, true);
		//traverser.Travers(board2);
		ContinuousNumber con = traverser.GetTotalContinuousNumber();
		cout << "row = " << con.row << endl;
		cout << "rowReverse = " << con.rowReverse << endl;
		cout << "column = " << con.column << endl;
		cout << "columnReverse = " << con.columnReverse << endl;*/
		cout << "Continuous = " << board0->GetTotalContinuousNumber(true) << endl;
		

		delete board4;
		delete board3;
		delete board2;
	}
	_CrtDumpMemoryLeaks();
	return 0;
#endif	

	int size = 4; // puzzle size
	int length = size * size - 1; // number of the puzzle blocks
	int option;
	bool exitFlag = true;
	
	string puzzleFileName = "15_Puzzle.txt";
	string solutionFileName = "SolutionFile.txt";
	vector<int> results;
	vector<NCLBoard*> boards;
	do
	{
		std::cout <<"\n0: exit the program"
			<< "\n1 :Manually type in a 15-puzzle configuration "
			<< "\n2: Random create 15-Puzzle configurations  "
			<< "\n3: Produce 15-Puzzle file "
			<< "\n4: Read 15-Puzzle file and output result on screen "
			<< "\n5: Output the Solution-File "
			<< "\n6: Go Crazy!"
			<< endl;
		if (InputInteger(option, 0, 6))
		{
			int inputNumber;

			switch (option)
			{
			case 0:
				exitFlag = false;
				// TODO: to another 'fun' to do 'fun' things! (if time avaliable)
				break;
			case 1:
				{
					std::cout << "Enter " << length <<" positive integers: ";
					int* inputArray = inputBoardConfiguration(length);
					NCLBoard(size, inputArray);

					// TODO: use a function to Make sure not to allow repeated numbers for the blocks 
					// and maybe done the input and return *array
					// create NCLBoard using this        -> ^^^
						
				}

				break;
			case 2:
				std::cout << "How many board configurations? Enter a positive integer: ";
				InputInteger(inputNumber, 1, INT_MAX);
				for (int i = 0; i < inputNumber; i++)
				{
					NCLBoard *newBoard = new NCLBoard(size, 1, 20);
					boards.push_back(newBoard);
				}
				break;
			case 3:
				WritePuzzleFile(boards, puzzleFileName);
				break;
			case 4:
				ReadPuzzleFile(length, boards, puzzleFileName);
				break;
			case 5:
				WriteSolutionFile(boards, results, puzzleFileName);
			case 6:
				// TODO: to another 'fun' to do 'fun' things! (if time avaliable)
				break;
			default:
				break;
			}
		}
		

	} while (exitFlag);

	for (NCLBoard* board : boards)
	{
		delete board;
		board = nullptr;
	}

#if MEMORY_LEAK_CHECK
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
