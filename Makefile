
CC = gcc
COMP_ATT = -Wall
# -Werror -pedantic 
LIBS = -lX11
BUILD = build

SOURCES = hello.c init.c

OBJECTS = hello.o init.o

OUT = xwin1


#	 $(CC)  $(SOURCES) $(LIBS)  $(COMP_ATT)

all:	$(SOURCES) $(OUT)

debug:
	$(CC)  $(SOURCES) -ggdb  $(COMP_ATT) $(LIBS)

clean:
	rm -f *.o

$(OUT): $(OBJECTS) 
	$(CC) $(addprefix $(BUILD)/,$^) $(LIBS) -o $@


.c.o:
	$(CC) $(COMP_ATT) $< -c -o $(BUILD)/$*.o 
