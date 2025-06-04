#include "Personal.h"
#include <iostream>
using namespace std;

Personal::Personal(int id, const string& name, double rate) : Employee(id, name), rate(rate) {}

void Personal::setWorkTime(int time)
{
    worktime = time;
}

double Personal::calcBase(double r, int h)
{
    return r * h;
}

double Personal::calcBonus()
{
    return 0.0;
}

void Personal::calc()
{
    payment = calcBase(rate, worktime) + calcBonus();
}

void Personal::printInfo() const
{
    cout << left << setw(3) << id
        << setw(27) << name
        << setw(15) << getPosition()
        << setw(12) << (getProject() != "" ? getProject() : "N/A")
        << payment << '\n';
}

string Personal::getPosition() const
{
    return "Personal";
}