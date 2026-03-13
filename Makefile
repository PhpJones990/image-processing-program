BITMAP_DEP = bitmap_reader.c data_types.h filters/algo.h filters/algo.c 
FILTERS_DEP = filters/algo.h filters/algo.c 

img_p.exe: bitmap_reader.o filters_algo.o
	gcc -g -Wall bitmap_reader.o filters_algo.o -o img_p.exe

bitmap_reader.o: $(BITMAP_DEP)
	gcc -g -Wall -c bitmap_reader.c -o bitmap_reader.o

filters_algo.o: $(FILTERS_DEP)
	gcc -g -Wall -c filters/algo.c -o filters_algo.o 

run: img_p.exe
	./img_p.exe test_image.bmp output_file.bmp

clean: 
	del -Q img_p.exe
	del -Q output_file.bmp
	del -Q *.o