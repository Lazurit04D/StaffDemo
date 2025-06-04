#pragma once
#include <vector>
#include <string>
#include <fstream>
#include <sstream>
#include "Employee.h"
using namespace std;

class StaffFactory
{
public:
    static vector<Employee*> makeStaff(const string& filename);
};