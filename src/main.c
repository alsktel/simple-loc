/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple linux tool for counting source code lines, written in C
 */

#include <loc_output.h>
#include <loc_args.h>

int main(int argc, const char** argv)
{
    print_logo(0.0);
    
    if(argc == 1 || arg_search(argc, argv, "-h") ||
        arg_search(argc, argv, "--help"))
    {
        print_help();
    }

    print_sep();

    return 0;
}
