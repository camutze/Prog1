# makefile generico para os TADs
# Carlos Maziero - DINF/UFPR

CC     = gcc
CFLAGS = -Wall -g
LIB    = liblista
MAIN   = tp4

$(MAIN):   $(MAIN).o $(LIB).o
$(MAIN).o: $(MAIN).c $(LIB).h
$(LIB).o:  $(LIB).c  $(LIB).h

clean:
	rm -f *.o *~ $(MAIN)
