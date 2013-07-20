#include <iostream>
#include <iomanip>
#include <string>
#include <ctime>
#include <cmath>
#include <sstream>
#include "intbigf.h"
using namespace std;
int main()
{
	clock_t t = clock();

	intbigd_fu::precision_affect_div_inf();
	intbigd_fu::precision_affect_all(16);
	intbigd_fu::trunc();
	//intbigd_fu::round();
	//intbigd_fu::fixed(9);
	//intbigd_fu::scientific();
	
	
	intbigf n3 = "3e-2";
	//n3 = 0.003;
	n3 = "3e-11";
	
	cout << n3.root_int(4) << endl;
	

	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}