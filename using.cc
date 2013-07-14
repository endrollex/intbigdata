#include <iostream>
#include <string>
#include <iomanip>
#include "intbigf.h"
using namespace std;
int main()
{
	
	intbigdata i1("12345");
	intbigf i2("12345");
	
	cout << (i1 != i2) << endl;
	
		
	
	return 0;
}