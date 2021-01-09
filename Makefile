# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

CC = @g++ -I include -Wall -c
MKDIR = @if [ ! -d obj ]; then mkdir obj; fi

all: obj/main.o obj/args.o obj/output.o
	$(MKDIR)
	@g++ -Wall $(shell find obj -type f -printf "%p ") -o bin/loc

obj/main.o: src/main.cpp
	$(CC) src/main.cpp -o obj/main.o

obj/args.o: src/args.cpp
	$(CC) src/args.cpp -o obj/args.o

obj/output.o: src/output.cpp
	$(CC) src/output.cpp -o obj/output.o

clean:
	@rm -f obj/*
