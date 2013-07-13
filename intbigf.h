/**
 *
 * The library is not fininshed!!
 *
*/
////////////////
//intbigf.h, calculate big float, environment: C++03 x86
//craft by endrollex, 2013.7.3
//http://endrollex.com/
//ATTENTION: This is an immature project with very simple arithemtic method,
//           that means the intbigf.h is less efficient.
////////////////
////////////////
#ifndef INTBIGDAF_H
#define INTBIGDAF_H
#include <iostream>
#include <fstream>//save_file, load_file
#include <deque>
#include <string>
#include <iterator>
#include "intbigdata.h"

namespace intbigd_fu
{
//skip tab

//global var, significant digits
int sig_digs = 64;


////////////////
//prepare calc point float
////////////////
////////////////
template <typename Tve> 
inline void pre_fcalc(const Tve &bus1, const Tve &bus2, Tve &bus_temp,
	int &i_offset, int &i_exp, char &check_d, int b_poi1, int b_poi2, const int &b_exp1, const int &b_exp2) {
	int b_poi1_o = b_poi1, b_poi2_o = b_poi2;
	if (b_exp1 > b_exp2) b_poi1 += b_exp1-b_exp2;
	if (b_exp2 > b_exp1) b_poi2 += b_exp2-b_exp1;
	i_offset = (bus1.size()-b_poi1)-(bus2.size()-b_poi2);
	if (i_offset < 0) {
		bus_temp = bus1;
		for (int ix = i_offset; ix < 0; ++ix) bus_temp.push_front(0);
		i_exp = i_offset-(bus1.size()-b_poi1_o)+b_exp1;
	}
	if (i_offset > 0) {
		bus_temp = bus2;
		for (int ix = i_offset; ix > 0; --ix) bus_temp.push_front(0);
		i_exp = -i_offset-(bus2.size()-b_poi2_o)+b_exp2;
	}
	if (i_offset == 0) {i_exp = -(bus1.size()-b_poi1_o)+b_exp1; check_d = 'y';}
}
////////////////deque use
//divf_f, y = a/b (a>=b && b!=0)
////////////////
////////////////from div_f
template <typename Tve>
Tve divf_f(const Tve &bigint, const Tve &di2, const bool &b_is_mod)
{
	unsigntp difsize = bigint.size()-di2.size()+1;
	//deque
	Tve bu1(bigint.begin()+difsize, bigint.end()), di_p(bigint.begin(), bigint.begin()+difsize), de_res;
	unsigntp ix1, ix2;
	
	int i_sigd= sig_digs-difsize, ibuff, ibuff_m;
	
	
	
	for (int ix= 0; ix != i_sigd; ++ix) di_p.push_front(0);
	
	
	//sub_reverse_
	for(typename Tve::reverse_iterator d_it = di_p.rbegin(); d_it != di_p.rend(); ++d_it) {
		bu1.push_front(*d_it);
		//remove zero
		while (bu1.back() == 0 && bu1.size() != 1) bu1.pop_back();
		ix2 = 0;
		while (ix2 != 10) {
			if (abso_big(bu1, di2) != -1) {
				//spcial version for div
				sub_ffordiv(bu1, di2);
				++ix2;
			}
			else {
				de_res.push_front(ix2);
				ix2 = 10;
			}
		}
	}
	
	
	
	
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
		
	if (b_is_mod) return bu1;
	
	//10000
	ibuff = i_sigd/100;
	ibuff_m = i_sigd%100;
	
	
	de_res.push_back(i_sigd);
	
	return de_res;
}


}

//
class intbigf
{
public:
	//Constructors:
	intbigf(): b_sign(true), bigint(1, 0), b_poi(0), b_exp(0) {};
	intbigf(const std::string &str1);//structure form string, can deal with scientific notation
	
	
	
	
	
	//Traditional arithmetics:
	intbigf add(const intbigf &bus2) const;
	intbigf sub(const intbigf &bus2) const;
	intbigf mul(const intbigf &bus2) const;
	intbigf div(const intbigf &bus2) const;
	intbigf mod(const intbigf &bus2) const;
	//
	
	
	friend std::istream &operator>>(std::istream &in, intbigf &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigf &bus1);
	
	
	
	
//protected:






	bool b_sign;
	std::deque<char> bigint;
	int b_poi;
	int b_exp;
	//
	intbigf(const std::deque<char> &di1, const int &bpi, const int &bep, const bool &bsn, const char &check_data);
	
	
	
	
	//Compare
	int who_big(const intbigf &bus2) const;
	bool is_zero() const;
	
};


// (\__/)
//(='.'=)
//(")_(") member
//structure2 vector
intbigf::intbigf(const deque<char> &di1, const int &bpi = 0, const int &bep = 0,
	const bool &bsn = true, const char &check_data = 'y')
{
	//sign
	b_sign = bsn;
	bigint = di1;
	b_poi = bpi;
	if (b_poi == -1) b_poi = bigint.size();
	b_exp = bep;
	if (bigint.empty()) {bigint.push_back(0); b_sign = true;}
	//check data and fix
	//if (check_data != 'n') this->fix_data();
	
	//for div
	if (check_data == 'd') {
		b_poi -= bigint.back();
		
		bigint.pop_back();
	}
}






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
			while (bigint.back() == 0 && bigint.size() != 1) {bigint.pop_back(); --b_exp;}
			while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
		}
		//zero no sign
		if (bigint.size() == 1 && bigint[0] == 0) {b_sign = true; b_poi = 1; b_exp = 0;}
	}
}


//arithmetic encapsulate
//add, sub, mul, div, pow, mod
//add
inline intbigf intbigf::add(const intbigf &bus2) const
{
	int i_offset, i_exp, i_absob;
	deque<char> bus_temp;
	char check_d = 'n';
	intbigd_fu::pre_fcalc(bigint, bus2.bigint, bus_temp, i_offset, i_exp, check_d, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	const deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	//sign
	if (b_sign == bus2.b_sign) return intbigf(intbigd_fu::add_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, check_d);
	else {
		i_absob = intbigd_fu::abso_big(*bus1_p, *bus2_p);
		if (i_absob == 1) return intbigf(intbigd_fu::sub_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, check_d);
		if (i_absob == -1) return intbigf(intbigd_fu::sub_f(*bus2_p, *bus1_p), -1, i_exp, bus2.b_sign, check_d);
	}
	return intbigf();
}
//sub
inline intbigf intbigf::sub(const intbigf &bus2) const
{
	int i_offset, i_exp, i_absob;
	deque<char> bus_temp;
	char check_d = 'n';
	intbigd_fu::pre_fcalc(bigint, bus2.bigint, bus_temp, i_offset, i_exp, check_d, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	const deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	//sign
	if (b_sign != bus2.b_sign) return intbigf(intbigd_fu::add_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, check_d);
	else {
		i_absob = intbigd_fu::abso_big(*bus1_p, *bus2_p);
		if (i_absob == 1) return intbigf(intbigd_fu::sub_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, check_d);
		if (i_absob == -1) return intbigf(intbigd_fu::sub_f(*bus2_p, *bus1_p), -1, i_exp, !bus2.b_sign, check_d);
	}
	return intbigf();
}
//mul
inline intbigf intbigf::mul(const intbigf &bus2) const
{
	int i_offset, i_exp, i_absob;
	deque<char> bus_temp;
	char check_d = 'n';
	intbigd_fu::pre_fcalc(bigint, bus2.bigint, bus_temp, i_offset, i_exp, check_d, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	const deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	//sign
	return intbigf(intbigd_fu::mul_f(*bus1_p, *bus2_p), -1, i_exp+i_exp, b_sign == bus2.b_sign, 'y');
}

//div
inline intbigf intbigf::div(const intbigf &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	//
	int i_offset, i_exp, i_absob;
	deque<char> bus_temp;
	char check_d = 'n';
	intbigd_fu::pre_fcalc(bigint, bus2.bigint, bus_temp, i_offset, i_exp, check_d, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	const deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	
	
	
	
	//
	int iabsobig = intbigd_fu::abso_big(*bus1_p, *bus2_p);
	
	
	if (iabsobig == -1) return intbigf();
	
	
	
	//sign
	return intbigf(intbigd_fu::divf_f(*bus1_p, *bus2_p, false), -1, 0, b_sign == bus2.b_sign, 'd');
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
	if (in) bus1 = intbigf(str1);
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
				while (rit_de != bus1.bigint.rbegin()+ibuff) out << (int)*rit_de++;
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



//who_big, compare value, return 1 = first big, -1 = second big, 0 = equal
inline int intbigf::who_big(const intbigf &bus2) const
{
	//sign
	if (b_sign == true && bus2.b_sign == false) return 1;
	if (b_sign == false && bus2.b_sign == true) return -1;
	int b_exp1 = b_exp, b_exp2 = bus2.b_exp, i_who_big;
	if (b_poi > bus2.b_poi) b_exp1 += b_poi-bus2.b_poi;
	if (bus2.b_poi > b_poi) b_exp2 += bus2.b_poi-b_poi;
	if (b_sign) {if (b_exp1 > b_exp2) return 1; if (b_exp2 > b_exp1) return -1;}
	if (!b_sign) {if (b_exp1 < b_exp2) return 1; if (b_exp2 < b_exp1) return -1;}
	i_who_big = intbigd_fu::abso_big(bigint, bus2.bigint);
	if (b_sign == false && bus2.b_sign == false) i_who_big = -i_who_big;
	return i_who_big;
}




//is_zero
inline bool intbigf::is_zero() const
{
	if (bigint.size() == 1 && bigint[0] == 0) return true;
	//skip check sign
	return false;
}



#endif