#include <iostream>
#include <string>
#include "intbigf.h"//use library
using namespace std;
int main()
{
        //three init methods
        intbigf test1(2);
        intbigf test2("-44867916611904333479495141036159177872720902");
        intbigf test3 = "2.00e400";
 
        //operator like int
        test2 = test1 * test3;
        //power functions
        test1 = test1.pow(1024);
        test2 = test3.root(2);

        //output I/O stream
        cout << "square root of 2e400 = " << test2 << "\n" << endl;
        cout << "2^1024 = "<< test1 << "\n" << endl;
        //scientific notation output
        cout << "2^1024 scientific notation: " << test1.scientific() << "\n" << endl;
        
        //set precision for float
        intbigd_fu::precision(128);
        cout << "square root of 3: " << intbigf(3).root(2) << endl;

        return 0;
}