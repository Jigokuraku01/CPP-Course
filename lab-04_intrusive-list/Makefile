CFlags = -Werror -Wall -Wextra

all: obj include src obj/clist.o obj/main.o lab-04_intrusive-list

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/clist.o: src/clist.c
	gcc -c src/clist.c -I include $(CFlags) -o obj/clist.o

obj/main.o: src/main.c
	gcc -c src/main.c -I include $(CFlags) -o obj/main.o


lab-04_intrusive-list: obj/clist.o obj/main.o 
	gcc obj/clist.o obj/main.o -o lab-04_intrusive-list




clean:
	rm -rf obj
	rm lab-04_intrusive-list