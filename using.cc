#include <iostream>
#include <string>
#include <iomanip>
#include "intbigf.h"
using namespace std;
int main()
{
	//intbigf t1("50"), t2("150");
	//intbigf t2("12.345"), t1("-0.0045");
	//intbigf t1("46146"), t2("0.893");
	intbigf t1(10.9432), t2(12345);
	
	
	intbigd_fu::sig_digs = 100;
	
	
	cout << t1 << endl;
	cout << t2 << endl;
	cout << endl;
	
	
	intbigf t3(t1.div(t2));
	
	cout << t3 << " (result)" << endl;
	cout << endl;


	return 0;
}