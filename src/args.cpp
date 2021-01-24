/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc arguments parser
 */

#include <string>
#include <iostream>
#include <filesystem>

#include <args.hpp>
#include <output.hpp>
#include <parser.hpp>

#define CONFIG "etc/simple-loc/langs.conf"

/* Parse arguments and call specified functions */
int loc::args::parse(int argc, std::vector<std::string>& argv)
{
    std::string conf_path = CONFIG; 

    #ifndef __local_dev__
        conf_path = "/" + conf_path;
    #endif

    std::string arg;
    loc::parser parser(conf_path);

    if(argc == 1)
    {
        std::string cdir = ".";

        parser.dir(cdir);
    }
    else
    {
        for(int i = 1; i < argc; i++)
        {
            arg = std::string(argv[i]);

            /* Show help */
            if(arg == "-h" || arg == "--help")
            {
                output::help();

                return 0;
            }
            else if(arg == "-f" || arg == "--files-only")
            {
                std::vector<std::string>::iterator iterator;
                iterator = std::find(argv.begin(), argv.end(), "-d");

                if(iterator != argv.end())
                    parser.files_only(*(std::next(iterator)));
                else
                {
                    iterator = std::find(argv.begin(), argv.end(),      
                                            "--directory");

                    if(iterator != argv.end())
                        parser.files_only(*(std::next(iterator)));
                    else
                        parser.files_only();
                }

                break;
            }
            else if(arg == "-d" || arg == "--directory")
            {
                parser.dir(argv[++i]);

                break;
            }
            else if(arg == "-l" || arg == "--language")
            {
                std::vector<std::string>::iterator iterator;
                iterator = std::find(argv.begin(), argv.end(), "-d");

                if(iterator != argv.end())
                    parser.language(argv[++i], *(std::next(iterator)));
                else
                {
                    iterator = std::find(argv.begin(), argv.end(), 
                                            "--directory");

                    if(iterator != argv.end())
                        parser.language(argv[++i], *(std::next(iterator)));
                    else
                        parser.language(argv[++i]);
                }

                break;
            }
            else
            {
                printf("\033[0;31mError\033[0m: No option %s\n", arg.c_str());
                output::tail();

                return 1;
            }
        }
    }

    output::name();
    output::head();

    for(size_t i = 0; i < parser.langs.size(); i++)
    {
        output::lang(parser.langs[i].get_name(), parser.langs[i].files, 
                        parser.langs[i].code);
    }

    output::tail();

    return 0;
}
