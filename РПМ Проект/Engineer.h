#pragma once
#include "Personal.h"
#include "Interfaces.h"
using namespace std;

class Engineer : public Personal, public ProjectBudget
{
protected:
    double budget;
    string project;
public:
    Engineer(int id, const string& name, double rate, double budget, const string& project);

    double calcBudgetPart() override;

    void calc() override;
    string getProject() const override;
    double getBudget() const override;
    string getPosition() const override;

    void setProject(const string& project) override;
    void setBudget(const double budget) override;

    void syncBudgetsFromFile() override;
};