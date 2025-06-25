#pragma once
#include <vector>
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class SeniorManager : public Employee, public ProjectBudget, public Heading
{
    vector<double> budgets;
    static string fileName;
    int peopleCount;
public:
    SeniorManager(int id, const string& name, const vector<double>& budgets, int peopleCount);

    void setWorkTime(int time) override;

    double calcBudgetPart() override;
    double calcProAdditions() override;
    double calcHeadingBonus() override;

    void calc() override;
    void printInfo() const override;

    double getBudget() const override;
    vector<double> getBudgets() const override;
    string getPosition() const override;

    void setProject(const string& project) override;
    void setBudget(const double budget) override;
    static void setFileName(const string& name);

    void syncBudgetsFromFile() override;
};