#pragma once

#include "zlib/zlib.h"

using zlib::var::shortTime;

shortTime parseTime(string time);
string formatCurrency(int value);

struct run
{
	vector<int> income;
	shortTime departure;
	shortTime arrival;

	shortTime totalTime;

	int fuelCost = 0;
	int repairCost = 0;

	void calculateDiff();	//Calculates the travel time and stores it in 'totalTime'

	int getGrossIncome();	//Returns the sum of 'income'

	int getTotalCost();		//Returns fuelCost + repairCost

	int getProfit();		//Returns getGrossIncome() - getTotalCost()

	void writeData();		//Writes the information from this run to the data file.  Only to be called by global::writeData()

	void loadData();		//Loads information from the datafile and stores it in this element.  Only to be called by global::readData()

	void run::displayFullStats();	//Writes the statistsc
};

extern vector<run> runs;

typedef long long int bigNum;

namespace global
{
	bigNum getGrossIncome();		//Returns the gross income for all runs
	bigNum getTotalCosts();			//Returns the total costs for all runs
	bigNum getProfit();				//Returns the total profits (grossIncome - total costs)
	bigNum getTotalTravelTime();	//Returns the total trime traveled for all runs

	void writeData();				//Writes the data from all runs to the datafile
	void readData();				//Loads run data from the datafile
	void displayStats();			//Displays the statistics for all runs (total profit, profit/hour, etc)
	void displayFullStats();		//Displays all information for all runs, individually
}