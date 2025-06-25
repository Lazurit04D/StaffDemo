#include "Employee.h"

Employee::Employee(int id, const string& name) : id(id), name(name), worktime(0), payment(0.0) {}

string Employee::getProject() const
{
    return "";
}

vector<double> Employee::getBudgets() const
{
    return {};
}

int Employee::getWorkTime() const
{
    return worktime;
}

double Employee::getPayment() const
{
    return payment;
}

string Employee::getName() const
{
    return name;
}

int Employee::getId() const
{
    return id;
}