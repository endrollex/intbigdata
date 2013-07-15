#include <iostream>
#include <string>
#include <iomanip>
#include <ctime>
#include "intbigf.h"
using namespace std;
int main()
{
	clock_t t = clock();
	
	intbigdata n1, n2, nres;
	vector<char> res;
	
	n1.assign("12345678123456781234567812345678");
	n2.assign("987654321987654321987654321987654321");
	
	//res = intbigd_fu::karatsuba(n1.bigint, n2.bigint);
	
	nres.assign(res);
	
	cout << nres << endl;
	cout << n1*n2 << endl;
	cout << n1.size() << endl;
	cout << n2.size() << endl;
	
	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;	
	
	return 0;
}