#pragma once
#include "Engineer.h"
using namespace std;

class Tester : public Engineer
{
    int bugsFound;
public:
    Tester(int id, const string& name, double rate, double budget, const string& project, int bugsFound);

    double calcProAdditions() override;
    string getPosition() const override;

    void setProject(const string& project) override;
};