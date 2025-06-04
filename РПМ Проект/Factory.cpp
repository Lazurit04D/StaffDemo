#include "Driver.h"
#include "Tester.h"
#include "Factory.h"
#include "Cleaner.h"
#include "Engineer.h"
#include "Programmer.h"
#include "TeamLeader.h"
#include "SeniorManager.h"
#include "ProjectManager.h"

vector<Employee*> StaffFactory::makeStaff(const string& filename)
{
    vector<Employee*> staff;
    ifstream file(filename);
    string line;

    while (getline(file, line))
    {
        istringstream iss(line);

        if (line.empty())
        {
            continue;
        }

        int id;
        string name;
        string position;
        double rate = 0;
        string project = "";
        double budget = 0;
        double bonus = 0;
        int extra = 0;

        iss >> id >> name >> position;

        if (position == "Cleaner")
        {
            iss >> rate;
            staff.push_back(new Cleaner(id, name, rate));
        }
        else if (position == "Driver")
        {
            iss >> rate >> bonus;
            Driver* d = new Driver(id, name, rate);
            d->setNightHours(bonus);
            staff.push_back(d);
        }
        else if (position == "Programmer")
        {
            iss >> rate >> budget >> project >> bonus;
            staff.push_back(new Programmer(id, name, rate, budget, project, bonus));
        }
        else if (position == "Tester")
        {
            iss >> rate >> budget >> project >> extra;
            staff.push_back(new Tester(id, name, rate, budget, project, extra));
        }
        else if (position == "TeamLeader")
        {
            iss >> rate >> budget >> project >> extra;
            staff.push_back(new TeamLeader(id, name, rate, budget, project, 0, extra));
        }
        else if (position == "ProjectManager")
        {
            iss >> budget >> project >> extra;
            staff.push_back(new ProjectManager(id, name, budget, project, extra));
        }
        else if (position == "SeniorManager")
        {
            int count;
            iss >> count;
            vector<double> budgets;
            for (int i = 0; i < count; i++)
            {
                double b;
                iss >> b;
                budgets.push_back(b);
            }
            iss >> extra;
            staff.push_back(new SeniorManager(id, name, budgets, extra));
        }
    }

    return staff;
}