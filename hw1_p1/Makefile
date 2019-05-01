compile: hw1_p1.o huffman.o
	g++ hw1_p1.o huffman.o -o hw1_p1

hw1_p2.o: hw1_p2.cpp
	g++ -c hw1_p2.cpp

huffman.o: huffman.cpp huffman.h
	g++ -c huffman.cpp

clean:
	rm *.o

# test1:
# 	./hw1_p2 -bin_to_dec 0x80000000

# test2:
# 	./hw1_p2 -dec_to_bin 0.5

# test3:
# 	./hw1_p2 -encode m < input.pgm

# test4:
# 	./hw1_p2 -encode 3 < msg1.pgm

# test5:
# 	./hw1_p2 -decode m xres yres max < image.enc

# test6:
# 	./hw1_p2 -encode 3 < sena.pgm | ./hw1_p2 -decode 3 256 256 255