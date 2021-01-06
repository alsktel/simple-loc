/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc arguments parser
 */

#include <string>

#include <args.hpp>
#include <output.hpp>

/* Parse arguments and call specified functions */
int loc::args::parse(int argc, const char** argv)
{
    std::string arg;

    for(int i = 0; i < argc; i++)
    {
        arg = std::string(argv[i]);

        /* Show help */
        if(arg == "-h" || arg == "--help")
        {
            output::help();

            return 0;
        }
    }

    return 0;
}
