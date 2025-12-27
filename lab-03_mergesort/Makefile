CFlags = -Werror -Wall -Wextra

all: obj include src obj/mergesort.o obj/main.o lab-03_mergesort

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/mergesort.o: src/mergesort.c
	gcc -c src/mergesort.c -I include $(CFlags) -o obj/mergesort.o

obj/main.o: src/main.c
	gcc -c src/main.c -I include $(CFlags) -o obj/main.o


lab-03_mergesort: obj/mergesort.o obj/main.o 
	gcc obj/mergesort.o obj/main.o -o lab-03_mergesort



clean:
	rm -rf obj
	rm lab-03_mergesort