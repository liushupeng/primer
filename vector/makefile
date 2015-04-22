FILE=vector

CFLAGS= -gdwarf-2 -g3 -W -Wall -Wshadow -Wreturn-type -Wno-unused-parameter -fno-common\
	-Wtrigraphs -Wformat -Wparentheses -Wpointer-arith

all:
	g++ ${CFLAGS} ${FILE}.cc -o ${FILE}
clean:
	rm -f ${FILE}
r:
	@echo "========> Result:"
	@./${FILE}
	@echo ""
	@echo "========> Valgrind:"
	@valgrind -q ./${FILE}
