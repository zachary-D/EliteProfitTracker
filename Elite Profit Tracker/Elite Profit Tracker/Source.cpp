#include <iostream>
#include <iomanip>
#include <string>
#include <vector>

using namespace std;

#include "zlib/zlib.h"

using zlib::var::shortTime;

shortTime parseTime(string time)
{
	int hour = conv::toNum(time.substr(0, time.find(' ')));
	time = time.substr(time.find(' ') + 1);

	int minute = conv::toNum(time.substr(0, time.find(' ')));
	time = time.substr(time.find(' ') + 1);

	int second = conv::toNum(time.substr(0, time.find(' ')));

	return shortTime(second, minute, hour);
}

struct run
{
	vector<string> profit;
	shortTime departure;
	shortTime arrival;

	shortTime totalTime;

	void calculateDiff()
	{
		totalTime = arrival - departure;
	}
};

int main()
{
	vector<run> runs;


	while(true)
	{
		run newRun;

		//Get the departure time
		cout << "Departure:";
		string departure;
		getline(cin, departure);

		newRun.departure = parseTime(departure);

		//Continually add prices to the payments vector (confirming each time) until nothing is entered
		while(true)
		{

		}
	}


	cin.get();



	return 0;
}