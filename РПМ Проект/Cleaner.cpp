#include "Cleaner.h"

Cleaner::Cleaner(int id, const string& name, double rate) : Personal(id, name, rate) {}

string Cleaner::getPosition() const
{
    return "Cleaner";
}