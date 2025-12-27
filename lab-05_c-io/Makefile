CFlags = -Werror -Wall -Wextra

all: obj include src obj/clist.o obj/main.o obj/point_list.o lab-05_c-io

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

obj/point_list.o: src/point_list.c
	gcc -c src/point_list.c -I include $(CFlags) -o obj/point_list.o


lab-05_c-io: obj/clist.o obj/main.o obj/point_list.o
	gcc obj/clist.o obj/main.o obj/point_list.o -o lab-05_c-io




clean:
	rm -rf obj
	rm lab-05_c-io
