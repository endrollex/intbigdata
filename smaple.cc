#include <iostream>
#include <string>
#include "intbigf.h"//use library
using namespace std;
int main()
{
	//some init methods
	//big integer
	intbigdata ibd1 = "27387497791304645971859572233658452667";
	ibd1 = 65536-789;
	//big float
	intbigf ib1(2);
	intbigf ib2("-44867916611904333479495141036159177872720902");
	intbigf ib3 = "6.72e9";
 
	//operator like int
	ib2 = ib1*ib2;
	//power functions
	ib1 = ib1.pow(1024);
	ib2 = ib3.root(3);
 
	//set precision for float
	intbigd_fu::precision(128);
	//output
	cout << "square root of 2: " << intbigf(2).root(2) << "\n" << endl;
	//scientific notation
	cout << "2^1024 (scientific notation): " << ib1.scientific() << "\n" << endl;
	//float pow, set precision range and method
	intbigd_fu::precision_affect_div(64);
	intbigd_fu::precision_affect_all(32);
	cout << "29^2.34: " << intbigf(29).pow(2.34) <<  "\n"  << endl;
	//big number
	cout << "1234^1234: " << intbigdata(1234).pow(1234) << endl;
	
	//complete functions please refer to source files.
 	return 0;
}