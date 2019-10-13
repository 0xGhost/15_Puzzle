// Author: Yiang Lu
// Date created: 10/Oct/2019
#include "pch.h"
#include "CppUnitTest.h"
#include "..//15_Puzzle/NCLBoard.h"
#include "..//15_Puzzle/NCLBoard.cpp"

#include <sstream>
#include <iostream>
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>

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
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 3;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}

		TEST_METHOD(CheckRowReverseContinuous)
		{
			int data[16] =
			{ 4, 3, 2, 1,
			5, 6, 17, 8,
			9, 10, 16, 12,
			15, 14, 13, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 2;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}

		TEST_METHOD(CheckColumnContinuous)
		{
			int data[16] =
			{ 1, 5, 9, 17,
			2, 6, 7, 18,
			3, 10, 20, 19,
			4, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 2;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}

		TEST_METHOD(CheckColumnReverseContinuous)
		{
			int data[16] =
			{ 4, 5, 9, 19,
			3, 6, 7, 18,
			2, 10, 20, 17,
			1, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 2;
			result1.rowReverse = 0;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}

		TEST_METHOD(CheckMixedContinuous1)
		{
			int data[16] =
			{ 4, 5, 9, 17,
			3, 6, 7, 18,
			2, 10, 20, 19,
			1, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 1;
			result1.row = 0;
			result1.columnReverse = 1;
			result1.rowReverse = 0;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}

		TEST_METHOD(CheckMixedContinuous2)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber* result0 = board1.CheckContinuous();
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 3;
			result1.columnReverse = 0;
			result1.rowReverse = 1;
			Assert::IsTrue(*result0 == result1);
			delete result0;
			result0 = nullptr;
		}
	};
}