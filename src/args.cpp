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
int loc::args::parse(int argc, const char** argv)
{
    if(argc == 1)
    {
        output::help();

        return 0;
    }

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
        else if(arg == "-f" || arg == "--files-only")
        {
            std::string conf_path = CONFIG; 

            #ifndef __local_dev__
                conf_path = "/" + conf_path;
            #endif

            parser parser(conf_path);

            for(auto & file : std::filesystem::directory_iterator("."))
            {
                if(file.is_directory())
                    continue;

                std::string file_path = file.path();

                if(file_path[0] == '.')
                {
                    file_path.erase(0, 2);
                }

                parser.file(file_path);
            }

            output::name();
            output::head();

            for(size_t i = 0; i < parser.langs.size(); i++)
            {
                output::lang(parser.langs[i].get_name(), 
                                parser.langs[i].files, 
                                parser.langs[i].code);
            }

            output::tail();
        }
    }

    return 0;
}
