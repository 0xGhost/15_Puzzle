// Author: Yiang Lu
// Date created: 13/Oct/2019
#include "pch.h"
#include "CppUnitTest.h"
#include "..//15_Puzzle/NCLBoard.h"
#include "..//15_Puzzle/NCLBoard.cpp"
#include "..//15_Puzzle/NCLBoardTraverser.h"
#include "..//15_Puzzle/NCLBoardTraverser.cpp"

#include <sstream>
#include <iostream>
#include <ctime>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTest
{
	TEST_CLASS(NCLBoardUnitTest)
	{
	public:
		/*
		TEST_METHOD(TestMethod1)
		{
			std::istringstream iss("2 \n");
			cin.rdbuf(iss.rdbuf());

		}
		*/
		
		TEST_CLASS_INITIALIZE(RandomSeed)
		{
			srand((unsigned int)time(NULL));
		}

		TEST_METHOD(CheckContinuousNumberEqual)
		{
			ContinuousNumber c1,c2;
			Assert::IsTrue(c1 == c2);
		}

		TEST_METHOD(CheckContinuousNumberNotEqual)
		{
			ContinuousNumber c1, c2;
			c2.row = 1;
			Assert::IsFalse(c1 == c2);
		}

		TEST_METHOD(CheckRowContinuous)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 3;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);
		}

		TEST_METHOD(CheckRowReverseContinuous)
		{
			int data[16] =
			{ 4, 3, 2, 1,
			5, 6, 17, 8,
			9, 10, 16, 12,
			15, 14, 13, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 2;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckColumnContinuous)
		{
			int data[16] =
			{ 1, 5, 9, 17,
			2, 6, 7, 18,
			3, 10, 20, 19,
			4, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 2;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckColumnReverseContinuous)
		{
			int data[16] =
			{ 4, 5, 9, 19,
			3, 6, 7, 18,
			2, 10, 20, 17,
			1, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 2;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckMixedContinuous1)
		{
			int data[16] =
			{ 4, 5, 9, 17,
			3, 6, 7, 18,
			2, 10, 20, 19,
			1, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 1;
			result1.row = 0;
			result1.columnReverse = 1;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);
		}

		TEST_METHOD(CheckMixedContinuous2)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 3;
			result1.columnReverse = 0;
			result1.rowReverse = 1;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckMixedContinuous3)
		{
			int data[16] =
			{ 4, 20, 19, 13,
			5, 6, 7, 14,
			18, 17, 16, 15,
			1, 2, 3, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true);
			ContinuousNumber result1;
			result1.column = 1;
			result1.row = 1;
			result1.columnReverse = 0;
			result1.rowReverse = 1;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(TestToString)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			string str = "1 2 3 4 5 6 7 8 20 19 18 17 13 14 15 -1 ";
			Assert::AreEqual(board1.ToString(), str);
		}

		TEST_METHOD(TestIsTurnEnd)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			Assert::IsTrue(board1.IsTurnEnd());
		}

		TEST_METHOD(TestIsNotTurnEnd)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, -1, 15 };

			NCLBoard board1(4, data);
			Assert::IsFalse(board1.IsTurnEnd());
		}

		TEST_METHOD(TestGetTotalContinuousNumber1)
		{
			int load = 5;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 8);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				Assert::AreEqual(board1.GetTotalContinuousNumber(true), c.row);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber2)
		{
			int load = 5;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 12);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				Assert::AreEqual(board1.GetTotalContinuousNumber(true), c.row);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber3)
		{
			int load = 5;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 10, 30);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				Assert::AreEqual(board1.GetTotalContinuousNumber(true), c.row);
			}
		}
	};
}