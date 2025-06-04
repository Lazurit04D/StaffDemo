#include <vector>
#include <string>
#include <limits>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <iostream>
#include <algorithm>

#define NOMINMAX
#include <windows.h>

#include "Tester.h"
#include "Factory.h"
#include "TeamLeader.h"
#include "Programmer.h"
#include "ProjectManager.h"
using namespace std;

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

double getOrCreateProjectBudget(const string& projectName)
{
    ifstream in("staff.txt");
    string line;
    double foundBudget = -1;

    while (getline(in, line))
    {
        istringstream iss(line);
        vector<string> tokens;
        string token;
        while (iss >> token)
        {
            tokens.push_back(token);
        }

        if (tokens.size() >= 6)
        {
            string pos = tokens[2];

            if ((pos == "Programmer" || pos == "Tester" || pos == "TeamLeader") && tokens[5] == projectName)
            {
                foundBudget = stod(tokens[4]);
                break;
            }
            else if (pos == "ProjectManager" && tokens[4] == projectName)
            {
                foundBudget = stod(tokens[3]);
                break;
            }
        }
    }
    in.close();

    if (foundBudget != -1)
    {
        return foundBudget;
    }

    double newBudget;
    cout << "������� ������ �������: ";
    while (!(cin >> newBudget))
    {
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
        cout << "����� �����!\n������� ������ �������: ";
    }

    ifstream in2("staff.txt");
    vector<string> lines;
    while (getline(in2, line))
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

            budgets.push_back(newBudget);
            sort(budgets.begin(), budgets.end());

            tokens[3] = to_string(budgets.size());
            
            vector<string> extraTokens;
            for (size_t i = 4 + count; i < tokens.size(); ++i)
            {
                extraTokens.push_back(tokens[i]);
            }

            tokens.resize(4);
            for (double b : budgets)
            {
                tokens.push_back(to_string(b));
            }

            tokens.insert(tokens.end(), extraTokens.begin(), extraTokens.end());

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
    in2.close();

    ofstream out("staff.txt");
    for (const string& l : lines)
    {
        out << l << '\n';
    }
    out.close();

    return newBudget;
}

void removeBudgetFromFile(double budgetToRemove)
{
    ifstream in("staff.txt");
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

    ofstream out("staff.txt");
    for (const string& l : lines)
    {
        out << l << '\n';
    }
    out.close();
}


void printHeader()
{
    cout << endl;
    cout << left << setw(3) << "ID" << setw(27) << "���" << setw(15) << "���������" << setw(12) << "������" << "�/�\n";
    cout << string(64, '-') << '\n';
}

void printAll(const vector<Employee*>& staff)
{
    printHeader();

    for (Employee* emp : staff)
    {
        emp->printInfo();
    }
}

void findByProject(const vector<Employee*>& staff, const string& project)
{
    bool found = false;

    for (Employee* emp : staff)
    {
        if (toLower(emp->getProject()) == toLower(project))
        {
            emp->printInfo();
            found = true;
        }
    }

    if (!found)
    {
        cout << "������ �� �������!\n";
    }
}

void findByPosition(const vector<Employee*>& staff, const string& position)
{
    bool found = false;

    for (Employee* emp : staff)
    {
        if (toLower(emp->getPosition()) == toLower(position))
        {
            emp->printInfo();
            found = true;
        }
    }

    if (!found)
    {
        cout << "������ �� �������!\n";
    }
}

void findByName(const vector<Employee*>& staff, const string& name)
{
    bool found = false;

    for (Employee* emp : staff)
    {
        if (toLower(emp->getName()).find(toLower(name)) != string::npos)
        {
            emp->printInfo();
            found = true;
        }
    }

    if (!found)
    {
        cout << "������ �� �������!\n";
    }
}

void findByPayment(const vector<Employee*>& staff, double amount, bool more)
{
    bool found = false;

    for (Employee* emp : staff)
    {
        if (more && emp->getPayment() > amount)
        {
            emp->printInfo();
            found = true;
        }
        else if (!more && emp->getPayment() < amount)
        {
            emp->printInfo();
            found = true;
        }
    }

    if (!found)
    {
        cout << "������ �� �������!\n";
    }
}

void setWorkTimeForAll(vector<Employee*>& staff, int worktime)
{
    for (Employee* emp : staff)
    {  
        emp->setWorkTime(worktime);
        emp->calc();
    }
}

void appendToStaffFile(const string& line)
{
    ofstream file("staff.txt", ios::app);
    file << line << '\n';
    file.close();
}

void addOrUpdateProject(int id, const string& newProject, double newBudget)
{
    ifstream in("staff.txt");
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

    ofstream out("staff.txt");
    for (const string& l : lines)
    {
        out << l << '\n';
    }
    out.close();
}

int main()
{
    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    int standartWorkTime = 50;
    vector<Employee*> staff = StaffFactory::makeStaff("staff.txt");
    setWorkTimeForAll(staff, standartWorkTime);

    while (true)
    {
        cout << "\n1. �������� ���� �����������\n";
        cout << "2. ���������� �������\n";
        cout << "3. ����� �� ���������\n";
        cout << "4. ����� �� �����\n";
        cout << "5. ����� �� ��������\n";
        cout << "6. �������� ������ ����������\n";
        cout << "7. ��������� ���������� �� ������ ������\n";
        cout << "8. �������� ���������� ����� ������ � ������\n";
        cout << "0. �����\n";
        cout << "�����: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "������� ����� ������!\n";
            continue;
        }

        if (choice == 0)
        {
            cout << "��������� �������!\n";
            break;
        }
        else if (choice == 1)
        {
            printAll(staff);
        }
        else if (choice == 2)
        {
            string project;
            cout << "������� �������� �������: ";
            cin >> project;
            findByProject(staff, project);
        }
        else if (choice == 3)
        {
            string pos;
            cout << "������� ���������: ";
            cin >> pos;
            findByPosition(staff, pos);
        }
        else if (choice == 4)
        {
            string name;
            cout << "������� ���: ";
            cin >> name;
            findByName(staff, name);
        }
        else if (choice == 5)
        {
            int mode;
            double amount;

            while (true)
            {
                cout << "1 - ������, 0 - ������: ";
                if (cin >> mode && (mode == 0 || mode == 1))
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "������� 0 ��� 1!\n";
            }

            while (true)
            {
                cout << "������� �����: ";
                if (cin >> amount && (amount > 0))
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "����� ������������� �����!\n";
            }

            findByPayment(staff, amount, mode == 1);
        }
        else if (choice == 6)
        {
            int id = 1;
            string name, position, project;
            double rate, budget, bonus;
            int posChoice, extra;

            ifstream file("staff.txt");
            string line;

            while (getline(file, line))
            {
                if (!line.empty())
                {
                    id++;
                }
            }
            file.close(); 

            cout << "��� (����� _): ";
            cin >> name;
            cout << "�������� ���������:\n[1] - Programmer\n[2] - Tester\n[3] - TeamLeader\n[4] - ProjectManager\n��� �����: ";
            cin >> posChoice;
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

            if (position == "Programmer")
            {
                while (true)
                {
                    cout << "������� ��������� ������: ";
                    if (cin >> rate && (rate > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                cout << "������� �������� �������: ";
                cin >> project;
                budget = getOrCreateProjectBudget(project);
                while (true)
                {
                    cout << "������� ������: ";
                    if (cin >> bonus && (bonus > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                auto* p = new Programmer(id, name, rate, budget, project, bonus);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "Tester")
            {
                while (true)
                {
                    cout << "������� ��������� ������: ";
                    if (cin >> rate && (rate > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                cout << "������� �������� �������: ";
                cin >> project;
                budget = getOrCreateProjectBudget(project);
                while (true)
                {
                    cout << "������� ���������� �����: ";
                    if (cin >> extra && (extra > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                auto* p = new Tester(id, name, rate, budget, project, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "TeamLeader")
            {
                while (true)
                {
                    cout << "������� ��������� ������: ";
                    if (cin >> rate && (rate > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                cout << "������� �������� �������: ";
                cin >> project;
                budget = getOrCreateProjectBudget(project);
                while (true)
                {
                    cout << "������� ������ �������: ";
                    if (cin >> extra && (extra > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                auto* p = new TeamLeader(id, name, rate, budget, project, 0, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "ProjectManager")
            {
                cout << "������� �������� �������: ";
                cin >> project;
                budget = getOrCreateProjectBudget(project);
                while (true)
                {
                    cout << "������� ������ �������: ";
                    if (cin >> extra && (extra > 0))
                    {
                        break;
                    }
                    cin.clear();
                    cin.ignore(numeric_limits<streamsize>::max(), '\n');
                    cout << "����� ������������� �����!\n";
                }
                auto* p = new ProjectManager(id, name, budget, project, extra);
                p->setWorkTime(standartWorkTime);
                p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else
            {
                cout << "��� ��������� �� ��������������.\n";
            }
        }
        else if (choice == 7)
        {
            int id;
            double newBudget = 0;
            string newProject = "Project_";

            cout << "������� ID ����������: ";
            cin >> id;

            bool canBeAdded = false, found = false;
            for (Employee* emp : staff)
            {
                if (emp->getId() == id)
                {
                    string oldProject = emp->getProject();
                    emp->setProject(newProject);
                    if (emp->getProject() != "")
                    {
                        canBeAdded = true;
                        emp->setProject(oldProject);
                    }
                    else
                    {
                        cout << "��������� �� ����� ���� �������� �� ������!\n";
                        canBeAdded = false;
                    }
                    found = true;
                    break;
                }
            }
            if (!found)
            {
                cout << "��������� �� ������.\n";
            }

            if (canBeAdded)
            {
                cout << "������� ����� ������: ";
                cin >> newProject;
                newBudget = getOrCreateProjectBudget(newProject);

                for (Employee* emp : staff)
                {
                    if (emp->getId() == id)
                    {
                        string oldProject = emp->getProject();
                        double budgetToRemove = emp->getBudget();
                        emp->setProject(newProject);
                        emp->setBudget(newBudget);
                        addOrUpdateProject(id, newProject, newBudget);
                        cout << "������ �������.\n";
                        emp->calc();
                        for (Employee* emp : staff)
                        {
                            if (emp->getPosition() == "SeniorManager")
                            {
                                emp->syncBudgetsFromFile();
                                emp->calc();
                                break;
                            }
                        }

                        bool projectStillUsed = false;
                        for (Employee* e : staff)
                        {
                            if (e->getProject() == oldProject)
                            {
                                projectStillUsed = true;
                                break;
                            }
                        }

                        if (!projectStillUsed)
                        {
                            removeBudgetFromFile(budgetToRemove);
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

                        break;
                    }
                }
            }
        }
        else if (choice == 8)
        {
            int worktime;
            while (true)
            {
                cout << "������� ������� � ������ �������� ����������?: ";
                if (cin >> worktime)
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "����� �����!\n";
            }
            setWorkTimeForAll(staff, worktime);
            cout << "����� ������ ����������� ��������!\n";
        }
        else
        {
            cout << "��� ������ ������!\n";
        }
    }

    for (Employee* emp : staff)
    {
        delete emp;
    }
    return 0;
}