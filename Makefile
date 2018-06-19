
CC = gcc
COMP_ATT = -Wall
# -Werror -pedantic 
LIBS = -lX11
BUILD = build

SOURCES = hello.c

OBJECTS = hello.o \

OUT = xwin1



all:
	 $(CC)  $(SOURCES) $(LIBS)  $(COMP_ATT)
	#$(SOURCES) $(OUT)

debug:
	$(CC)  $(SOURCES) -ggdb  $(COMP_ATT) $(LIBS)

clean:
	rm -f *.o

#$(OUT): $(OBJECTS) 
 	#$(CC) $(OBJECTS) $(LIBS) -o $@


%.o : %.c
	$(CC) $< -c $(COMP_ATT) -o $@
