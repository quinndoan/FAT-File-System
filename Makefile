IDIR = ./include
ODIR = ./objs

CC=gcc
CFLAGS=-I$(IDIR)

LDIR =../lib

LIBS = -lm

_DEPS = common.h decode.h lib.h Read_boot_sector.h Read_Display_Data.h OpenFile_Console.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o common.o Read_boot_sector.o Read_Display_Data.o OpenFile_Console.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)
$(ODIR)/%.o: $(IDIR)/%.c $(DEPS) 
	$(CC) -c -o $@ $< $(CFLAGS)


read: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 