// Author: Yiang Lu
// Date created: 13/Oct/2019
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
		TEST_METHOD(TestConstructorNoException1)
		{
			NCLBoard board1(4, 1, 15);
		}

		TEST_METHOD(TestConstructorNoException2)
		{
			NCLBoard board1(4, 3, 30);
		}

		TEST_METHOD(TestConstructorException0)
		{
			auto func = [&] { NCLBoard board1(4, 1, 2); };
			Assert::ExpectException<invalid_argument>(func);
		}

		TEST_METHOD(TestConstructorException1)
		{
			int data[] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, 12, 15, -1 };

			
			auto func = [&] { NCLBoard board1(4, data); };
			Assert::ExpectException<invalid_argument>(func);
		}

		TEST_METHOD(TestConstructorException2)
		{
			int data[] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, -1, 15, -1 };


			auto func = [&] { NCLBoard board1(4, data); };
			Assert::ExpectException<invalid_argument>(func);
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
			ContinuousNumber result0 = board1.CheckContinuous();
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
	};
}