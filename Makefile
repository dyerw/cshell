TARGET = 3600sh

default: all

$(TARGET): $(TARGET).c
	#gcc -std=c99 -O0 -g -lm -Wall -pedantic -Werror -Wextra -o $@ $<
	gcc -std=c99 -O0 -g -lm -Wall -pedantic -Werror -Wextra -o ./bin/$@ $< parsing.c

all: $(TARGET) 

run: all
		./bin/3600sh

debug_shell: all
		gdb ./bin/3600sh

debug_utest: unittests
					gdb ./bin/unittests

test: all
	cp bin/3600sh ./3600sh
	./test
	rm ./3600sh

unittests: unittests.c
	gcc -std=c99 -g -lm -Wall -pedantic -Wextra unittests.c parsing.c -o ./bin/unittests

utest: unittests
	./bin/unittests

clean:
	rm ./bin/$(TARGET)

cleanall:
	rm bin/*
