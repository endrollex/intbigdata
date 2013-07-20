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
	intbigd_fu::precision_affect_div_inf();
	intbigd_fu::precision_affect_all();
	intbigd_fu::trunc();
	//intbigd_fu::round();
	//intbigd_fu::fixed(9);
	//intbigd_fu::scientific();
	
	clock_t t = clock();
	
	intbigf n3 = 3000;
	
	cout << n3.root_int(3) << endl;
	cout << "1.4422495703074083823216383107801" << endl;
	

	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}