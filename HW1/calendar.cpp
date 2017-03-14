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
