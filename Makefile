CPPCOMP=g++
CPPFLAGS=-c -O0 -g -Wall -Wextra -std=c++23 #-DDEBUG
LINKER=g++
LDFLAGS=-O0 -g

run:
	$(CPPCOMP) lib.cpp -o lib.o $(CPPFLAGS)
	$(CPPCOMP) example.cpp -o example.o $(CPPFLAGS)
	$(LINKER) lib.o example.o -o a.out $(LDFLAGS)
	./a.out
