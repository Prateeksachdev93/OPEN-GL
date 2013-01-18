CC = g++
CFLAGS = -Wall
PROG = Assignment1_201101015

SRCS = Assignment1_201101015.cpp
LIBS = -lg -lGLUT -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
