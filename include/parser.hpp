/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc code parser
 */

#ifndef __PARSER_HPP__
#define __PARSER_HPP__

#include <string>
#include <vector>
#include <fstream>

#include <lang.hpp>

namespace loc
{
    class parser
    {
        std::ifstream config_reader;
        
        /* Get language name by file extension */
        lang get_lang(std::string& ext);

        public:

            std::vector<loc::lang> langs;

            /* Init */
            parser(std::string& config);

            /* Dispose */
            ~parser();

            /* Parse one file and add info to one languages in vector */
            void file(std::string& name);

            /* Parse files with specific extension in current directory */
            void ext(std::string& dir_name, std::string& ext);

            /* Parse all files in directory */
            void dir(std::string& name);

            /* Parse all files and subdirectories recursively */
            void all(std::string& name);
    };
}

#endif
