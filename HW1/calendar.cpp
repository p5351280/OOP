//404410053 資工二 張碩恩

#include <iostream>
using namespace std;

bool inputYrMn(int& year, int& month);
void get1stDayOfMonth(int year, int month, int& firstDay, int& numberOfDay);
void showCalendar(int year, int month, int firstDay, int numberOfDay);

int main(){
	int year, month, firstDay, numberOfDay;
	while(1){
		if(inputYrMn(year, month)){
			get1stDayOfMonth(year, month, firstDay, numberOfDay);
			showCalendar(year, month, firstDay, numberOfDay);
		}
		else
			cout<<"Wrong input, please try again!\n";
	}
	return 0;
}

/*
Precondition:
	year and month are both call by reference

Postcodition:
	input year and month, and return a bool value which tell if the input is legal or illegal
*/
bool inputYrMn(int& year, int& month){
	cout<<"Please input year (1901-2099) :";
	cin>>year;
	cout<<"Please input month (1-12) :";
	cin>>month;
	if(year>1900 && year<2100 && month>0 && month<13)
		return true;
	else
		return false;
}

/*
Precondition:
	year must be represented in Gregorian calendar, and also must between 1901 and 2099
	month must be represented in number, and also must between 1 and 12 (1 means Jan, 2 means Feb ... etc)

Postcondition:
	firstDay is call by reference, it will change into the weekday of the first day in the month (0 means Sum, 1 means Mon ... etc)
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

	/* using Zeller's congruence to caculate the first day by 404410053, Ref:Wiki */
    if(month<3){
        month += 12;
        year--;
    }
    firstDay = (-2*(year/100) + (year/100)/4 + year%100 + (year%100)/4 + 26*(month+1)/10) % 7;
    firstDay = (firstDay<0) ? firstDay+7 : firstDay;
}

/*
Precondition:
	year must be represented in Gregorian calendar, and also must between 1901 and 2099
	month must be represented in number, and also must between 1 and 12 (1 means Jan, 2 means Feb ... etc)
	firstDay tell the function which weekday is the first day in the month (0 means Sum, 1 means Mon ... etc)
	numberOfDay tell the function how many days are there in the month

Postcondition:
	print out the calendar
*/
void showCalendar(int year, int month, int firstDay, int numberOfDay){
	const char MONTH[13][5] = {"", "Jan", "Feb", "Mar", "Apr", "May", "Jan", 
								"Jul", "Aug", "Sep", "Oct", "Nov", "Dec"};
	cout<<"\n----------------------------------------------------\n"
		<<"\t\t"<<year<<"\t"<<MONTH[month]
		<<"\n----------------------------------------------------\n"
		<<"Sun\tMon\tTue\tWed\tThu\tFri\tSat\n";
	for(int i=0; i<firstDay; i++)
		cout<<" \t";
	for(int i=1; i<=numberOfDay; i++){
		cout<<i<<"\t";
		if(i%7 == (7-firstDay)%7)
			cout<<"\n";
	}
	cout<<"\n----------------------------------------------------\n";
}
