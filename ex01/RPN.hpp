#ifndef EX01_RPN_HPP
#define EX01_RPN_HPP

#include <exception>
#include <new>
#include <stack>
#include <string>

class RPN {
public:
	class RPNException : public std::exception {
	public:
		RPNException(void) throw(std::bad_alloc);
		RPNException(std::string const& message) throw(std::bad_alloc);
		RPNException(RPNException const& other) throw(std::bad_alloc);
		~RPNException(void) throw();

		char const* what(void) const throw();

	private:
		std::string message;
	};

	static long double calculate(char const* expr) throw(std::bad_alloc, RPNException);
	static long double calculate(std::stack<char>& symbols) throw(RPNException);

private:
	RPN(void) throw();
	RPN(RPN const& other) throw();
	~RPN(void) throw();

	RPN& operator=(RPN const& other) throw();
};
#endif
