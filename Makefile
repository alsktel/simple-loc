# SPDX-License-Identifier: GPL-3.0
# Copyright © eastev <eastevrud31@gmail.com>

CC = @g++ -g -I include -D __local_dev__ -Wall -c -std=c++20
OBJ = obj
SRC = src
OBJECTS = $(patsubst $(SRC)/%.cpp, $(OBJ)/%.o, \
		$(shell find src -type f -printf "%p "))

all: release
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
	@if [ ! -d bin ]; then mkdir bin; fi
	@g++ -Wall $(OBJECTS) -o bin/loc
	@if (( $$? == 0 )); then echo -e "\033[0;32mSuccess\033[0m!"; fi

release_set:
	@$(eval CC = @g++ -I include -Wall -c -std=c++20)

$(OBJ)/%.o: $(SRC)/%.cpp
	@set -o pipefail
	@if [ ! -d obj ]; then mkdir obj; fi
	@printf "%-64s" "Compilling source: '$<' to object: '$@'"
	$(CC) $< -o $@
	@if (( $$? == 0 )); then printf '%16s\033[0;32m%s\033[0m%s\n' \
	"[" "OK" "]"; fi

clean:
	@rm -f obj/*
	@rm -f bin/*

install:
	@echo ""
	@echo -e "Installing \033[1mSimple-loc\033[0m"
	@if [ ! -f bin/loc ]; then \
	echo -e "\033[0;31mError\033[0m: Simple-loc needs to be builded"; \
	echo ""; exit 1; fi
	@cp bin/loc /bin/loc
	@chmod a+x /bin/loc
	@cp -r etc/simple-loc /etc
	@echo -e "Installation completed \033[0;32msuccessfully\033[0m!"
	@echo ""

uninstall:
	@echo ""
	@echo -e "Uninstalling \033[1mSimple-loc\033[0m"
	@if [ -f /bin/loc ]; then rm /bin/loc; fi
	@if [ -d /etc/simple-loc ]; then rm -rf /etc/simple-loc/; fi
	@echo -e "Uninstallation completed \033[0;32msuccessfully\033[0m!"
	@echo ""

help:
	@echo ""
	@echo -en "\033[1mTo build simple-loc use:\033[0m "
	@echo -e "\033[3mmake\033[0m"
	@echo -en "\033[1mTo install simple-loc use:\033[0m "
	@echo -e "\033[3msudo make install\033[0m"
	@echo -en "\033[1mTo uninstall simple-loc use:\033[0m "
	@echo -e "\033[3msudo make uninstall\033[0m"
	@echo ""
