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
    std::vector<std::string> _argv;

    for(int i = 0; i < argc; i++)
    {
        _argv.push_back(argv[i]);
    }

    return loc::args::parse(argc, _argv);
}
