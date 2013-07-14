#include <iostream>
#include <string>
#include <iomanip>
#include "intbigf.h"
using namespace std;
int main()
{
	intbigd_fu::precision(33);
	intbigd_fu::precision_affect_all();
	intbigd_fu::fixed(32);
	
	int i = 0;
	
	intbigf i1("7");
	intbigf i2("1.7");
	intbigf r1, r2, r3, r4(i);
	r1 = 1/i1;
	r2 = 2/i2;
	r3 = r1*r2;
	
	cout << r1 << endl;
	cout << r2 << endl;
	cout << r3 << endl;
	cout << r4 << endl;
	
	cout << r1.size() << endl;
	cout << r2.size() << endl;
	cout << r3.size() << endl;
	cout << r4.size() << endl;
	
	return 0;
}
