#ifndef EX00_BITCOINEXCHANGE_HPP
#define EX00_BITCOINEXCHANGE_HPP

#include <exception>
#include <fstream>
#include <map>
#include <new>
#include <string>

class BitcoinExchange {
public:
	class BitcoinExchangeException : public std::exception {
	public:
		BitcoinExchangeException(void) throw(std::bad_alloc);
		BitcoinExchangeException(std::string const& message) throw(std::bad_alloc);
		BitcoinExchangeException(BitcoinExchangeException const& other) throw(std::bad_alloc);
		~BitcoinExchangeException(void) throw();

		BitcoinExchangeException& operator=(BitcoinExchangeException const& other) throw(
			std::bad_alloc);

		char const* what(void) const throw();

	private:
		std::string message;
	};

	BitcoinExchange(void) throw();
	BitcoinExchange(char const* dataBasePath) throw(std::ifstream::failure, std::bad_alloc,
													BitcoinExchangeException);
	BitcoinExchange(BitcoinExchange const& other) throw(std::bad_alloc);
	~BitcoinExchange(void) throw();

	BitcoinExchange& operator=(BitcoinExchange const& other) throw(std::bad_alloc);

	long double exchange(float currency, unsigned date) const throw();
	long double exchange(std::string const& currency, unsigned date) const
		throw(BitcoinExchangeException);
	long double exchange(std::string const& currency, std::string const& date) const
		throw(BitcoinExchangeException);

private:
	std::map<unsigned, long double> dataBase;

	static unsigned dateStringToUint(std::string const& str) throw(BitcoinExchangeException);
};
#endif
