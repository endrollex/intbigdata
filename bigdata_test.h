////////////////
//bigdata_test.h
//Some functions are being tested in intbigdata.h and floatbigdata.h
////////////////
////////////////
#ifndef BIGDATA_TEST_H
#define BIGDATA_TEST_H
namespace bigdata {namespace h_func
{
//skip tab
////////////////
//karatsuba algorithm
////////////////
////////////////test version, this function is not fit intbigdata's architecture yet
unsigned m_comp = 10, m_fix = 2;
template <typename Tve>
Tve karatsuba(const Tve &num1, const Tve &num2)
{
	unsigned num1siz = num1.size(), num2siz = num2.size(), m;
	if (num1siz < m_comp || num2siz < m_comp) return mul_f(num1, num2);
	m = num1siz > num2siz ? num2siz-m_fix : num1siz-m_fix;
	Tve low1(num1.begin(), num1.begin()+m), high1(num1.begin()+m, num1.end()),
		low2(num2.begin(), num2.begin()+m), high2(num2.begin()+m, num2.end()),
		z0, z1, z2;
	z2 = karatsuba(high1, high2);
	z0 = karatsuba(low1, low2);
	z1 = sub_f(sub_f(karatsuba(add_f(low1, high1), add_f(low2, high2)), z2), z0);
	Tve base1p(m*2, 0), base2p(m , 0);
	base1p.push_back(1);
	base2p.push_back(1);
	return add_f(add_f(mul_f(z2, base1p), mul_f(z1, base2p)), z0);
}
////////////////
//test ln
////////////////
////////////////
double ln_calc_test(const double &z, const int &n)
{
	double ret = 0.0;
	double zs1 = z-1;
	for (int ix = 1; ix != n+1; ++ix) {
		if (ix%2 == 1) ret += pow(zs1, ix)/ix;
		else ret -= pow(zs1, ix)/ix;
	}
	return ret;
}
////////////////
//test ln
////////////////
////////////////
floatbigdata ln_calc_test2(const floatbigdata &z, const int &n)
{
	floatbigdata ret = 0.0;
	floatbigdata zs1 = z-1;
	for (int ix = 1; ix != n+1; ++ix) {
		if (ix%2 == 1) ret += zs1.pow(ix)/ix;
		else ret -= zs1.pow(ix)/ix;
	}
	return ret;
}
////////////////
//test ln
////////////////
////////////////
floatbigdata ln_calc_test3(const floatbigdata &z, const int &n)
{
	floatbigdata ret = 0.0;
	floatbigdata zs1 = (z-1)/(z+1);
	for (int ix = 1; ix < n+1; ix += 2) {
		ret += zs1.pow_int(ix)/ix;
	}
	return 2*ret;
}
////////////////
//echo float info
////////////////
////////////////
void echo_i(const floatbigdata &ibf)
{
	std::cout << ibf << "\nsize " << ibf.size() << " poi " << ibf.b_poi << " exp " << ibf.b_exp << std::endl;
}
//
}}
#endif