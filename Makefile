# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

I = -I include

all: obj/main.o obj/args.o obj/output.o
	@if [ ! -d obj ]; then mkdir obj; fi
	@g++ -Wall obj/main.o obj/args.o obj/output.o -o bin/loc

obj/main.o: src/main.cpp
	@g++ $I -Wall -c src/main.cpp -o obj/main.o

obj/args.o: src/args.cpp
	@g++ $I -Wall -c src/args.cpp -o obj/args.o

obj/output.o: src/output.cpp
	@g++ $I -Wall -c src/output.cpp -o obj/output.o

clean:
	@if [ ! -d obj ]; then mkdir obj; fi
	@rm -f obj/*
