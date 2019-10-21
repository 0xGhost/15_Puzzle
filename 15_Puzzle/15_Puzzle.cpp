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
#include <sstream>
#include <unordered_set>
#include "NCLBoardTraverser.h"
#include "NCLBoard.h"

using namespace std;
using std::cout;

#define MEMORY_LEAK_CHECK true

#if MEMORY_LEAK_CHECK
	#define _CRTDBG_MAP_ALLOC
	#include <crtdbg.h>
#endif


inline void WritePuzzleFile(const vector<NCLBoard*>& boards, const string& fileName)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size();
	fileOutput.open(fileName.c_str());

	if(fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << *(boards[j]);
	}
	fileOutput.close();
}

// length: length of each puzzle 
inline void ReadPuzzleFile(const int& length, vector<NCLBoard*>& boards, const string& fileName) throw (invalid_argument)
{
	ifstream fileInput;
	int numberOfPuzzles;

	fileInput.open(fileName.c_str());

	if (fileInput.fail())
		throw invalid_argument("Fail to read the file \""+ fileName + "\".");
	fileInput >> numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		string firstRow;
		getline(fileInput, firstRow);
		stringstream ss;
		ss << firstRow;
		vector<int> firstRowBlocks;
		while (!ss.eof())
		{
			int a;
			ss >> a;
			firstRowBlocks.push_back(a);
		}
		int size = firstRowBlocks.size();
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

inline void WriteSolutionFile(const vector<NCLBoard*>& boards, const vector<BigPosInt>& results, const string& fileName) throw (invalid_argument)
{
	ofstream fileOutput;
	int numberOfPuzzles = boards.size();
	fileOutput.open(fileName.c_str());

	if (fileOutput.fail())
		throw invalid_argument("Fail to write the file \"" + fileName + "\".");
	fileOutput << numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		fileOutput << *(boards[j]);
		fileOutput << "row = " << results[j] << endl;
		fileOutput << "column = " << results[j] << endl;
		fileOutput << "reverse row = " << results[j] << endl;
		fileOutput << "reverse column = " << results[j] << endl;
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
#if true
	{

		int blocks4[] =
		{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 11, 12 ,
			13, 14, 15, -1 };

		NCLBoard *board4 = new NCLBoard(4, blocks4);
		//cout << *board4 << endl;
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

	int size = 4; // puzzle size
	int length = size * size - 1; // number of the puzzle blocks
	int option;
	bool exitFlag = false;
	bool containSpace = true;
	
	string puzzleFileName = "15_Puzzle.txt";
	string solutionFileName = "SolutionFile.txt";
	vector<BigPosInt> results;
	vector<NCLBoard*> boards;


	do
	{
		std::cout << "\n0: exit the program"
			<< "\n1: Manually type in a 15-puzzle configuration and store into memory"
			<< "\n2: Random create 15-Puzzle configurations and store into memory"
			<< "\n3: Output all 15-puzzle configuration from memory to a 15-Puzzle.txt file "
			<< "\n4: Read 15-Puzzle file and output result on screen (this action will remove all puzzle stored in memory)"
			<< "\n5: Output the SolutionFile.txt  "
			<< "\n6: Set if continuous blocks contain space, now is: " << (containSpace ? "contain" : "not contain")
			<< "\n7: find partial continuous "
			<< endl;
		InputInteger(option, 0, 6);
		
		int inputNumber;

		switch (option)
		{
		case 0:
			exitFlag = true;
			
			break;
		case 1:
			{
				std::cout << "Enter " << length <<" positive integers: ";
				int* inputArray = inputBoardConfiguration(length);
				NCLBoard *newBoard = new NCLBoard(size, inputArray);
				boards.push_back(newBoard);
				delete inputArray;
				inputArray = nullptr;						
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
			if (boards.size() == 0)
			{
				std::cout << "There is no puzzle in memory to write into the puzzle file." << endl;
			}
			else
			{
				try
				{
					WritePuzzleFile(boards, puzzleFileName);
				}
				catch (const invalid_argument& iae)
				{
					std::cout << " unable to write data : " << iae.what() << "\n";
				}
			}
			break;
		case 4:
			boards.clear();
			results.clear();
			try
			{
				ReadPuzzleFile(length, boards, puzzleFileName);
			}
			catch (const invalid_argument& iae)
			{
				std::cout << " unable to read data : " << iae.what() << "\n";
			}
			
			for (int i = 0; i < boards.size(); i++)
			{
				BigPosInt result = boards[i]->GetTotalContinuousNumber(containSpace);
				std::cout << *boards[i];
				std::cout << "row = " << result << endl;
				std::cout << "column = " << result << endl;
				std::cout << "reverse row = " << result << endl;
				std::cout << "reverse column = " << result << endl;
				results.push_back(result);
			}
			break;
		case 5:
			if (results.size() == 0)
			{
				std::cout << "There is no result in memory to write into the solution file." << endl;
			}
			else
			{
				try
				{
					WriteSolutionFile(boards, results, solutionFileName);
				}
				catch (const invalid_argument& iae)
				{
					std::cout << " unable to write data : " << iae.what() << "\n";
				}
			}
			break;
		case 6:
			std::cout << " 0: not contain SPACE.    1: contain SPACE." << endl;
			InputInteger(inputNumber, 0, 1);
			containSpace = inputNumber;
		case 7:
			// TODO: to another 'fun' to do 'fun' things! (if time avaliable)
			
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

#if MEMORY_LEAK_CHECK
	_CrtDumpMemoryLeaks();
#endif

	return 0;
}
