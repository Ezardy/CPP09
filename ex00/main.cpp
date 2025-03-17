#include <cstddef>
#include <fstream>
#include <iostream>
#include <new>
#include <ostream>
#include <string>

#include "BitcoinExchange.hpp"

int main(int argc, char const* const* const argv) {
	int error;

	if (argc == 2) {
		try {
			std::string		path(argv[0]);
			BitcoinExchange exchanger((path.substr(0, path.rfind('/') + 1) + "data.csv").c_str());
			std::ifstream	file;
			file.exceptions(std::ifstream::failbit);
			file.open(argv[1]);
			file.exceptions(std::ifstream::badbit);
			std::string line;
			if (!std::getline(file, line) || line != "date | value")
				throw BitcoinExchange::BitcoinExchangeException(
					"Invalid header in the input database");
			while (std::getline(file, line)) {
				try {
					std::size_t delPos = line.find(" | ");
					if (delPos == line.npos) {
						error = 1;
						std::cerr << "Error: The entry has no delimeter" << std::endl;
					} else {
						std::string const cur = line.substr(delPos + 3);
						std::string const date = line.substr(0, delPos);
						long double		  currency = exchanger.exchange(cur, date);
						std::cout << date << " => " << cur << " = " << currency << std::endl;
					}
				} catch (BitcoinExchange::BitcoinExchangeException const& e) {
					error = 1;
					std::cerr << "Error: " << e.what() << std::endl;
				}
			}
			error = 0;
		} catch (BitcoinExchange::BitcoinExchangeException const& e) {
			error = 3;
			std::cerr << "Error: " << e.what() << '\n';
		} catch (std::ifstream::failure const& e) {
			error = 4;
			std::cerr << "Error: " << e.what() << '\n';
		} catch (std::bad_alloc const& e) {
			error = 5;
			std::cerr << "Error: " << e.what() << '\n';
		}
	} else {
		error = 2;
		std::cerr << "Error: Wrong parameters number\n";
	}
	return error;
}
