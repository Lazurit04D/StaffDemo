#pragma once

class WorkBaseTime
{
public:
    virtual double calcBase(double rate, int hours) = 0;
    virtual double calcBonus() = 0;
    virtual ~WorkBaseTime() {}
};

class ProjectBudget
{
public:
    virtual double calcBudgetPart() = 0;
    virtual double calcProAdditions() = 0;
    virtual ~ProjectBudget() {}
};

class Heading
{
public:
    virtual double calcHeadingBonus() = 0;
    virtual ~Heading() {}
};