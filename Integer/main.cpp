#define BOOST_TEST_MODULE xiaoma_test_main_module
#include <boost/test/included/unit_test.hpp>
#include <vector>
#include <iostream>

#include "Integer.h"

using namespace std;
using namespace xiaoma;

// 测试构造函数和转化为string的函数
BOOST_AUTO_TEST_SUITE( constructors_and_to_string )

BOOST_AUTO_TEST_CASE(zero)
{
	Integer zeros[] = { Integer(), Integer(0),\
		Integer("0"), Integer("00"),\
		Integer("+0"), Integer("+000"),\
	Integer("-0"), Integer("-00000") };
	for (auto &i:zeros)
	{
		BOOST_REQUIRE_EQUAL(i.to_string(), string("0"));
	}
}

BOOST_AUTO_TEST_CASE(positive)
{
	vector<Integer> positives = { Integer(1),\
		Integer("222222222222222222222222222222222"),\
		Integer("+0222222222222222222222222222222222")};
	vector<string> strs = { "1",\
		"222222222222222222222222222222222",\
		"222222222222222222222222222222222" };
	for (size_t i=0; i<strs.size(); i++)
	{
		BOOST_REQUIRE_EQUAL(positives[i].to_string(), strs[i]);
	}
}

BOOST_AUTO_TEST_CASE(negative)
{
	vector<Integer> negative = { Integer(1),\
		Integer("-222222222222222222222222222222222"),\
		Integer("-0222222222222222222222222222222222") };
	vector<string> strs = { "1",\
		"-222222222222222222222222222222222",\
		"-222222222222222222222222222222222" };
	for (size_t i = 0; i < strs.size(); i++)
	{
		BOOST_REQUIRE_EQUAL(negative[i].to_string(), strs[i]);
	}
}

BOOST_AUTO_TEST_CASE(StringErr)
{
	BOOST_REQUIRE_THROW(Integer("0+2"), Str2IntegerErr);
	BOOST_REQUIRE_THROW(Integer("*"), Str2IntegerErr);
	BOOST_REQUIRE_THROW(Integer("-+2"), Str2IntegerErr);
	BOOST_REQUIRE_THROW(Integer("-"), Str2IntegerErr);
}

BOOST_AUTO_TEST_SUITE_END()


// 测试赋值函数
BOOST_AUTO_TEST_SUITE( assign )

BOOST_AUTO_TEST_CASE(longlong)
{
	vector<Integer> vec(3);
	vec[0] = static_cast<long long>(0);
	vec[1] = static_cast<long long>(-1);
	vec[2] = static_cast<long long>(1);
	vector<std::string> strs = { "0", "-1", "1" };
	for (size_t i = 0; i < strs.size(); i++)
	{
		BOOST_REQUIRE_EQUAL(vec[i].to_string(), strs[i]);
	}
}

BOOST_AUTO_TEST_CASE(String)
{
	vector<Integer> vec(7);
	vec[0] = string("0");
	vec[1] = string("-1");
	vec[2] = string("-01");
	vec[3] = string("-0222222222222222222222222222222222");
	vec[4] = string("1");
	vec[5] = string("01");
	vec[6] = string("0222222222222222222222222222222222");
	vector<string> strs = { "0",\
		"-1",\
		"-1",\
		"-222222222222222222222222222222222",\
		"1",\
		"1",\
		"222222222222222222222222222222222"};
	for (size_t i = 0; i < strs.size(); i++)
	{
		BOOST_REQUIRE_EQUAL(vec[i].to_string(), strs[i]);
	}
}

BOOST_AUTO_TEST_CASE(other)
{
	vector<Integer> vec(7);
	vec[0] = Integer("0");
	vec[1] = Integer("-1");
	vec[2] = Integer("-01");
	vec[3] = Integer("-0222222222222222222222222222222222");
	vec[4] = Integer("1");
	vec[5] = Integer("01");
	vec[6] = Integer("0222222222222222222222222222222222");
	vector<string> strs = { "0",\
		"-1",\
		"-1",\
		"-222222222222222222222222222222222",\
		"1",\
		"1",\
		"222222222222222222222222222222222" };
	for (size_t i = 0; i < strs.size(); i++)
	{
		BOOST_REQUIRE_EQUAL(vec[i].to_string(), strs[i]);
	}
}

BOOST_AUTO_TEST_SUITE_END()

// 测试四则运算
BOOST_AUTO_TEST_SUITE( arithmetic )

BOOST_AUTO_TEST_CASE(plus)
{
	BOOST_REQUIRE_EQUAL(Integer(0)+Integer(0), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(-1) + Integer(1), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(9) + Integer(1), Integer(10));
	BOOST_REQUIRE_EQUAL(\
		Integer("-222222222222222222222222222222222") \
		+ Integer("222222222222222222222222222222222"),\
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222") \
		+ Integer("-222222222222222222222222222222222"), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222") \
		+ Integer("222222222222222222222222222222222"), \
		Integer("444444444444444444444444444444444"));
	BOOST_REQUIRE_EQUAL(\
		Integer("-222222222222222222222222222222222") \
		+ Integer("-222222222222222222222222222222222"), \
		Integer("-444444444444444444444444444444444"));

	Integer t1("222222222222222222222222222222222");
	Integer t2 = t1++;
	BOOST_REQUIRE_EQUAL(t2, Integer("222222222222222222222222222222222"));
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222223"));
	t1 = Integer("222222222222222222222222222222222");
	t2 = ++t1;
	BOOST_REQUIRE_EQUAL(t2, Integer("222222222222222222222222222222223"));
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222223"));
	t1 = Integer("222222222222222222222222222222222");
	t1 += 1;
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222223"));
}

BOOST_AUTO_TEST_CASE(subtract)
{
	BOOST_REQUIRE_EQUAL(Integer(0) - Integer(0), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) - Integer(1), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(10) - Integer(1), Integer(9));
	BOOST_REQUIRE_EQUAL(Integer(-1) - Integer(-1), Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222") \
		- Integer("222222222222222222222222222222222"), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("-222222222222222222222222222222222") \
		- Integer("-222222222222222222222222222222222"), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222") \
		- Integer("-222222222222222222222222222222222"), \
		Integer("444444444444444444444444444444444"));
	BOOST_REQUIRE_EQUAL(\
		Integer("-222222222222222222222222222222222") \
		- Integer("222222222222222222222222222222222"), \
		Integer("-444444444444444444444444444444444"));
	Integer t1("222222222222222222222222222222222");
	Integer t2 = t1--;
	BOOST_REQUIRE_EQUAL(t2, Integer("222222222222222222222222222222222"));
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222221"));
	t1 = Integer("222222222222222222222222222222222");
	t2 = --t1;
	BOOST_REQUIRE_EQUAL(t2, Integer("222222222222222222222222222222221"));
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222221"));
	t1 = Integer("222222222222222222222222222222222");
	t1 -= 1;
	BOOST_REQUIRE_EQUAL(t1, Integer("222222222222222222222222222222221"));
}

BOOST_AUTO_TEST_CASE(multi)
{
	BOOST_REQUIRE_EQUAL(Integer(0) * Integer(0), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) * Integer(0), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(-1) * Integer(0), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) * Integer(-1), Integer(-1));
	BOOST_REQUIRE_EQUAL(Integer(-1) * Integer(-1), Integer(1));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222")\
		*\
		Integer(0), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222")\
		*\
		Integer(-1),\
		Integer("-222222222222222222222222222222222"));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222")\
		*\
		Integer(1), \
		Integer("222222222222222222222222222222222"));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222")\
		*\
		Integer(-2), \
		Integer("-444444444444444444444444444444444"));
	BOOST_REQUIRE_EQUAL(\
		Integer("222222222222222222222222222222222")\
		*\
		Integer(2), \
		Integer("444444444444444444444444444444444"));
	Integer t("222222222222222222222222222222222");
	t *= 2;
	BOOST_REQUIRE_EQUAL(t, Integer("444444444444444444444444444444444"));
}

BOOST_AUTO_TEST_CASE(divide)
{
	BOOST_REQUIRE_EQUAL(Integer(0) / Integer(1), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) / Integer(1), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(1) / Integer(2), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(5) / Integer(2), Integer(2));
	BOOST_REQUIRE_EQUAL(Integer(5) / Integer(-2), Integer(-2));
	BOOST_REQUIRE_EQUAL(Integer(-5) / Integer(2), Integer(-3));
	BOOST_REQUIRE_EQUAL(Integer(-5) / Integer(-2), Integer(3));
	BOOST_REQUIRE_EQUAL(Integer(4) / Integer(2), Integer(2));
	BOOST_REQUIRE_EQUAL(Integer(4) / Integer(-2), Integer(-2));
	BOOST_REQUIRE_EQUAL(Integer(-4) / Integer(2), Integer(-2));
	BOOST_REQUIRE_EQUAL(Integer(-4) / Integer(-2), Integer(2));
	BOOST_REQUIRE_EQUAL(\
		Integer(0)\
		/ \
		Integer("222222222222222222222222222222222"),\
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer(14)\
		/ \
		Integer("222222222222222222222222222222222"), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer("444444444444444444444444444444444")\
		/ \
		Integer("222222222222222222222222222222222"), \
		Integer(2));
	Integer t("444444444444444444444444444444444");
	t /= 2;
	BOOST_REQUIRE_EQUAL(t, Integer("222222222222222222222222222222222"));
	BOOST_REQUIRE_THROW(Integer(0) / Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(Integer(1) / Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(Integer(-1) / Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(\
		Integer("222222222222222222222222222222222")\
		/\
		Integer(0),\
		DivideByZero);
}

BOOST_AUTO_TEST_CASE(mod)
{
	BOOST_REQUIRE_EQUAL(Integer(0) % Integer(1), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) % Integer(1), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(1) % Integer(2), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(5) % Integer(2), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(5) % Integer(-2), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(-5) % Integer(2), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(-5) % Integer(-2), Integer(1));
	BOOST_REQUIRE_EQUAL(Integer(4) % Integer(2), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(4) % Integer(-2), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(-4) % Integer(2), Integer(0));
	BOOST_REQUIRE_EQUAL(Integer(-4) % Integer(-2), Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer(0)\
		% \
		Integer("222222222222222222222222222222222"), \
		Integer(0));
	BOOST_REQUIRE_EQUAL(\
		Integer(14)\
		% \
		Integer("222222222222222222222222222222222"), \
		Integer(14));
	BOOST_REQUIRE_EQUAL(\
		Integer("444444444444444444444444444444444")\
		% \
		Integer("222222222222222222222222222222222"), \
		Integer(0));
	Integer t("444444444444444444444444444444444");
	t %= 2;
	BOOST_REQUIRE_EQUAL(t, Integer(0));
	BOOST_REQUIRE_THROW(Integer(0) % Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(Integer(1) % Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(Integer(-1) % Integer(0), DivideByZero);
	BOOST_REQUIRE_THROW(\
		Integer("222222222222222222222222222222222")\
		% \
		Integer(0), \
		DivideByZero);
}

BOOST_AUTO_TEST_SUITE_END()

BOOST_AUTO_TEST_SUITE( compare )

BOOST_AUTO_TEST_CASE(equal)
{
	BOOST_REQUIRE(Integer(0) == 0);
	BOOST_REQUIRE(Integer(1) == 1);
	BOOST_REQUIRE(Integer(-1) == -1);
	BOOST_REQUIRE(\
		Integer("222222222222222222222222222222222")\
		== \
		Integer("+222222222222222222222222222222222"));
	BOOST_REQUIRE(\
		Integer("-222222222222222222222222222222222")\
		== \
		Integer("-0222222222222222222222222222222222"));
}

BOOST_AUTO_TEST_CASE(ne)
{
	BOOST_REQUIRE(Integer(0) != 1);
	BOOST_REQUIRE(Integer(1) != -1);
	BOOST_REQUIRE(Integer(-1) != 0);
	BOOST_REQUIRE(\
		Integer("-222222222222222222222222222222222")\
		!= \
		Integer("+222222222222222222222222222222222"));
	BOOST_REQUIRE(\
		Integer("-222222222222222222222222222222222")\
		!= \
		Integer(0));
}

BOOST_AUTO_TEST_CASE(lt)
{
	BOOST_REQUIRE(0 < Integer(1));
	BOOST_REQUIRE(-1 < Integer(0));
	BOOST_REQUIRE(\
		Integer("-222222222222222222222222222222222") \
		< \
		Integer(0));
	BOOST_REQUIRE(\
		0 \
		< \
		Integer("222222222222222222222222222222222"));
}

BOOST_AUTO_TEST_SUITE_END()