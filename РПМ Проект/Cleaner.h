#pragma once
#include "Personal.h"
using namespace std;

class Cleaner : public Personal
{
public:
    Cleaner(int id, const string& name, double rate);
    string getPosition() const override;
};