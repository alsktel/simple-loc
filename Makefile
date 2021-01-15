# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

CC = @g++ -g -I include -D __local_dev__ -Wall -c -std=c++20
OBJ = obj
SRC = src
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, \
		$(shell find src -type f -printf "%p "))

all: debug
	@echo ""

debug: d_log assemble

d_log:
	@echo ""
	@echo -e "Creating \033[1mdebug\033[0m build"

release: r_log release_set assemble

r_log:
	@echo ""
	@echo -e "Creating \033[1mrelease\033[0m build"

assemble: $(OBJECTS)
	@echo -n "Assembling loc - "
	@if [ ! -d obj ]; then mkdir bin; fi
	@g++ -Wall $(OBJECTS) -o bin/loc
	@if (( $$? == 0 )); then echo -e "\033[0;32mSuccess\033[0m!"; fi

release_set:
	CC = @g++ -g -I include -D __local_dev__ -Wall -c -std=c++20

$(OBJ)/%.o: $(SRC)/%.cpp
	@set -o pipefail
	@if [ ! -d obj ]; then mkdir obj; fi
	@printf "%-64s" "Compilling source: '$<' to object: '$@'"
	$(CC) $< -o $@
	@if (( $$? == 0 )); then printf '%16s\033[0;32m%s\033[0m%s\n' \
	"[" "OK" "]"; fi

clean:
	@rm -f obj/*
