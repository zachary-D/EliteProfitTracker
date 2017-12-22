#pragma once

#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#include "zlib/zlib.h"

#include "tracker.h"

int main()
{
	try 
	{
		global::readData();
		
	}
	catch(...)
	{
		//We should add some checks here to see if it was anything beyond 'the file wasn't there' but.... yeah
	}

	while(true)
	{
		if(runs.size() > 0)
		{
			//global::displayFullStats();
			global::displayStats();
		}

		run newRun;

		//Get the departure time
		cout << "Departure:";
		string departure;
		getline(cin, departure);

		newRun.departure = parseTime(departure);

		cout << "Departure:";
		cout << newRun.departure.getHours() << ":" << newRun.departure.getMinutes() << ":" << newRun.departure.getSeconds() << endl;
		cout << endl;

		cout << "Estimated time of arrival:";
		if(runs.size() > 0)
		{
			shortTime ETA = newRun.departure + shortTime(global::getTotalTravelTime() / runs.size());
			cout << ETA.getHours() << ":" << ETA.getMinutes() << ":" << ETA.getSeconds() << endl;
		}
		else cout << "Unavailable" << endl;
		cout << endl;

		cout << "Please enter payments:" << endl;

		//Continually add prices to the payments vector (confirming each time) until nothing is entered
		string inp;
		while(true)
		{
			getline(cin, inp);
			if(conv::isNum(inp))
			{
				int income = conv::toNum(inp);

				cout << formatCurrency(income) << endl;
				cout << "Is this correct? (type nothing for yes)" << endl;
				getline(cin, inp);
				if(inp == "")
				{
					newRun.income.push_back(income);
					inp = "~";
				}
			}

			if(inp == "") break;
		}

		cout << "Estimated time of arrival:";
		if(runs.size() > 0)
		{
			shortTime ETA = newRun.departure + shortTime(global::getTotalTravelTime() / runs.size());
			cout << ETA.getHours() << ":" << ETA.getMinutes() << ":" << ETA.getSeconds() << endl;
		}
		else cout << "Unavailable" << endl;
		cout << endl;
		
		cout << "Arrival:";
		string arrival;
		getline(cin, arrival);

		newRun.arrival = parseTime(arrival);

		cout << "Arrival:";
		cout << newRun.arrival.getHours() << ":" << newRun.arrival.getMinutes() << ":" << newRun.arrival.getSeconds() << endl;
		cout << endl;

		newRun.fuelCost = input::getNumInput("Fuel costs");

		newRun.repairCost = input::getNumInput("Repair costs");

		cout << "Run statistics:" << endl;
		newRun.calculateDiff();
		cout << endl;
		cout << "Gross income: " << formatCurrency(newRun.getGrossIncome()) << endl;
		cout << "Total costs: " << formatCurrency(newRun.getTotalCost()) << endl;
		cout << "Profit: " << formatCurrency(newRun.getProfit()) << endl;

		runs.push_back(newRun);

		cout << endl << endl;

		global::writeData();
	}


	cin.get();



	return 0;
}