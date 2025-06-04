#include "ProjectManager.h"
#include <iostream>
using namespace std;

ProjectManager::ProjectManager(int id, const string& name, double budget, const string& project, int teamSize) : Employee(id, name), budget(budget), project(project), teamSize(teamSize) {}

void ProjectManager::setWorkTime(int time)
{
    worktime = time;
}

double ProjectManager::calcBudgetPart()
{
    return budget * 0.1;
}

double ProjectManager::calcProAdditions()
{
    return 0;
}

double ProjectManager::calcHeadingBonus()
{
    return teamSize * 1500;
}

void ProjectManager::calc()
{
    payment = calcBudgetPart() + calcHeadingBonus();
}

void ProjectManager::printInfo() const
{
    cout << left << setw(3) << id
        << setw(27) << name
        << setw(15) << getPosition()
        << setw(12) << getProject()
        << payment << '\n';
}

string ProjectManager::getProject() const
{
    return project;
}

double ProjectManager::getBudget() const
{
    return budget;
}

string ProjectManager::getPosition() const
{
    return "ProjectManager";
}

void ProjectManager::setProject(const string& project)
{
    this->project = project;
}

void ProjectManager::setBudget(const double budget)
{
    this->budget = budget;
}

void ProjectManager::syncBudgetsFromFile() {}