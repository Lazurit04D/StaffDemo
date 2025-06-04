#pragma once
#include "Personal.h"
using namespace std;

class Driver : public Personal
{
    int nightHours;
public:
    Driver(int id, const string& name, double rate);

    void setNightHours(int hours);
    double calcBonus() override;
    string getPosition() const override;
};