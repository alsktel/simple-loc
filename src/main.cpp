/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc is a simple code lines counter. Created for Linux
 */

#include <args.hpp>

int main(int argc, const char** argv)
{
    return loc::args::parse(argc, argv);
}
