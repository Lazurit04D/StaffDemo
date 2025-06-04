#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class Personal : public Employee, public WorkBaseTime
{
protected:
    double rate;
public:
    Personal(int id, const string& name, double rate);

    void setWorkTime(int time) override;
    double calcBase(double rate, int hours) override;
    double calcBonus() override;

    void calc() override;
    void printInfo() const override;
    string getPosition() const override;
};