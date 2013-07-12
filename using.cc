#include <iostream>
#include <string>
#include "intbigf.h"
using namespace std;
int main()
{
	//intbigf t1("0.00456");
	//intbigf t2("1000234");
	
	intbigf t2("1000234");
	intbigf t1("0.00456");
	
	intbigf t3(t1.add(t2));
	
	
	
	cout << "res: " << t3 << endl;
	cout << "r " << t3.b_poi << ' ' << t3.b_exp << endl;
	
	
	cout << endl;
	cout << t1 << endl;
	cout << t2 << endl;
	



	return 0;
}