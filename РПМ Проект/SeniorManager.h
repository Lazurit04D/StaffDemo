#pragma once
#include <vector>
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class SeniorManager : public Employee, public ProjectBudget, public Heading
{
    vector<double> budgets;
    int peopleCount;
public:
    SeniorManager(int id, const string& name, const vector<double>& budgets, int peopleCount);

    void setWorkTime(int time) override;

    double calcBudgetPart() override;
    double calcProAdditions() override;
    double calcHeadingBonus() override;

    void calc() override;
    void printInfo() const override;

    string getPosition() const override;
};