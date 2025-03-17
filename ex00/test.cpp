#include "../test.hpp"

#include <cstdio>
#include <fstream>

#include "BitcoinExchange.hpp"

static bool default_constructor(void);
static bool constructor(void);
static bool copy_constructor(void);
static bool copy_assignment(void);
static bool exchange_currency(void);
static bool exchange_date(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {default_constructor, constructor,	   copy_constructor,
							   copy_assignment,		exchange_currency, exchange_date};
	size_t tests_count = sizeof(tests) / sizeof(tests[0]);
	for (size_t i = 0; success && i < tests_count; i += 1) {
		success = tests[i]();
		std::cout << '\n';
	}
	if (success)
		std::cout << "OK\n";
	return success;
}

// clang-format off

TEST_START(exchange_date)
	TEST_LOGIC_START
		BitcoinExchange	be("data.csv");

		TEST_EXCEPTION(be.exchange("1", ""), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", " 2016-12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "0-2016-12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "+2016-12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "9223372036854775808-12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "429497-12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016.12-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "201612-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-+1-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-1-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-001-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016--31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-12-031"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-12-1"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-00-01"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-13-01"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-12-00"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-12-32"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-11-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2015-02-29"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "1900-02-29"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2000-02-30"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2001-02-30"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2200-02-30"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-04-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-06-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-09-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-11-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-9223372036854775808-31"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-11-9223372036854775808"), BitcoinExchange::BitcoinExchangeException)
		TEST_EXCEPTION(be.exchange("1", "2016-09-15 "), BitcoinExchange::BitcoinExchangeException)

		TEST_ASSERT(be.exchange("1", "0-12-31") == 0)
		TEST_ASSERT(be.exchange("1", "2009-02-16") == 0)
		TEST_ASSERT(be.exchange("1", "2020-02-29") == 8712.35l)
		TEST_ASSERT(be.exchange("1", "2020-02-28") == 8712.35l)
		TEST_ASSERT(be.exchange("1", "2020-03-01") == 8712.35l)
		TEST_ASSERT(be.exchange("1", "2024-03-01") == 47115.93l)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(exchange_currency)
	TEST_LOGIC_START
		BitcoinExchange	be("data.csv");

		TEST_EXCEPTION_MESSAGE(be.exchange("", 20140716), BitcoinExchange::BitcoinExchangeException, "The currency string is empty")
		TEST_EXCEPTION_MESSAGE(be.exchange("1.234f", 20140716), BitcoinExchange::BitcoinExchangeException, "The value must not have following symbols")
		TEST_EXCEPTION_MESSAGE(be.exchange("3.5e38", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is out of range")
		TEST_EXCEPTION_MESSAGE(be.exchange("-3.5e38", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is out of range")
		TEST_EXCEPTION_MESSAGE(be.exchange(" nan", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is non-finite")
		TEST_EXCEPTION_MESSAGE(be.exchange(" +inf", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is non-finite")
		TEST_EXCEPTION_MESSAGE(be.exchange("	 -inf", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is non-finite")
		TEST_EXCEPTION_MESSAGE(be.exchange("0", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is out of range")
		TEST_EXCEPTION_MESSAGE(be.exchange("-3.5", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is out of range")
		TEST_EXCEPTION_MESSAGE(be.exchange("1000.1", 20140716), BitcoinExchange::BitcoinExchangeException, "The value is out of range")

		TEST_ASSERT(be.exchange("	 1e+0", 20140716) == 621.21l)
		TEST_ASSERT(be.exchange("1000", 20140716) == 1000.f * 621.21l)
		TEST_ASSERT(be.exchange(" +1.0E+3", 20140716) == 1000.f * 621.21l)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(copy_assignment)
	TEST_LOGIC_START
		BitcoinExchange	be("data.csv");
		BitcoinExchange	bec;

		TEST_ASSERT(be.exchange(1, 20160206) == 388.0l)
		TEST_ASSERT(be.exchange(1, 20160204) == 388.0l)
		TEST_ASSERT(be.exchange(1, 20160207) == 375.0l)
		TEST_ASSERT(be.exchange(1, 20240229) == 47115.93l)
		TEST_ASSERT(be.exchange(1, 20080229) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20160204) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20160206) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20160207) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20240229) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20080229) == 0.0l)
		bec = be;
		TEST_ASSERT(bec.exchange(1, 20160204) == 388.0l)
		TEST_ASSERT(bec.exchange(1, 20160206) == 388.0l)
		TEST_ASSERT(bec.exchange(1, 20160207) == 375.0l)
		TEST_ASSERT(bec.exchange(1, 20240229) == 47115.93l)
		TEST_ASSERT(bec.exchange(1, 20080229) == 0.0l)
		TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(copy_constructor)
	TEST_LOGIC_START
		BitcoinExchange	be("data.csv");
		BitcoinExchange	bec(be);

		TEST_ASSERT(be.exchange(1, 20160206) == 388.0l)
		TEST_ASSERT(be.exchange(1, 20160204) == 388.0l)
		TEST_ASSERT(be.exchange(1, 20160207) == 375.0l)
		TEST_ASSERT(be.exchange(1, 20240229) == 47115.93l)
		TEST_ASSERT(be.exchange(1, 20080229) == 0.0l)
		TEST_ASSERT(bec.exchange(1, 20160204) == 388.0l)
		TEST_ASSERT(bec.exchange(1, 20160206) == 388.0l)
		TEST_ASSERT(bec.exchange(1, 20160207) == 375.0l)
		TEST_ASSERT(bec.exchange(1, 20240229) == 47115.93l)
		TEST_ASSERT(bec.exchange(1, 20080229) == 0.0l)
		TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(constructor)
	TEST_LOGIC_START
		TEST_EXCEPTION(BitcoinExchange be("non_existant.csv"), std::ifstream::failure)
	
		std::ofstream("test.csv").write("", 0);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No header line in the rate database file")

		std::ofstream("test.csv").write("dat,exchange_rate\n"
										"2009-01-02,0", 30);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No 'date' entry in the rate database's header or something precedes it")

		std::ofstream("test.csv").write(" date,exchange_rate\n"
										"2009-01-02,0", 32);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No 'date' entry in the rate database's header or something precedes it")

		std::ofstream("test.csv").write("date,excange_rate\n"
										"2009-01-02,0", 30);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No 'exchange_rate' entry in the rate database's header or something following it")

		std::ofstream("test.csv").write("date,exchange_rate \n"
										"2009-01-02,0", 32);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No 'exchange_rate' entry in the rate database's header or something following it")

		std::ofstream("test.csv").write("dateexchange_rate\n"
										"2009-01-020", 29);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Empty delimeter between the data and the exchange_rate words in the header")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05 | 0\n"
										"2009-01-17,7", 59);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "No delimeter found in the rate database's entry")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"+2009-01-05,0\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '+2009-01-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05 ,0\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-01-05 '")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"9223372036854775808-01-05,0\n"
										"2009-01-17,7", 72);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '9223372036854775808-01-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"429497-01-05,0\n"
										"2009-01-17,7", 59);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '429497-01-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009.01-05,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009.01-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01.05,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-01.05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-001-05,0\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-001-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-1-05,0\n"
										"2009-01-17,7", 56);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-1-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009--05,0\n"
										"2009-01-17,7", 55);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009--05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"-01-05,0\n"
										"2009-01-17,7", 53);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '-01-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-00-05,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-00-05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009.01.05,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009.01.05'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-005,0\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-01-005'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-5,0\n"
										"2009-01-17,7", 56);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-01-5'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-,0\n"
										"2009-01-17,7", 55);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-01-'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-02-29,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '2009-02-29'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"1900-02-29,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '1900-02-29'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"1913-01-32,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '1913-01-32'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"1913-01-00,0\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => '1913-01-00'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-02,3\n"
										"2009-01-17,7", 57);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The date duplicate => '2009-01-02'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,1.9e4932\n"
										"2009-01-17,7", 64);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate value is out of range => '1.9e4932'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,1e\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Unrecognized symbol in the rate string => '1e'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										",1\n"
										"2009-01-17,7", 47);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => ''")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,\n"
										"2009-01-17,7", 56);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate string is empty")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										",\n"
										"2009-01-17,7", 46);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "Bad date => ''")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,-1\n"
										"2009-01-17,7", 58);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate value must be a non-negative number => '-1'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,nan\n"
										"2009-01-17,7", 59);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate value must be a finite number => 'nan'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,inf\n"
										"2009-01-17,7", 59);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate value must be a finite number => 'inf'")

		std::ofstream("test.csv").write("date,exchange_rate\n"
										"2009-01-02,0\n"
										"2009-01-05,-inf\n"
										"2009-01-17,7", 60);
		TEST_EXCEPTION_MESSAGE(BitcoinExchange be("test.csv"), BitcoinExchange::BitcoinExchangeException, "The rate value must be a finite number => '-inf'")

		std::remove("test.csv");
		BitcoinExchange	be("data.csv");
		TEST_ASSERT(be.exchange(1, 20100913) == 0.06l)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(default_constructor)
	TEST_LOGIC_START
		BitcoinExchange	broker;

		TEST_ASSERT(broker.exchange(0, 0) == 0.)
		TEST_ASSERT(broker.exchange(10, 0) == 0.)
		TEST_ASSERT(broker.exchange(10, 40000114) == 0.)
		TEST_ASSERT(broker.exchange(10, 20000114) == 0.)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on
