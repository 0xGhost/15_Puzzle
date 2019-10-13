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
			ContinuousNumber* c3 = new ContinuousNumber();
			Assert::IsTrue(c1 == c2);
			Assert::IsTrue(c1 == *c3);

			delete c3;
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
	};
}