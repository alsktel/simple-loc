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

        /* Get file extension associated with language */
        std::string get_lang_ext(std::string& lang);

        /* Extension language parsing algorithm */
        void parse_lang(std::string& lang, std::string& file);

        public:
            std::vector<loc::lang> langs;

            /* Init */
            parser(std::string& config);

            /* Dispose */
            ~parser();

            /* Parse one file and add info to one languages in vector */
            void file(std::string& name);

            /* Parse all files associated with specific language */
            void language(std::string& language);
            void language(std::string& language, std::string& directory);

            /* Parse all in specified directory */
            void dir(std::string& name);

            /* Process only files in curent directory and in other directory */
            void files_only();
            void files_only(std::string& dir);
    };
}

#endif
