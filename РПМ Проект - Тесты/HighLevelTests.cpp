#include "CppUnitTest.h"
#include <fstream>
#include <vector>
#include <string>
#include <sstream>
#include <cstdio>
#include "Factory.h"
#include "Employee.h"
#include "Programmer.h"
#include "Tester.h"
#include "TeamLeader.h"
#include "ProjectManager.h"
#include "SeniorManager.h"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;
using namespace std;

const string testFileName = "staff_test.txt";

namespace HighLevelTests
{
    TEST_CLASS(HighLevelTests)
    {
    public:

        void prepareTestFile(const string& content)
        {
            SeniorManager::setFileName(testFileName);
            ofstream out(testFileName);
            out << content;
            out.close();
        }

        vector<Employee*> loadStaff()
        {
            return StaffFactory::makeStaff(testFileName);
        }

        void cleanupStaff(vector<Employee*>& staff)
        {
            for (int i = 0; i < staff.size(); i++)
            {
                delete staff[i];
            }
            staff.clear();
        }

        string toLower(const string& s)
        {
            string result;

            for (unsigned char c : s)
            {
                if (c >= 'A' && c <= 'Z')
                {
                    result += c + ('a' - 'A');
                }
                else if (c >= 192 && c <= 223)
                {
                    result += c + 32;
                }
                else if (c == 168)
                {
                    result += 184;
                }
                else
                {
                    result += c;
                }
            }

            return result;
        }

        void appendToStaffFile(const string& line)
        {
            ofstream file(testFileName, ios::app);
            file << line << '\n';
            file.close();
        }

        void addOrUpdateProject(int id, const string& newProject, double newBudget)
        {
            ifstream in(testFileName);
            vector<string> lines;
            string line;

            while (getline(in, line))
            {
                istringstream iss(line);
                vector<string> tokens;
                string token;

                while (iss >> token)
                {
                    tokens.push_back(token);
                }

                if (!tokens.empty() && stoi(tokens[0]) == id)
                {
                    string position = tokens[2];

                    if (position == "Programmer" || position == "Tester")
                    {
                        tokens[4] = to_string(newBudget);
                        tokens[5] = newProject;
                    }
                    else if (position == "TeamLeader")
                    {
                        tokens[4] = to_string(newBudget);
                        tokens[5] = newProject;
                    }
                    else if (position == "ProjectManager")
                    {
                        tokens[3] = to_string(newBudget);
                        tokens[4] = newProject;
                    }

                    ostringstream oss;
                    for (const string& t : tokens)
                    {
                        oss << t << ' ';
                    }
                    line = oss.str();
                    line.pop_back();
                }

                lines.push_back(line);
            }
            in.close();

            ofstream out(testFileName);
            for (const string& l : lines)
            {
                out << l << '\n';
            }
            out.close();
        }

        void removeBudgetFromFile(double budgetToRemove)
        {
            ifstream in(testFileName);
            vector<string> lines;
            string line;

            while (getline(in, line))
            {
                istringstream iss(line);
                vector<string> tokens;
                string token;
                while (iss >> token)
                {
                    tokens.push_back(token);
                }

                if (!tokens.empty() && tokens[2] == "SeniorManager")
                {
                    int count = stoi(tokens[3]);
                    vector<double> budgets;

                    for (int i = 0; i < count; ++i)
                    {
                        budgets.push_back(stod(tokens[4 + i]));
                    }

                    for (auto it = budgets.begin(); it != budgets.end(); )
                    {
                        if (abs(*it - budgetToRemove) < 1e-6)
                        {
                            it = budgets.erase(it);
                        }
                        else
                        {
                            ++it;
                        }
                    }

                    tokens.erase(tokens.begin() + 4, tokens.begin() + 4 + count);

                    tokens[3] = to_string(budgets.size());
                    for (int i = 0; i < budgets.size(); ++i)
                    {
                        tokens.insert(tokens.begin() + 4 + i, to_string(budgets[i]));
                    }

                    ostringstream oss;
                    for (const string& t : tokens)
                    {
                        oss << t << ' ';
                    }
                    line = oss.str(); line.pop_back();
                }

                lines.push_back(line);
            }

            in.close();

            ofstream out(testFileName);
            for (const string& l : lines)
            {
                out << l << '\n';
            }
            out.close();
        }

        TEST_METHOD(TestFindByProject)
        {
            prepareTestFile(
                "1 Иванов_Иван_Иванович Cleaner 150\n"
                "2 Петров_Петр_Петрович Driver 200 5\n"
                "3 Сидоров_Сидор_Сидорович Programmer 300 100000 ProjectA 1000\n"
                "4 Кузнецов_Алексей_Сергеевич Tester 250 50000 ProjectB 5\n"
            );

            vector<Employee*> staff = loadStaff();

            int countA = 0;
            for (int i = 0; i < staff.size(); i++)
            {
                if (toLower(staff[i]->getProject()) == toLower("ProjectA"))
                {
                    countA++;
                }
            }

            Assert::AreEqual(1, countA);

            int counta = 0;
            for (int i = 0; i < staff.size(); i++)
            {
                if (toLower(staff[i]->getProject()) == toLower("projecta"))
                {
                    counta++;
                }
            }

            Assert::AreEqual(1, counta);

            cleanupStaff(staff);
        }

        TEST_METHOD(TestAddNewEmployee)
        {
            prepareTestFile(
                "1 Иванов_Иван_Иванович Cleaner 150\n"
                "2 Сидоров_Сидор_Сидорович Programmer 300 100000 ProjectA 1000\n"
            );

            auto staff = loadStaff();
            int standartWorkTime = 50;
            for (Employee* emp : staff)
            {
                emp->setWorkTime(standartWorkTime);
                emp->calc();
            }

            string name = "Петров_Петр_Петрович";
            int posChoice = 1;
            string position;

            if (posChoice == 1)
            {
                position = "Programmer";
            }
            else if (posChoice == 2)
            {
                position = "Tester";
            }
            else if (posChoice == 3)
            {
                position = "TeamLeader";
            }
            else if (posChoice == 4)
            {
                position = "ProjectManager";
            }

            double rate = 350;
            string project = "ProjectA";
            double budget = 100000;
            double bonus = 1200;
            int extra = 5;

            int id = 1;
            {
                ifstream file(testFileName);
                string line;
                while (getline(file, line))
                {
                    if (!line.empty())
                    {
                        id++;
                    }
                }
            }

            if (position == "Programmer")
            {
                Programmer* p = new Programmer(id, name, rate, budget, project, bonus);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);

                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus));
                addOrUpdateProject(id, project, budget);

                Assert::AreEqual(id, staff.back()->getId());
                Assert::AreEqual(position, staff.back()->getPosition());
                Assert::AreEqual(project, staff.back()->getProject());

                double expectedPayment = rate * standartWorkTime + budget * 0.05 + bonus;
                Assert::AreEqual(expectedPayment, staff.back()->getPayment());
            }
            else if (position == "Tester")
            {
                Tester* p = new Tester(id, name, rate, budget, project, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);

                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);

                Assert::AreEqual(id, staff.back()->getId());
                Assert::AreEqual(position, staff.back()->getPosition());
                Assert::AreEqual(project, staff.back()->getProject());

                double expectedPayment = rate * standartWorkTime + budget * 0.05 + extra * 100;
                Assert::AreEqual(expectedPayment, staff.back()->getPayment());
            }
            else if (position == "TeamLeader")
            {
                TeamLeader* p = new TeamLeader(id, name, rate, budget, project, 0, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);

                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);

                Assert::AreEqual(id, staff.back()->getId());
                Assert::AreEqual(position, staff.back()->getPosition());
                Assert::AreEqual(project, staff.back()->getProject());

                double expectedPayment = rate * standartWorkTime + budget * 0.05 + extra * 1000;
                Assert::AreEqual(expectedPayment, staff.back()->getPayment());
            }
            else if (position == "ProjectManager")
            {
                ProjectManager* p = new ProjectManager(id, name, budget, project, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);

                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);

                Assert::AreEqual(id, staff.back()->getId());
                Assert::AreEqual(position, staff.back()->getPosition());
                Assert::AreEqual(project, staff.back()->getProject());
    
                double expectedPayment = budget * 0.1 + extra * 1500;
                Assert::AreEqual(expectedPayment, staff.back()->getPayment());
            }
            else
            {
                Assert::Fail(L"Эта должность не поддерживается.");
            }

            cleanupStaff(staff);
        }

        TEST_METHOD(TestChangeProject)
        {
            prepareTestFile(
                "1 Иванов_Иван_Иванович Programmer 300 100000 ProjectX 1000\n"
                "2 Петров_Петр_Петрович SeniorManager 1 100000\n"
            );

            auto staff = loadStaff();
            int standartWorkTime = 50;
            for (Employee* emp : staff)
            {
                emp->setWorkTime(standartWorkTime);
                emp->calc();
            }

            int id = 1;
            string newProject = "ProjectY";
            double newBudget = 150000;

            string oldProject;
            bool canBeAdded = false;

            for (Employee* emp : staff)
            {
                if (emp->getId() == id)
                {
                    oldProject = emp->getProject();
                    emp->setProject(newProject);

                    if (emp->getProject() != "")
                    {
                        emp->setBudget(newBudget);
                        emp->calc();
                        addOrUpdateProject(id, newProject, newBudget);
                        canBeAdded = true;
                    }
                    break;
                }
            }

            Assert::IsTrue(canBeAdded);

            for (Employee* emp : staff)
            {
                if (emp->getPosition() == "SeniorManager")
                {
                    emp->syncBudgetsFromFile();
                    emp->calc();
                }
            }

            bool projectStillUsed = false;
            for (Employee* emp : staff)
            {
                if (emp->getProject() == oldProject)
                {
                    projectStillUsed = true;
                    break;
                }
            }

            if (!projectStillUsed)
            {
                for (Employee* emp : staff)
                {
                    if (emp->getPosition() == "SeniorManager")
                    {
                        emp->syncBudgetsFromFile();
                        emp->calc();
                        break;
                    }
                }
            }

            for (Employee* emp : staff)
            {
                if (emp->getId() == id)
                {
                    Assert::AreEqual(newProject, emp->getProject());
                    Assert::AreEqual(newBudget, emp->getBudget());
                }
            }

            cleanupStaff(staff);
        }

        TEST_METHOD(TestChangeWorkTime)
        {
            prepareTestFile(
                "1 Иванов_Иван_Иванович Programmer 300 100000 ProjectX 1000\n"
            );

            auto staff = loadStaff();
            int standartWorkTime = 40;
            for (Employee* emp : staff)
            {
                emp->setWorkTime(standartWorkTime);
                emp->calc();
            }

            for (Employee* emp : staff)
            {
                Assert::AreEqual(40, emp->getWorkTime());
            }

            standartWorkTime = 60;
            for (Employee* emp : staff)
            {
                emp->setWorkTime(standartWorkTime);
                emp->calc();
            }

            for (Employee* emp : staff)
            {
                Assert::AreEqual(60, emp->getWorkTime());
            }

            cleanupStaff(staff);
        }

        TEST_METHOD(TestRemoveUnusedProjectBudget)
        {
            prepareTestFile(
                "1 Иванов_Иван_Иванович Programmer 300 100000 ProjectX 1000\n"
                "2 Сидоров_Сидор_Сидорович SeniorManager 1 100000\n"
            );

            auto staff = loadStaff();
            int standartWorkTime = 50;
            for (Employee* emp : staff)
            {
                emp->setWorkTime(standartWorkTime);
                emp->calc();
            }

            int id = 1;
            string newProject = "ProjectY";
            double newBudget = 150000;
            string oldProject;
            double oldBudget;

            for (Employee* emp : staff)
            {
                if (emp->getId() == id)
                {
                    oldProject = emp->getProject();
                    oldBudget = emp->getBudget();
                    emp->setProject(newProject);
                    emp->setBudget(newBudget);
                    addOrUpdateProject(id, newProject, newBudget);
                    break;
                }
            }

            removeBudgetFromFile(oldBudget);

            for (Employee* emp : staff)
            {
                if (emp->getPosition() == "SeniorManager")
                {
                    emp->syncBudgetsFromFile();
                    emp->calc();
                    vector<double> budgets = emp->getBudgets();
                    for (double b : budgets)
                    {
                        Assert::IsTrue(abs(b - oldBudget) >= 1e-6);
                    }
                }
            }

            cleanupStaff(staff);
        }

    };
}