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
		intbigf y = a/(intbigf)x;
		cout << y.pow_int(x) << endl;
	}
}

int main()
{
	clock_t t = clock();

	intbigd_fu::precision_affect_div_inf();
	intbigd_fu::precision_affect_all();
	intbigd_fu::trunc();
	//intbigd_fu::round();
	//intbigd_fu::fixed(9);
	//intbigd_fu::scientific();
	
	//frac_test(50);

	
	intbigf n1 = "123456";
	cout << "n1 p " << n1.b_poi << endl;
	cout << "n1 e " << n1.b_exp << endl;
	
	intbigf n2 = "2";
	
	cout << n1.pow_int(n2) << endl;
	cout << setprecision(16) << pow(n1.get_double(), n2.get_double()) << endl;
	

	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}