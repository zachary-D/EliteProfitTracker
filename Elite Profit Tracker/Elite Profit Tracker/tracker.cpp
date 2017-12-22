#pragma once

#include <iostream>	//Remove these when we jump to cinder
#include <iomanip>	//Remove these when we jump to cinder
#include <string>
#include <vector>

using namespace std;

#include "zlib/zlib.h"

#include "tracker.h"

using zlib::var::shortTime;
using std::cin;

zlib::fileIO::fileWriter writer;
zlib::fileIO::fileReader reader;

const string saveLoc = "dataFile";

shortTime parseTime(string time)
{
	int hour = conv::toNum(time.substr(0, time.find(' ')));
	time = time.substr(time.find(' ') + 1);

	int minute = conv::toNum(time.substr(0, time.find(' ')));
	time = time.substr(time.find(' ') + 1);

	int second = conv::toNum(time.substr(0, time.find(' ')));

	return shortTime(second, minute, hour);
}

string formatCurrency(int value)
{
	string val = conv::toString(value);

	string ret;

	for(int i = val.size() - 1; i >= 0; i--)
	{
		ret = val[i] + ret;
		if((val.size() - 1 - i) % 3 == 2) ret = "," + ret;
	}

	if(ret[0] == ',') ret.erase(ret.begin());

	return ret;
}

void run::calculateDiff()
{
	totalTime = arrival - departure;
	while(totalTime < shortTime(0)) totalTime += shortTime(0, 0, 0, 1);
}

int run::getGrossIncome()
{
	int sum = 0;
	for(auto iter = income.begin(); iter != income.end(); iter++)
	{
		sum += *iter;
	}
	return sum;
}

int run::getTotalCost()
{
	return fuelCost + repairCost;
}

int run::getProfit()
{
	return getGrossIncome() - getTotalCost();
}

void run::writeData()
{
	//Write out 'income'
	writer.write("<vector(int)>");
	writer.write(income.size());
	for(auto iter = income.begin(); iter != income.end(); iter++)
	{
		writer.write(*iter);
	}
	writer.write("</vector(int)>");

	writer.write(departure.getTotalSeconds());
	writer.write(arrival.getTotalSeconds());
	writer.write(totalTime.getTotalSeconds());

	writer.write(fuelCost);
	writer.write(repairCost);
}

void run::loadData()
{
	reader.getLine();
	int size = conv::toNum(reader.getLine());
	for(int i = 0; i < size; i++)
	{
		income.push_back(conv::toNum(reader.getLine()));
	}
	reader.getLine();

	departure = var::shortTime(conv::toNum(reader.getLine()));
	arrival = var::shortTime(conv::toNum(reader.getLine()));
	totalTime = var::shortTime(conv::toNum(reader.getLine()));

	fuelCost = conv::toNum(reader.getLine());
	repairCost = conv::toNum(reader.getLine());
}

void run::displayFullStats()
{
	cout << "Income:" << endl;
	for(auto iter = income.begin(); iter != income.end(); iter++)
	{
		cout << formatCurrency(*iter) << endl;
	}
	cout << "Departure: " << departure.toStringHMS() << endl;
	cout << "Arrival: " << arrival.toStringHMS() << endl;
	cout << "Travel Time: " << totalTime.toStringHMS() << endl;
	cout << "FuelCost: " << fuelCost << endl;
	cout << "Repair Cost: " << repairCost << endl;
}

vector<run> runs;

namespace global
{
	bigNum getGrossIncome()
	{
		bigNum sum = 0;
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			sum += iter->getGrossIncome();
		}
		return sum;
	}

	bigNum getTotalCosts()
	{
		bigNum sum = 0;
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			sum += iter->getTotalCost();
		}
		return sum;
	}

	bigNum getProfit()
	{
		bigNum sum = 0;
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			sum += iter->getProfit();
		}
		return sum;
	}

	bigNum getTotalTravelTime()
	{
		bigNum sum = 0;
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			sum += iter->totalTime.getTotalSeconds();
		}
		return sum;
	}

	void writeData()		//Write data to the file
	{
		writer.open(saveLoc);

		writer.write("<vector(run)>");
		writer.write(runs.size());
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			iter->writeData();
		}
		writer.write("</vector(run)>");

		writer.close();
	}

	void readData()		//Read data from the file
	{
		reader.open(saveLoc);

		reader.getLine();
		int size = conv::toNum(reader.getLine());
		for(int i = 0; i < size; i++)
		{
			run newRun;
			newRun.loadData();
			runs.push_back(newRun);
		}
		reader.getLine();

		reader.close();
	}

	void displayStats()
	{
		cout << "Global stats:" << endl;
		cout << "Gross income: " << formatCurrency(global::getGrossIncome()) << endl;
		cout << "Total costs: " << formatCurrency(global::getTotalCosts()) << endl;
		cout << "Total profit: " << formatCurrency(global::getProfit()) << endl;
		cout << "Average run length: ";
		shortTime length = global::getTotalTravelTime() / runs.size();
		cout << length.getHours() << ":" << length.getMinutes() << ":" << length.getSeconds() << endl;
		cout << "Profit/hr: " << formatCurrency(bigNum(bigNum(global::getProfit()) / bigNum(global::getTotalTravelTime())) * bigNum(var::shortTime::secondsPerHour)) << endl;

		cout << endl << endl;
	}

	void displayFullStats()
	{
		for(auto iter = runs.begin(); iter != runs.end(); iter++)
		{
			iter->displayFullStats();
			cout << endl << endl;
		}

		displayStats();
	}
}