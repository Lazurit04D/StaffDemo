//небольшая проверка git 
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
    cout << left << setw(3) << "ID" << setw(27) << "ФИО" << setw(15) << "Должность" << setw(12) << "Проект" << "З/п\n";
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
        cout << "Ничего не найдено!\n";
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
        cout << "Ничего не найдено!\n";
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
        cout << "Ничего не найдено!\n";
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
        cout << "\n1. Показать всех сотрудников\n";
        cout << "2. Сотрудники проекта\n";
        cout << "3. Поиск по должности\n";
        cout << "4. Поиск по имени\n";
        cout << "5. Поиск по зарплате\n";
        cout << "6. Добавить нового сотрудника\n";
        cout << "7. Перевести сотрудника на другой проект\n";
        cout << "8. Изменить количество часов работы в неделю\n";
        cout << "0. Выход\n";
        cout << "Выбор: ";

        int choice;
        cin >> choice;

        if (cin.fail())
        {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            cout << "Введите номер пункта!\n";
            continue;
        }

        if (choice == 0)
        {
            cout << "Программа закрыта!\n";
            break;
        }
        else if (choice == 1)
        {
            printAll(staff);
        }
        else if (choice == 2)
        {
            string project;
            cout << "Введите название проекта: ";
            cin >> project;
            findByProject(staff, project);
        }
        else if (choice == 3)
        {
            string pos;
            cout << "Введите должность: ";
            cin >> pos;
            findByPosition(staff, pos);
        }
        else if (choice == 4)
        {
            string name;
            cout << "Введите имя: ";
            cin >> name;
            findByName(staff, name);
        }
        else if (choice == 5)
        {
            int mode;
            double amount;

            while (true)
            {
                cout << "1 - больше, 0 - меньше: ";
                if (cin >> mode && (mode == 0 || mode == 1))
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Введите 0 или 1!\n";
            }

            while (true)
            {
                cout << "Введите сумму: ";
                if (cin >> amount)
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Нужно число!\n";
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

            cout << "Имя (через _): ";
            cin >> name;
            cout << "Должность (Programmer / Tester / TeamLeader / ProjectManager): ";
            cin >> position;

            if (position == "Programmer")
            {
                cout << "Введите почасовую ставку: "; cin >> rate;
                cout << "Введите название проекта: "; cin >> project;
                //TODO Сделать проверку, что если проект уже существует, то берём бюджет из него
                cout << "Введите бюджет проекта: "; cin >> budget;
                //TODO После добавления нового проекта/бюджета заносить его в SeniorManager
                cout << "Введите премию: "; cin >> bonus;
                auto* p = new Programmer(id, name, rate, budget, project, bonus);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus));
                addOrUpdateProject(id, project, budget);
                cout << "Сотрудник успешно добавлен.\n";
            }
            else if (position == "Tester")
            {
                cout << "Введите почасовую ставку: "; cin >> rate;
                cout << "Введите название проекта: "; cin >> project;
                //TODO Сделать проверку, что если проект уже существует, то берём бюджет из него
                cout << "Введите бюджет проекта: "; cin >> budget;
                //TODO После добавления нового проекта/бюджета заносить его в SeniorManager
                cout << "Введите количество багов: "; cin >> extra;
                auto* p = new Tester(id, name, rate, budget, project, extra);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "Сотрудник успешно добавлен.\n";
            }
            else if (position == "TeamLeader")
            {
                cout << "Введите почасовую ставку: "; cin >> rate;
                cout << "Введите название проекта: "; cin >> project;
                //TODO Сделать проверку, что если проект уже существует, то берём бюджет из него
                cout << "Введите бюджет проекта: "; cin >> budget;
                //TODO После добавления нового проекта/бюджета заносить его в SeniorManager
                cout << "Введите премию: "; cin >> bonus;
                cout << "Введите размер команды: "; cin >> extra;
                auto* p = new TeamLeader(id, name, rate, budget, project, bonus, extra);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(rate) + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(bonus) + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "Сотрудник успешно добавлен.\n";
            }
            else if (position == "ProjectManager")
            {
                cout << "Введите название проекта: "; cin >> project;
                //TODO Сделать проверку, что если проект уже существует, то берём бюджет из него
                cout << "Введите бюджет проекта: "; cin >> budget;
                //TODO После добавления нового проекта/бюджета заносить его в SeniorManager
                cout << "Введите размер команды: "; cin >> extra;
                auto* p = new ProjectManager(id, name, budget, project, extra);
                p->setWorkTime(160); p->calc();
                staff.push_back(p);
                appendToStaffFile(to_string(id) + ' ' + name + ' ' + position + ' ' + to_string(budget) + ' ' + project + ' ' + to_string(extra));
                addOrUpdateProject(id, project, budget);
                cout << "Сотрудник успешно добавлен.\n";
            }
            else
            {
                cout << "Эта должность не поддерживается.\n";
            }
        }
        else if (choice == 7)
        {
            int id;
            string newProject;
            double newBudget;
            cout << "Введите ID сотрудника: "; cin >> id;
            cout << "Введите новый проект: "; cin >> newProject;
            //TODO Сделать проверку, что если проект уже существует, то берём бюджет из него
            cout << "Введите бюджет проекта: "; cin >> newBudget;
            //TODO После добавления нового проекта/бюджета заносить его в SeniorManager

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
                        cout << "Проект обновлён.\n";
                        found = true;
                        break;
                    }
                    else
                    {
                        cout << "У этого сотрудника нет проекта.\n";
                    }
                }
            }
            if (!found)
            {
                cout << "Сотрудник не найден.\n";
            }
        }
        else if (choice == 8)
        {
            int worktime;
            while (true)
            {
                cout << "Сколько времени в неделю работают сотрудники?: ";
                if (cin >> worktime)
                {
                    break;
                }
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                cout << "Нужно число!\n";
            }
            setWorkTimeForAll(staff, worktime);
            cout << "Время работы сотрудников изменено!\n";
        }
        else
        {
            cout << "Нет такого пункта!\n";
        }
    }

    for (Employee* emp : staff)
    {
        delete emp;
    }
    return 0;
}