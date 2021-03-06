/*
Noah Fulton
Date Created: 10/20/2018

Description: This program reads a users input for a blood sugar test. The value is added up in a two dimensional array after first seeing if it is a min value or max value.
The value is segmented into sections of 1000000 or 10^6s. The D or Day call outputs the daily count as well as the total and daily mins and maxes. There is a catch for no readings thus far.
The W or Week call uses the array dayCount to find the total count as well as find the biggest delta change in reading count. The function also adds up all the dayCounts and outputs the result
in 10^6 notation as well as the week min and max.
The N or Next function clears the count, week min and max, and totals when day seven is past; clears day min and max and increments the day.
The system uses a while true loop to keep the system from closing.



*/

#include "pch.h"
#include <iostream>
#include <string>
using namespace std;







int main()
{
	//define the usable variables
	float BloodSugarTotals[10][7] = {0};
	int dayCount[7] = { 0 };
	int weekCount = 0;
	int day = 0;
	float dayMin = 1000000;
	float dayMax = 0;;
	float weekMin = 1000000;
	float weekMax = 0;
	string tempHold;
	//tell the user what they are using
	cout << "This is a Blood sugar weekly recorder. Enter any float number to add an entry" << endl;
	cout << " Type D or Day to show today's summary \n Type W or Weel to show a weekly summary\n Type N or Next to start a new day." << endl;
	do
	{
		cin >> tempHold;
		if (tempHold == "D" || tempHold == "Day")
		{
			//check if any readings occured today at all.
			if (dayCount[day] == 0)
			{
				cout << "No readings have occured today.\n\n\n";
			}
			else
			{
			
			//Output day summary
			bool atNum = false;

			//output the bloodsugar total of the day
			cout << "Total blood sugar read was: ";
			for (int i = 9; i >= 0; i--)
			{
				if (atNum || BloodSugarTotals[i][day] > 0)
				{
					atNum = true;

					//output the total of the day in 10^6 notation
					cout << "(10^"<< 6*i << ")*" << BloodSugarTotals[i][day]  << " + ";


				}
			}
			//output the values of day summary.
			cout << "\nThe times read today was: " << dayCount[day] << endl;
			cout << "The max of the day was: " << dayMax << endl;
			cout << "The min of the day was: " << dayMin << "\n\n\n\n";
		}
		}
		else if (tempHold == "W"||tempHold == "Week")
		{
			cout << "The week total is: ";
			//output the summary of the week
			float weekTotal[11] = { 0 };
			for (int i = 0; i <= 10; i++)
			{
				//get week total in sections of 10^6
				for (int j = 0; j < 7; j++)
				{
					weekTotal[i] += BloodSugarTotals[i][j];
				}
				while (weekTotal[i] > 1000000)
				{
					weekTotal[i + 1]++;
					weekTotal[i] -= 1000000;
				}



			}
			//display week total in terms of 10^6
			bool atnum = false;
			for (int i = 10; i >= 0; i--)
			{
				if (atnum || weekTotal[i] > 0)
				{
					atnum = true;
					cout << "(10^" << 6 * i << ")*" << weekTotal[i] << " + ";
				}
			}

			cout << "\nThe Week Max was: " << weekMax << endl;
			cout << "The Week Min was: " << weekMin << endl;
			cout << "The Week Count was: ";
			int totalCount = 0;
			int deltaDay = 0;
			int delta = 0;
			//get the week count and delta day
			for (int i = 0; i < 7; i++)
			{
				//add to the week count
				totalCount += dayCount[i];
				//if the day has passed and isnt day 1
				if (i != 0)
				{
					//if this is the biggest delta day so far save it
					if (delta < abs(dayCount[i] - dayCount[i - 1])&& i <= day)
					{
						deltaDay = i+1;
						delta = abs(dayCount[i] - dayCount[i - 1]);
					}
				}

			}
			//output the results
			cout << totalCount << endl;
			cout << "The Day with biggest change in delta count was: " << deltaDay << "\n\n\n";


			
		}
		else if (tempHold == "N" || tempHold == "Next")
		{
			//update the day upon request
			if (day == 6)
			{
				day = 0;
				weekMin = 1000000;
				weekMax = 0;


				//reset the week's data
				for (int i = 0; i < 7; i++)
				{
					for (int j = 0; j < 10; j++)
					{
						BloodSugarTotals[j][i] = 0;
					}
					dayCount[i] = 0;
				}


			}
			else
			{
				day++;
			}

			//reset data on any day passed
			dayMax = 0;
			dayMin = 1000000;

		}
		else
		{
			//turn the string to a float
			float temp = stof(tempHold);
			//if the float is positive insert it
			if (temp > 0)
			{
				//insert the new data and use the array to create a massive float
				BloodSugarTotals[0][day] += temp;
				int tempPos = 0;
				while(BloodSugarTotals[tempPos][day] > 1000000)
				{
					BloodSugarTotals[tempPos][day] -= 1000000;
					tempPos++;
					BloodSugarTotals[tempPos][day]++;
				}
				dayCount[day]++;

				//check if the value is less than the day's min
				if (temp < dayMin)
				{
					dayMin = temp;
					//check if the value is lower than the week's min
					if (temp < weekMin)
					{
						weekMin = temp;
					}
				}
				//check if the value is the day's max
				if (temp > dayMax)
				{
					dayMax = temp;
					//check if the value is the week's max
					if (temp > weekMax)
					{
						weekMax = temp;
					}
				}



			}
		}
	} while (true);


	


	return 0;
}

