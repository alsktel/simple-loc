/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc arguments parser
 */

#ifndef __ARGS_HPP__
#define __ARGS_HPP__

#include <string>
#include <vector>

namespace loc
{
    /* Arguments parser class */
    class args
    {
        public:
            static int parse(int argc, std::vector<std::string>& argv);
    };
}

#endif
