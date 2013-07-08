/* The library is not fininshed!!
__          __ ____   _____   _  __ _____  _   _   _____ 
\ \        / // __ \ |  __ \ | |/ /|_   _|| \ | | / ____|
 \ \  /\  / /| |  | || |__) || ' /   | |  |  \| || |  __ 
  \ \/  \/ / | |  | ||  _  / |  <    | |  | . ` || | |_ |
   \  /\  /  | |__| || | \ \ | . \  _| |_ | |\  || |__| |
    \/  \/    \____/ |_|  \_\|_|\_\|_____||_| \_| \_____|
*/
////////////////
//intbigf.h, calculate big float, environment: C++03 x86
//craft by endrollex, 2013.7.3
//http://endrollex.com/
//ATTENTION: This is a immature project with very simple arithemtic method,
//           that means the intbigf.h is not very efficiently.
////////////////
////////////////
#ifndef INTBIGDAF_H
#define INTBIGDAF_H
#include <iostream>
#include <fstream>//save_file, load_file
#include <deque>
#include <vector>
#include <string>
#include <iterator>
#include "intbigdata.h"
using namespace std;
typedef vector<char>::size_type unsigntp;
//
class intbigf
{
public:
	//Constructors:
	intbigf(): b_sign(true), bigint(1, 0), poi(0), ext(0) {};
	intbigf(const std::string &str1);//structure form string, can deal with scientific notation
	
	
	
	
	
	//Traditional arithmetics:
	intbigf add(const intbigf &bus2) const;
	
	
	friend std::istream &operator>>(std::istream &in, intbigf &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigf &bus1);
	
	
	
//private:

	bool b_sign;
	std::vector<char> bigint;
	int poi;
	int ext;
	//
	intbigf(const std::vector<char> &di1, const bool &bsn, const char &check_data);//inconvenience, don't use
	
	
	
};


//structure3 string
intbigf::intbigf(const std::string &str1)
{
	//"0123456789" will check converting
	string s_number("0123456789"), s_expo;
	bool b_do_e = false, ignore_e = true;
	//judge scientific notation
	string::size_type s_ixe = 0, s_ixn, s_ixn2, s_ixp;
	//'#', hide parameter, force ignore scientific notation
	if (str1[str1.size()-1] != '#') {
		s_ixe = str1.find_first_of("Ee");
		s_ixn = str1.find_last_of(s_number);
		if (s_ixe != string::npos && s_ixn != string::npos) {
			if (s_ixn > s_ixe) ignore_e = false;
		}
	}
	//scientific notation, 0 <= exponent <= 2147483647
	if (!ignore_e) {
		;
	}
	//normal number
	else {
		
		//
		
		
		int ibuff = 0;
		s_ixp = 0;
		//sign
		if (str1[0] == '-') b_sign = false;
		else b_sign = true;
		
		//trim
		
		for (s_ixn = str1.size(); s_ixn != 0; --s_ixn) {
			
			cout << "# " << str1[s_ixn-1] << endl;
			
			//point
			s_ixn2 = s_number.find(str1[s_ixn-1]);
			if (s_ixn2 != string::npos) {bigint.push_back(s_ixn2); ++ibuff;}
			if (s_ixp == 0 && str1[s_ixn-1] == '.') s_ixp = ibuff;
		}
		
		s_ixp = ibuff-s_ixp;
		if (bigint.empty()) bigint.push_back(0);
		
		ibuff = 0;
		
		//remove zero
		
		if (s_ixp != 0) {
			vector<char>::const_reverse_iterator v_it;
			for (v_it = bigint.rbegin(); v_it != bigint.rend(); ++v_it) {
				
				if (*v_it != 0) break;
				++ibuff;
				if (ibuff == s_ixp) break;
				cout << "ibuff " << ibuff << ' ' << (int)(*(v_it+1)) << endl;
				
			}
		}
		else while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
		
		
		poi = s_ixp-ibuff;
		
		
		for (int ix = 0; ix != ibuff; ++ix) bigint.pop_back();
		
		//
		//zero no sign
		if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) b_sign = true;
		
		ext = 0;
	}
	
}







//istream &operator>>
istream &operator>>(istream &in, intbigf &bus1)
{
	string s_number("0123456789"), str1;
	string::size_type s_ix;
	bus1.bigint.clear();
	in >> str1;
	//sign
	bus1.b_sign = true;
	if (str1[0] == '-') bus1.b_sign = false;
	string::reverse_iterator s_it = str1.rbegin();
	if (in) {
		for (; s_it != str1.rend(); ++s_it) {
			s_ix = s_number.find(*s_it);
			if (s_ix != string::npos) bus1.bigint.push_back(s_ix);
		}
		if (bus1.bigint.size() == 0) bus1.bigint.push_back(0);
		//remove zero
		while (bus1.bigint.back() == 0 && bus1.bigint.size() != 1) bus1.bigint.pop_back();
		//zero no sign
		if (bus1.bigint.size() == 1 && bus1.bigint[0] == 0 && bus1.b_sign == false) bus1.b_sign = true;
	}
	else bus1.bigint.push_back(0);
	return in;
}
//ostream &operator<<
ostream &operator<<(ostream &out, const intbigf &bus1)
{
	vector<char>::const_reverse_iterator rit_de = bus1.bigint.rbegin();
	//sign
	if (bus1.b_sign == false) out << '-';
	while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
	return out;
}



#endif