//404410053 資工二 張碩恩

#include <iostream>
using namespace std;

bool inputYrMn(int& year, int& month);
void get1stDayOfMonth(int year, int month, int& firstDay, int& numberOfDay);
void showCalendar();

int main(){
	int year, month, firstDay, numberOfDay;
	while(1){
		if(inputYrMn(year, month)){
			get1stDayOfMonth(year, month, firstDay, numberOfDay);
//			showCalendar();
		}
		else
			cout<<"Wrong input, please try again!\n";
	}
	return 0;
}

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
