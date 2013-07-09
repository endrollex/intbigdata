////////////////
//intbigdata.h, calculate big number, environment: C++03 x86
//craft by endrollex, 2012.10.03
//http://endrollex.com/
//ATTENTION: This is a immature project with very simple arithemtic method,
//           that means the intbigdata.h is not very efficiently.
////////////////
////////////////
#ifndef INTBIGDATA_H
#define INTBIGDATA_H
#include <iostream>
#include <fstream>//save_file, load_file
#include <deque>
#include <vector>
#include <string>
#include <iterator>
//
using std::deque;
using std::vector;
using std::string;
using std::istream;
using std::ostream;
using std::ofstream;
using std::ifstream;
using std::cerr;
using std::endl;
//
typedef vector<char>::size_type unsigntp;
class intbigdata_error
{
public:
	intbigdata_error() {};
	~intbigdata_error() {};
	const char *what() const {return "intbigdata.h: divide or mod by zero";}
};
//
class intbigdata
{
public:
	//Constructors:
	intbigdata(): b_sign(true), bigint(1, 0) {};
	intbigdata(const std::string &str1);//structure form string, can deal with scientific notation
	intbigdata(const int &us1_o);
	intbigdata(const char *cstr1);
	intbigdata(const unsigned &us1_o, const int &dummy);//explicit convert unsigned to intbigdata
	~intbigdata() {};
	//Traditional arithmetics:
	intbigdata add(const intbigdata &bus2) const;
	intbigdata sub(const intbigdata &bus2) const;
	intbigdata mul(const intbigdata &bus2) const;
	intbigdata div(const intbigdata &bus2) const;
	intbigdata mod(const intbigdata &bus2) const;
	//Power functions:
	intbigdata pow(const intbigdata &bus2) const;//exponent's value is a int, cannot too big
	intbigdata sqrt() const;//ignore sign, assume positive number
	//Exponential and logarithmic functions:
	//
	//Operators:
	operator int() const;
	operator string() const;
	friend std::istream &operator>>(std::istream &in, intbigdata &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigdata &bus1);
	//memo: defining own copy constructors need string and also int, otherwise will cause ambiguous with copy 0
	//use synthesized copy constructors to save code lines
	//
	//overload operators: between intbigdata and int, ATTENTION: unsigned must be explicit conversion
	intbigdata &operator+=(const intbigdata &bus2) {return *this = this->add(bus2);}
	intbigdata &operator-=(const intbigdata &bus2) {return *this = this->sub(bus2);}
	intbigdata &operator*=(const intbigdata &bus2) {return *this = this->mul(bus2);}
	intbigdata &operator/=(const intbigdata &bus2) {return *this = this->div(bus2);}
	intbigdata &operator%=(const intbigdata &bus2) {return *this = this->mod(bus2);}
	friend bool operator==(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == 0;}
	friend bool operator==(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) == 0;}
	friend bool operator==(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == 0;}
	friend bool operator!=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != 0;}
	friend bool operator!=(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) != 0;}
	friend bool operator!=(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != 0;}
	friend bool operator>(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == 1;}
	friend bool operator>(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) == 1;}
	friend bool operator>(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == 1;}
	friend bool operator>=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != -1;}
	friend bool operator>=(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) != -1;}
	friend bool operator>=(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != -1;}
	friend bool operator<(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == -1;}
	friend bool operator<(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) == -1;}
	friend bool operator<(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == -1;}
	friend bool operator<=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != 1;}
	friend bool operator<=(const intbigdata &bus1, const int &ib2) {return bus1.who_big(ib2) != 1;}
	friend bool operator<=(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != 1;}
	intbigdata &operator++();
	intbigdata &operator--();
	intbigdata operator++(int);
	intbigdata operator--(int);
	intbigdata &operator+() {return *this;}
	intbigdata &operator-() {b_sign = !b_sign; return *this;}
	//Modifiers:
	void assign(const std::vector<char> &di2, const bool &bsn, const char &check_data);//inconvenience
	void assign(const intbigdata &bus2);
	void assign(const std::string &str1);
	void assign(const int &us1);
	void assign_unsigned(const unsigned &us1);//to avoid ambiguous with int
	void swap(intbigdata &bus2);
	void clear();//to assign 0
	//intbigdata operators:
	std::string scientific(const int &i_point) const;//scientific notation
	int save_file(const std::string file_name_o, const std::string file_msg_o) const;
	int load_file(const string &file_name);
	int get_int() const;
	unsigned get_unsigned() const;
	std::string get_string() const;
	//Capacity:
	unsigntp size();
	unsigntp max_size();
private:
	bool b_sign;
	std::vector<char> bigint;
	//sample: if int i = 190, convert to vector<char> d: 091
	//positive : bool b_sign = ture, negative : b_sign = false, zero: b_sign = ture
	intbigdata(const std::vector<char> &di1, const bool &bsn, const char &check_data);//inconvenience, don't use
	intbigdata(const std::deque<char> &di1): b_sign(true), bigint(di1.begin(), di1.end()) {};//debug
	//Traditional arithmetics:
	template <typename Tve> std::vector<char> add_f(const Tve &di2) const;
	template <typename Tve> void sub_fself(const Tve &di2);
	template <typename Tve> std::vector<char> sub_f(const Tve &di2) const;
	template <typename Tve> void sub_fself_contra(Tve &di1) const;
	template <typename Tve, typename Tve2> void sub_ffordiv(Tve &di1, const Tve2 &di2) const;
	template <typename Tve> std::vector<char> mul_f(const Tve &di2) const;
	template <typename Tve> void mul_fself(const Tve &di2);
	template <typename Tve> std::vector<char> div_f(const Tve &di2_o, const bool &b_is_mod = false) const;
	//Compare:
	template <typename Tve> int abso_big(const Tve &di2) const;
	template <typename Tve, typename Tve2> int abso_big_fordiv(const Tve &di1, const Tve2 &di2) const;
	int who_big(const intbigdata &bus2) const;
	bool is_zero() const;
	void fix_data();
	bool is_not_corrupt() const;
};
//nonmember operators overload
//overload operators: between intbigdata and int, ATTENTION: unsigned must be explicit conversion
inline intbigdata operator+(const intbigdata &bus1, const intbigdata &bus2) {return bus1.add(bus2);}
inline intbigdata operator+(const intbigdata &bus1, const int &ib2) {return bus1.add(ib2);}
inline intbigdata operator+(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).add(bus2);}
inline intbigdata operator-(const intbigdata &bus1, const intbigdata &bus2) {return bus1.sub(bus2);}
inline intbigdata operator-(const intbigdata &bus1, const int &ib2) {return bus1.sub(ib2);}
inline intbigdata operator-(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).sub(bus2);}
inline intbigdata operator*(const intbigdata &bus1, const intbigdata &bus2) {return bus1.mul(bus2);}
inline intbigdata operator*(const intbigdata &bus1, const int &ib2) {return bus1.mul(ib2);}
inline intbigdata operator*(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).mul(bus2);}
inline intbigdata operator/(const intbigdata &bus1, const intbigdata &bus2) {return bus1.div(bus2);}
inline intbigdata operator/(const intbigdata &bus1, const int &ib2) {return bus1.div(ib2);}
inline intbigdata operator/(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).div(bus2);}
inline intbigdata operator%(const intbigdata &bus1, const intbigdata &bus2) {return bus1.mod(bus2);}
inline intbigdata operator%(const intbigdata &bus1, const int &ib2) {return bus1.mod(ib2);}
inline intbigdata operator%(const int &ib1, const intbigdata &bus2) {return intbigdata(ib1).mod(bus2);}
// __  (\_ 
//(_ \ ( '> 
//  ) \/_)=
//  (_(_ )_ member
//structure2 vector
intbigdata::intbigdata(const vector<char> &di1, const bool &bsn = true, const char &check_data = 'y')
{
	//sign
	b_sign = bsn;
	bigint = di1;
	if (bigint.empty()) {bigint.push_back(0); b_sign = true;}
	//check data and fix
	if (check_data != 'n') this->fix_data();
}
//structure3 string
intbigdata::intbigdata(const std::string &str1)
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
		string s_expo(str1, s_ixe+1), str1_p;
		s_expo += '#';
		//fix string data
		int i_expo = static_cast<int>(intbigdata(s_expo)), ibuff;
		s_ixp = string::npos;
		for (s_ixn = 0; s_ixn != s_ixe; ++s_ixn) {
			s_ixn2 = s_number.find(str1[s_ixn]);
			if (s_ixn2 != string::npos) str1_p += str1[s_ixn];
			//point
			if (s_ixp == string::npos && str1[s_ixn] == '.') s_ixp = str1_p.size();
		}
		if (s_ixp != string::npos) ibuff = static_cast<int>(str1_p.size()-s_ixp);
		else ibuff = str1_p.size()-1;
		ibuff = i_expo-ibuff;
		if (str1_p.size() == 0) str1_p += '1';
		if (ibuff < 0) {
			ibuff = static_cast<int>(str1_p.size())+ibuff;
			if (ibuff > 0) str1_p.assign(str1_p, 0, ibuff);
			else str1_p.assign("0");
		}
		else for (int ix = 0; ix != ibuff; ++ix) str1_p += '0';
		str1_p += '#';
		*this = intbigdata(str1_p);
		//sign
		if (str1[0] == '-') b_sign = false;
	}
	//normal number
	else {
		//sign
		if (str1[0] == '-') b_sign = false;
		else b_sign = true;
		//point, no need trim
		s_ixp = str1.find_first_of('.');
		if (s_ixp == string::npos) s_ixp = 0;
		else s_ixp = str1.size()-s_ixp;
		string::const_reverse_iterator s_it;
		for (s_it = str1.rbegin()+s_ixp; s_it != str1.rend(); ++s_it) {
			s_ixn = s_number.find(*s_it);
			if (s_ixn != string::npos) bigint.push_back(s_ixn);
		}
		if (bigint.empty()) bigint.push_back(0);
		//remove zero
		while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
		//zero no sign
		if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) b_sign = true;
	}
}
//structure4 int
intbigdata::intbigdata(const int &us1_o)
{
	int ibuff, us1;
	//sign
	if (us1_o < 0) {b_sign = false; us1 = -us1_o;}
	else {b_sign = true; us1 = us1_o;}
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
}
//structure5 c style string
intbigdata::intbigdata(const char *cstr1)
{
	string str1(cstr1);
	*this = intbigdata(str1);
}
//structure6 unsigned
intbigdata::intbigdata(const unsigned &us1_o, const int &dummy)
{
	unsigned ibuff, us1;
	//sign
	b_sign = true;
	us1 = us1_o;
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
}
////////////////
//add_f
////////////////
////////////////
template <typename Tve>//Tve: vector<char>, deque<char>...
vector<char> intbigdata::add_f(const Tve &di2) const
{
	vector<char> de_res;
	int ip3 = 0, ip1, ip2, ipadd;
	bool irun1 = true, irun2 = true;
	vector<char>::const_iterator d_it1 = bigint.begin();
	typename Tve::const_iterator d_it2 = di2.begin();
	while (irun1 || irun2) {
		if (d_it1 != bigint.end()) {ip1 = *d_it1; ++d_it1;}
		else {ip1 = 0; irun1 = false;}
		if (d_it2 != di2.end()) {ip2 = *d_it2; ++d_it2;}
		else {ip2 = 0; irun2 = false;}
		ipadd = ip1+ip2+ip3;
		if (ipadd < 10) {de_res.push_back(ipadd); ip3 = 0;}
		else {de_res.push_back(ipadd-10); ip3 = 1;}
	}
	//remove zero, irun will generate zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	return de_res;
}
////////////////
//sub_fself, a = a-b (a>=b)
////////////////
////////////////original
template <typename Tve>
void intbigdata::sub_fself(const Tve &di2)
{
	vector<char>::iterator d_it1 = bigint.begin();
	typename Tve::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != bigint.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= *d_it2+ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			else d_it1 = bigint.end()-1;
		}
		++d_it1;
	}
	//remove zero
	while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
}
////////////////
//sub_f, y = a-b (a>=b)
////////////////when operator-= call this function will cause a little performance loss
////////////////from sub_fself
template <typename Tve>
vector<char> intbigdata::sub_f(const Tve &di2) const
{
	vector<char> ret(bigint);
	vector<char>::iterator d_it1 = ret.begin();
	typename Tve::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != ret.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= *d_it2+ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			else d_it1 = ret.end()-1;
		}
		++d_it1;
	}
	//remove zero
	while (ret.back() == 0 && ret.size() != 1) ret.pop_back();
	return ret;
}
////////////////
//sub_fself_contra, CAUTION: reverse, b = b-a (b>=a)
////////////////
////////////////from sub_fself
template <typename Tve>
void intbigdata::sub_fself_contra(Tve &di1) const
{
	typename Tve::iterator d_it1 = di1.begin();
	vector<char>::const_iterator d_it2 = bigint.begin();
	int ibuff = 0;
	while (d_it1 != di1.end()) {
		if (d_it2 != bigint.end()) {
			*d_it1 -= *d_it2+ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			else d_it1 = di1.end()-1;
		}
		++d_it1;
	}
	//remove zero
	while (di1.back() == 0 && di1.size() != 1) di1.pop_back();
}
////////////////
//sub_ffordiv, b = b-c (b>=c)
////////////////
////////////////from sub_fself
template <typename Tve, typename Tve2>
void intbigdata::sub_ffordiv(Tve &di1, const Tve2 &di2) const
{
	typename Tve::iterator d_it1 = di1.begin();
	typename Tve2::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != di1.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= *d_it2+ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= ibuff;
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			else d_it1 = di1.end()-1;
		}
		++d_it1;
	}
	//remove zero
	while (di1.back() == 0 && di1.size() != 1) di1.pop_back();
}
////////////////
//mul_f, y = a*b
////////////////
////////////////original
template <typename Tve>
vector<char> intbigdata::mul_f(const Tve &di2) const
{
	unsigntp ix1 = 0, ix2 = 0, i_buff, ipos1, ipos2, ixadd, ipos_x;
	vector<char> de_res;
	vector<char>::const_iterator d_it1;
	typename Tve::const_iterator d_it2;
	//2 skip tab
	for (d_it2 = di2.begin(); d_it2 != di2.end(); ++d_it2) {
	for (d_it1 = bigint.begin(); d_it1 != bigint.end(); ++d_it1) {
		i_buff = *d_it1**d_it2;
		ipos1 = i_buff%10;
		ixadd = ix1+ix2;
		if (i_buff >= 10) ipos2 = i_buff/10;
		else ipos2 = 0;
		//skip tab
		if (ixadd+1 <= de_res.size()) {
		i_buff = de_res[ixadd]+ipos1;
		if (i_buff < 10) de_res[ixadd] += ipos1;
		else {
			ipos_x = i_buff/10;
			de_res[ixadd] = i_buff%10;
			ipos2 += ipos_x;
		}}
		else de_res.push_back(ipos1);
		//step2
		if (ipos2 != 0) {
			if (ixadd+2 <= de_res.size()) de_res[ixadd+1] += ipos2;
			else de_res.push_back(ipos2);
		}
		++ix1;		
	}
		++ix2;
		ix1 = 0;
	}
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	return de_res;
}
////////////////
//mul_fself, a = a*b
////////////////
////////////////from mul_f
template <typename Tve>
void intbigdata::mul_fself(const Tve &di2)
{
	unsigntp ix1 = 0, ix2 = 0, i_buff, ipos1, ipos2, ixadd, ipos_x;
	vector<char> de_res;
	vector<char>::const_iterator d_it1;
	typename Tve::const_iterator d_it2;
	//2 skip tab
	for (d_it2 = di2.begin(); d_it2 != di2.end(); ++d_it2) {
	for (d_it1 = bigint.begin(); d_it1 != bigint.end(); ++d_it1) {
		i_buff = *d_it1**d_it2;
		ipos1 = i_buff%10;
		ixadd = ix1+ix2;
		if (i_buff >= 10) ipos2 = i_buff/10;
		else ipos2 = 0;
		//skip tab
		if (ixadd+1 <= de_res.size()) {
		i_buff = de_res[ixadd]+ipos1;
		if (i_buff < 10) de_res[ixadd] += ipos1;
		else {
			ipos_x = i_buff/10;
			de_res[ixadd] = i_buff%10;
			ipos2 += ipos_x;
		}}
		else de_res.push_back(ipos1);
		//step2
		if (ipos2 != 0) {
			if (ixadd+2 <= de_res.size()) de_res[ixadd+1] += ipos2;
			else de_res.push_back(ipos2);
		}
		++ix1;		
	}
		++ix2;
		ix1 = 0;
	}
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	//difference form mul_f
	bigint.swap(de_res);
}
////////////////deque use
//div_f, y = a/b (a>=b && b!=0)
////////////////
////////////////
template <typename Tve>
vector<char> intbigdata::div_f(const Tve &di2, const bool &b_is_mod) const
{
	unsigntp difsize = bigint.size()-di2.size()+1;
	intbigdata dummy_empty;
	//deque
	deque<char> bu1(bigint.begin()+difsize, bigint.end()), de_res;
	vector<char> di_p(bigint.begin(), bigint.begin()+difsize), ve_res;
	unsigntp ix1, ix2;
	//sub_reverse_
	for(vector<char>::reverse_iterator d_it = di_p.rbegin(); d_it != di_p.rend(); ++d_it) {
		bu1.push_front(*d_it);
		//remove zero
		while (bu1.back() == 0 && bu1.size() != 1) bu1.pop_back();
		ix2 = 0;
		while (ix2 != 10) {
			//spcial version for div
			if (dummy_empty.abso_big_fordiv(bu1, di2) != -1) {
				//spcial version for div
				dummy_empty.sub_ffordiv(bu1, di2);
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
	if (b_is_mod) {ve_res.assign(bu1.begin(), bu1.end()); return ve_res;}
	ve_res.assign(de_res.begin(), de_res.end());
	return ve_res;
}
////////////////
//abso_big, compare absolute value, return 1 = first big, -1 = second big, 0 = equal
////////////////
////////////////original
template <typename Tve>
int intbigdata::abso_big(const Tve &di2) const
{
	if (bigint.size() > di2.size()) return 1;
	if (bigint.size() < di2.size()) return -1;
	vector<char>::const_reverse_iterator d_it1 = bigint.rbegin();
	typename Tve::const_reverse_iterator d_it2 = di2.rbegin();
	for (; d_it1 != bigint.rend(); ++d_it1) {
		if (d_it1 != bigint.rbegin()) ++d_it2;
		if (*d_it1 > *d_it2)  return 1;
		else {if (*d_it1 != *d_it2) return -1;}
	}
	return 0;
}
////////////////
//abso_big_fordiv, 2 template parameter version
////////////////
////////////////from abso_big
template <typename Tve, typename Tve2>
int intbigdata::abso_big_fordiv(const Tve &di1, const Tve2 &di2) const
{
	if (di1.size() > di2.size()) return 1;
	if (di1.size() < di2.size()) return -1;
	typename Tve::const_reverse_iterator d_it1 = di1.rbegin();
	typename Tve2::const_reverse_iterator d_it2 = di2.rbegin();
	for (; d_it1 != di1.rend(); ++d_it1) {
		if (d_it1 != di1.rbegin()) ++d_it2;
		if (*d_it1 > *d_it2)  return 1;
		else {if (*d_it1 != *d_it2) return -1;}
	}
	return 0;
}
//who_big, compare value, return 1 = first big, -1 = second big, 0 = equal
inline int intbigdata::who_big(const intbigdata &bus2) const
{
	//sign
	if (b_sign == true && bus2.b_sign == false) {return 1;}
	if (b_sign == false && bus2.b_sign == true) {return -1;}
	int i_who_big = this->abso_big(bus2.bigint);
	if (b_sign == false && bus2.b_sign == false) i_who_big = -i_who_big;
	return i_who_big;
}
//is_zero
inline bool intbigdata::is_zero() const
{
	if (bigint.size() == 1 && bigint[0] == 0) return true;
	//skip check sign
	return false;
}
//arithmetic encapsulate
//add, sub, mul, div, pow, mod
//add
inline intbigdata intbigdata::add(const intbigdata &bus2) const
{
	int i_absob;
	//sign
	if (b_sign == bus2.b_sign) return intbigdata(this->add_f(bus2.bigint), b_sign, 'n');
	else {
		i_absob = this->abso_big(bus2.bigint);
		if (i_absob == 1) return intbigdata(this->sub_f(bus2.bigint), b_sign, 'n');
		if (i_absob == -1) return intbigdata(bus2.sub_f(bigint), bus2.b_sign, 'n');
	}
	return intbigdata();
}
//sub
inline intbigdata intbigdata::sub(const intbigdata &bus2) const
{
	int i_absob;
	//sign
	if (b_sign != bus2.b_sign) return intbigdata(this->add_f(bus2.bigint), b_sign, 'n');
	else {
		i_absob = this->abso_big(bus2.bigint);
		if (i_absob == 1) return intbigdata(this->sub_f(bus2.bigint), b_sign, 'n');
		if (i_absob == -1) return intbigdata(bus2.sub_f(bigint), !bus2.b_sign, 'n');
	}
	return intbigdata();
}
//mul
inline intbigdata intbigdata::mul(const intbigdata &bus2) const
{
	//sign
	return intbigdata(this->mul_f(bus2.bigint), b_sign == bus2.b_sign, 'n');
}
//div
inline intbigdata intbigdata::div(const intbigdata &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	int iabsobig = this->abso_big(bus2.bigint);
	if (iabsobig == -1) return intbigdata();
	//sign
	return intbigdata(this->div_f(bus2.bigint, false), b_sign == bus2.b_sign, 'n');
}
//mod
inline intbigdata intbigdata::mod(const intbigdata &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	int iabsobig = this->abso_big(bus2.bigint);
	if (iabsobig == -1) {return *this;}	
	//sign
	intbigdata ret(this->div_f(bus2.bigint, true), b_sign, 'n');
	if (ret.is_zero()) ret.b_sign = true;
	return ret;
}
//pow, exponent's value is a int
//large result of pow spends some time
inline intbigdata intbigdata::pow(const intbigdata &bus2) const
{
	intbigdata ret;
	int ixpow = static_cast<int>(bus2);
	if (ixpow == 0) {ret.bigint[0] = 1; return ret;}
	//sign
	if (bus2.b_sign == false) {
		ixpow = -ixpow;
		if (bigint.size() != 1 || bigint[0] != 1) return ret;
	}
	if (ixpow%2 == 1) ret.b_sign = b_sign;
	ret.bigint = bigint;
	for (int ixc = 1; ixc != ixpow; ++ixc) ret.mul_fself(bigint);
	return ret;
}
////////////////deque use
//sqrt, method: digit-by-digit calculation
intbigdata intbigdata::sqrt() const
{
	//deque
	deque<char> rema;//remainder
	vector<char>::const_reverse_iterator v_it = bigint.rbegin();
	//sign
	if (b_sign == false) cerr << "intbigdata.h: imaginary number" << endl;
	//initialize value
	if (bigint.size()%2 == 1) {rema.push_front(0); rema.push_front(*v_it++);}
	else {rema.push_front(*v_it++); rema.push_front(*v_it++);}
	int i_temp = rema[0]+rema[1]*10, ix = 0;
	while (ix*ix <= i_temp) ++ix;
	if (ix != 0) --ix;
	intbigdata ib_rootsqr(ix*ix), ib_20, ib_20p, di_temp, ib_root_res;
	//deque
	deque<char> de_root(1, ix);
	ib_20.bigint.push_back(2);
	ib_rootsqr.sub_fself_contra(rema);
	//iterate
	//skip tab
	while (v_it != bigint.rend()) {
	//add the two digits
	rema.push_front(*v_it++);
	rema.push_front(*v_it++);
	while (rema.back() == 0 && rema.size() != 1) rema.pop_back();
	ib_20p.bigint = ib_20.mul_f(de_root);
	//formula: x(20p+x) <= remainder
	//try division
	di_temp.bigint.assign(rema.begin(), rema.end());
	ix = 0;
	while (di_temp.abso_big(ib_20p.bigint) != -1) {
		di_temp.sub_fself(ib_20p.bigint);
		++ix;
	}
	//note: ix < 10
	if (ix > 9) ix = 9;
	//try division end, ix = try quetient
	//_division 2, find the part of the root
	ib_20p.bigint[0] = ix;
	i_temp = 1;
	//note:
	if (ix == 1 && di_temp.is_zero()) {i_temp = 2; ib_20p.bigint[0] = 0;}
	while (i_temp == 1) {
		di_temp.bigint.assign(rema.begin(), rema.end());
		ix = 0;
		//note: ix < 10
		while (di_temp.abso_big(ib_20p.bigint) != -1 && ix != 9) {
			di_temp.sub_fself(ib_20p.bigint);
			++ix;
		}
		if (ix < ib_20p.bigint[0]) --ib_20p.bigint[0];
		else {
			i_temp = 2;
			if (ix > ib_20p.bigint[0]) di_temp.bigint = di_temp.add_f(ib_20p.bigint);
		}
	}
	de_root.push_front(ib_20p.bigint[0]);
	if (ib_20p.bigint[0] != 0) rema.assign(di_temp.bigint.begin(), di_temp.bigint.end());
	}
	ib_root_res.bigint.assign(de_root.begin(), de_root.end());
	return ib_root_res;
	//by the way: return pair to indicate square number
}
//operator int()
////////////////original
intbigdata::operator int() const
{
	//int, 32-bit, -2147483648 to 2147483647
	//the const -2147483648 some compiler warning (cc1plus), so ignore
	string s_max("2147483647");
	intbigdata ibd_max(s_max);
	vector<char>::const_reverse_iterator v_it;
	int get_int = 0;
	if (this->abso_big(ibd_max.bigint) == 1) {
		//cerr << intbigdata.h: out of range << endl;
		ibd_max.bigint = this->div_f(ibd_max.bigint, true);
		v_it = ibd_max.bigint.rbegin();
		while (v_it != ibd_max.bigint.rend()) get_int = get_int*10+*v_it++;
	}
	else {
		v_it = bigint.rbegin();
		while (v_it != bigint.rend()) get_int = get_int*10+*v_it++;
	}
	//sign
	if (b_sign == false) get_int = -get_int;
	return get_int;
}
//operator string()
intbigdata::operator string() const
{
	string s_number("0123456789"), str_res, s_buff;
	vector<char>::const_reverse_iterator rit_de;
	//sign
	if (b_sign == false) str_res.assign("-");
	for (rit_de = bigint.rbegin(); rit_de != bigint.rend(); ++rit_de) {
		str_res += s_number[*rit_de];
	}
	return str_res;
}
//istream &operator>>
istream &operator>>(istream &in, intbigdata &bus1)
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
ostream &operator<<(ostream &out, const intbigdata &bus1)
{
	vector<char>::const_reverse_iterator rit_de = bus1.bigint.rbegin();
	//sign
	if (bus1.b_sign == false) out << '-';
	while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
	return out;
}
//operator++
inline intbigdata &intbigdata::operator++()
{
	intbigdata bu_d;
	bu_d.bigint[0] = 1;
	return *this = this->add(bu_d);
}
//operator--
inline intbigdata &intbigdata::operator--()
{
	intbigdata bu_d;
	bu_d.bigint[0] = 1;
	return *this = this->sub(bu_d);
}
//operator++(int) postfix
inline intbigdata intbigdata::operator++(int)
{
	intbigdata ret(bigint, b_sign, 'n'), bu_d;
	bu_d.bigint[0] = 1;
	*this = this->add(bu_d);
	return ret;
}
//operator--(int) postfix
inline intbigdata intbigdata::operator--(int)
{
	intbigdata ret(bigint, b_sign, 'n'), bu_d;
	bu_d.bigint[0] = 1;
	*this = this->sub(bu_d);
	return ret;
}
//assign1
inline void intbigdata::assign(const vector<char> &di2, const bool &bsn = true, const char &check_data = 'y')
{
	//sign
	b_sign = bsn;
	bigint = di2;
	if (bigint.empty()) bigint.push_back(0);
	//check data and fix
	if (check_data != 'n') this->fix_data();
}
//assign2 overload
inline void intbigdata::assign(const intbigdata &bus2)
{
	//sign
	b_sign = bus2.b_sign;
	bigint = bus2.bigint;
}
//assign3 overload
inline void intbigdata::assign(const string &str1)
{
	*this = intbigdata(str1);
}
//assign4 overload 
inline void intbigdata::assign(const int &us1)
{
	*this = intbigdata(us1);
}
//assign_unsigned
void intbigdata::assign_unsigned(const unsigned &us1)
{
	*this = intbigdata(us1, 1);
}
//swap
inline void intbigdata::swap(intbigdata &bus2)
{
	bigint.swap(bus2.bigint);
	bool b_temp = b_sign;
	b_sign = bus2.b_sign;
	bus2.b_sign = b_temp;	
}
//clear, assign 0
inline void intbigdata::clear()
{
	bigint.assign(1, 0);
	b_sign = true;
}
//scientific
string intbigdata::scientific(const int &i_point = 6) const
{
	string s_number("0123456789"), s_temp, s_scient;
	unsigntp i1_get = i_point, ixsz = bigint.size()-1, ix1;
	vector<char> d_one(1, 1);
	if (bigint.size() == 1) {s_scient = s_number[bigint[0]]; s_scient += "e+0"; return s_scient;}
	//decimal point reserve
	if (i_point < 1) i1_get = 6;
	if ((unsigned)i_point > ixsz) i1_get = ixsz;
	//sign
	if (b_sign == false) s_scient += '-';
	intbigdata i_round;
	//round
	i_round.bigint.assign(bigint.begin()+(ixsz-i1_get), bigint.end());
	if (i1_get != ixsz) {
		if (bigint[ixsz-i1_get-1] > 4) i_round.bigint = i_round.add_f(d_one);
	}
	//remove tail zero
	for (ix1 = 0; ix1 != i_round.bigint.size(); ++ix1) if (i_round.bigint[ix1] != 0) break;
	vector<char>::reverse_iterator d_it = i_round.bigint.rbegin();
	for (; d_it != i_round.bigint.rbegin()+(i_round.bigint.size()-ix1); ++d_it) {
		s_temp += s_number[*d_it];
	}	
	s_scient += s_temp[0];
	s_scient += '.';
	s_scient.append(s_temp, 1, s_temp.size()-1);
	s_scient += "e+";
	//s_temp clear
	s_temp.clear();
	while (ixsz != 0) {s_temp += s_number[ixsz%10]; ixsz /= 10;}
	string::reverse_iterator s_it = s_temp.rbegin();
	while (s_it != s_temp.rend()) s_scient += *s_it++;
	return s_scient;
}
//save_file
int intbigdata::save_file(const string file_name_o = "auto", const string file_msg_o = "nomessage") const
{
	string file_name(file_name_o), file_msg("//");
	if (file_name == "auto") {
		file_name.assign("intbigdata_");
		file_name += this->scientific(6);
		file_name += ".txt";
	}
	ofstream outfile(file_name.c_str());
	if (!outfile) {cerr << "intbigdata.h: open file failed" << endl; return -1;}
	if (file_msg_o != "nomessage") {
		file_msg += file_msg_o;
		outfile << file_msg << endl;
	}
	vector<char>::const_reverse_iterator vi_rit = bigint.rbegin();
	//sign
	if (b_sign == false) outfile << '-';
	while (vi_rit != bigint.rend())	outfile << (int)*vi_rit++;
	outfile.close();
	outfile.clear();
	return 0;
}
//load_file
int intbigdata::load_file(const string &file_name)
{
	string::size_type pos1, pos2;
	int i_iscomment = 0;
	string s_line, s_lineadd;
	ifstream infile(file_name.c_str());
	if (!infile) {cerr << "intbigdata.h: open file faile" << endl; return -1;}
	while (getline(infile, s_line)) {
		//ignore comments
		pos1 = s_line.find("//");
		if (pos1 != string::npos) s_line.assign(s_line.begin(), s_line.begin()+pos1);
		pos1 = s_line.find("/*");
		pos2 = s_line.find("*/");
		if (pos1 != string::npos && pos2 != string::npos) s_line.replace(pos1, pos2-pos1+2, "");
		if (pos1 != string::npos && pos2 == string::npos) {
			s_line.assign(s_line.begin(), s_line.begin()+pos1);
			i_iscomment = 1;
		}
		if (pos1 == string::npos && pos2 != string::npos) {
			s_line.assign(s_line.begin()+pos2+2, s_line.end());
			i_iscomment = 0;
		}
		if (i_iscomment != 2 && s_line.size() != 0) s_lineadd += s_line;
		if (i_iscomment == 1) i_iscomment = 2;
	}
	*this = intbigdata(s_lineadd);
	infile.close();
	infile.clear();
	return 0;
}
//get_int
int intbigdata::get_int() const
{
	return int(*this);
}
//get_unsigned
////////////////from int()
unsigned intbigdata::get_unsigned() const
{
	//unsigned, 32-bit, 0 to 4294967295
	string s_max("4294967295");
	intbigdata ibd_max(s_max);
	vector<char>::const_reverse_iterator v_it;
	unsigned get_int = 0;
	if (this->abso_big(ibd_max.bigint) == 1) {
		//cerr << intbigdata.h: out of range << endl;
		ibd_max.bigint = this->div_f(ibd_max.bigint, true);
		v_it = ibd_max.bigint.rbegin();
		while (v_it != ibd_max.bigint.rend()) get_int = get_int*10+*v_it++;
	}
	else {
		v_it = bigint.rbegin();
		while (v_it != bigint.rend()) get_int = get_int*10+*v_it++;
	}
	//sign
	if (b_sign == false) get_int = -get_int;
	return get_int;
}
//get_string
string intbigdata::get_string() const
{
	return string(*this);
}
//size
inline unsigntp intbigdata::size()
{
	return bigint.size();
}
//max_size
inline unsigntp intbigdata::max_size()
{
	return bigint.max_size();
}
//fix_data
void intbigdata::fix_data()
{
	if (bigint.empty()) bigint.push_back(0);
	vector<char>::reverse_iterator rit_de = bigint.rbegin();
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
}
//is_not_corrupt
bool intbigdata::is_not_corrupt() const
{
	if (bigint.empty()) return false;
	vector<char>::const_reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0 || *rit_de > 9) return false;
		++rit_de;
	}
	//remove zero
	unsigntp ix2 = bigint.size()-1;
	if (bigint[ix2] == 0) return false;
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) return false;
	return true;
}
////////////////
//exception cerr: operator int(), get_unsigned, div, mod, sqrt, save_file, load_file
////////////////
////////////////
#endif