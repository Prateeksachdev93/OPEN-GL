CC = g++
CFLAGS = -Wall
PROG = main

SRCS = main.cpp
LIBS = -lg -lGLUT -lGLU

all: $(PROG)

$(PROG):	$(SRCS)
	$(CC) $(CFLAGS) -o $(PROG) $(SRCS) $(LIBS)

clean:
	rm -f $(PROG)
