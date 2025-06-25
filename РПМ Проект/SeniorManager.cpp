#include "SeniorManager.h"
#include <iostream>
#include <fstream>
#include <sstream>
using namespace std;

string SeniorManager::fileName = "staff.txt";

SeniorManager::SeniorManager(int id, const string& name, const vector<double>& budgets, int peopleCount) : Employee(id, name), budgets(budgets), peopleCount(peopleCount) {}

void SeniorManager::setWorkTime(int time)
{
    worktime = time;
}

double SeniorManager::calcBudgetPart()
{
    double sum = 0;
    for (double b : budgets)
    {
        sum += b * 0.1;
    }
    return sum;
}

double SeniorManager::calcProAdditions()
{
    return 0;
}

double SeniorManager::calcHeadingBonus()
{
    return peopleCount * 2000;
}

void SeniorManager::calc()
{
    payment = calcBudgetPart() + calcHeadingBonus();
}

void SeniorManager::printInfo() const
{
    cout << left << setw(3) << id
        << setw(27) << name
        << setw(15) << getPosition()
        << setw(12) << "Все проекты"
        << payment << '\n';
}

double SeniorManager::getBudget() const
{
    return 0.0;
}

vector<double> SeniorManager::getBudgets() const
{
    return budgets;
}

string SeniorManager::getPosition() const
{
    return "SeniorManager";
}

void SeniorManager::setProject(const string& project) {}

void SeniorManager::setBudget(const double budget) {}

void SeniorManager::setFileName(const string& name)
{
    fileName = name;
}

void SeniorManager::syncBudgetsFromFile()
{
    ifstream in(fileName);
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

        if (!tokens.empty() && tokens[2] == "SeniorManager" && stoi(tokens[0]) == this->id)
        {
            int count = stoi(tokens[3]);
            budgets.clear();

            for (int i = 0; i < count; ++i)
            {
                budgets.push_back(stod(tokens[4 + i]));
            }
            break;
        }
    }

    in.close();
}