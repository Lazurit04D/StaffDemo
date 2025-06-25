#include "pch.h"
#include "CppUnitTest.h"
#include "Factory.h"
#include "Driver.h"
#include "Cleaner.h"
#include "Tester.h"
#include "Programmer.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "SeniorManager.h"
#include <vector>
#include <string>
#include <fstream>

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

static constexpr const char* testFileName = "staff_test.txt";

namespace FileFunctionsTests
{
    TEST_CLASS(FileFunctionsTests)
    {
    public:

        TEST_METHOD_INITIALIZE(CleanAndPrepareTestFile)
        {
            ofstream out(testFileName, ios::trunc);
            out <<
                "1 Иванов_Иван_Иванович Cleaner 150\n"
                "2 Петров_Петр_Петрович Driver 200 5\n"
                "3 Сидоров_Сидор_Сидорович Programmer 300 100000 ProjectA 1000\n"
                "4 Кузнецов_Алексей_Сергеевич Tester 250 50000 ProjectB 5\n"
                "5 Козлов_Дмитрий_Викторович TeamLeader 350 150000 ProjectC 3\n"
                "6 Васильев_Олег_Игоревич ProjectManager 150000 ProjectC 5\n"
                "7 Смирнова_Елена_Николаевна SeniorManager 3 100000 50000 150000 10\n";
            out.close();
        }

        TEST_METHOD(TestCleaner)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("Cleaner"), staff[0]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestDriver)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("Driver"), staff[1]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestProgrammer)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("Programmer"), staff[2]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestTester)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("Tester"), staff[3]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestTeamLeader)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("TeamLeader"), staff[4]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestProjectManager)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("ProjectManager"), staff[5]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }

        TEST_METHOD(TestSeniorManager)
        {
            auto staff = StaffFactory::makeStaff(testFileName);
            Assert::AreEqual(string("SeniorManager"), staff[6]->getPosition());
            for (auto e : staff)
            {
                delete e;
            }
        }
    };
}