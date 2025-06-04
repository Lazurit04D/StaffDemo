#include "Engineer.h"

Engineer::Engineer(int id, const string& name, double rate, double budget, const string& project) : Personal(id, name, rate), budget(budget), project(project) {}

double Engineer::calcBudgetPart()
{
    return budget * 0.05;
}

void Engineer::calc()
{
    payment = calcBase(rate, worktime) + calcBudgetPart() + calcProAdditions();
}

string Engineer::getProject() const
{
    return project;
}

double Engineer::getBudget() const
{
    return budget;
}

string Engineer::getPosition() const
{
    return "Engineer";
}

void Engineer::setProject(const string& project)
{
    this->project = project;
}

void Engineer::setBudget(const double budget)
{
    this->budget = budget;
}

void Engineer::syncBudgetsFromFile() {}