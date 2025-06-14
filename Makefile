BITMAP_DEP = bitmap_reader.c data_types.h filters/black_and_white_normal.h filters/black_and_white_normal.c filters/box_blur.c filters/box_blur.h
B_W_DEP = data_types.h filters/black_and_white_normal.h filters/black_and_white_normal.c
BOX_BLUR_DEP = data_types.h filters/box_blur.c filters/box_blur.h
FILTERS_DEP = black_and_white_normal.o box_blur.o

img_p.exe: bitmap_reader.o filters_algo.o
	gcc -g -Wall bitmap_reader.o filters_algo.o -o img_p.exe

bitmap_reader.o: $(BITMAP_DEP)
	gcc -g -Wall -c bitmap_reader.c -o bitmap_reader.o

filters_algo.o: $(FILTERS_DEP)
	ld -r $(FILTERS_DEP) -o filters_algo.o

black_and_white_normal.o: $(B_W_DEP)
	gcc -g -Wall -c filters/black_and_white_normal.c -o black_and_white_normal.o

box_blur.o: $(BOX_BLUR_DEP)
	gcc -g -Wall -c filters/box_blur.c -o box_blur.o 

run: img_p.exe
	./img_p.exe test_image.bmp output_file.bmp

clean: 
	del -Q img_p.exe
	del -Q output_file.bmp
	del -Q *.o