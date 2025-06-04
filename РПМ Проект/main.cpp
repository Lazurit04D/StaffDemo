//��������� �������� git 
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
    for (Employee* emp : staff)
    {
        if (more && emp->getPayment() > amount)
        {
            emp->printInfo();
        }
        else if (!more && emp->getPayment() < amount)
        {
            emp->printInfo();
        }
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

    vector<Employee*> staff = StaffFactory::makeStaff("staff.txt");
    setWorkTimeForAll(staff, 50);

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
                if (cin >> amount)
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "����� �����!\n";
            }

            findByPayment(staff, amount, mode == 1);
        }
        else if (choice == 6)
        {
            int id = 1;
            string name, position, project;
            double rate, budget, bonus;
            int extra;

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
            cout << "��������� (Programmer / Tester / TeamLeader / ProjectManager): ";
            cin >> position;

            if (position == "Programmer")
            {
                cout << "������� ��������� ������: "; cin >> rate;
                cout << "������� �������� �������: "; cin >> project;
                //TODO ������� ��������, ��� ���� ������ ��� ����������, �� ���� ������ �� ����
                cout << "������� ������ �������: "; cin >> budget;
                //TODO ����� ���������� ������ �������/������� �������� ��� � SeniorManager
                cout << "������� ������: "; cin >> bonus;
                auto* p = new Programmer(id, name, rate, budget, project, bonus);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "Tester")
            {
                cout << "������� ��������� ������: "; cin >> rate;
                cout << "������� �������� �������: "; cin >> project;
                //TODO ������� ��������, ��� ���� ������ ��� ����������, �� ���� ������ �� ����
                cout << "������� ������ �������: "; cin >> budget;
                //TODO ����� ���������� ������ �������/������� �������� ��� � SeniorManager
                cout << "������� ���������� �����: "; cin >> extra;
                auto* p = new Tester(id, name, rate, budget, project, extra);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "TeamLeader")
            {
                cout << "������� ��������� ������: "; cin >> rate;
                cout << "������� �������� �������: "; cin >> project;
                //TODO ������� ��������, ��� ���� ������ ��� ����������, �� ���� ������ �� ����
                cout << "������� ������ �������: "; cin >> budget;
                //TODO ����� ���������� ������ �������/������� �������� ��� � SeniorManager
                cout << "������� ������: "; cin >> bonus;
                cout << "������� ������ �������: "; cin >> extra;
                auto* p = new TeamLeader(id, name, rate, budget, project, bonus, extra);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus) + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "��������� ������� ��������.\n";
            }
            else if (position == "ProjectManager")
            {
                cout << "������� �������� �������: "; cin >> project;
                //TODO ������� ��������, ��� ���� ������ ��� ����������, �� ���� ������ �� ����
                cout << "������� ������ �������: "; cin >> budget;
                //TODO ����� ���������� ������ �������/������� �������� ��� � SeniorManager
                cout << "������� ������ �������: "; cin >> extra;
                auto* p = new ProjectManager(id, name, budget, project, extra);
                p->setWorkTime(160); p->calc();
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
            string newProject;
            double newBudget;
            cout << "������� ID ����������: "; cin >> id;
            cout << "������� ����� ������: "; cin >> newProject;
            //TODO ������� ��������, ��� ���� ������ ��� ����������, �� ���� ������ �� ����
            cout << "������� ������ �������: "; cin >> newBudget;
            //TODO ����� ���������� ������ �������/������� �������� ��� � SeniorManager

            bool found = false;
            for (Employee* emp : staff)
            {
                if (emp->getId() == id)
                {
                    if (emp->getProject() != "")
                    {
                        emp->setProject(newProject);
                        emp->calc();
                        addOrUpdateProject(id, newProject, newBudget);
                        cout << "������ �������.\n";
                        found = true;
                        break;
                    }
                    else
                    {
                        cout << "� ����� ���������� ��� �������.\n";
                    }
                }
            }
            if (!found)
            {
                cout << "��������� �� ������.\n";
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