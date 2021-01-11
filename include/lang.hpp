/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc language info storage implementation
 */

#ifndef __LANG_HPP__
#define __LANG_HPP__

#include <string>

namespace loc
{
    class lang
    {
        uint files;
        uint code;
        std::string name;

        public:

            /* Init */
            lang(std::string& name);

            /* Get language name */
            std::string& get_name();

            /* Add file to file counter */
            void add_file();

            /* Add code lines to code counter */
            void add_code(uint code_lines);
    };
}

#endif
