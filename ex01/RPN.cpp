#include "RPN.hpp"

#include <cctype>
#include <cstddef>
#include <cstring>
#include <new>

RPN::RPNException::RPNException(void) throw(std::bad_alloc) : message("RPN exception") {
}

RPN::RPNException::RPNException(std::string const& message) throw(std::bad_alloc)
	: message(message) {
}

RPN::RPNException::RPNException(RPNException const& other) throw(std::bad_alloc)
	: message(other.message) {
}

RPN::RPNException::~RPNException(void) throw() {
}

char const* RPN::RPNException::what(void) const throw() {
	return message.c_str();
}

RPN::RPN(void) throw() {
}

RPN::RPN(RPN const& other) throw() {
	(void)other;
}

RPN::~RPN(void) throw() {
}

RPN& RPN::operator=(RPN const& other) throw() {
	(void)other;
	return *this;
}

long double RPN::calculate(char const* expr) throw(std::bad_alloc, RPNException) {
	std::stack<char> symbols;

	bool		issymbol = std::isspace(expr[0]);
	std::size_t len = std::strlen(expr);
	if (len == 0)
		throw RPNException("Empty expression");
	for (std::size_t i = 0; i < len; i += 1) {
		if (issymbol) {
			if (!std::isspace(expr[i]))
				throw RPNException("Operators and operands must be a single character");
			issymbol = false;
			while (std::isspace(expr[i + 1]))
				i += 1;
		} else {
			issymbol = true;
			symbols.push(expr[i]);
		}
	}
	long double result = calculate(symbols);
	if (!symbols.empty())
		throw RPNException("Invalid expression");
	return result;
}

long double RPN::calculate(std::stack<char>& symbols) throw(RPNException) {
	long double result = 0;

	if (symbols.empty())
		throw RPNException("Invalid expression");
	char s = symbols.top();
	symbols.pop();
	if (std::isdigit(s))
		result = s - '0';
	else {
		long double b;
		switch (s) {
			case '+': {
				b = calculate(symbols);
				result = calculate(symbols) + b;
				break;
			}
			case '-': {
				b = calculate(symbols);
				result = calculate(symbols) - b;
				break;
			}
			case '*': {
				b = calculate(symbols);
				result = calculate(symbols) * b;
				break;
			}
			case '/': {
				b = calculate(symbols);
				result = calculate(symbols) / b;
				break;
			}
			default: {
				result = 0;
				throw RPNException("Unknown symbol");
			}
		}
	}
	return result;
}
