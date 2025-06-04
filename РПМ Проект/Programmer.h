#pragma once
#include "Engineer.h"
using namespace std;

class Programmer : public Engineer
{
    double bonus;
public:
    Programmer(int id, const string& name, double rate, double budget, const string& project, double bonus);

    double calcProAdditions() override;
    string getPosition() const override;

    void setProject(const string& project) override;
};