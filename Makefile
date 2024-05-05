IDIR = ./include
ODIR = ./objs

CC=gcc
CFLAGS=-I$(IDIR)

LDIR =../lib

LIBS = -lm

_DEPS = common.h lib.h Read_boot_sector.h Read_Display_Data.h imath.h hex.h sort.h strHandler.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

# _OBJ = main.o common.o Read_boot_sector.o Read_Display_Data.o
_OBJ = main.o common.o Read_boot_sector.o Read_Display_Data.o imath.o hex.o sort.o strHandler.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)


a: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 