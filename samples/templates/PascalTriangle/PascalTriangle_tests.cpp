// PascalTriangle.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "PascalTriangle.h"
#include <boost/test/output/compiler_log_formatter.hpp>

class SpecLogFormatter : public boost::unit_test::output::compiler_log_formatter
{
private:
	void test_unit_start(std::ostream& os, boost::unit_test::test_unit const& tu) override
	{
		os << std::string(m_indent, ' ') << boost::replace_all_copy(tu.p_name.get(), "_", " ") << std::endl;
		m_indent += 2;
	}
	void test_unit_finish(std::ostream& os, boost::unit_test::test_unit const& tu, unsigned long elapsed) override
	{
		(void)&elapsed;
		(void)&tu;
		(void)&os;
		m_indent -= 2;
	}

	int m_indent = 0;
};

boost::unit_test::test_suite* init_unit_test_suite(int /*argc*/, char* /*argv*/ [])
{
	boost::unit_test::unit_test_log.set_formatter(new SpecLogFormatter);
	boost::unit_test::framework::master_test_suite().p_name.value = "All tests";
	return 0;
}

struct A_PascalTriangleGenerator_
{
	PascalTriangleGenerator<int> generator;
	void ExpectRow(unsigned rowIndex, const decltype(generator)::RowType& expectedRow)
	{
		BOOST_CHECK(generator.GetRow(rowIndex) == expectedRow);
	}
};
BOOST_FIXTURE_TEST_SUITE(A_PascalTriangleGenerator, A_PascalTriangleGenerator_)
	BOOST_AUTO_TEST_CASE(returns_1_for_row_0)
	{
		ExpectRow(0, { 1 });
	}
	BOOST_AUTO_TEST_CASE(returns_1_1_for_row_1)
	{
		ExpectRow(1, { 1, 1 });
	}
	BOOST_AUTO_TEST_CASE(returns_1_2_1_for_row_2)
	{
		ExpectRow(2, { 1, 2, 1 });
	}
	BOOST_AUTO_TEST_CASE(returns_1_3_3_1_for_row_3)
	{
		ExpectRow(3, { 1, 3, 3, 1 });
	}
	BOOST_AUTO_TEST_CASE(returns_1_6_15_20_15_6_1_for_row_6)
	{
		ExpectRow(6, { 1, 6, 15, 20, 15, 6, 1 });
	}
	BOOST_AUTO_TEST_CASE(returns_1_7_21_35_35_21_7_1_for_row_7)
	{
		ExpectRow(7, { 1, 7, 21, 35, 35, 21, 7, 1 });
	}
BOOST_AUTO_TEST_SUITE_END()

int main(int argc, char* argv[])
{
	return boost::unit_test::unit_test_main(&init_unit_test_suite, argc, argv);
}
