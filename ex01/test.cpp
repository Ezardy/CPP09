#include "../test.hpp"

#include "RPN.hpp"

static bool normal_test(void);
static bool invalid_input_test(void);

int main() {
	bool   success = true;
	bool   (*tests[])(void) = {normal_test, invalid_input_test};
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

TEST_START(invalid_input_test)
	TEST_LOGIC_START
		TEST_EXCEPTION_MESSAGE(RPN::calculate(""), RPN::RPNException, "Empty expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate(" "), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("10"), RPN::RPNException, "Operators and operands must be a single character")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 10 +"), RPN::RPNException, "Operators and operands must be a single character")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 10 ++"), RPN::RPNException, "Operators and operands must be a single character")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 10 +*"), RPN::RPNException, "Operators and operands must be a single character")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 1 ^"), RPN::RPNException, "Unknown symbol")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("a 1 +"), RPN::RPNException, "Unknown symbol")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 b +"), RPN::RPNException, "Unknown symbol")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 +"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 *"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 -"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 /"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 1"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 1 + 1"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 1 1 +"), RPN::RPNException, "Invalid expression")
		TEST_EXCEPTION_MESSAGE(RPN::calculate("1 1 1 + + +"), RPN::RPNException, "Invalid expression")
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END

TEST_START(normal_test)
	TEST_LOGIC_START
		TEST_ASSERT(RPN::calculate("9") == 9.0l)
		TEST_ASSERT(RPN::calculate("1 2 +") == 3.0l)
		TEST_ASSERT(RPN::calculate(" 1 2 +") == 3.0l)
		TEST_ASSERT(RPN::calculate("1 2 + ") == 3.0l)
		TEST_ASSERT(RPN::calculate(" 1 2 + ") == 3.0l)
		TEST_ASSERT(RPN::calculate("   	    1		 2 	 +   ") == 3.0l)
		TEST_ASSERT(RPN::calculate("9 2 /") == 4.5l)
		TEST_ASSERT(RPN::calculate("9 2 *") == 18.0l)
		TEST_ASSERT(RPN::calculate("9 2 -") == 7.0l)
		TEST_ASSERT(RPN::calculate("1 3 4 6 - * 1 2 4 * - / +") == 1 + 3.0l * (4.0l - 6) / (1 - 2 * 4))
		TEST_ASSERT(RPN::calculate("8 9 * 9 - 9 - 9 - 4 - 1 +") == 42.0l)
		TEST_ASSERT(RPN::calculate("7 7 * 7 -") == 42.0l)
		TEST_ASSERT(RPN::calculate("1 2 * 2 / 2 * 2 4 - +") == 0.0l)
	TEST_LOGIC_END
	TEST_EMERGENCY_START
	TEST_EMERGENCY_END
TEST_END
// clang-format on
