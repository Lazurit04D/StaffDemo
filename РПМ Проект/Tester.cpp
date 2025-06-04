#include "Tester.h"

Tester::Tester(int id, const string& name, double rate, double budget, const string& project, int bugsFound) : Engineer(id, name, rate, budget, project), bugsFound(bugsFound) {}

double Tester::calcProAdditions()
{
    return bugsFound * 100;
}

string Tester::getPosition() const
{
    return "Tester";
}

void Tester::setProject(const string& project)
{
    this->project = project;
}