cc = g++
cflags = -Wall -Werror -pedantic -std=gnu++11 -ggdb3
dedup: dedup.cpp
	$(cc) -o $@ $(cflags) $<
