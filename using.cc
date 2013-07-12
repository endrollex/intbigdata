#include <iostream>
#include <string>
#include "intbigf.h"
using namespace std;
int main()
{
	intbigf t2("0.00000000000005");
	intbigf t1("1.00000000000005");
	
	//intbigf t2("12.345");
	//intbigf t1("-0.0045");	
	
	
	cout << t1 << endl;
	cout << t2 << endl;
	cout << endl;
	
	
	intbigf t3(t1.add(t2));
	
	
	
	cout << t3 << endl;
	
	
	



	return 0;
}