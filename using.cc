#include <iostream>
#include <string>
#include "intbigf.h"
using namespace std;
int main()
{
	//intbigf t("2.3e-8");
	
	intbigf t ("0.00000023e-1");
	
	
	//intbigf t("123.45e1");

	//intbigdata t("7.51E-9");
	
	cout << t << endl;
	cout << t.b_poi << endl;
	cout << t.b_exp << endl;
	
	
	
	
	
	return 0;
}