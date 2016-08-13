#include "Integer.h"

#include <regex>
#include <algorithm>
#include <functional>
#include <cassert>

using namespace std;

const char* xiaoma::DivideByZero::what() const throw()
{
	return "除0错误";
}

const char* xiaoma::Str2IntegerErr::what() const throw()
{
	return "字符串无法转化为整数";
}

xiaoma::Integer::Integer()
{
	_d.clear();
	sign = true;
}

xiaoma::Integer::Integer(long long num)
	:Integer()
{
	if (num < 0)
	{
		sign = false;
		num = -num;
	}
	while (num)
	{
		_d.push_back(num % 10);
		num /= 10;
	}
}

xiaoma::Integer::Integer(const std::string &str) throw (Str2IntegerErr)
	:Integer()
{
	Integer();
	regex reg("[+,-]?[0-9]+");
	if (!regex_match(str, reg))
	{
		throw Str2IntegerErr();
	}
	if (str[0] == '-')
	{
		sign = false;
	}
	else
	{
		sign = true;
	}
	int i = 0;
	if (str[0]=='+' || str[0]=='-')
	{
		i++;
	}
	for (int j=str.size()-1; j>=i; j--)
	{
		_d.push_back(str[j] - '0');
	}
	remove_front_zeros();
}

xiaoma::Integer::Integer(const Integer& num)
	:Integer()
{
	_d = num._d;
	sign = num.sign;
}

xiaoma::Integer::Integer(Integer&& num)
{
	sign = num.sign;
	_d.swap(num._d);
}

xiaoma::Integer& xiaoma::Integer::operator=(long long num)
{
	Integer t(num);
	sign = t.sign;
	_d = t._d;
	return *this;
}

xiaoma::Integer& xiaoma::Integer::operator=(const std::string &str) throw (Str2IntegerErr)
{
	Integer t(str);
	sign = t.sign;
	_d = t._d;
	return *this;
}

xiaoma::Integer& xiaoma::Integer::operator=(const Integer& num)
{
	if (this != &num)
	{
		sign = num.sign;
		_d = num._d;
	}
	return *this;
}

xiaoma::Integer& xiaoma::Integer::operator=(Integer&& num)
{
	assert(this != &num);
	sign = num.sign;
	_d.swap(num._d);
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator+(const Integer &b) const
{
	if (sign && b.sign)
	{
		Integer c;
		//两个正数
		c._d.reserve(max(_d.size(), b._d.size()) + 1);
		unsigned char jinwei = 0;
		auto iter1 = _d.begin();
		auto iter2 = b._d.begin();
		while (iter1!=_d.end() || iter2!=b._d.end())
		{
			unsigned char t = (iter1 == _d.end() ? 0 : *iter1++) + \
				(iter2 == b._d.end() ? 0 : *iter2++) + jinwei;
			c._d.push_back(t % 10);
			jinwei = t >= 10 ? 1 : 0;
		}
		if (jinwei)
		{
			c._d.push_back(jinwei);
		}
		return c;
	}
	else if(!sign && !b.sign)
	{
		// 两个负数
		return -((-(*this) + (-b)));
	}
	else if (!sign)
	{
		// a为负数，b为正数
		return b - (-(*this));
	}
	else
	{
		// a为正数，b为负数
		return ((*this)) - (-b);
	}
}

xiaoma::Integer& xiaoma::Integer::operator++()
{
	*this = (*this) + 1;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator++(int)
{
	Integer t(*this);
	operator++();
	return t;
}

xiaoma::Integer& xiaoma::Integer::operator+=(const Integer &b)
{
	*this = (*this) + b;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator-(const Integer &b) const
{
	if (sign && b.sign)
	{
		//两个正数
		Integer c;
		if (*this >= b)
		{
			c._d.reserve(_d.size());
			bool jiewei = false;
			auto iter1 = _d.begin();
			auto iter2 = b._d.begin();
			while (iter1 != _d.end())
			{
				char t = char(*iter1++) - (jiewei ? 1 : 0) - char(iter2 == b._d.end() ? 0 : *iter2++);
				if (t < 0)
				{
					t += 10;
					jiewei = true;
				}
				c._d.push_back(t);
			}
			c.remove_front_zeros();
			return c;
		}
		else
		{
			return -((b - (*this)));
		}
	}
	else if (!sign && !b.sign)
	{
		// 两个负数
		return -((-(*this) +b));
	}
	else if (!sign)
	{
		// a为负数，b为正数
		return -((-(*this) + b));
	}
	else
	{
		// a为正数，b为负数
		return ((*this) + (-b));
	}
}

xiaoma::Integer& xiaoma::Integer::operator--()
{
	*this = (*this) - 1;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator--(int)
{
	Integer t(*this);
	operator--();
	return t;
}

xiaoma::Integer& xiaoma::Integer::operator-=(const Integer &b)
{
	*this = (*this) - b;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator-() const
{
	Integer t(*this);
	if (!t._d.empty())
	{
		t.sign = !t.sign;
	}
	return t;
}

xiaoma::Integer xiaoma::Integer::operator*(const Integer &b) const
{
	Integer c;
	if (_d.empty() || b._d.empty())
	{
		// 乘以0，得0
		return c;
	}
	if ((*b._d.rbegin() == 1) && (find_if(b._d.begin(), b._d.end(), [](unsigned char c) {return c != 0;}) == b._d.end()))
	{
		// 乘以十的倍数
		c._d.resize(b._d.size() - 1);
		fill(c._d.begin(), c._d.end(), 0);
		c._d.insert(c._d.end(), _d.begin(), _d.end());
		return c;
	}
	else if (b._d.size()==1)
	{
		c._d.reserve(_d.size() + 1);
		unsigned char jinwei = 0;
		int t = 0;
		for (auto iter = _d.begin(); iter!=_d.end(); iter++)
		{
			t = jinwei + int(*iter) * int(b._d[0]);
			c._d.push_back(t % 10);
			jinwei = t / 10;
		}
		if (jinwei)
		{
			c._d.push_back(jinwei);
		}
	}
	else
	{
		for (size_t i = 0; i < b._d.size(); i++)
		{
			Integer t1 = (*this) * Integer(b._d[i]);
			Integer t2;
			t2._d.resize(i);
			fill(t2._d.begin(), t2._d.end(), 0);
			t2._d.insert(t2._d.end(), t1._d.begin(), t1._d.end());
			c = t2 + c;
		}
	}
	if (sign&&b.sign)
	{
		// 正正相乘
		c.sign = true;
	}
	else if ((!sign) && (!b.sign))
	{
		// 负负相乘
		c.sign = true;
	}
	else
	{
		// 一正一负
		c.sign = false;
	}
	return c;
}

xiaoma::Integer& xiaoma::Integer::operator*=(const Integer &b)
{
	*this = (*this)*b;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator/(const Integer &b) const throw (DivideByZero)
{
	Integer Q, R;
	do_divide(b, Q, R);
	return Q;
}

xiaoma::Integer& xiaoma::Integer::operator/=(const Integer &b)
{
	*this = (*this) / b;
	return *this;
}

xiaoma::Integer xiaoma::Integer::operator%(const Integer &b) const
{
	Integer Q, R;
	do_divide(b, Q, R);
	return R;
}

xiaoma::Integer& xiaoma::Integer::operator%=(const Integer &b)
{
	*this = (*this) % b;
	return *this;
}

bool xiaoma::Integer::operator==(const Integer &b) const
{
	return (sign == b.sign) && (_d == b._d);
}

bool xiaoma::Integer::operator!=(const Integer &b) const
{
	return !(*this == b);
}

bool xiaoma::Integer::operator<(const Integer &b) const
{
	bool small_than_without_sign = false;
	if (((sign && b.sign) == false) &&\
		(sign || b.sign))
	{
		// 两个数不同号
		return b.sign;
	}
	else
	{
		if (_d.size() < b._d.size())
		{
			small_than_without_sign = true;
		}
		else if (_d.size() > b._d.size())
		{
			small_than_without_sign = false;
		}
		else if (_d.size()==0 && b._d.size()==0)
		{
			return false;
		}
		else
		{
			auto iter1 = _d.rbegin();
			auto iter2 = b._d.rbegin();
			for (; iter1!=_d.rend(); iter1++, iter2++)
			{
				if (*iter1 > *iter2)
				{
					small_than_without_sign = false;
					break;
				}
				else if (*iter1 < *iter2)
				{
					small_than_without_sign = true;
					break;
				}
			}
			if (!(iter1!=_d.rend()) && *(iter1-1)==*(iter2-1))
			{
				// 相等
				return false;
			}
		}
		if (sign)
		{
			return small_than_without_sign;
		}
		else
		{
			return !small_than_without_sign;
		}
	}
}

bool xiaoma::Integer::operator<= (const Integer &b) const
{
	return (*this == b) || (*this < b);
}

bool xiaoma::Integer::operator> (const Integer &b) const
{
	return !(*this <= b);
}

bool xiaoma::Integer::operator>= (const Integer &b) const
{
	return !(*this < b);
}

const std::string xiaoma::Integer::to_string() const
{
	if (_d.empty())
	{
		return std::string("0");
	}
	string str;
	if (!sign)
	{
		str += "-";
	}
	for (auto iter = _d.crbegin(); iter != _d.crend(); iter++)
	{
		str += (*iter + '0');
	}
	return str;
}

void xiaoma::Integer::remove_front_zeros()
{
	if (!_d.empty())
	{
		auto iter = _d.rbegin();
		if (*iter == 0)
		{
			while (iter != _d.rend() && *iter == 0)
			{
				++iter;
			}
			_d.erase(iter.base(), _d.end());
		}
		if (_d.empty())
		{
			sign = true;
		}
	}
}

void xiaoma::Integer::do_divide(const Integer &D, Integer &Q, Integer &R) const throw (DivideByZero)
{
	if (D._d.empty())
	{
		// 除数是0
		throw DivideByZero();
	}
	else if (_d.empty())
	{
		// 被除数是0，返回0
		Q = 0;
		R = 0;
	}
	else if (sign&&D.sign)
	{
		//两个正数
		if (*this >= D)
		{
			R = *this;
			for (size_t i = _d.size() - D._d.size() + 1; i > 0; i--)
			{
				Integer t;
				t._d.resize(i);
				fill(t._d.begin(), t._d.end() - 1, 0);
				(*t._d.rbegin()) = 1;
				t *= D;
				unsigned int x = 1;
				while ((t*x) <= R)
				{
					x++;
				}
				x--;
				R -= t*x;
				Q._d.push_back(x);
			}
			Q.remove_front_zeros();
		}
		else
		{
			Q = Integer(0);
			R = *this;
		}
	}
	else if (sign && !D.sign)
	{
		// 正数除以负数
		do_divide(-D, Q, R);
		Q = -Q;
	}
	else if (!sign && D.sign)
	{
		// 负数除以正数
		Integer t(-*this);
		t.do_divide(D, Q, R);
		Q = -Q - (R == 0 ? 0 : 1);
		R = (R == 0 ? 0 : D - R);
	}
	else
	{
		// 负数除以负数
		Integer t(-*this);
		t.do_divide(-D, Q, R);
		if (R != 0)
		{
			R = -D - R;
			Q += 1;
		}
	}
}

std::ostream & xiaoma::operator<<(std::ostream & o, const Integer& num)
{
	o << num.to_string();
	return o;
}

xiaoma::Integer xiaoma::operator+(const long long& l, const Integer& r)
{
	return Integer(l) + r;
}

xiaoma::Integer xiaoma::operator-(const long long& l, const Integer& r)
{
	return Integer(l) - r;
}

xiaoma::Integer xiaoma::operator*(const long long& l, const Integer& r)
{
	return Integer(l) * r;
}

xiaoma::Integer xiaoma::operator/(const long long& l, const Integer& r) throw (DivideByZero)
{
	return Integer(l) / r;
}

xiaoma::Integer xiaoma::operator%(const long long& l, const Integer& r) throw (DivideByZero)
{
	return Integer(l) % r;
}

xiaoma::Integer xiaoma::operator+(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) + r;
}

xiaoma::Integer xiaoma::operator-(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) - r;
}

xiaoma::Integer xiaoma::operator*(const std::string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) * r;
}

xiaoma::Integer xiaoma::operator/(const std::string& l, const Integer& r) throw (DivideByZero, Str2IntegerErr)
{
	return Integer(l) / r;
}

xiaoma::Integer xiaoma::operator%(const std::string& l, const Integer& r) throw (DivideByZero, Str2IntegerErr)
{
	return Integer(l) % r;
}

bool xiaoma::operator==(const long long& l, const Integer& r)
{
	return Integer(l) == r;
}

bool xiaoma::operator!=(const long long& l, const Integer& r)
{
	return Integer(l) != r;
}

bool xiaoma::operator<(const long long& l, const Integer& r)
{
	return Integer(l)  < r;
}

bool xiaoma::operator<=(const long long& l, const Integer& r)
{
	return Integer(l) <= r;
}

bool xiaoma::operator>(const long long& l, const Integer& r)
{
	return Integer(l)  > r;
}

bool xiaoma::operator>=(const long long& l, const Integer& r)
{
	return Integer(l) >= r;
}

bool xiaoma::operator==(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) == r;
}

bool xiaoma::operator!=(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) != r;
}

bool xiaoma::operator<(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l)  < r;
}

bool xiaoma::operator<=(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) <= r;
}

bool xiaoma::operator>(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l)  > r;
}

bool xiaoma::operator>=(const string& l, const Integer& r) throw (Str2IntegerErr)
{
	return Integer(l) >= r;
}