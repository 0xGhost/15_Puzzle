// Author: Yiang Lu
// Date created: 10/Oct/2019
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

		int before[16] =
		{ 1, 2, 3, 4,
		5, 6, 7, 8,
		9, 10, -1, 12,
		13, 14, 15, 20 };

		TEST_METHOD(TestGetNumberLength)
		{
			Assert::AreEqual(3, GetNumberLength(123));
		}

		TEST_METHOD(TestBoardEqual)
		{
			int after[] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, -1, 12,
			13, 14, 15, 20 };
			Board board1(4, after);
			Board board0(4, before);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardNotEqual)
		{
			int after[] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, -1, 13,
			13, 14, 15, 20 };
			Board board1(4, after);
			Board board0(4, before);
			Assert::IsFalse(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardGoodMove)
		{
			Board board0(4, before);
			Assert::IsTrue(board0.Move(Direction::Top));
		}

		TEST_METHOD(TestBoardNoBottomMove)
		{
			int noBottom[] =
			{ 1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 15, 12,
				13, 14, -1, 20 };
			Board board0(4, noBottom);
			Board board1(4, noBottom);
			Assert::IsFalse(board0.Move(Direction::Bottom));
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardNoTopMove)
		{
			int noTop[] =
			{ 1, 2, -1, 4,
				5, 6, 7, 8,
				9, 10, 15, 12,
				13, 14, 3, 20 };
			Board board0(4, noTop);
			Board board1(4, noTop);
			Assert::IsFalse(board0.Move(Direction::Top));
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardNoLeftMove)
		{
			int noLeft[] =
			{ 1, 2, 9, 4,
				5, 6, 7, 8,
				-1, 10, 15, 12,
				13, 14, 3, 20 };
			Board board0(4, noLeft);
			Board board1(4, noLeft);
			Assert::IsFalse(board0.Move(Direction::Left));
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardNoRightMove)
		{
			int noRight[] =
			{ 1, 2, 9, 4,
				5, 6, 7, 8,
				12, 10, 15, -1,
				13, 14, 3, 20 };
			Board board0(4, noRight);
			Board board1(4, noRight);
			Assert::IsFalse(board0.Move(Direction::Right));
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveTop)
		{
			int afterTop[] =
			{ 1, 2, 3, 4,
			5, 6, -1, 8, 
			9, 10, 7, 12,
			13, 14, 15, 20 };
			Board board1(4, afterTop);
			Board board0(4, before);
			board0.Move(Direction::Top);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveBottom)
		{
			int afterBottom[] = 
			{ 1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 15, 12,
				13, 14, -1, 20 };
			
			Board board1(4, afterBottom);
			Board board0(4, before);
			board0.Move(Direction::Bottom);
			Assert::IsTrue(board0.isEqualTo(board1));

		}

		TEST_METHOD(TestBoardMoveLeft)
		{
			int afterLeft[] =
			{ 1, 2, 3, 4,
				5, 6, 7, 8,
				9, -1, 10, 12,
				13, 14, 15, 20 };

			Board board1(4, afterLeft);
			Board board0(4, before);
			board0.Move(Direction::Left);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveRight)
		{
			int afterRight[] =
			{ 1, 2, 3, 4,
				5, 6, 7, 8,
				9, 10, 12, -1,
				13, 14, 15, 20 };

			Board board1(4, afterRight);
			Board board0(4, before);
			board0.Move(Direction::Right);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveRightTop)
		{
			int afterRight[] =
			{ 1, 2, 3, 4,
				5, 6, 7, -1,
				9, 10, 12, 8,
				13, 14, 15, 20 };

			Board board1(4, afterRight);
			Board board0(4, before);
			board0.Move(Direction::Right);
			board0.Move(Direction::Top);
			Assert::IsTrue(board0.isEqualTo(board1));
		}

		TEST_METHOD(TestBoardMoveRightTopLeft)
		{
			int afterRight[] =
			{ 1, 2, 3, 4,
				5, 6, -1, 7,
				9, 10, 12, 8,
				13, 14, 15, 20 };

			Board board1(4, afterRight);
			Board board0(4, before);
			board0.Move(Direction::Right);
			board0.Move(Direction::Top);
			board0.Move(Direction::Left);
			Assert::IsTrue(board0.isEqualTo(board1));
		}
	};
}
