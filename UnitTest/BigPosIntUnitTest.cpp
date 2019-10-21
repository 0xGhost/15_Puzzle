// Author: Yiang Lu
// Date created: 20/Oct/2019
#include "pch.h"
#include "CppUnitTest.h"
#include "..//15_Puzzle/BigPosInt.h"
#include "..//15_Puzzle/BigPosInt.cpp"


#include <sstream>
#include <iostream>
#include <ctime>


using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;


namespace UnitTest
{
	TEST_CLASS(BigPosIntBoardUnitTest)
	{
	public:

		TEST_CLASS_INITIALIZE(RandomSeed)
		{
			srand((unsigned int)time(NULL));
		}

		TEST_METHOD(OstreamAndAssignTest)
		{
			stringstream ss;
			BigPosInt a = 123;
			string str1 = "123";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(OstreamAndAssignTest2)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			string str1 = "18446744073709551615";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(OstreamAndAssignTest3)
		{
			stringstream ss;
			BigPosInt a = 18446744073700000000;
			string str1 = "18446744073700000000";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest1)
		{
			stringstream ss;
			BigPosInt a = 123;
			BigPosInt b = 456;
			a += b;
			string str1 = "579";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest2)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			BigPosInt b = 1;
			a += b;
			string str1 = "18446744073709551616";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest3)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			BigPosInt b = 18446744073709551615;
			
			a += b;
			string str1 = "36893488147419103230";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest4)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			BigPosInt b = 615;
			a += b;
			string str1 = "18446744073709552230";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest5)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			BigPosInt b = 10000000000000000615;
			a += b;
			string str1 = "28446744073709552230";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(AddTest6)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			BigPosInt b = 10000000000000000000;
			a += b + b + b;
			string str1 = "48446744073709551615";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(MultiplyTest1)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			unsigned int b = 2;

			a = a * b;
			string str1 = "36893488147419103230";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(MultiplyTest2)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			unsigned int b = 2000000;

			a = a * b;
			string str1 = "36893488147419103230000000";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

		TEST_METHOD(MultiplyTest3)
		{
			stringstream ss;
			BigPosInt a = 18446744073709551615;
			unsigned int b = 20;

			a = a * b;
			string str1 = "368934881474191032300";
			string str2;
			ss << a;
			ss >> str2;
			Assert::AreEqual(str1, str2);
		}

	};
}