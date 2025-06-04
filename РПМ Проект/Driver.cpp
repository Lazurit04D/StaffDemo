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

string Driver::getPosition() const
{
    return "Driver";
}