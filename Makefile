TARGET=encoder_test
CFLAGS=-Wall -g
OBJS=encoder_test.o encoder.o
CC=gcc

.PHONY: clean all

all: ${TARGET}

${TARGET}: ${OBJS}
	${CC} -o ${TARGET} ${OBJS} ${LIBS}

clean:
	rm -f ${TARGET} ${OBJS}
