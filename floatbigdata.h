////////////////
//floatbigdata.h, calculate big float, environment: C++03 x86
//craft by endrollex, start work 2013.07.03
//http://endrollex.com/
//ATTENTION: This is an immature project with very simple arithemtic method,
//           that means the floatbigdata.h has very poor performance.
////////////////
////////////////
#ifndef FLOATBIGDATA_H
#define FLOATBIGDATA_H
#include "intbigdata.h"
//
namespace bigdata
{
//skip tab
////////////////
//global var, significant digits, rounding or truncation, cout type
////////////////
////////////////
int digits_precision = 64;
int digits_precision_affect = 1;
int digits_limit_type = 1;
int cout_type = 1;
unsigned cout_scientific = 16;
int cout_fixed = 64;
////////////////
//global set function
////////////////
////////////////
void precision(int i_value = 64) {if (i_value < 0) i_value = -i_value; digits_precision = i_value;}
void precision_affect_div(int i_value = digits_precision)
{
	digits_precision_affect = 1;
	if (i_value < 0) i_value = -i_value;
	digits_precision = i_value;
}
void precision_affect_all(int i_value = digits_precision)
{
	digits_precision_affect = 2;
	if (i_value < 0) i_value = -i_value;
	digits_precision = i_value;
}
void round() {digits_limit_type = 1;}
void trunc() {digits_limit_type = 2;}
void cout_default() {cout_type = 1;}
void scientific(unsigned i_value = 16) {cout_type = 2; cout_scientific = i_value;}
void fixed(int i_value = 64) {cout_type = 3; if (i_value < 0) i_value = -i_value; cout_fixed = i_value;}
////////////////
//pre_faddsub, prepare calc point float, add sub
////////////////
////////////////
template <typename Tve> 
int pre_faddsub(const Tve &bus1, const Tve &bus2, Tve &bus_temp,
	int &i_offset, int &i_exp, int b_poi1, int b_poi2, int b_exp1, int b_exp2) {
	int bd1 = static_cast<int>(b_poi1+b_exp1), bd2 = static_cast<int>(b_poi2+b_exp2),
		size1 = static_cast<int>(bus1.size()), size2 = static_cast<int>(bus2.size());
	i_offset = (size1-bd1)-(size2-bd2);
	//over precision, if round
	if (digits_precision_affect == 2 && digits_limit_type == 1) {
		int ibuff = bd1-bd2;
		if (ibuff > 0 && ibuff > digits_precision) return 1;
		if (ibuff < 0 && -ibuff > digits_precision) return 2;
	}
	//normal
	if (i_offset < 0) {
		bus_temp = bus1;
		for (int ix = i_offset; ix < 0; ++ix) bus_temp.push_front(0);
		i_exp = i_offset-(size1-b_poi1)+b_exp1;
	}
	if (i_offset > 0) {
		bus_temp = bus2;
		for (int ix = i_offset; ix > 0; --ix) bus_temp.push_front(0);
		i_exp = -i_offset-(size2-b_poi2)+b_exp2;
	}
	if (i_offset == 0) {i_exp = -(size1-b_poi1)+b_exp1;}
	return 0;
}
////////////////
//significant_fix
////////////////
////////////////
template <typename Tve>
void significant_fix(
	Tve &bigint, int &digits_offset, const int &i_sigd = digits_precision, const int &force_round = 0, const bool &is_div = false)
{
	//digits_offset is for div only
	int i_five = 5, ibuff;
	bool is_round = false;
	if (digits_limit_type == 1 || force_round == 1) is_round = true;
	if (force_round == 2) is_round = false;
	if (force_round == 3) {is_round = true; i_five = 0;}
	if (is_round) {
		if (static_cast<int>(bigint.size()) > i_sigd) {
			ibuff = static_cast<int>(bigint.size()-i_sigd-1);
			if (is_div) digits_offset -= ibuff+1;
			while (ibuff > 0) {bigint.pop_front(); --ibuff;}
			if (bigint[bigint.size()-i_sigd-1] >= i_five) {
				bigint.pop_front();
				bigint = add_f(bigint, Tve(1, 1));
			}
			else bigint.pop_front();
		}
	}
	else {
		if (static_cast<int>(bigint.size()) > i_sigd) {
			ibuff = static_cast<char>(bigint.size()-i_sigd);
			digits_offset -= ibuff;
			while (ibuff > 0) {bigint.pop_front(); --ibuff;}
		}
	}
	//tail zero
	if (!is_div) while (bigint.size() != 1 && bigint.front() == 0) bigint.pop_front();
}
////////////////
//significant_fix_point
////////////////
////////////////
void significant_fix_point(std::deque<char> &bigint, const int &poi_exp, const int &fix_point = 6, const int &force_round = 0)
{
	int i_sigd = poi_exp+fix_point;
	significant_fix(bigint, i_sigd, i_sigd, force_round);//first i_sigd is dummy
}
////////////////std::deque use
//divf_f, y = a/b (b!=0)
////////////////
////////////////from div_f
template <typename Tve>
Tve divf_f(const Tve &bigint, const Tve &di2, const bool &b_is_mod = false)
{
	int ibuff = 0, di_p_cou = 0, di_p_siz, difsize, i_sigd;
	unsigntp ix2;	
	difsize = static_cast<int>(bigint.size())-static_cast<int>(di2.size())+1;
	i_sigd= digits_precision-difsize+1;
	if (i_sigd < 0) i_sigd = 0;
	if (difsize < 1) {
		ibuff = -difsize+2;
		difsize = static_cast<int>(bigint.size());
	}
	//if rounding
	if (digits_limit_type == 1) ++i_sigd;
	//std::deque
	Tve bu1(bigint.begin()+difsize, bigint.end()), di_p(bigint.begin(), bigint.begin()+difsize), de_res;
	di_p_siz = static_cast<int>(di_p.size());
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
				de_res.push_front(static_cast<char>(ix2));
				ix2 = 10;
			}
		}
	}
	if (b_is_mod) return bu1;
	//remove zero
	while (de_res.back() == 0 && de_res.size() != 1) de_res.pop_back();
	//significant digits transfer
	i_sigd = di_p_cou-di_p_siz;
	//truncation or rounding
	if (digits_precision_affect == 2) significant_fix(de_res, i_sigd, digits_precision, 0, true);
	if (i_sigd != 0) {
		ibuff = i_sigd;
        if (i_sigd < 0) ibuff = -ibuff;
		de_res.push_back(101);
		while (ibuff > 0) {
			de_res.push_back(ibuff%100);
			ibuff = ibuff/100;
		}
		if (i_sigd > 0) de_res.push_back(101);
		else de_res.push_back(102);
	}
	return de_res;
}
////////////////
//gcd
////////////////
////////////////
int gcd(const int &v1_o, const int &v2_o)
{
	int v1 = v1_o, v2 = v2_o;
	while (v2 != 0) {int temp = v2; v2 = v1%v2; v1 = temp;}
	return v1;
}
//do not inherit
class floatbigdata
{
public:
	//Constructors:
	floatbigdata(): b_sign(true), bigint(1, 0), b_poi(1), b_exp(0) {};
	floatbigdata(const std::string &str1);//structure form std::string, can deal with scientific notation
	floatbigdata(const double &dou1_o);
	floatbigdata(const int &us1_o, const int &dummy);
	floatbigdata(const intbigdata &bus1);
	floatbigdata(const char *cstr1);
	floatbigdata(const std::deque<char> &di1, const int &bpi, const int &bep, const bool &bsn, const char &check_data);//inconvenience
	~floatbigdata() {};
	//Traditional arithmetics:
	floatbigdata add(const floatbigdata &bus2) const;
	floatbigdata sub(const floatbigdata &bus2) const;
	floatbigdata mul(const floatbigdata &bus2) const;
	void mul_self(const floatbigdata &bus2);
	floatbigdata div(const floatbigdata &bus2) const;
	//Power functions:
	floatbigdata pow_int(const int &ib) const;
	floatbigdata root_int(const int &n) const;
	floatbigdata pow(const double &ib, const bool &is_root) const;
	floatbigdata root(const double &ib) const;
	floatbigdata pow_frac(const int &nume, const int &deno, const bool &sign);
	//Exponential and logarithmic functions:
	//
	//Rounding and remainder functions:
	floatbigdata trunc(const int &digits, const bool &is_point) const;
	floatbigdata trunc_self(const int &digits, const bool &is_point);
	floatbigdata round(const int &digits, const bool &is_point) const;
	floatbigdata round_self(const int &digits, const bool &is_point);
	floatbigdata ceil(const int &digits, const bool &is_point) const;
	floatbigdata floor(const int &digits, const bool &is_point) const;
	//Operators:
	operator int() const;
	operator std::string() const;
	operator double() const;
	operator intbigdata() const;
	friend std::istream &operator>>(std::istream &in, floatbigdata &bus1);
	friend std::ostream &operator<<(std::ostream &out, const floatbigdata &bus1);
	//overload operators:
	floatbigdata &operator+=(const floatbigdata &bus2) {return *this = this->add(bus2);}
	floatbigdata &operator-=(const floatbigdata &bus2) {return *this = this->sub(bus2);}
	floatbigdata &operator*=(const floatbigdata &bus2) {return *this = this->mul(bus2);}
	floatbigdata &operator/=(const floatbigdata &bus2) {return *this = this->div(bus2);}
	friend bool operator==(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) == 0;}
	template <typename Tve> friend bool operator==(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == 0;}
	template <typename Tve> friend bool operator==(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) == 0;}
	friend bool operator!=(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) != 0;}
	template <typename Tve> friend bool operator!=(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != 0;}
	template <typename Tve> friend bool operator!=(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) != 0;}
	friend bool operator>(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) == 1;}
	template <typename Tve> friend bool operator>(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == 1;}
	template <typename Tve> friend bool operator>(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) == 1;}	
	friend bool operator>=(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) != -1;}
	template <typename Tve> friend bool operator>=(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != -1;}
	template <typename Tve> friend bool operator>=(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) != -1;}
	friend bool operator<(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) == -1;}
	template <typename Tve> friend bool operator<(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) == -1;}
	template <typename Tve> friend bool operator<(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) == -1;}
	friend bool operator<=(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.who_big(bus2) != 1;}
	template <typename Tve> friend bool operator<=(const floatbigdata &bus1, const Tve &ib2) {return bus1.who_big(ib2) != 1;}
	template <typename Tve> friend bool operator<=(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).who_big(bus2) != 1;}
	floatbigdata &operator+() {return *this;}
	floatbigdata &operator-() {b_sign = !b_sign; return *this;}
	//Modifiers:
	void assign(const intbigdata &bus2);
	void assign(const floatbigdata &bus2);
	void assign(const std::string &str1);
	void assign_int(const int &us1);
	void assign(const double &us1);
	void assign(const char *cstr1);
	void swap(floatbigdata &bus2);
	void clear();
	//Class operators:
	std::string scientific(const int &i_point) const;//scientific notation
	int save_file(const std::string file_name_o, const std::string file_msg_o) const;
	int load_file(const std::string &file_name);
	int get_int() const;
	double get_double() const;
	std::string get_string() const;
	//Capacity:
	unsigntp size() const;
	unsigntp max_size() const;
	//Objects:
	bool b_sign;
	std::deque<char> bigint;
	int b_poi;//point position
	int b_exp;//exponent
	//Compare:
	int who_big(const floatbigdata &bus2) const;
	bool is_zero() const;
	void fix_data();
	bool is_not_corrupt() const;	
private:
	//Constructors:
	floatbigdata(const std::vector<char> &di1, const bool &di1_sign);
};
//nonmember operators overload
//overload operators:
inline floatbigdata operator+(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.add(bus2);}
template <typename Tve> inline floatbigdata operator+(const floatbigdata &bus1, const Tve &ib2) {return bus1.add(ib2);}
template <typename Tve> inline floatbigdata operator+(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).add(bus2);}
inline floatbigdata operator-(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.sub(bus2);}
template <typename Tve> inline floatbigdata operator-(const floatbigdata &bus1, const Tve &ib2) {return bus1.sub(ib2);}
template <typename Tve> inline floatbigdata operator-(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).sub(bus2);}
inline floatbigdata operator*(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.mul(bus2);}
template <typename Tve> inline floatbigdata operator*(const floatbigdata &bus1, const Tve &ib2) {return bus1.mul(ib2);}
template <typename Tve> inline floatbigdata operator*(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).mul(bus2);}
inline floatbigdata operator/(const floatbigdata &bus1, const floatbigdata &bus2) {return bus1.div(bus2);}
template <typename Tve> inline floatbigdata operator/(const floatbigdata &bus1, const Tve &ib2) {return bus1.div(ib2);}
template <typename Tve> inline floatbigdata operator/(const Tve &ib1, const floatbigdata &bus2) {return floatbigdata(ib1).div(bus2);}
////////////////
//global var
////////////////
////////////////
const floatbigdata floatbigdata_one(std::deque<char>(1, 1), 1, 0, true, 'n');
bool normal_stream = false;
int i_dummy = 0;
// (\__/)
//(='.'=)
//(")_(") member
////////////////
//Constructors:
////////////////////////////////
//structure2 std::deque
floatbigdata::floatbigdata(const std::deque<char> &di1, const int &bpi = 0, const int &bep = 0,
	const bool &bsn = true, const char &check_data = 'n')
{
	//sign
	b_sign = bsn;
	bigint = di1;
	b_poi = bpi;
	if (bpi == -1) b_poi = static_cast<int>(bigint.size());
	b_exp = bep;
	if (bigint.empty()) {bigint.push_back(0); b_sign = true; b_poi = 1; b_exp = 0;}	
	//check data and fix
	if (check_data == 'y') this->fix_data();
	//remove tail zero
	if (check_data == 'n') {
		while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
	}
	//for div, rounding and significant fix
	if (check_data == 'd' && bigint.back()-100 > 0) {
		bool digit_sign = true;
		if (bigint.back() == 102) digit_sign = false;
		bigint.pop_back();
		int i_count = 1, ibuff = 0;
		while (bigint.back() != 101 && bigint.size() != 1) {
			ibuff = ibuff*i_count+bigint.back();
			i_count *= 100;
			bigint.pop_back();
			--b_poi;
		}
		bigint.pop_back();
		if (digit_sign) b_poi -= ibuff+2;
		else b_poi -= -ibuff+2;
	}
	//other lim
	else {
		if (digits_precision_affect == 2) {
			significant_fix(bigint, i_dummy);
		}
	}
	//is zero
	if (bigint.size() == 1 && bigint[0] == 0) {b_sign = true; b_poi = 1; b_exp = 0;}
}
//structure3 std::string
floatbigdata::floatbigdata(const std::string &str1)
{
	//"0123456789" will check converting
	std::string s_number("0123456789");
	bool ignore_e = true;
	//judge scientific notation
	std::string::size_type s_ixe = 0, s_ixn, s_ixn2, s_ixp, s_ixbu;
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
		std::string s_expo(str1, s_ixe+1), str1_p(str1, 0, s_ixe);
		s_expo += '#';
		//fix std::string data
		int i_expo = static_cast<int>(intbigdata(s_expo));
		str1_p += '#';
		*this = floatbigdata(str1_p);
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
			if (s_ixn2 != std::string::npos) {bigint.push_back(static_cast<char>(s_ixn2)); ++s_ixbu;}
			if (s_ixp == 0 && str1[s_ixn-1] == '.') s_ixp = s_ixbu;
		}
		if (bigint.empty()) bigint.push_back(0);
		//remove zero
		if (s_ixp != 0) {
			s_ixp = s_ixbu-s_ixp;
			s_ixbu = 0;
			std::deque<char>::const_reverse_iterator v_it;
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
		}
		//remove tail zero
		while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
		//zero no sign
		if (bigint.size() == 1 && bigint[0] == 0) {b_sign = true; b_poi = 1; b_exp = 0;}
	}
}
//structure4 int
floatbigdata::floatbigdata(const int &us1_o, const int &dummy)
{
	DUMMY(dummy);
	int us1;
	//sign
	if (us1_o < 0) {b_sign = false; us1 = -us1_o;}
	else {b_sign = true; us1 = us1_o;}
	while (us1 != 0) {bigint.push_back(us1%10); us1 /= 10;}
	if (us1_o == 0) bigint.push_back(0);
	b_poi = static_cast<int>(bigint.size());
	b_exp = 0;
	//remove tail zero
	while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
}
//structure5 c style std::string
inline floatbigdata::floatbigdata(const char *cstr1)
{
	*this = floatbigdata(std::string(cstr1));
}
//structure7 double
floatbigdata::floatbigdata(const double &dou1_o)
{
	std::ostringstream ostri;
	normal_stream = true;
	ostri << dou1_o;
	normal_stream = false;
	*this = floatbigdata(ostri.str());
}
//structure8 intbigdata
inline floatbigdata::floatbigdata(const intbigdata &bus1)
{
	*this = floatbigdata(std::deque<char>(bus1.bigint.begin(), bus1.bigint.end()), -1, 0, bus1.b_sign, 'n');
}
////////////////
//Compare:
////////////////////////////////
//who_big, compare value, return 1 = first big, -1 = second big, 0 = equal
int floatbigdata::who_big(const floatbigdata &bus2) const
{
	//sign
	if (b_sign == true && bus2.b_sign == false) return 1;
	if (b_sign == false && bus2.b_sign == true) return -1;
	int b_exp1 = b_exp, b_exp2 = bus2.b_exp, i_who_big;
	if (b_poi > bus2.b_poi) b_exp1 += b_poi-bus2.b_poi;
	if (bus2.b_poi > b_poi) b_exp2 += bus2.b_poi-b_poi;
	if (b_sign) {if (b_exp1 > b_exp2) return 1; if (b_exp2 > b_exp1) return -1;}
	if (!b_sign) {if (b_exp1 < b_exp2) return 1; if (b_exp2 < b_exp1) return -1;}
	i_who_big = abso_big(bigint, bus2.bigint);
	if (b_sign == false && bus2.b_sign == false) i_who_big = -i_who_big;
	return i_who_big;
}
//is_zero
bool floatbigdata::is_zero() const
{
	if (bigint.size() == 1 && bigint[0] == 0) return true;
	//skip check sign, point, exponent
	return false;
}
//fix_data
void floatbigdata::fix_data()
{
	if (bigint.empty()) bigint.push_back(0);
	std::deque<char>::reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0) *rit_de = -*rit_de;
		if (*rit_de > 9) *rit_de = *rit_de%10;
		++rit_de;
	}
	//remove tail zero
	while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
	while (bigint.back() == 0 && bigint.size() != 1) bigint.pop_back();
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) b_sign = true;
	//
	if (b_poi < 0) b_poi = 0;
}
//is_not_corrupt
bool floatbigdata::is_not_corrupt() const
{
	if (bigint.empty()) return false;
	std::deque<char>::const_reverse_iterator rit_de = bigint.rbegin();
	while (rit_de != bigint.rend()) {
		if (*rit_de < 0 || *rit_de > 9) return false;
		++rit_de;
	}
	//remove tail zero
	if (bigint.front() == 0 && bigint.size() != 1) return false;
	if (bigint.back() == 0 && bigint.size() != 1) return false;
	//zero no sign
	if (bigint.size() == 1 && bigint[0] == 0 && b_sign == false) return false;
	//
	if (b_poi < 0) return false;
	return true;
}
////////////////
//Traditional arithmetics:
////////////////////////////////
//arithmetic encapsulate
//add, sub, mul, div, pow
//add
floatbigdata floatbigdata::add(const floatbigdata &bus2) const
{
	int i_offset, i_exp, ibuff;
	std::deque<char> bus_temp;
	ibuff = pre_faddsub(bigint, bus2.bigint, bus_temp, i_offset, i_exp, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	if (ibuff == 1) return floatbigdata(bigint, b_poi, b_exp, b_sign, 'n');
	if (ibuff == 2) return floatbigdata(bus2.bigint, bus2.b_poi, bus2.b_exp, bus2.b_sign, 'n');
	const std::deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	//sign
	if (b_sign == bus2.b_sign) return floatbigdata(add_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, 'n');
	else {
		ibuff = abso_big(*bus1_p, *bus2_p);
		if (ibuff == 1) return floatbigdata(sub_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, 'n');
		if (ibuff == -1) return floatbigdata(sub_f(*bus2_p, *bus1_p), -1, i_exp, bus2.b_sign, 'n');
	}
	return floatbigdata();
}
//sub
floatbigdata floatbigdata::sub(const floatbigdata &bus2) const
{
	int i_offset, i_exp, ibuff;
	std::deque<char> bus_temp;
	ibuff = pre_faddsub(bigint, bus2.bigint, bus_temp, i_offset, i_exp, b_poi, bus2.b_poi, b_exp, bus2.b_exp);
	if (ibuff == 1) return floatbigdata(bigint, b_poi, b_exp, b_sign, 'n');
	if (ibuff == 2) return floatbigdata(bus2.bigint, bus2.b_poi, bus2.b_exp, bus2.b_sign, 'n');
	const std::deque<char> *bus1_p = &bigint, *bus2_p = &bus2.bigint;
	if (i_offset < 0) bus1_p = &bus_temp;
	if (i_offset > 0) bus2_p = &bus_temp;
	//sign
	if (b_sign != bus2.b_sign) return floatbigdata(add_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, 'n');
	else {
		ibuff = abso_big(*bus1_p, *bus2_p);
		if (ibuff == 1) return floatbigdata(sub_f(*bus1_p, *bus2_p), -1, i_exp, b_sign, 'n');
		if (ibuff == -1) return floatbigdata(sub_f(*bus2_p, *bus1_p), -1, i_exp, !bus2.b_sign, 'n');
	}
	return floatbigdata();
}
//mul
floatbigdata floatbigdata::mul(const floatbigdata &bus2) const
{
	int i_exp = static_cast<int>((b_poi+b_exp)-bigint.size()+(bus2.b_poi+bus2.b_exp)-bus2.bigint.size());
	//sign
	return floatbigdata(mul_f(bigint, bus2.bigint), -1, i_exp, b_sign == bus2.b_sign, 'n');
}
//mul_self
void floatbigdata::mul_self(const floatbigdata &bus2)
{
	int i_exp = static_cast<int>((b_poi+b_exp)-bigint.size()+(bus2.b_poi+bus2.b_exp)-bus2.bigint.size());
	mul_fself(bigint, bus2.bigint);
	//sign
	b_poi = static_cast<int>(bigint.size());
	b_exp = i_exp;
	b_sign = (b_sign == bus2.b_sign);
	//remove tail zero
	while (bigint.front() == 0 && bigint.size() != 1) bigint.pop_front();
	if (digits_precision_affect == 2) significant_fix(bigint, i_dummy);
}
//div
floatbigdata floatbigdata::div(const floatbigdata &bus2) const
{
	if (bus2.is_zero()) throw intbigdata_error();
	//
	int i_exp = static_cast<int>((b_poi+b_exp)-bigint.size()-(bus2.b_poi+bus2.b_exp)+bus2.bigint.size());
	return floatbigdata(divf_f(bigint, bus2.bigint, false), -1, i_exp, b_sign == bus2.b_sign, 'd');
}
////////////////
////Power functions:
////////////////////////////////
//pow_int
floatbigdata floatbigdata::pow_int(const int &ib) const
{
	floatbigdata ret;
	int ibx = ib;
	if (ib == 0) {ret.bigint[0] = 1; return ret;}
	if (ib < 0) ibx = -ibx;
	if (ibx%2 == 1) ret.b_sign = b_sign;	
	ret = *this;
	for (int ixc = 1; ixc != ibx; ++ixc) {
		ret.mul_self(*this);
	}
	if (ib < 0) return floatbigdata_one.div(ret);
	return ret;
}
//root_int, method: paper-and-pencil nth roots
floatbigdata floatbigdata::root_int(const int &n_o) const
{
	if (n_o == 0) throw intbigdata_error();
	if (n_o == 1) return *this;
	if (n_o == -1) return floatbigdata_one.div(*this);
	//wikipedia.org: paper-and-pencil nth roots
	floatbigdata y;
	int n = n_o, size_fix = static_cast<int>(bigint.size()), rad_p = b_poi+b_exp, preci = 0, offset2 = 0,
		iwhobig = 1, offset1 = 0, offset_f = 0, ibuff;
	if (n < 0) n = -n;
	if (n%2 == 1) y.b_sign = b_sign;
	else if (!b_sign) std::cerr << "intbigdata.h: imaginary number" << std::endl;
	//
	if (rad_p > 0) {
		offset1 = rad_p%n;
		if (bigint.size() < rad_p) size_fix = rad_p;
		if (size_fix > rad_p) offset2 = (size_fix-rad_p)%n;
	}
	else {
		offset1 = n-(-rad_p)%n;
		if (offset1 < 0) offset1 = -offset1;
		if (size_fix < offset1) offset_f = offset1-size_fix;
		else offset2 = (size_fix-offset1)%n;
		if (offset2 < 0) offset2 = -offset2;
	}
	preci = digits_precision+1-(size_fix+offset1+offset2+offset_f)/n;
	if (preci < 0) preci = 0;
	else preci = preci*n;
	//take apart
	std::deque<char> base_pn(n, 0), beta(1, 0), proc1, proc2, base_y, pick_t, pick_t_setp, pick1, pick2;
	if (size_fix == bigint.size()) {
		ibuff = size_fix-offset1;
		if (ibuff < 0) ibuff = 0;
		proc1.assign(bigint.begin()+ibuff, bigint.end());
		for(int ix = 0; ix != offset_f; ++ix) proc1.push_front(0);
		if (size_fix-offset1 > 0) proc2.assign(bigint.begin(), bigint.begin()+size_fix-offset1);
	}
	else {
		pick_t = bigint;
		for (int ix = 0; ix != size_fix-bigint.size(); ++ix) pick_t.push_front(0);
		proc1.assign(pick_t.begin()+size_fix-offset1, pick_t.end());
		proc2.assign(pick_t.begin(), pick_t.begin()+size_fix-offset1);
	}
	//
	for (int ix = 0; ix != preci-offset2; ++ix) proc2.push_front(0);
	base_pn.push_back(1);
	std::deque<char>::const_reverse_iterator rit = proc2.rbegin();
	bool proc_go = false;
	y.b_poi = rad_p/n;
	if (offset1 != 0) ++y.b_poi;
	if (rad_p <= 0) --y.b_poi;
	if (proc1.empty()) proc_go = true;
	//loop
	while (rit != proc2.rend()) {
		if (proc_go) for (int ix = 0; ix != n; ++ix) proc1.push_front(*rit++);
		while (proc1.size() != 1 && proc1.back() == 0) proc1.pop_back();
		pick_t.assign(1, 0);
		iwhobig = 1;
		base_y = y.bigint;
		if (y.bigint.size() == 1 && y.bigint[0] == 0) base_y = y.bigint;
		else base_y.push_front(0);
		pick2 = mul_f(base_pn, pow_f(y.bigint, n));
		beta[0] = 0;
		//
		while (iwhobig == 1) {
			pick_t_setp = pick_t;
			++beta[0];
			pick1 = pow_f(add_f(base_y, beta), n);
			pick_t = sub_f(pick1, pick2);
			iwhobig = abso_big(proc1, pick_t);
		}
		//
		if (iwhobig == 0) {
			proc1.assign(1, 0);
			if (y.bigint.size() == 1 && y.bigint[0] == 0) y.bigint[0] = beta[0];
			else y.bigint.push_back(beta[0]);
		}
		else {
			sub_fself(proc1, pick_t_setp);
			if (y.bigint.size() == 1 && y.bigint[0] == 0) y.bigint[0] = --beta[0];
			else y.bigint.push_front(--beta[0]);
		}
		proc_go = true;
	}
	if (n_o < 0) return floatbigdata_one.div(y);
	return y;
}
//pow
floatbigdata floatbigdata::pow(const double &ib, const bool &is_root = false) const
{
	float dou1 = static_cast<float>(ib);
	if (ib < 0) dou1 = -dou1;
	int i2 = 1, i1, i_gcd;
	//float*10 will lost precision sometimes
	while (dou1-static_cast<int>(dou1+0.000001) > 0) {i2 *= 10; dou1 *= 10.0;}
	i1 = static_cast<int>(dou1+0.000001);
	i_gcd = gcd(i1, i2);
	i1 = i1/i_gcd;
	i2 = i2/i_gcd;
	if (is_root) {i_gcd = i1; i1 = i2; i2 = i_gcd;}
	//
	floatbigdata ret(*this);
	if (ib > 0) return (ret.root_int(i2)).pow_int(i1);
	if (ib < 0) return floatbigdata_one.div((ret.root_int(i2)).pow_int(i1));
	return floatbigdata_one;
}
//root
inline floatbigdata floatbigdata::root(const double &ib) const
{
	return this->pow(ib, true);
}
//pow_frac
floatbigdata floatbigdata::pow_frac(const int &nume, const int &deno, const bool &sign = true)
{
	floatbigdata ret(*this);
	if (sign) return (ret.root_int(deno)).pow_int(nume);
	if (!sign) return floatbigdata_one.div((ret.root_int(deno)).pow_int(nume));
	return floatbigdata_one;
}
////////////////
////Rounding and remainder functions:
////////////////////////////////
//trunc
floatbigdata floatbigdata::trunc(const int &digits, const bool &is_point = false) const
{
	floatbigdata ret(*this);
	if (is_point) significant_fix_point(ret.bigint, b_poi+b_exp, digits, 2);
	else significant_fix(ret.bigint, i_dummy, digits, 2);
	return ret;
}
//trunc_self
floatbigdata floatbigdata::trunc_self(const int &digits, const bool &is_point = false)
{
	if (is_point) significant_fix_point(bigint, b_poi+b_exp, digits, 2);
	else significant_fix(bigint, i_dummy, digits, 2);
	return *this;
}
//round
floatbigdata floatbigdata::round(const int &digits, const bool &is_point = false) const
{
	floatbigdata ret(*this);
	if (is_point) significant_fix_point(ret.bigint, b_poi+b_exp, digits, 1);
	else significant_fix(ret.bigint, i_dummy, digits, 1);
	return ret;
}
//round_self
floatbigdata floatbigdata::round_self(const int &digits, const bool &is_point = false)
{
	if (is_point) significant_fix_point(bigint, b_poi+b_exp, digits, 1);
	else significant_fix(bigint, i_dummy, digits, 1);
	return *this;
}
//ceil
floatbigdata floatbigdata::ceil(const int &digits, const bool &is_point = false) const
{
	floatbigdata ret(*this);
	int round_type = 3;
	if (!b_sign) round_type = 2;
	if (is_point) significant_fix_point(ret.bigint, b_poi+b_exp, digits, round_type);
	else significant_fix(ret.bigint, i_dummy, digits, round_type);
	return ret;
}
//floor
floatbigdata floatbigdata::floor(const int &digits, const bool &is_point = false) const
{
	floatbigdata ret(*this);
	int round_type = 2;
	if (!b_sign) round_type = 3;
	if (is_point) significant_fix_point(ret.bigint, b_poi+b_exp, digits, round_type);
	else significant_fix(ret.bigint, i_dummy, digits, round_type);
	return ret;
}
////////////////
//Operators:
////////////////////////////////
//operator int()
floatbigdata::operator int() const
{
	int ret;
	std::ostringstream ostri;
	normal_stream = true;
	ostri << *this;
	normal_stream = false;
	std::istringstream istri(ostri.str());
	istri >> ret;
	return ret;
}
//operator std::string()
floatbigdata::operator std::string() const
{
	std::ostringstream ostri;
	normal_stream = true;
	ostri << *this;
	normal_stream = false;
	return ostri.str();
}
//operator double()
floatbigdata::operator double() const
{
	double ret;
	std::ostringstream ostri;
	normal_stream = true;
	ostri << *this;
	normal_stream = false;
	std::istringstream istri(ostri.str());
	istri >> ret;
	return ret;
}
//operator intbigdata()
floatbigdata::operator intbigdata() const
{
	return intbigdata(std::string(this->trunc(0, true)));
}
//std::istream &operator>>
std::istream &operator>>(std::istream &in, floatbigdata &bus1)
{
	std::string str1;
	bus1.bigint.clear();
	in >> str1;
	//sign
	bus1.b_sign = true;
	if (str1[0] == '-') bus1.b_sign = false;
	std::string::reverse_iterator s_it = str1.rbegin();
	if (in) bus1 = floatbigdata(str1);
	else bus1.bigint.push_back(0);
	return in;
}
//std::ostream &operator<<
std::ostream &operator<<(std::ostream &out, const floatbigdata &bus1)
{
	//scientific
	if (cout_type == 2 && !normal_stream) {
		out << bus1.scientific(cout_scientific);
		return out;
	}
	const floatbigdata *intf_p = &bus1;
	floatbigdata intf_temp;
	int i_poi_fix = 0, ibuff;
	bool poi_couted = false;
	//fixed
	if (cout_type == 3 && !normal_stream) {
		ibuff = bus1.b_poi+bus1.b_exp;
		if (-ibuff <= cout_fixed && static_cast<int>(bus1.bigint.size())-ibuff > cout_fixed) {
			intf_temp = bus1;
			if (digits_limit_type == 1) intf_temp.round_self(cout_fixed, true);
			else intf_temp.trunc_self(cout_fixed, true);
			intf_p = &intf_temp;
		}
		if (-ibuff > cout_fixed) {
			//is zero
			intf_p = &intf_temp;
			ibuff = 1;
		}
		i_poi_fix = cout_fixed-static_cast<int>(((*intf_p).bigint.size())-ibuff);
	}
	std::deque<char>::const_reverse_iterator rit_de = (*intf_p).bigint.rbegin();
	//sign
	if ((*intf_p).b_sign == false) out << '-';
	ibuff = (*intf_p).b_poi+bus1.b_exp;
	if (ibuff <= 0) {
		if ((*intf_p).bigint.size() == 1 && (*intf_p).bigint.back() == 0) out << '0';
		else {
			out << "0.";
			poi_couted = true;
			while (ibuff < 0) {out << '0'; ++ibuff;}
			while (rit_de != (*intf_p).bigint.rend()) out << (int)*rit_de++;
		}
	}
	else {
		if (ibuff != (*intf_p).bigint.size()) {
			if (static_cast<int>((*intf_p).bigint.size()) > ibuff) {
				while (rit_de != (*intf_p).bigint.rbegin()+ibuff) out << (int)*rit_de++;
				out << '.';
				poi_couted = true;
				while (rit_de != (*intf_p).bigint.rend()) out << (int)*rit_de++;
			}
			else {
				ibuff = ibuff-static_cast<int>((*intf_p).bigint.size());
				while (rit_de != (*intf_p).bigint.rend()) out << (int)*rit_de++;
				for (int ix = 0; ix != ibuff; ++ix) out << '0';
			}
		}
		else while (rit_de != (*intf_p).bigint.rend()) out << (int)*rit_de++;
	}
	if (i_poi_fix > 0 && !poi_couted) out << '.';
	while (i_poi_fix > 0) {out << '0'; --i_poi_fix;}
	return out;
}
////////////////
//Modifiers:
////////////////////////////////
//assign1
inline void floatbigdata::assign(const intbigdata &bus2)
{
	*this = floatbigdata(std::deque<char>(bus2.bigint.begin(), bus2.bigint.end()), -1, 0, bus2.b_sign, 'n');
}
//assign2 overload
void floatbigdata::assign(const floatbigdata &bus2)
{
	//sign
	b_sign = bus2.b_sign;
	bigint = bus2.bigint;
	b_poi = bus2.b_poi;
	b_exp = bus2.b_exp;	
}
//assign3 overload
inline void floatbigdata::assign(const std::string &str1)
{
	*this = floatbigdata(str1);
}
//assign4 overload
inline void floatbigdata::assign_int(const int &us1)
{
	*this = floatbigdata(us1);
}
//assign5 overload 
inline void floatbigdata::assign(const double &us1)
{
	*this = floatbigdata(us1);
}
//assign6 overload
inline void floatbigdata::assign(const char *cstr1)
{
	*this = floatbigdata(std::string(cstr1));
}
//swap
void floatbigdata::swap(floatbigdata &bus2)
{
	bigint.swap(bus2.bigint);
	bool b_temp = b_sign;
	b_sign = bus2.b_sign;
	bus2.b_sign = b_temp;
	int b_poi_t = b_poi, b_exp_t = b_exp;
	b_poi = bus2.b_poi;
	bus2.b_poi = b_poi_t;
	b_exp = bus2.b_exp;
	bus2.b_exp = b_exp_t;
}
//clear, assign 0
void floatbigdata::clear()
{
	bigint.assign(1, 0);
	b_sign = true;
	b_poi = 1;
	b_exp = 0;
}
////////////////
//Class operators:
////////////////////////////////
//scientific
std::string floatbigdata::scientific(const int &i_point = 6) const
{
	std::string s_number("0123456789"), s_temp, s_scient;
	unsigntp i1_get = i_point, ixsz = bigint.size()-1, ix1;
	//decimal point reserve
	if (i_point < 1) i1_get = 6;
	if (static_cast<unsigned>(i_point) > ixsz) i1_get = ixsz;
	//sign
	if (b_sign == false) s_scient += '-';
	floatbigdata i_round;
	//round
	i_round.bigint.assign(bigint.begin()+(ixsz-i1_get), bigint.end());
	if (i1_get != ixsz) {
		if (bigint[ixsz-i1_get-1] > 4) i_round.bigint = add_f(i_round.bigint, std::deque<char>(1, 1));
	}
	//remove tail zero
	for (ix1 = 0; ix1 != i_round.bigint.size(); ++ix1) if (i_round.bigint[ix1] != 0) break;
	std::deque<char>::reverse_iterator d_it = i_round.bigint.rbegin();
	for (; d_it != i_round.bigint.rbegin()+(i_round.bigint.size()-ix1); ++d_it) {
		s_temp += s_number[*d_it];
	}
	if (s_temp.empty()) s_temp = '0';
	s_scient += s_temp[0];
	if (s_temp.size() != 1) {
		s_scient += '.';
		s_scient.append(s_temp, 1, s_temp.size()-1);
	}
	s_scient += "e";
	//s_temp clear
	s_temp.clear();
	int ibuff = b_poi+b_exp-1;
	if (ibuff < 0) {s_scient += "-"; ibuff = -ibuff;}
	else s_scient += "+";
	if (ibuff == 0) s_temp = '0';
	while (ibuff != 0) {s_temp = s_number[ibuff%10]+s_temp; ibuff /= 10;}
	s_scient += s_temp;
	return s_scient;
}
//save_file
int floatbigdata::save_file(const std::string file_name_o = "auto", const std::string file_msg_o = "nomessage") const
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
	outfile << static_cast<std::string>(*this);
	outfile.close();
	outfile.clear();
	return 0;
}
//load_file
int floatbigdata::load_file(const std::string &file_name)
{
	std::string::size_type pos1, pos2;
	int is_comm = 0;
	std::string s_line, s_lineadd;
	std::ifstream infile(file_name.c_str());
	if (!infile) {std::cerr << "floatbigdata.h: open file faile" << std::endl; return -1;}
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
inline int floatbigdata::get_int() const
{
	return int(*this);
}
//get_double
inline double floatbigdata::get_double() const
{
	return double(*this);
}
//get_string
inline std::string floatbigdata::get_string() const
{
	return std::string(*this);
}
////////////////
//Capacity:
////////////////////////////////
//size
inline unsigntp floatbigdata::size() const
{
	return bigint.size();
}
//max_size
inline unsigntp floatbigdata::max_size() const
{
	return bigint.max_size();
}
}//namespace intbigd
//
////////////////
//exception or std::cerr: div, save_file, load_file, root_int
////////////////
////////////////
#endif