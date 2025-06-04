#include "TeamLeader.h"

TeamLeader::TeamLeader(int id, const string& name, double rate, double budget, const string& project, double bonus, int teamSize) : Programmer(id, name, rate, budget, project, bonus), teamSize(teamSize) {}

double TeamLeader::calcHeadingBonus()
{
    return teamSize * 1000;
}

void TeamLeader::calc()
{
    payment = calcBase(rate, worktime) + calcBudgetPart() + calcHeadingBonus();
}

string TeamLeader::getPosition() const
{
    return "TeamLeader";
}

void TeamLeader::setProject(const string& project)
{
    this->project = project;
}