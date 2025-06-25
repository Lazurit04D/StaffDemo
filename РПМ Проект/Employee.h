#pragma once
#include <string>
#include <iomanip>
#include <vector>
using namespace std;

class Employee
{
protected:
    int id;
    string name;
    int worktime;
    double payment;
public:
    Employee(int id, const string& name);

    virtual void setWorkTime(int time) = 0;
    virtual void calc() = 0;
    virtual void printInfo() const = 0;

    virtual string getProject() const;
    virtual double getBudget() const = 0;
    virtual vector<double> getBudgets() const;
    virtual string getPosition() const = 0;

    virtual int getWorkTime() const;
    virtual double getPayment() const;
    virtual string getName() const;
    virtual int getId() const;

    virtual void setProject(const string& project) = 0;
    virtual void setBudget(const double budget) = 0;

    virtual void syncBudgetsFromFile() = 0;

    virtual ~Employee() {}
};