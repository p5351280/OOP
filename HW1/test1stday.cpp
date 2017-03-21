//404410053 資工二 張碩恩

#include <iostream>
using namespace std;

void get1stDayOfMonth(int year, int month, int& firstDay, int& numberOfDay);

int main(){
	int year, month, firstDay, numberOfDay;
	while(1){
		cin>>year>>month;
		get1stDayOfMonth(year, month, firstDay, numberOfDay);
		const char* DAY[8] = {"Sun", "Mon", "Tue", "Wed", "Thu", "Fri", "Sat"};
		cout<<"year : "<<year
			<<"\nmonth : "<<month
			<<"\nfirstDay : "<<DAY[firstDay]
			<<"\nnumberOfDay : "<<numberOfDay<<endl;
	}
	return 0;
}

/*
 Precondition:
	year must be represented in Gregorian calendar, and also must between 1901 and 2099
	month must be represented in number, and also must between 1 and 12 (1 means Jan, 2 means Feb ... etc)
 
 Postcondition:
	firstDay is call by reference, it will change into the weekday of the first day in the month (0 means Sun, 1 means Mon ... etc)
	numberOfDay is call by reference, it is represent how many days are there in the month
 */
void get1stDayOfMonth(int year, int month, int& firstDay, int& numberOfDay){
	switch(month){
		case 1: case 3: case 5: case 7: case 8: case 10: case 12:
			numberOfDay = 31;
			break;
		case 4: case 6: case 9: case 11:
			numberOfDay = 30;
			break;
		case 2:
			if((year%4==0 && year%100) || year%400==0)
				numberOfDay = 29;
			else
				numberOfDay = 28;
			break;
	}
	if(month<3){
		month += 12;
		year--;
	}
	firstDay = (-2*(year/100) + (year/100)/4 + year%100 + (year%100)/4 + 26*(month+1)/10) % 7;
	firstDay = (firstDay<0) ? firstDay+7 : firstDay;
}
