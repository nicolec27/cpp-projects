CC = gcc
CFLAGS = -Wall -std=c18 -ggdb

test : baconEncode baconDecode test.txt
	./baconEncode <test.txt >test_encode.txt
	cat test_encode.txt
	./baconDecode <test_encode.txt >test_decode.txt
	diff -i test.txt test_decode.txt
	
baconEncode : baconEncode.c baconCode.h
	${CC} ${CFLAGS} -o baconEncode baconEncode.c

baconDecode : baconDecode.c baconCode.h
	${CC} ${CFLAGS} -o baconDecode baconDecode.c

	
clean :
	-rm baconEncode baconDecode
	-rm test_encode.txt test_decode.txt