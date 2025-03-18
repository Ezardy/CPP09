all: test RPN

src=RPN
obj=$(addsuffix .o, $(src))

test: $(obj) test.o
	c++ $(cflags) -o $@ $(obj) test.o

RPN: $(obj) main.o
	c++ $(cflags) -o $@ $(obj) main.o

cflags=-Wall -Wextra -Werror -std=c++98
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d) main.o main.d test.o test.d

fclean: clean
	rm -f test RPN

re: fclean all

debug_test: cflags+=-g
debug_test: test

debug_btc: cflags+=-g
debug_btc: RPN

$(obj:.o=.d):
-include $(obj:.o=.d)
main.d:
-include main.d
test.d:
-include test.d
