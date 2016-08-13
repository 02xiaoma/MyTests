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
		// ���캯��
		Integer();
		Integer(long long num);
		Integer(const std::string &str) throw (Str2IntegerErr);
		Integer(const Integer& num);
		Integer(Integer&& num);

		// ��ֵ����
		Integer& operator=(long long num);
		Integer& operator=(const std::string &str) throw (Str2IntegerErr);
		Integer& operator=(const Integer& num);
		Integer& operator=(Integer&& num);

		// ��������
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

		// �Ƚ�
		bool operator==(const Integer &b) const;
		bool operator!=(const Integer &b) const;
		bool operator< (const Integer &b) const;
		bool operator<= (const Integer &b) const;
		bool operator> (const Integer &b) const;
		bool operator>= (const Integer &b) const;

		// ���
		const std::string to_string()const;

	private:
		std::vector<unsigned char> _d;//��������洢������123�洢Ϊ[3,2,1]
		bool sign=true;	//TRUEΪ����FALSEΪ��

		void remove_front_zeros();//ɾ����ͷ�Ķ����0,��������������0��positive��Ϊtrue
		void do_divide(const Integer &D, Integer &Q, Integer &R) const throw (DivideByZero);//����ִ�г���
	};

	std::ostream & operator<< (std::ostream & o, const Integer& num);

	// ��Integer�������������ұߵ�ʱ��(�����long long��stringʱ)
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
	
	// ��Integer���ڱȽϷ����ұߵ�ʱ��(�����long long��stringʱ)
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