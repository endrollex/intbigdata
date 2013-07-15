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
	
	n1.load_file("num1.txt");
	n2.load_file("num2.txt");
	
	res = intbigd_fu::karatsuba(n1.bigint, n2.bigint);
	
	nres.assign(res);
	
	
	cout << nres << endl;
	
	//cout << n1*n2 << endl;
	
	cout << n1.size() << endl;
	cout << n2.size() << endl;
	
	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;	
	
	return 0;
}
