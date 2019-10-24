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
#include "ctpl_stl.h"

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

inline void ReadPuzzleFile(vector<NCLBoard*>& boards, const string& fileName) throw (invalid_argument)
{
	ifstream fileInput;
	int numberOfPuzzles;
	if (fileName.find_first_not_of("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789._"/*"a-to-zA-to-Z0-to-9_."*/) != std::string::npos)
	{
		throw invalid_argument("File name invalid \"" + fileName + "\".");
	}

	fileInput.open(fileName.c_str());

	if (fileInput.fail())
		throw invalid_argument("Fail to read the file \""+ fileName + "\".");
	fileInput >> numberOfPuzzles;
	for (int j = 0; j < numberOfPuzzles; j++)
	{
		// get the first row of a puzzle and find out it size
		ull size = 0;
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

		// read the whole puzzle
		for (int i = 0; i < size; i++)
		{
			inputArray[i] = firstRowBlocks[i];
		}
		for (int i = size; i < length; i++)
		{
			fileInput >> inputArray[i];
		}
		inputArray[length] = -1;

		// create puzzle board and stored into the vector 'boards'
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
	int* array = new int[length + 1];
	int inputNumber;
	for (int i = 0; i < length; i++)
	{
		do
		{
			InputInteger(inputNumber, 1, INT_MAX);
			// check if the number is already in the hashTable
			if (hashTable.count(inputNumber) != 0)
			{
				std::cout << "Number " << inputNumber << " is already exist." << endl;
			}
			else 
			{
				hashTable.insert(inputNumber);
				array[i] = inputNumber;
				break;
			}
		} while (true);
	}
	array[length] = -1;
	return array;
}

int main()
{
	srand((unsigned)time(0));
#if MEMORY_LEAK_CHECK
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
#endif
	
	const int threadsNum = std::thread::hardware_concurrency();
	ctpl::thread_pool thPool(threadsNum);
	std::mutex boardsMutex;

	const int MAX_SIZE = 100;

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
				std::cout << "\n" << *newBoard;
				delete inputArray;
				inputArray = nullptr;						
			}
			break;
		case 2:
		{
			int size, min, max;
			std::cout << "Enter the size of random generated puzzles(eg: 4 for a 15-puzzle): ";
			InputInteger(size, 3, MAX_SIZE);
			std::cout << "How many puzzle do you want to generate? Enter a positive integer: ";
			InputInteger(inputNumber, 1, INT_MAX);
			std::cout << "Enter the minimum integer for the random generation:";
			InputInteger(min, 1, INT_MAX - (size * size));
			std::cout << "Enter the maximum integer for the random generation:";
			InputInteger(max, min + (size * size) - 2, INT_MAX);

			int count = inputNumber;
			int loopNum = 0.5f + (float)inputNumber / threadsNum; // inner loop limit (to the nearest whole number) 
			auto* f = new std::future<void>[threadsNum];
			int thLoopCount = threadsNum < count ? threadsNum : count; // outter loop limit max(threadNum, count)
			for (int j = 0; j < thLoopCount; j++)
			{
				// check if is the last loop
				if (j == thLoopCount - 1)
					loopNum = count;
				else
					count -= loopNum;
				
				f[j] = thPool.push([&](int, int loopNum)
					{
						for (int i = 0; i < loopNum; i++)
						{
							NCLBoard* newBoard = new NCLBoard(size, min, max);
							boardsMutex.lock(); // lock cout and boards
							boards.push_back(newBoard);
							std::cout << "\n" << *newBoard;
							boardsMutex.unlock();
						}
					}, loopNum);
				
			}
			// wait all thread finish
			for (int j = 0; j < thLoopCount; j++)
			{
				f[j].get();
			}
			delete[] f;
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
				string readFilename;
				cout << "Please input your file name(for default file name input 0):";
				cin >> readFilename;
				if (readFilename == "0")
					readFilename = puzzleFileName;
				ReadPuzzleFile(boards, readFilename);
				for (int i = 0; i < boards.size(); i++)
				{
					std::cout << "\n" << *boards[i];
				}
			}
			catch (const invalid_argument& iae)
			{
				std::cout << "Unable to read data : " << iae.what() << endl;
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
			break;
		case 7:
			for (NCLBoard* board : boards)
			{
				delete board;
				board = nullptr;
			}
			boards.clear();
			break;
		case 8:
		{
			if (boards.size() == 0)
			{
				std::cout << "There is no puzzle in memory." << endl;
				break;
			}
			cout << "How many digits for partial continuous (enter an integer N to find N-partial):" << endl;
			InputInteger(inputNumber, 2, MAX_SIZE);

			ContinuousNumber* results = new ContinuousNumber[boards.size()]; // stored all results from different threads
			std::future<int>* fResult = new std::future<int>[threadsNum];
			int numberOfboards = boards.size();
			int loopCount = 0.5f + (float)numberOfboards / threadsNum;
			int index = 0;
			int thLoopCount = threadsNum < numberOfboards ? threadsNum : numberOfboards;
			for (int j = 0; j < thLoopCount; j++)
			{
				if (j == thLoopCount - 1)
					loopCount = numberOfboards;
				else
					numberOfboards -= loopCount;
				fResult[j] = thPool.push([&](int, int loopCount, int th_index)
					{
						// each thread write different part of the results array
						for (int i = 0; i < loopCount; i++)
						{
							results[th_index] = boards[th_index]->CheckContinuous(containSpace, inputNumber);
							th_index++;
						}
						return th_index;
					}, loopCount, index);
				index += loopCount;
			}

			index = 0;
			for (int j = 0; j < thLoopCount; j++)
			{
				int end = fResult[j].get();
				// output each part of the results array
				while(index < end)
				{
					ContinuousNumber con = results[index];
					cout << "\n" << *(boards[index]);
					cout << "row = " << con.row << endl;
					cout << "rowReverse = " << con.rowReverse << endl;
					cout << "column = " << con.column << endl;
					cout << "columnReverse = " << con.columnReverse << endl;
					index++;
				}
			}

			delete[] results;
			delete[] fResult;
			results = nullptr;
			fResult = nullptr;
		}
			break;
		case 9:
		{
			if (boards.size() == 0)
			{
				std::cout << "There is no puzzle in memory." << endl;
				break;
			}
			cout << "How many digits for partial continuous (enter an integer N to find N-partial):" << endl;
			InputInteger(inputNumber, 2, MAX_SIZE);

			BigPosInt* results = new BigPosInt[boards.size()];
			std::future<int>* fResult = new std::future<int>[threadsNum];
			int numberOfboards = boards.size();
			int loopCount = 0.5f + (float)numberOfboards / threadsNum;
			int index = 0;
			int thLoopCount = threadsNum < numberOfboards ? threadsNum : numberOfboards;
			for (int j = 0; j < thLoopCount; j++)
			{
				if (j == thLoopCount - 1)
					loopCount = numberOfboards;
				else
					numberOfboards -= loopCount;
				fResult[j] = thPool.push([&](int, int loopCount, int th_index)
					{
						for (int i = 0; i < loopCount; i++)
						{
							results[th_index] = boards[th_index]->GetTotalContinuousNumber(containSpace, inputNumber);
							th_index++;
						}
						return th_index;
					}, loopCount, index);
				index += loopCount;

			}

			index = 0;
			for (int j = 0; j < thLoopCount; j++)
			{
				int end = fResult[j].get();

				while (index < end)
				{
					BigPosInt result = results[index];
					cout << "\n" << *(boards[index]);
					cout << "row = " << result << endl;
					cout << "rowReverse = " << result << endl;
					cout << "column = " << result << endl;
					cout << "columnReverse = " << result << endl;
					index++;
				}
			}

			delete[] results;
			delete[] fResult;
			results = nullptr;
			fResult = nullptr;
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
