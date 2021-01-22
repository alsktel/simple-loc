/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc output functions
 */

#include <fstream>

#include <output.hpp>

#define CONFPATH "etc/simple-loc/loc.conf"

/* Print name and version */
void loc::output::name()
{
    output::tail();

    std::string v;
    std::string config_path = CONFPATH;
    std::string line;
    std::ifstream reader;

    #ifndef __local_dev__
        config_path = "/" + config_path;
    #endif

    reader.open(config_path);

    while(!reader.eof())
    {
        std::getline(reader, line);

        if(line.find("#") == std::string::npos && line.find("VERSION") != 
            std::string::npos)
        {
            v = line.substr(line.find("=") + 1 + 1);
        }
    }

    reader.close();

    printf("\033[1m%s v. %s\033[0m\n", "Simple code lines counter", v.c_str());
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

/* Print table header */
void loc::output::head()
{
    printf("\033[1m%-16s  %8s  %8s\033[0m\n", "Language", "Files", "Code");
}

 /* Print statistics for specified language */
void loc::output::lang(std::string lang, uint files, uint code)
{
    printf("%-16s  %*d  %*d\n", lang.c_str(), 8, files, 8, code);
}
