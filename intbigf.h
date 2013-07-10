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
//           that means the intbigf.h is less efficient.
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
typedef deque<char>::size_type unsigntp;
//
class intbigf
{
public:
	//Constructors:
	intbigf(): b_sign(true), bigint(1, 0), b_poi(0), b_exp(0) {};
	intbigf(const std::string &str1);//structure form string, can deal with scientific notation
	
	
	
	
	
	//Traditional arithmetics:
	intbigf add(const intbigf &bus2) const;
	
	
	friend std::istream &operator>>(std::istream &in, intbigf &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigf &bus1);
	
	
	
//private:

	bool b_sign;
	std::deque<char> bigint;
	int b_poi;
	int b_exp;
	//
	intbigf(const std::deque<char> &di1, const bool &bsn, const char &check_data);//inconvenience, don't use
	
	
	//
	bool is_zero() const;
	
};


//structure3 string
intbigf::intbigf(const std::string &str1)
{
	//"0123456789" will check converting
	string s_number("0123456789"), s_expo;
	bool b_do_e = false, ignore_e = true;
	//judge scientific notation
	string::size_type s_ixe = 0, s_ixn, s_ixn2, s_ixp, s_ixbu;
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
		string s_expo(str1, s_ixe+1), str1_p(str1, 0, s_ixe);
		s_expo += '#';
		//fix string data
		int i_expo = static_cast<int>(intbigdata(s_expo));
		str1_p += '#';
		*this = intbigf(str1_p);
		b_exp += i_expo;
	}
	//normal number
	else {
		s_ixp = 0;
		s_ixbu = 0;
		//sign
		if (str1[0] == '-') b_sign = false;
		else b_sign = true;
		//trim
		for (s_ixn = str1.size(); s_ixn != 0; --s_ixn) {
			//point
			s_ixn2 = s_number.find(str1[s_ixn-1]);
			if (s_ixn2 != string::npos) {bigint.push_back(s_ixn2); ++s_ixbu;}
			if (s_ixp == 0 && str1[s_ixn-1] == '.') s_ixp = s_ixbu;
		}
		if (bigint.empty()) bigint.push_back(0);
		//remove zero
		if (s_ixp != 0) {
			s_ixp = s_ixbu-s_ixp;
			s_ixbu = 0;
			deque<char>::const_reverse_iterator v_it;
			for (v_it = bigint.rbegin(); v_it != bigint.rend(); ++v_it) {
				if (*v_it != 0) break;
				++s_ixbu;
				if (s_ixbu == s_ixp) break;
			}
			b_poi = static_cast<int>(s_ixp-s_ixbu);
		}
		else {
			b_poi = static_cast<int>(s_ixbu-s_ixp);
			while (bigint.back() == 0 && bigint.size() != 1) {bigint.pop_back(); --b_poi;}
		}
		b_exp = 0;
		if (s_ixp != 0) {
			for (unsigned ix = 0; ix != s_ixbu; ++ix) bigint.pop_back();
			s_ixbu = 0;
			while (bigint.back() == 0 && bigint.size() != 1) {bigint.pop_back(); --b_exp;}
			
			
			
			
			
			while (bigint[s_ixbu] == 0 && bigint.size() != 1) ++s_ixbu;
			deque<char>::const_iterator v_it2 = bigint.begin();
			bigint.erase(v_it2, v_it2+s_ixbu);
		}
		//zero no sign
		if (bigint.size() == 1 && bigint[0] == 0) {b_sign = true; b_poi = 1; b_exp = 0;}
	}
	
	cout << "p " << b_poi << endl;
	cout << "e " << b_exp << endl;
	
}







//istream &operator>>
istream &operator>>(istream &in, intbigf &bus1)
{
	string str1;
	bus1.bigint.clear();
	in >> str1;
	//sign
	bus1.b_sign = true;
	if (str1[0] == '-') bus1.b_sign = false;
	string::reverse_iterator s_it = str1.rbegin();
	if (in) {
		
		
		
		
		bus1 = intbigf(str1);
	}
	else bus1.bigint.push_back(0);
	

	return in;
}
//ostream &operator<<
ostream &operator<<(ostream &out, const intbigf &bus1)
{
	deque<char>::const_reverse_iterator rit_de = bus1.bigint.rbegin();
	//sign
	if (bus1.b_sign == false) out << '-';
	int ibuff = bus1.b_poi+bus1.b_exp;
	if (ibuff <= 0) {
		out << "0.";
		while (ibuff < 0) {out << '0'; ++ibuff;}
		while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
	}
	else {
		if (ibuff != bus1.bigint.size()) {
			if (bus1.bigint.size() > ibuff) {
				while (rit_de != bus1.bigint.rend()-ibuff) out << (int)*rit_de++;
				out << '.';
				while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
			}
			else {
				ibuff = ibuff-bus1.bigint.size();
				while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
				for (unsigned ix = 0; ix != ibuff; ++ix) out << '0';
			}
		}
		else while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
	}
	return out;
}



//is_zero
inline bool intbigf::is_zero() const
{
	if (bigint.size() == 1 && bigint[0] == 0) return true;
	//skip check sign
	return false;
}



#endif