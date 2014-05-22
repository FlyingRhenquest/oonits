OBJS = run_cppunit.o oonits_test.o
EXE = run_cppunit
CFLAGS += -g --std=c++11 -I..
LFLAGS = -lcppunit

.cpp.o:
	g++ -c ${CFLAGS} $<

all: ${OBJS}
	g++ -o ${EXE} ${OBJS} ${LFLAGS}

clean:
	rm -f *~ ${EXE} ${OBJS} core
