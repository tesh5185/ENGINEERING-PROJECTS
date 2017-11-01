INCLUDE_DIRS = 
LIB_DIRS = 
CC=gcc

CDEFS= 
CFLAGS= -g $(INCLUDE_DIRS) $(CDEFS)
LIBS= 

PRODUCT=dfc

HFILES=
CFILES= dfc.c

SRCS= ${HFILES} ${CFILES}
OBJS= ${CFILES:.c=.o}

all:	${PRODUCT}

clean:
	-rm -f *.o *.NEW *~ *.d
	-rm -f ${PRODUCT} ${GARBAGE}

server:	dfc.o
	$(CC) $(LDFLAGS) $(CFLAGS) -o $@ dfc.o $(LIBS)

depend:

.c.o:
	$(CC) $(CFLAGS) -c $<
