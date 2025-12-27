CFlags = -Werror -Wall -Wextra

all: obj include src obj/bmp.o obj/stego.o obj/main.o hw-01_bmp

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/bmp.o: src/bmp.c
	gcc -c src/bmp.c -I include $(CFlags) -o obj/bmp.o

obj/stego.o: src/stego.c
	gcc -c src/stego.c -I include $(CFlags) -o obj/stego.o

obj/main.o: src/main.c
	gcc -c src/main.c -I include $(CFlags) -o obj/main.o


hw-01_bmp: obj/bmp.o obj/main.o obj/stego.o
	gcc obj/bmp.o obj/main.o obj/stego.o -o hw-01_bmp

clean:
	rm -rf obj
	rm hw-01_bmp