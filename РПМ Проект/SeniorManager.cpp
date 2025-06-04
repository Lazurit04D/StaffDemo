#include "SeniorManager.h"
#include <iostream>
using namespace std;

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

string SeniorManager::getPosition() const
{
    return "SeniorManager";
}