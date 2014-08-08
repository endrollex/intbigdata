////////////////
//intbigdata.h, calculate big number, environment: C++03 x86
//craft by endrollex, start work 2012.10.03
//http://endrollex.com/
//ATTENTION: This is an immature project with very simple arithemtic method,
//           that means the intbigdata.h has very poor performance.
////////////////
////////////////
#ifndef INTBIGDATA_H
#define INTBIGDATA_H
#include <ostream>
#include <fstream>//save_file, load_file
#include <deque>
#include <vector>
#include <string>
#include <iterator>
#include <sstream>
#define DUMMY(x) (x)
//
namespace bigdata
{
//skip tab
typedef std::vector<char>::size_type unsigntp;
//
//skip tab
//Traditional arithmetics:
////////////////
//add_f
////////////////
////////////////
template <typename Tve>//Tve: std::vector<char>, std::deque<char>...
Tve add_f(const Tve &bigint, const Tve &di2)
{
	Tve de_res;
	int ip3 = 0, ip1, ip2, ipadd;
	bool irun1 = true, irun2 = true;
	typename Tve::const_iterator d_it1 = bigint.begin(), d_it2 = di2.begin();
	while (irun1 || irun2) {
		if (d_it1 != bigint.end()) {ip1 = *d_it1; ++d_it1;}
		else {ip1 = 0; irun1 = false;}
		if (d_it2 != di2.end()) {ip2 = *d_it2; ++d_it2;}
		else {ip2 = 0; irun2 = false;}
		ipadd = ip1+ip2+ip3;
		if (ipadd < 10) {de_res.push_back(static_cast<char>(ipadd)); ip3 = 0;}
		else {de_res.push_back(static_cast<char>(ipadd-10)); ip3 = 1;}
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
void sub_fself(Tve &bigint, const Tve &di2)
{
	typename Tve::iterator d_it1 = bigint.begin();
	typename Tve::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != bigint.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= static_cast<char>(*d_it2+ibuff);
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= static_cast<char>(ibuff);
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
////////////////when operator-= call this function will be less efficient.
////////////////from sub_fself
template <typename Tve>
Tve sub_f(const Tve &bigint, const Tve &di2)
{
	Tve ret(bigint);
	typename Tve::iterator d_it1 = ret.begin();
	typename Tve::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != ret.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= static_cast<char>(*d_it2+ibuff);
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= static_cast<char>(ibuff);
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
template <typename Tve, typename Tve2>
void sub_fself_contra(const Tve2 &bigint, Tve &di1)
{
	typename Tve::iterator d_it1 = di1.begin();
	typename Tve2::const_iterator d_it2 = bigint.begin();
	int ibuff = 0;
	while (d_it1 != di1.end()) {
		if (d_it2 != bigint.end()) {
			*d_it1 -= static_cast<char>(*d_it2+ibuff);
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= static_cast<char>(ibuff);
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
void sub_ffordiv(Tve &di1, const Tve2 &di2)
{
	typename Tve::iterator d_it1 = di1.begin();
	typename Tve2::const_iterator d_it2 = di2.begin();
	int ibuff = 0;
	while (d_it1 != di1.end()) {
		if (d_it2 != di2.end()) {
			*d_it1 -= static_cast<char>(*d_it2+ibuff);
			ibuff = 0;
			if (*d_it1 < 0) {*d_it1 += 10; ++ibuff;}
			++d_it2;
		}
		else {
			*d_it1 -= static_cast<char>(ibuff);
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
template <typename Tve, typename Tve2>
Tve mul_f(const Tve &bigint, const Tve2 &di2)
{
	unsigntp ix1 = 0, ix2 = 0, i_buff, ipos1, ipos2, ixadd, ipos_x;
	Tve de_res;
	typename Tve::const_iterator d_it1;
	typename Tve2::const_iterator d_it2;
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
		if (i_buff < 10) de_res[ixadd] += static_cast<char>(ipos1);
		else {
			ipos_x = i_buff/10;
			de_res[ixadd] = i_buff%10;
			ipos2 += ipos_x;
		}}
		else de_res.push_back(static_cast<char>(ipos1));
		//step2
		if (ipos2 != 0) {
			if (ixadd+2 <= de_res.size()) de_res[ixadd+1] += static_cast<char>(ipos2);
			else de_res.push_back(static_cast<char>(ipos2));
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
void mul_fself(Tve &bigint, const Tve &di2)
{
	unsigntp ix1 = 0, ix2 = 0, i_buff, ipos1, ipos2, ixadd, ipos_x;
	Tve de_res;
	typename Tve::const_iterator d_it1, d_it2;
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
		if (i_buff < 10) de_res[ixadd] += static_cast<char>(ipos1);
		else {
			ipos_x = i_buff/10;
			de_res[ixadd] = i_buff%10;
			ipos2 += ipos_x;
		}}
		else de_res.push_back(static_cast<char>(ipos1));
		//step2
		if (ipos2 != 0) {
			if (ixadd+2 <= de_res.size()) de_res[ixadd+1] += static_cast<char>(ipos2);
			else de_res.push_back(static_cast<char>(ipos2));
		}
		++ix1;
	}
		++ix2;
		ix1 = 0;
	}
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	bigint.swap(de_res);
}
////////////////std::deque use
//div_f, y = a/b (a>=b && b!=0)
////////////////
////////////////
template <typename Tve>
Tve div_f(const Tve &bigint, const Tve &di2, const bool &b_is_mod = false)
{
	unsigntp difsize = bigint.size()-di2.size()+1;
	//std::deque
	std::deque<char> bu1(bigint.begin()+difsize, bigint.end()), de_res;
	Tve di_p(bigint.begin(), bigint.begin()+difsize), ve_res;
	unsigntp ix2;
	//sub_reverse_
	for(typename Tve::reverse_iterator d_it = di_p.rbegin(); d_it != di_p.rend(); ++d_it) {
		bu1.push_front(*d_it);
		//remove zero
		while (bu1.back() == 0 && bu1.size() != 1) bu1.pop_back();
		ix2 = 0;
		while (ix2 != 10) {
			//spcial version for div
			if (abso_big_tve(bu1, di2) != -1) {
				//spcial version for div
				sub_ffordiv(bu1, di2);
				++ix2;
			}
			else {
				de_res.push_front(static_cast<char>(ix2));
				ix2 = 10;
			}
		}
	}
	if (b_is_mod) {ve_res.assign(bu1.begin(), bu1.end()); return ve_res;}
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	ve_res.assign(de_res.begin(), de_res.end());
	return ve_res;
}
////////////////
//abso_big, compare absolute value, return 1 = first big, -1 = second big, 0 = equal
////////////////
////////////////original
template <typename Tve>
int abso_big(const Tve &bigint, const Tve &di2)
{
	if (bigint.size() > di2.size()) return 1;
	if (bigint.size() < di2.size()) return -1;
	if (bigint == di2) return 0;
	typename Tve::const_reverse_iterator d_it1 = bigint.rbegin(), d_it2 = di2.rbegin();
	for (; d_it1 != bigint.rend(); ++d_it1) {
		if (d_it1 != bigint.rbegin()) ++d_it2;
		if (*d_it1 > *d_it2)  return 1;
		else {if (*d_it1 != *d_it2) return -1;}
	}
	return 0;
}
////////////////
//abso_big_tve, compare different templete type
////////////////
////////////////from abso_big
template <typename Tve, typename Tve2>
int abso_big_tve(const Tve2 &bigint, const Tve &di2)
{
	if (bigint.size() > di2.size()) return 1;
	if (bigint.size() < di2.size()) return -1;
	typename Tve2::const_reverse_iterator d_it1 = bigint.rbegin();
	typename Tve::const_reverse_iterator d_it2 = di2.rbegin();
	for (; d_it1 != bigint.rend(); ++d_it1) {
		if (d_it1 != bigint.rbegin()) ++d_it2;
		if (*d_it1 > *d_it2)  return 1;
		else {if (*d_it1 != *d_it2) return -1;}
	}
	return 0;
}
////////////////
//pow_f
////////////////
////////////////
template <typename Tve>
Tve pow_f(const Tve &bus1, const unsigned &exp)
{
	Tve ret;
	if (exp == 0) {ret.push_back(1); return ret;}
	ret = bus1;
	for (unsigned ixc = 1; ixc != exp; ++ixc) mul_fself(ret, bus1);
	return ret;
}
////////////////
//class intbigdata
////////////////
////////////////
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
	intbigdata(const std::string &str1);//structure form std::string, can deal with scientific notation
	intbigdata(const int &us1_o);
	intbigdata(const char *cstr1);
	intbigdata(const unsigned &us1_o, const int &dummy);//explicit convert unsigned to intbigdata
	intbigdata(const std::vector<char> &di1, const bool &bsn, const char &check_data);//inconvenience
	~intbigdata() {};
	//Traditional arithmetics:
	intbigdata add(const intbigdata &bus2) const;
	intbigdata sub(const intbigdata &bus2) const;
	intbigdata mul(const intbigdata &bus2) const;
	intbigdata div(const intbigdata &bus2) const;
	intbigdata mod(const intbigdata &bus2) const;
	//Power functions:
	intbigdata pow(const intbigdata &bus2) const;//exponent's value is int, cannot too big
	intbigdata sqrt() const;//ignore sign, assume positive number
	//Exponential and logarithmic functions:
	//
	//Operators:
	operator int() const;
	operator std::string() const;
	friend std::istream &operator>>(std::istream &in, intbigdata &bus1);
	friend std::ostream &operator<<(std::ostream &out, const intbigdata &bus1);
	//memo: defining own copy constructors need std::string and also int, otherwise will cause ambiguous with copy 0
	//use synthesized copy constructors
	//
	//overload operators:
	intbigdata &operator+=(const intbigdata &bus2) {return *this = this->add(bus2);}
	intbigdata &operator-=(const intbigdata &bus2) {return *this = this->sub(bus2);}
	intbigdata &operator*=(const intbigdata &bus2) {return *this = this->mul(bus2);}
	intbigdata &operator/=(const intbigdata &bus2) {return *this = this->div(bus2);}
	intbigdata &operator%=(const intbigdata &bus2) {return *this = this->mod(bus2);}
	friend bool operator==(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == 0;}
	template <typename Tve> friend bool operator==(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == 0;}
	template <typename Tve> friend bool operator==(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == 0;}
	friend bool operator!=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != 0;}
	template <typename Tve> friend bool operator!=(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != 0;}
	template <typename Tve> friend bool operator!=(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != 0;}
	friend bool operator>(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == 1;}
	template <typename Tve> friend bool operator>(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == 1;}
	template <typename Tve> friend bool operator>(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == 1;}
	friend bool operator>=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != -1;}
	template <typename Tve> friend bool operator>=(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != -1;}
	template <typename Tve> friend bool operator>=(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != -1;}
	friend bool operator<(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) == -1;}
	template <typename Tve> friend bool operator<(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == -1;}
	template <typename Tve> friend bool operator<(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) == -1;}
	friend bool operator<=(const intbigdata &bus1, const intbigdata &bus2) {return bus1.who_big(bus2) != 1;}
	template <typename Tve> friend bool operator<=(const intbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != 1;}
	template <typename Tve> friend bool operator<=(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).who_big(bus2) != 1;}
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
	void assign_unsigned(const unsigned &us1);//avoid ambiguous with int
	void assign(const char *cstr1);
	void swap(intbigdata &bus2);
	void clear();//to assign 0
	//Class operators:
	std::string scientific(const int &i_point) const;//scientific notation
	int save_file(const std::string file_name_o, const std::string file_msg_o) const;
	int load_file(const std::string &file_name);
	int get_int() const;
	unsigned get_unsigned() const;
	std::string get_string() const;
	//Capacity:
	unsigntp size() const;
	unsigntp max_size() const;
	//Objects:
	bool b_sign;//positive : bool b_sign = ture, negative : b_sign = false, zero: b_sign = ture
	std::vector<char> bigint;//sample: if int i = 190, convert to std::vector<char> d: 091
	//Compare:
	int who_big(const intbigdata &bus2) const;
	bool is_zero() const;
	void fix_data();
	bool is_not_corrupt() const;	
//private:
	//Constructors:
	intbigdata(const std::deque<char> &di1, const bool &bsn = true): b_sign(bsn), bigint(di1.begin(), di1.end()) {};
};
//nonmember operators overload
//overload operators:
inline intbigdata operator+(const intbigdata &bus1, const intbigdata &bus2) {return bus1.add(bus2);}
template <typename Tve> inline intbigdata operator+(const intbigdata &bus1, const Tve &ib2) {return bus1.add(ib2);}
template <typename Tve> inline intbigdata operator+(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).add(bus2);}
inline intbigdata operator-(const intbigdata &bus1, const intbigdata &bus2) {return bus1.sub(bus2);}
template <typename Tve> inline intbigdata operator-(const intbigdata &bus1, const Tve &ib2) {return bus1.sub(ib2);}
template <typename Tve> inline intbigdata operator-(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).sub(bus2);}
inline intbigdata operator*(const intbigdata &bus1, const intbigdata &bus2) {return bus1.mul(bus2);}
template <typename Tve> inline intbigdata operator*(const intbigdata &bus1, const Tve &ib2) {return bus1.mul(ib2);}
template <typename Tve> inline intbigdata operator*(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).mul(bus2);}
inline intbigdata operator/(const intbigdata &bus1, const intbigdata &bus2) {return bus1.div(bus2);}
template <typename Tve> inline intbigdata operator/(const intbigdata &bus1, const Tve &ib2) {return bus1.div(ib2);}
template <typename Tve> inline intbigdata operator/(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).div(bus2);}
inline intbigdata operator%(const intbigdata &bus1, const intbigdata &bus2) {return bus1.mod(bus2);}
template <typename Tve> inline intbigdata operator%(const intbigdata &bus1, const Tve &ib2) {return bus1.mod(ib2);}
template <typename Tve> inline intbigdata operator%(const Tve &ib1, const intbigdata &bus2) {return intbigdata(ib1).mod(bus2);}
// __  (\_ 
//(_ \ ( '> 
//  ) \/_)=
//  (_(_ )_ member
////////////////
//Constructors:
////////////////////////////////
//structure2 std::vector
intbigdata::intbigdata(const std::vector<char> &di1, const bool &bsn = true, const char &check_data = 'n')
{
	//sign
	b_sign = bsn;
	bigint = di1;
	if (bigint.empty()) {bigint.push_back(0); b_sign = true;}
	//check data and fix
	if (check_data == 'y') this->fix_data();
}
//structure3 std::string
intbigdata::intbigdata(const std::string &str1)
{
	//"0123456789" will check converting
	std::string s_number("0123456789"), s_expo;
	bool ignore_e = true;
	//judge scientific notation
	std::string::size_type s_ixe = 0, s_ixn, s_ixn2, s_ixp;
	//'#', hide parameter, force ignore scientific notation
	if (str1[str1.size()-1] != '#') {
		s_ixe = str1.find_first_of("Ee");
		s_ixn = str1.find_last_of(s_number);
		if (s_ixe != std::string::npos && s_ixn != std::string::npos) {
			if (s_ixn > s_ixe) ignore_e = false;
		}
	}
	//scientific notation, 0 <= exponent <= 2147483647
	if (!ignore_e) {
		std::string s_expo(str1, s_ixe+1), str1_p;
		s_expo += '#';
		//fix std::string data
		int i_expo = static_cast<int>(intbigdata(s_expo)), ibuff;
		s_ixp = std::string::npos;
		for (s_ixn = 0; s_ixn != s_ixe; ++s_ixn) {
			s_ixn2 = s_number.find(str1[s_ixn]);
			if (s_ixn2 != std::string::npos) str1_p += str1[s_ixn];
			//point
			if (s_ixp == std::string::npos && str1[s_ixn] == '.') s_ixp = str1_p.size();
		}
		if (s_ixp != std::string::npos) ibuff = static_cast<int>(str1_p.size()-s_ixp);
		else ibuff = static_cast<int>(str1_p.size()-1);
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
		if (s_ixp == std::string::npos) s_ixp = 0;
		else s_ixp = str1.size()-s_ixp;
		std::string::const_reverse_iterator s_it;
		for (s_it = str1.rbegin()+s_ixp; s_it != str1.rend(); ++s_it) {
			s_ixn = s_number.find(*s_it);
			if (s_ixn != std::string::npos) bigint.push_back(static_cast<char>(s_ixn));
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
	int us1;
	//sign
	if (us1_o < 0) {b_sign = false; us1 = -us1_o;}
	else {b_sign = true; us1 = us1_o;}
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
}
//structure5 c style std::string
inline intbigdata::intbigdata(const char *cstr1)
{
	*this = intbigdata(std::string(cstr1));
}
//structure6 unsigned
intbigdata::intbigdata(const unsigned &us1_o, const int &dummy)
{
	DUMMY(dummy);
	unsigned us1;
	//sign
	b_sign = true;
	us1 = us1_o;
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
}
////////////////
//Compare:
////////////////////////////////
//who_big, compare value, return 1 = first big, -1 = second big, 0 = equal
int intbigdata::who_big(const intbigdata &bus2) const
{
	//sign
	if (b_sign == true && bus2.b_sign == false) return 1;
	if (b_sign == false && bus2.b_sign == true) return -1;
	int i_who_big = abso_big(bigint, bus2.bigint);
	if (b_sign == false && bus2.b_sign == false) i_who_big = -i_who_big;
	return i_who_big;
}
//is_zero
bool intbigdata::is_zero() const
{
	if (bigint.size() == 1 && bigint[0] == 0) return true;
	//skip check sign
	return false;
}
//fix_data
void intbigdata::fix_data()
{
	if (bigint.empty()) bigint.push_back(0);
	std::vector<char>::reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0) *rit_de = -*rit_de;
		if (*rit_de > 9) *rit_de = *rit_de%10;
		++rit_de;
	}
	//remove zero
	while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) b_sign = true;
}
//is_not_corrupt
bool intbigdata::is_not_corrupt() const
{
	if (bigint.empty()) return false;
	std::vector<char>::const_reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0 || *rit_de > 9) return false;
		++rit_de;
	}
	//remove zero
	if (bigint.back() == 0 && bigint.size() != 1) return false;
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) return false;
	return true;
}
////////////////
//Traditional arithmetics:
////////////////////////////////
//arithmetic encapsulate
//add, sub, mul, div, pow, mod
//add
intbigdata intbigdata::add(const intbigdata &bus2) const
{
	int i_absob;
	//sign
	if (b_sign == bus2.b_sign) return intbigdata(add_f(bigint, bus2.bigint), b_sign, 'n');
	else {
		i_absob = abso_big(bigint, bus2.bigint);
		if (i_absob == 1) return intbigdata(sub_f(bigint, bus2.bigint), b_sign, 'n');
		if (i_absob == -1) return intbigdata(sub_f(bus2.bigint, bigint), bus2.b_sign, 'n');
	}
	return intbigdata();
}
//sub
intbigdata intbigdata::sub(const intbigdata &bus2) const
{
	int i_absob;
	//sign
	if (b_sign != bus2.b_sign) return intbigdata(add_f(bigint, bus2.bigint), b_sign, 'n');
	else {
		i_absob = abso_big(bigint, bus2.bigint);
		if (i_absob == 1) return intbigdata(sub_f(bigint, bus2.bigint), b_sign, 'n');
		if (i_absob == -1) return intbigdata(sub_f(bus2.bigint, bigint), !bus2.b_sign, 'n');
	}
	return intbigdata();
}
//mul
inline intbigdata intbigdata::mul(const intbigdata &bus2) const
{
	//sign
	return intbigdata(mul_f(bigint, bus2.bigint), b_sign == bus2.b_sign, 'n');
}
//div
intbigdata intbigdata::div(const intbigdata &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	int iabsobig = abso_big(bigint, bus2.bigint);
	if (iabsobig == -1) return intbigdata();
	//sign
	return intbigdata(div_f(bigint, bus2.bigint, false), b_sign == bus2.b_sign, 'n');
}
//mod
intbigdata intbigdata::mod(const intbigdata &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	int iabsobig = abso_big(bigint, bus2.bigint);
	if (iabsobig == -1) {return *this;}	
	//sign
	intbigdata ret(div_f(bigint, bus2.bigint, true), b_sign, 'n');
	if (ret.is_zero()) ret.b_sign = true;
	return ret;
}
////////////////
//Power functions:
////////////////////////////////
//pow, exponent's value is int
//large result of pow spends some time
intbigdata intbigdata::pow(const intbigdata &bus2) const
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
	for (int ixc = 1; ixc != ixpow; ++ixc) mul_fself(ret.bigint, bigint);
	return ret;
}
////////////////std::deque use
//sqrt, method: digit-by-digit calculation
intbigdata intbigdata::sqrt() const
{
	//std::deque
	std::deque<char> rema;//remainder
	std::vector<char>::const_reverse_iterator v_it = bigint.rbegin();
	//sign
	if (b_sign == false) std::cerr << "intbigdata.h: imaginary number" << std::endl;
	//initialize value
	if (bigint.size()%2 == 1) {rema.push_front(0); rema.push_front(*v_it++);}
	else {rema.push_front(*v_it++); rema.push_front(*v_it++);}
	int i_temp = rema[0]+rema[1]*10, ix = 0;
	while (ix*ix <= i_temp) ++ix;
	if (ix != 0) --ix;
	intbigdata ib_rootsqr(ix*ix), ib_20, ib_20p, di_temp, ib_root_res;
	//std::deque
	std::deque<char> de_root(1, static_cast<char>(ix));
	ib_20.bigint.push_back(2);
	sub_fself_contra(ib_rootsqr.bigint, rema);
	//iterate
	while (v_it != bigint.rend()) {
		//add the two digits
		rema.push_front(*v_it++);
		rema.push_front(*v_it++);
		while (rema.back() == 0 && rema.size() != 1) rema.pop_back();
		ib_20p.bigint = mul_f(ib_20.bigint, de_root);
		//formula: x(20p+x) <= remainder
		//try division
		di_temp.bigint.assign(rema.begin(), rema.end());
		ix = 0;
		while (abso_big(di_temp.bigint, ib_20p.bigint) != -1) {
			sub_fself(di_temp.bigint, ib_20p.bigint);
			++ix;
		}
		//note: ix < 10
		if (ix > 9) ix = 9;
		//try division end, ix = try quetient
		//_division 2, find the part of the root
		ib_20p.bigint[0] = static_cast<char>(ix);
		i_temp = 1;
		//note:
		if (ix == 1 && di_temp.is_zero()) {i_temp = 2; ib_20p.bigint[0] = 0;}
		while (i_temp == 1) {
			di_temp.bigint.assign(rema.begin(), rema.end());
			ix = 0;
			//note: ix < 10
			while (abso_big(di_temp.bigint, ib_20p.bigint) != -1 && ix != 9) {
				sub_fself(di_temp.bigint, ib_20p.bigint);
				++ix;
			}
			if (ix < ib_20p.bigint[0]) --ib_20p.bigint[0];
			else {
				i_temp = 2;
				if (ix > ib_20p.bigint[0]) di_temp.bigint = add_f(di_temp.bigint, ib_20p.bigint);
			}
		}
		de_root.push_front(ib_20p.bigint[0]);
		if (ib_20p.bigint[0] != 0) rema.assign(di_temp.bigint.begin(), di_temp.bigint.end());
	}
	ib_root_res.bigint.assign(de_root.begin(), de_root.end());
	return ib_root_res;
	//by the way: return pair to indicate square number
}
////////////////
//Operators:
////////////////////////////////
//operator int()
intbigdata::operator int() const
{
	int ret;
	std::ostringstream ostri;
	ostri << *this;
	std::istringstream istri(ostri.str());
	istri >> ret;
	return ret;	
}
//operator std::string()
intbigdata::operator std::string() const
{
	std::string s_number("0123456789"), str_res, s_buff;
	std::vector<char>::const_reverse_iterator rit_de;
	//sign
	if (b_sign == false) str_res.assign("-");
	for (rit_de = bigint.rbegin(); rit_de != bigint.rend(); ++rit_de) {
		str_res += s_number[*rit_de];
	}
	return str_res;
}
//std::istream &operator>>
std::istream &operator>>(std::istream &in, intbigdata &bus1)
{
	std::string s_number("0123456789"), str1;
	std::string::size_type s_ix;
	bus1.bigint.clear();
	in >> str1;
	//sign
	bus1.b_sign = true;
	if (str1[0] == '-') bus1.b_sign = false;
	std::string::reverse_iterator s_it = str1.rbegin();
	if (in) {
		for (; s_it != str1.rend(); ++s_it) {
			s_ix = s_number.find(*s_it);
			if (s_ix != std::string::npos) bus1.bigint.push_back(static_cast<char>(s_ix));
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
//std::ostream &operator<<
std::ostream &operator<<(std::ostream &out, const intbigdata &bus1)
{
	std::vector<char>::const_reverse_iterator rit_de = bus1.bigint.rbegin();
	//sign
	if (bus1.b_sign == false) out << '-';
	while (rit_de != bus1.bigint.rend()) out << (int)*rit_de++;
	return out;
}
//operator++
intbigdata &intbigdata::operator++()
{
	intbigdata bu_d;
	bu_d.bigint[0] = 1;
	return *this = this->add(bu_d);
}
//operator--
intbigdata &intbigdata::operator--()
{
	intbigdata bu_d;
	bu_d.bigint[0] = 1;
	return *this = this->sub(bu_d);
}
//operator++(int) postfix
intbigdata intbigdata::operator++(int)
{
	intbigdata ret(bigint, b_sign, 'n'), bu_d;
	bu_d.bigint[0] = 1;
	*this = this->add(bu_d);
	return ret;
}
//operator--(int) postfix
intbigdata intbigdata::operator--(int)
{
	intbigdata ret(bigint, b_sign, 'n'), bu_d;
	bu_d.bigint[0] = 1;
	*this = this->sub(bu_d);
	return ret;
}
////////////////
//Modifiers:
////////////////////////////////
//assign1
void intbigdata::assign(const std::vector<char> &di2, const bool &bsn = true, const char &check_data = 'y')
{
	//sign
	b_sign = bsn;
	bigint = di2;
	if (bigint.empty()) bigint.push_back(0);
	//check data and fix
	if (check_data != 'n') this->fix_data();
}
//assign2 overload
void intbigdata::assign(const intbigdata &bus2)
{
	//sign
	b_sign = bus2.b_sign;
	bigint = bus2.bigint;
}
//assign3 overload
inline void intbigdata::assign(const std::string &str1)
{
	*this = intbigdata(str1);
}
//assign4 overload 
inline void intbigdata::assign(const int &us1)
{
	*this = intbigdata(us1);
}
//assign_unsigned
inline void intbigdata::assign_unsigned(const unsigned &us1)
{
	*this = intbigdata(us1, 1);
}
//assign6 overload
inline void intbigdata::assign(const char *cstr1)
{
	*this = intbigdata(std::string(cstr1));
}
//swap
void intbigdata::swap(intbigdata &bus2)
{
	bigint.swap(bus2.bigint);
	bool b_temp = b_sign;
	b_sign = bus2.b_sign;
	bus2.b_sign = b_temp;	
}
//clear, assign 0
void intbigdata::clear()
{
	bigint.assign(1, 0);
	b_sign = true;
}
////////////////
//Class operators:
////////////////////////////////
//scientific
std::string intbigdata::scientific(const int &i_point = 6) const
{
	std::string s_number("0123456789"), s_temp, s_scient;
	unsigntp i1_get = i_point, ixsz = bigint.size()-1, ix1;
	if (bigint.size() == 1) {s_scient = s_number[bigint[0]]; s_scient += "e+0"; return s_scient;}
	//decimal point reserve
	if (i_point < 1) i1_get = 6;
	if (static_cast<unsigned>(i_point) > ixsz) i1_get = ixsz;
	//sign
	if (b_sign == false) s_scient += '-';
	intbigdata i_round;
	//round
	i_round.bigint.assign(bigint.begin()+(ixsz-i1_get), bigint.end());
	if (i1_get != ixsz) {
		if (bigint[ixsz-i1_get-1] > 4) i_round.bigint = add_f(i_round.bigint, std::vector<char>(1, 1));
	}
	//remove tail zero
	for (ix1 = 0; ix1 != i_round.bigint.size(); ++ix1) if (i_round.bigint[ix1] != 0) break;
	std::vector<char>::reverse_iterator d_it = i_round.bigint.rbegin();
	for (; d_it != i_round.bigint.rbegin()+(i_round.bigint.size()-ix1); ++d_it) {
		s_temp += s_number[*d_it];
	}	
	s_scient += s_temp[0];
	if (s_temp.size() != 1) s_scient += '.';
	s_scient.append(s_temp, 1, s_temp.size()-1);
	s_scient += "e+";
	//s_temp clear
	s_temp.clear();
	while (ixsz != 0) {s_temp = s_number[ixsz%10]+s_temp; ixsz /= 10;}
	s_scient += s_temp;
	return s_scient;
}
//save_file
int intbigdata::save_file(const std::string file_name_o = "auto", const std::string file_msg_o = "nomessage") const
{
	std::string file_name(file_name_o), file_msg("//");
	if (file_name == "auto") {
		file_name.assign("num_");
		file_name += this->scientific(6);
		file_name += ".txt";
	}
	std::ofstream outfile(file_name.c_str());
	if (!outfile) {std::cerr << "intbigdata.h: open file failed" << std::endl; return -1;}
	if (file_msg_o != "nomessage") {
		file_msg += file_msg_o;
		outfile << file_msg << std::endl;
	}
	std::vector<char>::const_reverse_iterator vi_rit = bigint.rbegin();
	//sign
	if (b_sign == false) outfile << '-';
	while (vi_rit != bigint.rend())	outfile << (int)*vi_rit++;
	outfile.close();
	outfile.clear();
	return 0;
}
//load_file
int intbigdata::load_file(const std::string &file_name)
{
	std::string::size_type pos1, pos2;
	int is_comm = 0;
	std::string s_line, s_lineadd;
	std::ifstream infile(file_name.c_str());
	if (!infile) {std::cerr << "intbigdata.h: open file faile" << std::endl; return -1;}
	while (getline(infile, s_line)) {
		//ignore comments
		pos1 = s_line.find("//");
		if (pos1 != std::string::npos) s_line.assign(s_line.begin(), s_line.begin()+pos1);
		pos1 = s_line.find("/*");
		pos2 = s_line.find("*/");
		if (pos1 != std::string::npos && pos2 != std::string::npos) s_line.replace(pos1, pos2-pos1+2, "");
		if (pos1 != std::string::npos && pos2 == std::string::npos) {
			s_line.assign(s_line.begin(), s_line.begin()+pos1);
			is_comm = 1;
		}
		if (pos1 == std::string::npos && pos2 != std::string::npos) {
			s_line.assign(s_line.begin()+pos2+2, s_line.end());
			is_comm = 0;
		}
		if (is_comm != 2 && s_line.size() != 0) s_lineadd += s_line;
		if (is_comm == 1) is_comm = 2;
	}
	*this = intbigdata(s_lineadd);
	infile.close();
	infile.clear();
	return 0;
}
//get_int
inline int intbigdata::get_int() const
{
	return int(*this);
}
//get_unsigned
unsigned intbigdata::get_unsigned() const
{
	unsigned ret;
	std::ostringstream ostri;
	ostri << *this;
	std::istringstream istri(ostri.str());
	istri >> ret;
	return ret;		
}
//get_string
inline std::string intbigdata::get_string() const
{
	return std::string(*this);
}
////////////////
//Capacity:
////////////////////////////////
//size
inline unsigntp intbigdata::size() const
{
	return bigint.size();
}
//max_size
inline unsigntp intbigdata::max_size() const
{
	return bigint.max_size();
}
}//namespace intbigd
//
////////////////
//exception or std::cerr: div, mod, sqrt, save_file, load_file
////////////////
////////////////
#endif