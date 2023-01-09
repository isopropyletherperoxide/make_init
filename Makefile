all:
	cc main.c -Wall -lm -lgit2 -o make_init
clean:
	rm make_init
install:
	cp make_init /usr/local/bin/
