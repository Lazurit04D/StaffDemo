#include "Programmer.h"

Programmer::Programmer(int id, const string& name, double rate, double budget, const string& project, double bonus) : Engineer(id, name, rate, budget, project), bonus(bonus) {}

double Programmer::calcProAdditions()
{
    return bonus;
}

string Programmer::getPosition() const
{
    return "Programmer";
}

void Programmer::setProject(const string& project)
{
    this->project = project;
}

void Programmer::setBudget(const double budget)
{
    this->budget = budget;
}