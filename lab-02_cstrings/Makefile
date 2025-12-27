CFlags = -Werror -Wall -Wextra

all: obj include src obj/str.o obj/test_str.o obj/test.o lab-02_cstrings

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/str.o: src/str.c
	gcc -c src/str.c -I include $(CFlags) -o obj/str.o

obj/test_str.o: src/test_str.c
	gcc -c src/test_str.c -I include $(CFlags) -o obj/test_str.o


obj/test.o: src/test.c
	gcc -c src/test.c -I include $(CFlags) -o obj/test.o


lab-02_cstrings: obj/str.o obj/test_str.o obj/test.o
	gcc obj/str.o obj/test_str.o obj/test.o  -o lab-02_cstrings



clean:
	rm -rf obj
	rm lab-02_cstrings