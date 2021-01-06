# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

all: build/main.o build/help.o
	gcc -Wall build/main.o build/help.o -o bin/loc

build/main.o: src/main.cpp
	gcc -Wall -c src/main.cpp -o build/main.o

build/help.o: src/output/help.c
	gcc -Wall -c src/output/help.c -o build/help.o
