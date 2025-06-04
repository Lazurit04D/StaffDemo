#pragma once
#include "Employee.h"
#include "Interfaces.h"
using namespace std;

class ProjectManager : public Employee, public ProjectBudget, public Heading
{
    double budget;
    string project;
    int teamSize;
public:
    ProjectManager(int id, const string& name, double budget, const string& project, int teamSize);

    void setWorkTime(int time) override;

    double calcBudgetPart() override;
    double calcProAdditions() override;
    double calcHeadingBonus() override;

    void calc() override;
    void printInfo() const override;

    string getProject() const override;
    double getBudget() const override;
    string getPosition() const override;

    void setProject(const string& project) override;
    void setBudget(const double budget) override;

    void syncBudgetsFromFile() override;
};