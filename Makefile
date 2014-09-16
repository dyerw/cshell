TARGET = 3600sh
CFILES = $(wildcard *.c)

$(TARGET): $(TARGET).c
	#gcc -std=c99 -O0 -g -lm -Wall -pedantic -Werror -Wextra -o $@ $<
	gcc -std=c99 -O0 -g -lm -Wall -pedantic -Wextra -o $@ $<

%: %.c
	gcc -g -std=c99 -O0 -o $@ $< -lm

all: $(basename $(CFILES))

test: all
	./test

utest: all
	./unittests

clean:
	rm $(TARGET)

