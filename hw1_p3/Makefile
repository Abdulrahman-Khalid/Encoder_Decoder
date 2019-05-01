compile: hw1_p3.o lz77.o
	g++ -g hw1_p3.o lz77.o -o hw1_p3

debug: hw1_p3.o lz77.o
	g++ -g hw1_p3.o lz77.o

hw1_p3.o: hw1_p3.cpp
	g++ -c hw1_p3.cpp

lz77.o: lz77.cpp lz77.h
	g++ -c lz77.cpp

clean:
	rm *.o
