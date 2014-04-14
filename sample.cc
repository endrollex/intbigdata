#include <iostream>
#include <string>
#include "floatbigdata.h"//include library
using namespace std;
//using class
using bigdata::intbigdata;
using bigdata::floatbigdata;
int main()
{
	//some init methods
	//big integer
	intbigdata ib1 = "27387497791304645971859572233658452667";
	ib1 = 65536-789;
	//big float
	floatbigdata fb1(2);
	floatbigdata fb2("-44867916611904333479495141036159177872720902");
	floatbigdata fb3 = "6.72e9";
	//operator like int
	fb2 = fb1*fb2;
	//power functions
	fb1 = fb1.pow(1024);
	fb2 = fb3.root(3);
	//set precision for float
	bigdata::precision(128);
	//output
	cout << "square root of 2: " << floatbigdata(2).root(2) << "\n" << endl;
	//scientific notation
	cout << "2^1024 (scientific notation): " << fb1.scientific() << "\n" << endl;
	//float pow, set precision range and method
	bigdata::precision_affect_div(64);
	bigdata::precision_affect_all(32);
	cout << "29^2.3: " << floatbigdata(29).pow(2.3) <<  "\n"  << endl;
	//big number
	cout << "123^123: " << intbigdata(123).pow(123) << endl;
	//complete functions please refer to source files.
 	return 0;
}