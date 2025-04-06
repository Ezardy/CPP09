all: RPN

src=RPN main
obj=$(addsuffix .o, $(src))

RPN: $(obj)
	c++ $(cflags) -o $@ $(obj)

cflags=-Wall -Wextra -Werror -std=c++98
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d)

fclean: clean
	rm -f RPN

re: fclean all

debug_main: cflags+=-g
debug_main: RPN

$(obj:.o=.d):
-include $(obj:.o=.d)
