CCOMP=gcc
LINKER=gcc
CFLAGS=-O0 -g
LDFLAGS=-O0 -g

run:
	$(CCOMP) lib.c -o lib.o -c $(CFLAGS)
	$(CCOMP) example.c -o example.o -c $(CFLAGS)
	$(LINKER) lib.o example.o -o a.out $(LDFLAGS)
	./a.out
