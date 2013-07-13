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
#include <sstream>
#include "intbigdata.h"
using std::ostringstream;
using std::istringstream;
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
	if (i_offset == 0) {i_exp = -(bus1.size()-b_poi1_o)+b_exp1; check_d = 'z';}
}
////////////////deque use
//divf_f, y = a/b (a>=b && b!=0)
////////////////
////////////////from div_f
template <typename Tve>
Tve divf_f(const Tve &bigint, const Tve &di2, const bool &b_is_mod)
{
	unsigntp difsize = bigint.size()-di2.size()+1;
	int i_sigd= sig_digs-difsize, ibuff = 0, di_p_siz, di_p_cou = 0;
	unsigntp ix1, ix2;
	if (difsize > bigint.size()) {ibuff = bigint.size()-difsize; difsize = bigint.size();}
	//deque
	Tve bu1(bigint.begin()+difsize, bigint.end()), di_p(bigint.begin(), bigint.begin()+difsize), de_res;
	di_p_siz = di_p.size();
	for (int ix= 0; ix != i_sigd+ibuff; ++ix) di_p.push_front(0);
	//sub_reverse_
	for(typename Tve::reverse_iterator d_it = di_p.rbegin(); d_it != di_p.rend(); ++d_it) {
		//stop div
		if (di_p_cou >= di_p_siz) if (bu1.back() == 0 && bu1.size() == 1) break;
		++di_p_cou;
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
	//significant digits
	i_sigd = di_p_cou-di_p_siz;
	if (i_sigd > 0) {
		de_res.push_back(101);
		while (i_sigd > 0) {
			de_res.push_back(i_sigd%100);
			i_sigd = i_sigd/100;
		}
		de_res.push_back(101);
	}
	return de_res;
}
}
//do not inherit
class intbigf
{
public:
	//Constructors:
	intbigf(): b_sign(true), bigint(1, 0), b_poi(0), b_exp(0) {};
	intbigf(const std::string &str1);//structure form string, can deal with scientific notation
	intbigf(const double &dou1_o);
	intbigf(const int &us1_o);
	intbigf(const intbigdata &bus1);
	intbigf(const char *cstr1);
	
	~intbigf() {};
	//Traditional arithmetics:
	intbigf add(const intbigf &bus2) const;
	intbigf sub(const intbigf &bus2) const;
	intbigf mul(const intbigf &bus2) const;
	intbigf div(const intbigf &bus2) const;
	//Operators:
	operator int() const;
	operator string() const;
	operator double() const;
	operator intbigdata() const;
	
	friend std::istream &operator>>(std::istream &in, intbigf &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigf &bus1);
	
	//overload operators: between intbigf and int, ATTENTION: unsigned must be explicit conversion
	intbigf &operator+=(const intbigf &bus2) {return *this = this->add(bus2);}
	intbigf &operator-=(const intbigf &bus2) {return *this = this->sub(bus2);}
	intbigf &operator*=(const intbigf &bus2) {return *this = this->mul(bus2);}
	intbigf &operator/=(const intbigf &bus2) {return *this = this->div(bus2);}
	friend bool operator==(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) == 0;}
	friend bool operator==(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) == 0;}
	friend bool operator==(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) == 0;}
	friend bool operator!=(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) != 0;}
	friend bool operator!=(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) != 0;}
	friend bool operator!=(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) != 0;}
	friend bool operator>(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) == 1;}
	friend bool operator>(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) == 1;}
	friend bool operator>(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) == 1;}
	friend bool operator>=(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) != -1;}
	friend bool operator>=(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) != -1;}
	friend bool operator>=(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) != -1;}
	friend bool operator<(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) == -1;}
	friend bool operator<(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) == -1;}
	friend bool operator<(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) == -1;}
	friend bool operator<=(const intbigf &bus1, const intbigf &bus2) {return bus1.who_big(bus2) != 1;}
	friend bool operator<=(const intbigf &bus1, const int &ib2) {return bus1.who_big(ib2) != 1;}
	friend bool operator<=(const int &ib1, const intbigf &bus2) {return intbigf(ib1).who_big(bus2) != 1;}
	intbigf &operator+() {return *this;}
	intbigf &operator-() {b_sign = !b_sign; return *this;}
	//Capacity:
	unsigntp size();
	unsigntp max_size();
//protected:
	bool b_sign;
	std::deque<char> bigint;
	int b_poi;
	int b_exp;
	//Constructors:
	intbigf(const std::deque<char> &di1, const int &bpi, const int &bep, const bool &bsn, const char &check_data);
	
	intbigf(const std::vector<char> &di1, const bool &di1_sign);
	
	//Compare:
	int who_big(const intbigf &bus2) const;
	bool is_zero() const;
	void fix_data();
	bool is_not_corrupt() const;
};
//nonmember operators overload
//overload operators: between intbigf and int, double, intbigdata, ATTENTION: other types must be explicit converted
inline intbigf operator+(const intbigf &bus1, const intbigf &bus2) {return bus1.add(bus2);}
inline intbigf operator+(const intbigf &bus1, const int &ib2) {return bus1.add(ib2);}
inline intbigf operator+(const int &ib1, const intbigf &bus2) {return intbigf(ib1).add(bus2);}
inline intbigf operator-(const intbigf &bus1, const intbigf &bus2) {return bus1.sub(bus2);}
inline intbigf operator-(const intbigf &bus1, const int &ib2) {return bus1.sub(ib2);}
inline intbigf operator-(const int &ib1, const intbigf &bus2) {return intbigf(ib1).sub(bus2);}


inline intbigf operator*(const intbigf &bus1, const intbigf &bus2) {return bus1.mul(bus2);}
inline intbigf operator*(const intbigf &bus1, const int &ib2) {return bus1.mul(ib2);}
inline intbigf operator*(const int &ib1, const intbigf &bus2) {return intbigf(ib1).mul(bus2);}

inline intbigf operator*(const intbigf &bus1, const intbigdata &bus2) {return bus1.mul(bus2);}
inline intbigf operator*(const intbigdata &bus1, const intbigf &bus2) {return intbigf(bus1).mul(bus2);}
inline intbigf operator*(const intbigf &bus1, const double &ib2) {return bus1.mul(ib2);}
inline intbigf operator*(const double &ib1, const intbigf &bus2) {return intbigf(ib1).mul(bus2);}


inline intbigf operator/(const intbigf &bus1, const intbigf &bus2) {return bus1.div(bus2);}
inline intbigf operator/(const intbigf &bus1, const int &ib2) {return bus1.div(ib2);}
inline intbigf operator/(const int &ib1, const intbigf &bus2) {return intbigf(ib1).div(bus2);}
// (\__/)
//(='.'=)
//(")_(") member
////////////////
//Constructors:
////////////////////////////////
//structure2 deque
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
	if (check_data == 'y') this->fix_data();
	//remove point zero
	if (check_data == 'z') {
		int ibuff = b_poi+b_exp;
		if (ibuff < 0) ibuff = -ibuff;
		if (bigint.size() > ibuff) while (bigint.front() == 0 && bigint.size() != ibuff) bigint.pop_front();
	}
	//for div
	if (check_data == 'd' && bigint.back() == 101) {
		bigint.pop_back();
		int i_count = 1, ibuff = 0;
		while (bigint.back() != 101 && bigint.size() != 1) {
			ibuff = ibuff*i_count+bigint.back();
			i_count *= 100;
			bigint.pop_back();
			--b_poi;
		}
		bigint.pop_back();
		b_poi -= ibuff+2;
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
//structure4 int
intbigf::intbigf(const int &us1_o)
{
	int ibuff, us1;
	//sign
	if (us1_o < 0) {b_sign = false; us1 = -us1_o;}
	else {b_sign = true; us1 = us1_o;}
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
	b_poi = bigint.size();
	b_exp = 0;
	
}
//structure5 c style string
intbigf::intbigf(const char *cstr1)
{
	string str1(cstr1);
	*this = intbigf(str1);
}
//structure7 double
intbigf::intbigf(const double &dou1_o)
{
	ostringstream ostri;
	ostri << dou1_o;
	*this = intbigf(ostri.str());
}
//structure8 intbigdata
intbigf::intbigf(const intbigdata &bus1)
{
	*this = intbigf(deque<char>(bus1.bigint.begin(), bus1.bigint.end()), -1, 0, bus1.b_sign, 'n');
}






////////////////
//Compare:
////////////////////////////////
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
	//skip check sign, point, exponent
	return false;
}
//fix_data
void intbigf::fix_data()
{
	if (bigint.empty()) bigint.push_back(0);
	deque<char>::reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0) *rit_de = -*rit_de;
		if (*rit_de > 9) *rit_de = *rit_de%10;
		++rit_de;
	}
	unsigntp ix2 = bigint.size()-1;
	//remove zero
	while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) b_sign = true;
	//
	if (b_poi < 0) b_poi = 0;
	//remove point zero
	int ibuff = b_poi+b_exp;
	if (bigint.size() > ibuff) while (bigint.front() == 0 && bigint.size() != ibuff) bigint.pop_front();
}
//is_not_corrupt
bool intbigf::is_not_corrupt() const
{
	if (bigint.empty()) return false;
	deque<char>::const_reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0 || *rit_de > 9) return false;
		++rit_de;
	}
	//remove zero
	unsigntp ix2 = bigint.size()-1;
	if (bigint[ix2] == 0) return false;
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) return false;
	//
	if (b_poi < 0) return false;
	//remove point zero
	int ibuff = b_poi+b_exp;
	if (bigint.size() > ibuff) if (bigint.front() == 0 && bigint.size() > ibuff) return false;
	return true;
}
////////////////
//Traditional arithmetics:
////////////////////////////////
//arithmetic encapsulate
//add, sub, mul, div, pow
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
	return intbigf(intbigd_fu::mul_f(*bus1_p, *bus2_p), -1, i_exp+i_exp, b_sign == bus2.b_sign, 'z');
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
	//sign
	return intbigf(intbigd_fu::divf_f(*bus1_p, *bus2_p, false), -1, 0, b_sign == bus2.b_sign, 'd');
}
////////////////
//Operators:
////////////////////////////////
//operator int()
intbigf::operator int() const
{
	int ret;
	ostringstream ostri;
	ostri << *this;
	istringstream istri(ostri.str());
	istri >> ret;	
	return ret;
}
//operator string()
intbigf::operator string() const
{
	ostringstream ostri;
	ostri << *this;
	return ostri.str();
}
//operator double()
intbigf::operator double() const
{
	double ret;
	ostringstream ostri;
	ostri << *this;
	istringstream istri(ostri.str());
	istri >> ret;
	return ret;
}
//operator intbigdata()
intbigf::operator intbigdata() const
{
	vector<char> ret(bigint.begin()+(bigint.size()-b_poi+b_exp), bigint.end());
	return intbigdata(ret, b_sign, 'n');
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
		if (bus1.bigint.size() == 1 && bus1.bigint.back() == 0) {out << '0'; return out;}
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
////////////////
//Capacity:
////////////////////////////////
//size
inline unsigntp intbigf::size()
{
	return bigint.size();
}
//max_size
inline unsigntp intbigf::max_size()
{
	return bigint.max_size();
}
#endif