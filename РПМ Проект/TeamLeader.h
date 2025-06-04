#pragma once
#include "Programmer.h"
#include "Interfaces.h"
using namespace std;

class TeamLeader : public Programmer, public Heading
{
    int teamSize;
public:
    TeamLeader(int id, const string& name, double rate, double budget, const string& project, double bonus, int teamSize);

    double calcHeadingBonus() override;
    void calc() override;
    string getPosition() const override;

    void setProject(const string& project) override;
};