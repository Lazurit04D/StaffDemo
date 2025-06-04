#include "Cleaner.h"

Cleaner::Cleaner(int id, const string& name, double rate) : Personal(id, name, rate) {}

string Cleaner::getPosition() const
{
    return "Cleaner";
}

void Cleaner::setProject(const string& project) {}

void Cleaner::setBudget(const double budget) {}