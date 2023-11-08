# makefile The Boys
# Carlos Maziero - DINF/UFPR, 10/2023

CC      = gcc
CFLAGS  = -Wall -Wextra -g -std=c99 -pedantic
LDLIBS  = -lm
MAIN    = theboys
ENTREGA = $(MAIN)-entrega
TESTES  = testa-lef

# programa principal
$(MAIN):   $(MAIN).o lef.o lista.o set.o simulador.o  eventos.o
$(MAIN).o: $(MAIN).c lef.h lista.h set.h simulador.h  eventos.h	
 

# TADs
lef.o:   lef.c   lef.h
lista.o: lista.c lista.h
set.o:   set.c   set.h
simulador.o: simulador.c simulador.h
eventos.o: eventos.c eventos.h

# Teste da LEF
testa-lef:    testa-lef.o  lef.o
testa-lef.o:  testa-lef.c  lef.h

clean:
	rm -f *.o *~ $(MAIN) $(TESTES) $(ENTREGA) $(ENTREGA).tgz

entrega: clean
	mkdir $(ENTREGA)
	cp *.c *.h makefile $(ENTREGA)
	rm -f $(ENTREGA)/testa*
	chmod 600 $(ENTREGA)/*
	tar czvf $(ENTREGA).tgz $(ENTREGA)
	rm -rf $(ENTREGA)
	@echo "Arquivo $(ENTREGA).tgz criado para entrega"

