# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

# Simple-loc makefile

all:
	@gcc -Wall -I include/ -o bin/loc src/main.c src/output.c src/args.c

test:
	@./bin/loc
