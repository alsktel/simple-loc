/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc arguments searching functions 
 */

#include <string.h>

#include <loc_args.h>

/* Search for argument, return index or 0 if not found */
int arg_search(int argc, const char** argv, const char* arg)
{
    for(int i = 1; i < argc; i++)
    {
        if(!strcmp(argv[i], arg))
        {
            return i;
        }
    }

    return 0;
}

/* Get argument parameter */
const char* get_arg_param(int argc, const char** argv, const char* arg)
{
    int index = arg_search(argc, argv, arg);

    if(index == 0 || index == argc - 1)
    {
        return NULL;
    }

    return argv[index + 1];
}
