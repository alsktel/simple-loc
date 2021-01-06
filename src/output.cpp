/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc output functions
 */

#include <stdio.h>

#include <output.hpp>

#define DEBUG

/* Print name and version */
void loc::output::name()
{
    output::tail();

    float version;

    FILE* fd = fopen("/etc/simple-loc/loc.conf", "r");

    if(fd == NULL)
    {
        #ifdef DEBUG
            fd = fopen("etc/simple-loc/loc.conf", "r");
        #else

        #endif
    }

    fscanf(fd, "%f", &version);
    fclose(fd);

    printf("\033[1m%s v. %.1f\033[0m\n", "Simple code lines counter", version);
    printf("Copyright © eastev <eastevrud31@gmail.com>\n\n");
}

/* Print usage and options list */
void loc::output::help()
{
    output::name();
    printf("\033[1m%s\033[0m %s ", "Usage:", "loc");
    printf("\033[2m%s\033[0m\n", "[OPTIONS]");
    printf("Print info about lines of code of each language for each file\n");
    printf("in this directory and subdirectories.\n\n");
    printf("\033[1mOptions list:\033[0m\n");
    printf("%-24s %s\n", "-h --help", "Print this help");
    printf("%-24s %s\n", "-c --configure", "Run configuration tool");
    printf("%-24s %s\n", "-l --language", "Process only specified language");
    printf("%-24s %s\n", "-f --files-only", "Process files only (no subdirs)");
    printf("%-24s %s\n", "-d --directory", "Start from specified directory");
    printf("\n%s", "Without any option loc will start from current directory");
    printf("\n");
    output::tail();
}

/* Print 2 lines trailing space */
void loc::output::tail()
{
    printf("\n\n");
}
