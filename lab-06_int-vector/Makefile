CFlags = -Werror -Wall -Wextra

all: obj include src obj/my_vector.o obj/main.o lab-06_int-vector

obj: 
	mkdir obj
include: 
	mkdir include
src:
	mkdir src

obj/my_vector.o: src/my_vector.cpp
	g++ -c -O2 src/my_vector.cpp -I include $(CFlags) -o obj/my_vector.o

obj/main.o: src/main.cpp
	g++ -c -O2 src/main.cpp -I include $(CFlags) -o obj/main.o


lab-06_int-vector: obj/my_vector.o obj/main.o
	g++ obj/my_vector.o obj/main.o -o lab-06_int-vector




clean:
	rm -rf obj
	rm lab-06_int-vector
