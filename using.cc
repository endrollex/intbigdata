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
	//intbigd_fu::precision_affect_div_inf();
	//intbigd_fu::precision_affect_all();
	//intbigd_fu::truncation();
	//intbigd_fu::fixed(9);
	//intbigd_fu::scientific();
	
	clock_t t = clock();
	
	deque<char> de(1, 1);
	de.push_front(0);
	de.push_front(0);
	
	intbigf it(de, 1, 2);
	
	cout << it << endl;
	cout << it.is_not_corrupt() << endl;
	

	t = clock() - t;
	cout << "It took me " << ((float)t)/CLOCKS_PER_SEC << " seconds." << endl;
	
	return 0;
}