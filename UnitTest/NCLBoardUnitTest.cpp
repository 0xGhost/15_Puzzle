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

		TEST_METHOD(CheckRowContinuousNoSpace)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 2;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);
		}

		TEST_METHOD(CheckPartialRowContinuous)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true, 3);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 6;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);
		}

		TEST_METHOD(CheckPartialRowContinuousNoSpace)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			9, 10, 17, 12,
			13, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false, 3);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 5;
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

		TEST_METHOD(CheckRowReverseContinuousNoSpace)
		{
			int data[16] =
			{ 4, 3, 2, 1,
			5, 6, 17, 8,
			9, 10, 16, 12,
			15, 14, 13, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 1;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckPartialRowReverseContinuous)
		{
			int data[16] =
			{ 4, 3, 2, 1,
			5, 6, 17, 8,
			9, 10, 16, 12,
			15, 14, 13, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true, 3);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 4;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckPartialRowReverseContinuousNoSpace)
		{
			int data[16] =
			{ 4, 3, 2, 1,
			5, 6, 17, 8,
			9, 10, 16, 12,
			15, 14, 13, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false, 3);
			ContinuousNumber result1;
			result1.column = 0;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 3;
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

		TEST_METHOD(CheckColumnContinuousNoSpace)
		{
			int data[16] =
			{ 1, 5, 9, 17,
			2, 6, 7, 18,
			3, 10, 20, 19,
			4, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false);
			ContinuousNumber result1;
			result1.column = 1;
			result1.row = 0;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckPartialColumnContinuous)
		{
			int data[16] =
			{ 1, 5, 9, 17,
			2, 6, 7, 18,
			3, 10, 20, 19,
			4, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(true, 3);
			ContinuousNumber result1;
			result1.column = 4;
			result1.row = 1;
			result1.columnReverse = 0;
			result1.rowReverse = 0;
			Assert::IsTrue(result0 == result1);

		}

		TEST_METHOD(CheckPartialColumnContinuousNoSpace)
		{
			int data[16] =
			{ 1, 5, 9, 17,
			2, 6, 7, 18,
			3, 10, 20, 19,
			4, 14, 15, -1 };

			NCLBoard board1(4, data);
			ContinuousNumber result0 = board1.CheckContinuous(false, 3);
			ContinuousNumber result1;
			result1.column = 3;
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

		TEST_METHOD(CheckContinuousLoadNoMultiThreading1)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };
			int load = 10000;
			for (int i = 0; i < load; i++)
			{
				NCLBoard board1(4, data);
				ContinuousNumber result0 = board1.CheckContinuous(true);
				ContinuousNumber result1;
				result1.column = 0;
				result1.row = 3;
				result1.columnReverse = 0;
				result1.rowReverse = 1;
				Assert::IsTrue(result0 == result1);
			}

		}

		TEST_METHOD(CheckContinuousLoadNoMultiThreading2)
		{
			
			int load = 10000;
			for (int i = 0; i < load; i++)
			{
				NCLBoard board1(4, 1, 20);
				ContinuousNumber result0 = board1.CheckContinuous(true);
			}

		}

		TEST_METHOD(CheckContinuousLoadMultiThreading1)
		{
			int data[16] =
			{ 1, 2, 3, 4,
			5, 6, 7, 8,
			20, 19, 18, 17,
			13, 14, 15, -1 };
			int thNum = 6;
			ctpl::thread_pool thPool(thNum);
			int load = 10000;
			auto* f = new std::future<void>[thNum];
			for (int j = 0; j < thNum; j++)
			{
				f[j] = thPool.push([&](int)
					{
						for (int i = 0; i < load / thNum; i++)
						{

							NCLBoard board1(4, data);
							ContinuousNumber result0 = board1.CheckContinuous(true);
							ContinuousNumber result1;
							result1.column = 0;
							result1.row = 3;
							result1.columnReverse = 0;
							result1.rowReverse = 1;
							Assert::IsTrue(result0 == result1);

						}
					});
			}
			for (int j = 0; j < thNum; j++)
			{
				f[j].get();
			}
		}

		TEST_METHOD(CheckContinuousLoadMultiThreading2)
		{
			int thNum = 6;
			ctpl::thread_pool thPool(thNum);
			int load = 10000;
			auto* f = new std::future<void>[thNum];
			for (int j = 0; j < thNum; j++)
			{
				f[j] = thPool.push([&](int)
					{
						for (int i = 0; i < load/ thNum; i++)
						{
							NCLBoard board1(4, 1, 20);
							ContinuousNumber result0 = board1.CheckContinuous(true);
						}
					});
			}
			for (int j = 0; j < thNum; j++)
			{
				f[j].get();
			}
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
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 8);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(true) == b);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber1_nospace)
		{
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 8);
				NCLBoardTraverser t(&board1, false);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(false) == b);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber2)
		{
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 12);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(true) == b);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber2_nospace)
		{
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 12);
				NCLBoardTraverser t(&board1, false);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(false) == b);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber3)
		{
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 10, 30);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(true) == b);
			}
		}

		TEST_METHOD(TestGetTotalContinuousNumber3_nospace)
		{
			int load = 2;
			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 10, 30);
				NCLBoardTraverser t(&board1, false);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(false) == b);
			}
		}
		TEST_METHOD(TestGetTotalContinuousNumberNoMultiThreading1)
		{
			int load = 5;

			for (int i = 1; i < load; i++)
			{
				NCLBoard board1(3, 1, 12);
				NCLBoardTraverser t(&board1, true);
				ContinuousNumber c = t.GetTotalContinuousNumber();
				BigPosInt b = c.row;
				Assert::IsTrue(board1.GetTotalContinuousNumber(true) == b);
			}
		}
		TEST_METHOD(TestGetTotalContinuousNumberMultiThreading1)
		{
			int load = 5;
			ctpl::thread_pool thPool(5);
			std::future<bool> *futures = new std::future<bool>[load];

			for (int i = 1; i < load; i++)
			{
				futures[i] = thPool.push([](int)
					{
						NCLBoard board1(3, 1, 12);
						NCLBoardTraverser t(&board1, true);
						ContinuousNumber c = t.GetTotalContinuousNumber();
						BigPosInt b = c.row;
						return board1.GetTotalContinuousNumber(true) == b;
					}

				);
			}
			for (int i = 1; i < load; i++)
			{
				Assert::IsTrue(futures[i].get());
			}
			delete[] futures;
		}
	};
}