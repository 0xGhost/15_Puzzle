// 15_Puzzle.cpp : This file contains the 'main' function. Program execution begins and ends there.
// Author: Yiang Lu
// Date created: 11/Oct/2019

#define MEMORY_LEAK_CHECK true

#if MEMORY_LEAK_CHECK
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <iostream>
#include <limits>
#include <stdlib.h>
#include <ctime>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include <unordered_set>
#include "NCLBoardTraverser.h"
#include "NCLBoard.h"

using namespace std;
using std::cout;




inline void WritePuzzleFile(const vector<NCLBoard*>& boards, const string& fileName)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size();
	fileOutput.open(fileName.c_str());

	if(fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles << endl;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << *(boards[j]) << endl;
	}
	fileOutput.close();
}

// length: length of each puzzle 
inline void ReadPuzzleFile(vector<NCLBoard*>& boards, const string& fileName) throw (invalid_argument)
{
	ifstream fileInput;
	int numberOfPuzzles;

	fileInput.open(fileName.c_str());

	if (fileInput.fail())
		throw invalid_argument("Fail to read the file \""+ fileName + "\".");
	fileInput >> numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		int size = 0;
		string firstRow;
		vector<int> firstRowBlocks;
		while (size < 3)
		{
			firstRowBlocks.clear();
			getline(fileInput, firstRow);
			stringstream ss;
			ss << firstRow;
			int block;
			while (ss >> block)
			{
				firstRowBlocks.push_back(block);
			}
			size = firstRowBlocks.size();
		}
		int length = size * size - 1;
		int *inputArray = new int[length + 1];
		
		for (int i = 0; i < size; i++)
		{
			inputArray[i] = firstRowBlocks[i];
		}
		for (int i = size; i < length; i++)
		{
			fileInput >> inputArray[i];
		}
		inputArray[length] = -1;
		boards.push_back(new NCLBoard(size, inputArray));
		delete[] inputArray;
		inputArray = nullptr;
	}

	fileInput.close();
}

inline void WriteSolutionFile(const vector<NCLBoard*>& boards, const bool& containSpace, const string& fileName) throw (invalid_argument)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size();
	fileOutput.open(fileName.c_str());

	if (fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << "\n" << *(boards[j]);
		int size = boards[j]->SIZE;
		BigPosInt result = boards[j]->GetTotalContinuousNumber(containSpace, size);
		fileOutput << "row = " << result << endl;
		fileOutput << "column = " << result << endl;
		fileOutput << "reverse row = " << result << endl;
		fileOutput << "reverse column = " << result << endl;
		fileOutput << "(total for row & column, including reverse, in this configuration)" << endl;
		for (int i = 2; i <= size; i++)
		{
			ContinuousNumber cResult = boards[j]->CheckContinuous(containSpace, i);
			unsigned long long outputResult = cResult.row + cResult.column + cResult.rowReverse + cResult.columnReverse;
			fileOutput << i << " = " << outputResult << endl;
		}
		fileOutput << "(total for row & column, including reverse, for all valid turns)" << endl;
		for (int i = 2; i <= size; i++)
		{
			BigPosInt result = boards[j]->GetTotalContinuousNumber(containSpace, i);
			result *= 4;
			fileOutput << i << " = " << result << endl;
		}
	}
	fileOutput.close();
}

inline void InputInteger(int& input, const int& min, const int& max)
{
	int inputNumber;

	do
	{
		cin >> inputNumber;
		if (!cin.fail() && inputNumber >= min && inputNumber <= max)
			break;
		std::cout << "Please enter a valid integer in Range (" << min << ", " << max << "): ";
		cin.clear();
		cin.ignore(numeric_limits<streamsize>::max(), '\n');
	} while (1);

	input = inputNumber;
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
			array[i] = inputNumber;
		} while (false);
	}
	return array;
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
			9, 10, 11, 12 ,
			13, 14, 15, -1 };

		NCLBoard *board4 = new NCLBoard(4, blocks4);
		cout << *board4 << endl;
		NCLBoard boardr(4, 1, 20);
		cout << boardr << endl;
		//cout << board4->ToString() << endl;
		
		//int blocks3[] =
		//{ 1, 2, 3, 15,
		//205, 7, 18, 4, -1 };
		int blocks3[] =
		{ 1, 2, 3, 4,
		5, 6, -1, 8, 9 };
		NCLBoard *board3 = new NCLBoard(3, blocks3);
		//cout << *board3 << endl;
		//cout << board3->ToString() << endl;
		
		int blocks2[] =
		{ 1, 2, 3, -1 };
		NCLBoard *board2 = new NCLBoard(2, blocks2);
		//cout << *board2 << endl;
		//cout << board2->ToString() << endl;
		

		NCLBoard* board0 = board4;// = new NCLBoard(100, 1, 12000);
		cout << *board0 << endl;
		cout << "Continuous = " << board0->GetTotalContinuousNumber(false) << endl;
		ContinuousNumber con = board4->CheckContinuous(true, 3);
		cout << "row = " << con.row << endl;
		cout << "rowReverse = " << con.rowReverse << endl;
		cout << "column = " << con.column << endl;
		cout << "columnReverse = " << con.columnReverse << endl; 
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
		//delete board0;
	}
	_CrtDumpMemoryLeaks();
	return 0;
#endif	

	const int MAX_SIZE = 10;

	int option;
	bool exitFlag = false;
	bool containSpace = true;
	
	string puzzleFileName = "15_Puzzle.txt";
	string solutionFileName = "SolutionFile.txt";
	vector<NCLBoard*> boards;
	do
	{
		std::cout << "\nThere are " << boards.size() << " puzzle(s) stored in the memory"
			<< "\n0: Exit the program"
			<< "\n1: Manually type in a 15-puzzle configuration and store into memory"
			<< "\n2: Random create 15-Puzzle configurations and store into memory"
			<< "\n3: Write all 15-puzzle configuration from memory to a 15-Puzzle.txt file "
			<< "\n4: Read 15-Puzzle file (this action will remove all puzzles stored in memory)"
			<< "\n5: Write the SolutionFile.txt  "
			<< "\n6: Set if continuous blocks contain space, now is: " << (containSpace ? "contain" : "not contain")
			<< "\n7: Clear the puzzles that stored in the memory"
			<< "\n8: Find partial(full) continuous column/row (including reverse) for puzzles in the memory "
			<< "\n9: Find total partial(full) continuous column/row (including reverse) in all valid reachable \"turns\" for puzzles in the memory"
			<< endl;
		InputInteger(option, 0, 9);
		
		int inputNumber;

		switch (option)
		{
		case 0:
			exitFlag = true;
			
			break;
		case 1:
			{
				int size;
				std::cout << "Enter the size of the puzzle(eg: 4 for a 15-puzzle): ";
				InputInteger(size, 3, MAX_SIZE);
				int length = size * size - 1;
				std::cout << "Enter " << length <<" positive integers: ";
				int* inputArray = inputBoardConfiguration(length);
				NCLBoard *newBoard = new NCLBoard(size, inputArray);
				boards.push_back(newBoard);
				delete inputArray;
				inputArray = nullptr;						
			}
			break;
		case 2:
			int size, min, max;
			std::cout << "Enter the size of random generated puzzles(eg: 4 for a 15-puzzle): ";
			InputInteger(size, 3, MAX_SIZE);
			std::cout << "How many puzzle do you want to generate? Enter a positive integer: ";
			InputInteger(inputNumber, 1, INT_MAX);
			std::cout << "Enter the minimum integer for the random generation:";
			InputInteger(min, 1, INT_MAX - (size * size));
			std::cout << "Enter the maximum integer for the random generation:";
			InputInteger(max, min + (size * size) - 2, INT_MAX);

			for (int i = 0; i < inputNumber; i++)
			{
				NCLBoard *newBoard = new NCLBoard(size, min, max);
				boards.push_back(newBoard);
				std::cout << "\n" << *newBoard;
			}
			break;
		case 3:
			if (boards.size() == 0)
			{
				std::cout << "There is no puzzle in memory to write into the puzzle file." << endl;
			}
			else
			{
				try
				{
					WritePuzzleFile(boards, puzzleFileName);
					std::cout << "Puzzle file write successful." << endl;
				}
				catch (const invalid_argument& iae)
				{
					std::cout << "Unable to write data : " << iae.what() << endl;
				}
			}
			break;
		case 4:
			try
			{
				ReadPuzzleFile(boards, puzzleFileName);
			}
			catch (const invalid_argument& iae)
			{
				std::cout << "Unable to read data : " << iae.what() << endl;
			}
			for (int i = 0; i < boards.size(); i++)
			{
				std::cout << "\n" << *boards[i];
			}
			break;
		case 5:
			if (boards.size() == 0)
			{
				std::cout << "There is no puzzle in memory to write into the solution file." << endl;
			}
			else
			{
				try
				{
					WriteSolutionFile(boards, containSpace, solutionFileName);
					std::cout << "Solution file write successful." << endl;
				}
				catch (const invalid_argument& iae)
				{
					std::cout << "Unable to write data : " << iae.what() << "\n";
				}
			}
			break;
		case 6:
			std::cout << " 0: not contain SPACE.    1: contain SPACE." << endl;
			InputInteger(inputNumber, 0, 1);
			containSpace = inputNumber;
		case 7:
			for (NCLBoard* board : boards)
			{
				delete board;
				board = nullptr;
			}
			boards.clear();
			break;
		case 8:
			cout << "How many digits for partial continuous (enter an integer N to find N-partial):" << endl;
			InputInteger(inputNumber, 2, MAX_SIZE);
			ContinuousNumber* cResults = new ContinuousNumber[boards.size()];
			for (int i = 0; i < boards.size(); i++)
			{
				ContinuousNumber con = boards[i]->CheckContinuous(containSpace, inputNumber);
				cout << "\n" << *boards[i];
				cout << "row = " << con.row << endl;
				cout << "rowReverse = " << con.rowReverse << endl;
				cout << "column = " << con.column << endl;
				cout << "columnReverse = " << con.columnReverse << endl;
			}
			break;
		case 9:
			cout << "How many digits for partial continuous (enter an integer N to find N-partial):" << endl;
			InputInteger(inputNumber, 2, MAX_SIZE);
			for (int i = 0; i < boards.size(); i++)
			{
				BigPosInt result = boards[i]->GetTotalContinuousNumber(containSpace, inputNumber);
				cout << "\n" << *boards[i];
				cout << "row = " << result << endl;
				cout << "rowReverse = " << result << endl;
				cout << "column = " << result << endl;
				cout << "columnReverse = " << result << endl;
			}
			break;
		default:
			break;
		}
		
	} while (!exitFlag);

	for (NCLBoard* board : boards)
	{
		delete board;
		board = nullptr;
	}
	return 0;
}
