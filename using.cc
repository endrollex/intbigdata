/*#include <iostream>
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
*/

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
		cout << (y).pow_int(x) << endl;
	}
}
int main()
{
	intbigd_fu::precision_affect_all(200);
	//intbigd_fu::fixed(9);
	intbigd_fu::scientific();
		
	clock_t t = clock();
	
	//frac_test(100);
	

	intbigf f("0.000245");
	
	intbigf f2 = f.pow_int(-44);
	
	cout << f2 << endl;
	
	cout << pow(0.000245, -44) << endl;	
	
	
	
	
	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}