#include "pch.h"
#include "CppUnitTest.h"
#include "Driver.h"
#include "Cleaner.h"
#include "Tester.h"
#include "Programmer.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "SeniorManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace StaffTests
{
	TEST_CLASS(TestDriver)
	{
		TEST_METHOD(CalcBonus)
		{
			Driver d(1, "Test Driver", 100);
			d.setNightHours(5);
			Assert::AreEqual(500.0, d.calcBonus());
		}
	};

	TEST_CLASS(TestCleaner)
	{
		TEST_METHOD(GetPosition)
		{
			Cleaner c(2, "Test Cleaner", 120);
			Assert::AreEqual("Cleaner", c.getPosition().c_str());
		}
	};

	TEST_CLASS(TestTester)
	{
		TEST_METHOD(CalcProAdditions)
		{
			Tester t(3, "Test Tester", 150, 50000, "ProjX", 7);
			Assert::AreEqual(700.0, t.calcProAdditions());
		}
	};

	TEST_CLASS(TestProgrammer)
	{
		TEST_METHOD(CalcProAdditions)
		{
			Programmer p(4, "Test Programmer", 200, 60000, "ProjY", 1500);
			Assert::AreEqual(1500.0, p.calcProAdditions());
		}
	};

	TEST_CLASS(TestTeamLeader)
	{
		TEST_METHOD(CalcHeadingBonus)
		{
			TeamLeader tl(5, "Team Lead", 300, 70000, "ProjZ", 1000, 4);
			Assert::AreEqual(4000.0, tl.calcHeadingBonus());
		}
	};

	TEST_CLASS(TestProjectManager)
	{
		TEST_METHOD(CalcBudgetPart)
		{
			ProjectManager pm(6, "PM", 80000, "ProjA", 5);
			Assert::AreEqual(8000.0, pm.calcBudgetPart());
		}
	};

	TEST_CLASS(TestSeniorManager)
	{
		TEST_METHOD(CalcBudgetPart)
		{
			vector<double> budgets = { 100000, 50000, 150000 };
			SeniorManager sm(7, "SM", budgets, 10);
			Assert::AreEqual(30000.0, sm.calcBudgetPart());
		}
	};
}