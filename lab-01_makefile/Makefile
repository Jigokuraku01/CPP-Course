CFlags = -Werror -Wall -Wextra

all: obj include src obj/main.o obj/io.o obj/util.o obj/algorithm.o lab-01_makefile

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/main.o: src/main.c
	gcc -c src/main.c -I include $(CFlags) -o obj/main.o

obj/io.o: src/io.c
	gcc -c src/io.c -I include $(CFlags) -o obj/io.o


obj/util.o: src/util.c
	gcc -c src/util.c -I include $(CFlags) -o obj/util.o


obj/algorithm.o: src/algorithm.c
	gcc -c src/algorithm.c -I include $(CFlags) -o obj/algorithm.o


lab-01_makefile: obj/main.o obj/io.o obj/util.o obj/algorithm.o
	gcc obj/main.o obj/io.o obj/util.o obj/algorithm.o -o lab-01_makefile



clean:
	rm -rf obj
	mkdir obj
	rm lab-01_makefile