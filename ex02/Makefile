all: PmergeMe

src=PmergeMe main
obj=$(addsuffix .o, $(src))

PmergeMe: $(obj)
	c++ $(cflags) -o $@ $(obj)

cflags=-Wall -Wextra -Werror -std=c++98
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d)

fclean: clean
	rm -f PmergeMe

re: fclean all

debug_test: cflags+=-g
debug_test: test

debug_main: cflags+=-g
debug_main: PmergeMe

$(obj:.o=.d):
-include $(obj:.o=.d)
