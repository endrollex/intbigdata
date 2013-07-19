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
		cout << "a = " << a << ", "<< y << "^" << x << ": " << endl;
		cout << ((y).pow_int(x)).size() << " " << ((y).pow_int(x)) << endl;
	}
}
int main()
{
	intbigd_fu::precision_affect_div_inf();
	intbigd_fu::precision_affect_all();
	intbigd_fu::trunc();
	//intbigd_fu::round();
	//intbigd_fu::fixed(9);
	//intbigd_fu::scientific();
	
	clock_t t = clock();
	
	//frac_test(100);
	
	
	intbigf n1("14422");
	intbigf n2("59720728576");
	
	intbigf n3 = 3;
	
	cout << n3 << endl;
	cout << n3.root_int(66) << endl;
	//cout << cbrt(3.0) << endl;
	cout << "1.4422495703074083823216383107801" << endl;
	

	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}