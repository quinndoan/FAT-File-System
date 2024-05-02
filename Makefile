IDIR = ./include
ODIR = ./objs

CC=gcc
CFLAGS=-I$(IDIR)

LDIR =../lib

LIBS = -lm

_DEPS = hex.h imath.h sort.h strHandler.h linked_list.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = hex.o imath.o main.o sort.o strHandler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)


a: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)
# $(CC) -o $@ $^ $(CFLAGS) 


.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 