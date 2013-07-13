#include <iostream>
#include <string>
#include <iomanip>
#include "intbigf.h"
using namespace std;
int main()
{
	//intbigf t2("0.00000000000005"), t1("1.00000000000005");
	//intbigf t1("12.345"), t2("-0.0045");
	intbigf t1("46146"), t2("0.893");
	//intbigf t1("10000"), t2("50");
	
	intbigd_fu::sig_digs = 100;
	
	
	cout << t1 << endl;
	cout << t2 << endl;
	cout << endl;
	
	
	intbigf t3(t1.div(t2));
	
	
	
	cout << t3 << " (result)" << endl;
	



	return 0;
}