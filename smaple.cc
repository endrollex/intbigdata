#include <iostream>
#include <string>
#include "intbigdata.h"//use library
using namespace std;
int main()
{
	//three init methods
	IntBigdata test1(2);
	IntBigdata test2("-44867916611904333479495141036159177872720902");
	IntBigdata test3 = "2.00e400";
 
	//operator like int
	test2 = test1 * test3;
	//power functions
	test1 = test1.pow(1024);
	test2 = test3.sqrt();
	
	//output I/O stream
	cout << "square root of 2e400 = " << test2 << "\n" << endl;
	cout << "2^1024 = "<< test1 << "\n" << endl;
	//scientific notation output
	cout << "2^1024 scientific notation: " << test1.scientific() << endl;
	
	//implicit conversion form IntBigdata to int
	//if exceeds max int, the value will be modulo
	test2 = test3 - 54321;
	int i = test2;
	cout << "i value is: " << i << endl;
	
	return 0;
}