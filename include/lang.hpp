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
        std::string name;
        std::string comment;
        std::string comment_block_open;
        std::string comment_block_close;

        public:

            uint files;
            uint code;

            /* Init */
            lang(std::string& name, std::string& comment,
                    std::string& comment_block_open, 
                    std::string& comment_block_close);

            /* Get language name */
            std::string& get_name();

            /* Add file to file counter */
            void add_file();

            /* Add code lines to code counter */
            void add_code(uint code_lines);

            /* Get language line comment token */
            std::string& get_comment();

            /* Get language comment block open token */
            std::string& get_comment_block_open();

            /* Get language comment block close token */
            std::string& get_comment_block_close();
    };
}

#endif
