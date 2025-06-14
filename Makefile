img_p.exe: bitmap_reader.o black_and_white_normal.o
	gcc -g -Wall bitmap_reader.o black_and_white_normal.o -o img_p.exe

bitmap_reader.o: bitmap_reader.c data_types.h filters/black_and_white_normal.h filters/black_and_white_normal.c
	gcc -g -Wall -c bitmap_reader.c -o bitmap_reader.o

black_and_white_normal.o: data_types.h filters/black_and_white_normal.h filters/black_and_white_normal.c
	gcc -g -Wall -c filters/black_and_white_normal.c -o black_and_white_normal.o

run: img_p.exe
	./img_p.exe test_image.bmp output_file.bmp

clean: 
	del -Q img_p.exe
	del -Q *.o