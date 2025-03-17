#include "BitcoinExchange.hpp"

#include <cctype>
#include <cerrno>
#include <cmath>
#include <cstddef>
#include <cstdlib>
#include <fstream>
#include <limits>
#include <map>
#include <string>

BitcoinExchange::BitcoinExchange(void) throw() {
}

BitcoinExchange::BitcoinExchange(char const* dataBasePath) throw(std::ifstream::failure,
																 std::bad_alloc,
																 BitcoinExchangeException) {
	std::ifstream file;
	file.exceptions(std::ifstream::failbit);
	file.open(dataBasePath);
	file.exceptions(std::ifstream::badbit);
	std::string line;
	if (!std::getline(file, line))
		throw BitcoinExchangeException("No header line in the rate database file");
	std::size_t datePos = line.find("date");
	if (datePos == std::string::npos || datePos != 0)
		throw BitcoinExchangeException(
			"No 'date' entry in the rate database's header or something precedes it");
	std::size_t ratePos = line.rfind("exchange_rate");
	if (ratePos == std::string::npos || ratePos + 13 != line.length())
		throw BitcoinExchangeException(
			"No 'exchange_rate' entry in the rate database's header or something following it");
	if (datePos + 4 == ratePos)
		throw BitcoinExchangeException(
			"Empty delimeter between the data and the exchange_rate words in the header");
	std::string const delimeter = line.substr(datePos + 4, ratePos - datePos - 4);
	while (std::getline(file, line)) {
		std::size_t delPos = line.find(delimeter);
		if (delPos == line.npos)
			throw BitcoinExchangeException("No delimeter found in the rate database's entry");
		std::string const dateStr = line.substr(0, delPos);
		unsigned		  date = dateStringToUint(dateStr);
		if (dataBase.find(date) != dataBase.end())
			throw BitcoinExchangeException("The date duplicate => '" + dateStr + '\'');
		std::string const rateStr = line.substr(delPos + delimeter.length());
		if (rateStr.empty())
			throw BitcoinExchangeException("The rate string is empty");
		errno = 0;
		char*		numEnd;
		long double rate = std::strtold(rateStr.c_str(), &numEnd);
		if (errno == ERANGE && (rate == HUGE_VALL || rate == -HUGE_VALL))
			throw BitcoinExchangeException("The rate value is out of range => '" + rateStr + '\'');
		if (*numEnd)
			throw BitcoinExchangeException("Unrecognized symbol in the rate string => '" + rateStr
										   + '\'');
		if (rate != rate || rate == std::numeric_limits<long double>::infinity()
			|| rate == -std::numeric_limits<long double>::infinity())
			throw BitcoinExchangeException("The rate value must be a finite number => '" + rateStr
										   + '\'');
		if (rate < 0)
			throw BitcoinExchangeException("The rate value must be a non-negative number => '"
										   + rateStr + '\'');
		dataBase[date] = rate;
	}
}

BitcoinExchange::BitcoinExchange(BitcoinExchange const& other) throw(std::bad_alloc)
	: dataBase(other.dataBase) {
}

BitcoinExchange::~BitcoinExchange(void) throw() {
}

BitcoinExchange& BitcoinExchange::operator=(BitcoinExchange const& other) throw(std::bad_alloc) {
	if (this != &other)
		dataBase = other.dataBase;
	return *this;
}

long double BitcoinExchange::exchange(std::string const& currency, std::string const& date) const
	throw(BitcoinExchangeException) {
	return exchange(currency, dateStringToUint(date));
}

long double BitcoinExchange::exchange(std::string const& currency, unsigned date) const
	throw(BitcoinExchangeException) {
	char* end;
	if (currency.empty())
		throw BitcoinExchangeException("The currency string is empty");
	errno = 0;
	float c = std::strtof(currency.c_str(), &end);
	if (*end != '\0')
		throw BitcoinExchangeException("The value must not have following symbols");
	if (errno == ERANGE && (c == HUGE_VALF || c == -HUGE_VALF))
		throw BitcoinExchangeException("The value is out of range");
	if (c != c || c == std::numeric_limits<float>::infinity()
		|| c == -std::numeric_limits<float>::infinity())
		throw BitcoinExchangeException("The value is non-finite");
	if (c <= 0.0f || c > 1000.0f)
		throw BitcoinExchangeException("The value is out of range");
	return exchange(c, date);
}

long double BitcoinExchange::exchange(float currency, unsigned date) const throw() {
	long double rate;

	if (!dataBase.empty()) {
		std::map<unsigned, long double>::const_iterator it = dataBase.upper_bound(date);
		if (it == dataBase.begin())
			rate = 0;
		else
			rate = (--it)->second;
	} else
		rate = 0;
	return rate * currency;
}

unsigned BitcoinExchange::dateStringToUint(std::string const& str) throw(BitcoinExchangeException) {
	bool	 success = false;
	bool	 leap;
	char*	 end;
	unsigned days;
	unsigned date;
	long	 tmp;

	if (std::isdigit(str[0])) {
		errno = 0;
		tmp = std::strtol(str.c_str(), &end, 10);
		if (errno == 0 && tmp <= 429496 && *end == '-' && std::isdigit(end[1])
			&& std::isdigit(end[2]) && end[3] == '-' && std::isdigit(end[4]) && std::isdigit(end[5])
			&& end[6] == 0) {
			leap = tmp % 400 == 0 || (tmp % 100 && tmp % 4 == 0);
			date = static_cast<unsigned>(tmp) * 10000;
			tmp = std::strtol(end + 1, &end, 10);
			if (errno == 0 && tmp > 0 && tmp < 13) {
				date += tmp * 100;
				if (tmp < 8) {
					if (tmp % 2)
						days = 31;
					else if (tmp != 2)
						days = 30;
					else if (leap)
						days = 29;
					else
						days = 28;
				} else if (tmp % 2)
					days = 30;
				else
					days = 31;
				tmp = std::strtol(end + 1, &end, 10);
				if (errno == 0 && tmp <= days && tmp > 0) {
					date += tmp;
					success = true;
				}
			}
		}
	}
	if (!success)
		throw BitcoinExchangeException("Bad date => '" + str + '\'');
	return date;
}

BitcoinExchange::BitcoinExchangeException::BitcoinExchangeException(void) throw(std::bad_alloc)
	: message("BitcoinExchange exception") {
}

BitcoinExchange::BitcoinExchangeException::BitcoinExchangeException(
	std::string const& message) throw(std::bad_alloc)
	: message(message) {
}

BitcoinExchange::BitcoinExchangeException::BitcoinExchangeException(
	BitcoinExchangeException const& other) throw(std::bad_alloc)
	: message(other.message) {
}

BitcoinExchange::BitcoinExchangeException::~BitcoinExchangeException(void) throw() {
}

BitcoinExchange::BitcoinExchangeException& BitcoinExchange::BitcoinExchangeException::operator=(
	BitcoinExchangeException const& other) throw(std::bad_alloc) {
	if (this != &other)
		message = other.message;
	return *this;
}

char const* BitcoinExchange::BitcoinExchangeException::what(void) const throw() {
	return message.c_str();
}
