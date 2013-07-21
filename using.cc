#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <sstream>
#include "intbigf.h"
using namespace std;
void frac_test(const intbigf &a)
{
	for (int x = 1; x != (int)a+1; ++x) {
		intbigf y = a/x;
		cout << ((y-1).pow_int(x)) << endl;
	}
}
void frac_test2(const double &a)
{
	for (int x = 1; x != (int)a+1; ++x) {
		double y = a/x;
		cout << pow(y-1, x) << endl;
	}
}
int main()
{
	clock_t t = clock();

	intbigd_fu::precision_affect_div_inf();
	intbigd_fu::precision_affect_all();
	//intbigd_fu::trunc();
	//intbigd_fu::round();
	//intbigd_fu::fixed(6);
	//intbigd_fu::scientific();
	
	//frac_test(100);
	
	intbigf n1 = "3";
	intbigf n2 = "12.5";
	n2 = 1.5;
	
	//cout << n1.pow_int(n2) << endl;
	//cout << setprecision(16) << pow((double)n1, (double)(1/n2)) << endl;
	cout << setprecision(16) << pow((double)n1, (double)(n2)) << endl;
	
	cout << n1.pow(n2) << endl;
	//cout << n1.root(n2) << endl;
	
	cout << n1.pow_frac(3, 2) << endl;
	
	cout << intbigf(100000).root(2) << endl;
	
	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}