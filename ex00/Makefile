all: btc

src=BitcoinExchange main
obj=$(addsuffix .o, $(src))

btc: $(obj)
	c++ $(cflags) -o $@ $(obj)

cflags=-Wall -Wextra -Werror -std=c++98
depflags = -MT $@ -MMD -MP -MF $*.d

%.o: %.cpp %.d Makefile
	c++ $(cflags) $(depflags) -o $@ -c $<

clean:
	rm -f $(obj) $(obj:.o=.d)

fclean: clean
	rm -f btc

re: fclean all

debug_btc: cflags+=-g
debug_btc: btc

$(obj:.o=.d):
-include $(obj:.o=.d)
