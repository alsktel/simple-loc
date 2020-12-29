/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc terminal output functions
 */

#include <stdio.h>

/* Print logo and copyright notice */
void print_logo(float version)
{
    printf("\n\n\033[1m%s ", "Simple source code lines counter");
    printf("v. %.1f\033[0m\n", version);
    printf("%s\n", "Copyright © eastev <eastevrud31@gmail.com>");
}

/* Print bottom separator blank space */
void print_sep()
{
    printf("\n\n");
}

/* Print table header */
void print_header()
{
    printf("\033[1m%-16s%16s%16s\033[0m\n", "Language", "Code", "Files");
}

/* Print info about one language */
void print_lang(const char* lang, int code, int files)
{
    printf("%-16s%16d%16d\n", lang, code, files);
}

/* Print tool info and help */
void print_help()
{
    printf("\n\033[1m%s\033[0m \033[3m%s \033[2m%s\033[0m\n", "Usage:", "loc", "[OPTIONS]");
    printf("Count and print info about lines of source code.\n\n");
    printf("\033[1m%s\033[0m\n", "Options list:");
    printf("%-10s\t%-10s\t%-50s\n", "-h --help", "NONE", "Show this help");
    printf("%-10s\t%-10s\t%-50s\n", "-f --file", "FILE", "Process specified file");
    printf("%-10s\t%-10s\t%-50s\n", "-d --dir", "DIRECTORY", "Process all files in specified directory");
    printf("%-10s\t%-10s\t%-50s\n", "-l --lang", "LANGUAGE", "Process specified language only");
    printf("%-10s\t%-10s\t%-50s\n", "-c --conf", "NONE", "Run configuration tool");
    printf("\n\033[1m%s\033[0m\n", "Specifying no parameters runs loc for current directory.");
}
