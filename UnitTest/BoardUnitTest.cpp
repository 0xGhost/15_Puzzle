// Author: Yiang Lu
// Date created: 11/Oct/2019
#include "pch.h"
#include "CppUnitTest.h"
#include "..//15_Puzzle/Board.h"
#include "..//15_Puzzle/Board.cpp"

#include <sstream>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTest
{
	TEST_CLASS(BoardUnitTest)
	{
	public:
		/*
		TEST_METHOD(TestMethod1)
		{
			std::istringstream iss("2 \n");
			cin.rdbuf(iss.rdbuf());
			
		}
		*/

		TEST_METHOD(TestBoardMemory)
		{
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			_CrtSetReportMode(_CRT_ERROR, _CRTDBG_MODE_DEBUG);
			//Board board();

			_CrtDumpMemoryLeaks();
		}

		TEST_METHOD(TestBoardMoveTop)
		{
			int before[] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, -1, 12,
			13, 14, 15, 20 };
			int afterTop[] =
			{ 1, 2, 3, 4,
			5, 6, -1, 8, 
			9, 10, 7, 12,
			13, 14, 15, 20 };
			Board board0(4, before);
			Board board1(4, afterTop);

			board0.Move(Direction::Top);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveBottom)
		{
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

			board0.Move(Direction::Bottom);
			Assert::IsTrue(board0.isEqualTo(board1));

		}
	};
}
