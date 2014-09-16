TARGET = 3600sh

$(TARGET): $(TARGET).c
	#gcc -std=c99 -O0 -g -lm -Wall -pedantic -Werror -Wextra -o $@ $<
	gcc -std=c99 -O0 -g -lm -Wall -pedantic -Wextra -o ./bin/$@ $< parsing.c


all: $(TARGET) 

test: all
	./test

unittests: unittests.c
	gcc -std=c99 -g -lm -Wall -pedantic -Wextra unittests.c parsing.c -o ./bin/unittests

utest: unittests
	./bin/unittests

clean:
	rm ./bin/$(TARGET)

cleanall:
	rm bin/*
