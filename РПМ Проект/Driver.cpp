#include "Driver.h"

Driver::Driver(int id, const string& name, double rate) : Personal(id, name, rate), nightHours(0) {}

void Driver::setNightHours(int hours)
{
    nightHours = hours;
}

double Driver::calcBonus()
{
    return rate * nightHours;
}

double Driver::getBudget() const
{
    return 0.0;
}

string Driver::getPosition() const
{
    return "Driver";
}

void Driver::setProject(const string& project) {}
void Driver::setBudget(const double budget) {}