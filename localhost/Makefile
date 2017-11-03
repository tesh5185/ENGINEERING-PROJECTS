INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS= 
CFLAGS= -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

PRODUCT=webserver

HFILES=
CFILES= webserver.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

server:	webserver.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ webserver.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
