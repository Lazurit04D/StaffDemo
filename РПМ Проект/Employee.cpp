#include "Employee.h"

Employee::Employee(int id, const string& name) : id(id), name(name), worktime(0), payment(0.0) {}

string Employee::getProject() const
{
    return "";
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