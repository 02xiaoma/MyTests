#pragma once
#ifndef _INTEGER_H_
#define _INTEGER_H_

#include <vector>
#include <string>
#include <exception>
#include <ostream>

namespace xiaoma
{
	class DivideByZero : std::exception
	{
		const char* what() const throw();
	};
	class Str2IntegerErr : std::exception
	{
		const char* what() const throw();
	};

	class Integer
	{
	public:
		// 构造函数
		Integer();
		Integer(long long num);
		Integer(const std::string &str) throw (Str2IntegerErr);
		Integer(const Integer& num);
		Integer(Integer&& num);

		// 赋值函数
		Integer& operator=(long long num);
		Integer& operator=(const std::string &str) throw (Str2IntegerErr);
		Integer& operator=(const Integer& num);
		Integer& operator=(Integer&& num);

		// 四则运算
		Integer operator+(const Integer &b) const;
		Integer& operator++();
		Integer operator++(int);
		Integer& operator+=(const Integer &b);
		Integer operator-(const Integer &b) const;
		Integer& operator--();
		Integer operator--(int);
		Integer& operator-=(const Integer &b);
		Integer operator-()const;
		Integer operator*(const Integer &b) const;
		Integer& operator*=(const Integer &b);
		Integer operator/(const Integer &b) const throw (DivideByZero);
		Integer& operator/=(const Integer &b);
		Integer operator%(const Integer &b) const;
		Integer& operator%=(const Integer &b);

		// 比较
		bool operator==(const Integer &b) const;
		bool operator!=(const Integer &b) const;
		bool operator< (const Integer &b) const;
		bool operator<= (const Integer &b) const;
		bool operator> (const Integer &b) const;
		bool operator>= (const Integer &b) const;

		// 输出
		const std::string to_string()const;

	private:
		std::vector<unsigned char> _d;//按照逆序存储。比如123存储为[3,2,1]
		bool sign=true;	//TRUE为正，FALSE为负

		void remove_front_zeros();//删除开头的多余的0,并且如果最后结果是0则positive赋为true
		void do_divide(const Integer &D, Integer &Q, Integer &R) const throw (DivideByZero);//用来执行除法
	};

	std::ostream & operator<< (std::ostream & o, const Integer& num);

	// 当Integer处于四则运算右边的时候(左边是long long、string时)
	Integer operator+(const long long& l, const Integer& r);
	Integer operator-(const long long& l, const Integer& r);
	Integer operator*(const long long& l, const Integer& r);
	Integer operator/(const long long& l, const Integer& r) throw (DivideByZero);
	Integer operator%(const long long& l, const Integer& r) throw (DivideByZero);
	Integer operator+(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	Integer operator-(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	Integer operator*(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	Integer operator/(const std::string& l, const Integer& r) throw (DivideByZero, Str2IntegerErr);
	Integer operator%(const std::string& l, const Integer& r) throw (DivideByZero, Str2IntegerErr);
	
	// 当Integer处于比较符号右边的时候(左边是long long、string时)
	bool operator==(const long long& l, const Integer& r);
	bool operator!=(const long long& l, const Integer& r);
	bool operator<(const long long& l, const Integer& r);
	bool operator<=(const long long& l, const Integer& r);
	bool operator>(const long long& l, const Integer& r);
	bool operator>=(const long long& l, const Integer& r);
	bool operator==(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	bool operator!=(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	bool operator<(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	bool operator<=(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	bool operator>(const std::string& l, const Integer& r) throw (Str2IntegerErr);
	bool operator>=(const std::string& l, const Integer& r) throw (Str2IntegerErr);
}

#endif