/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc output class
 */

#ifndef __OUTPUT_HPP__
#define __OUTPUT_HPP__

#include <string>

namespace loc 
{
    /* Output provider */
    class output
    {
        public:

            /* Print help (usage and options) */
            static void help();

            /* Print table header */
            static void head();

            /* Print 2 lines trailing space */
            static void tail();

            /* Print name and version */
            static void name();

            /* Print statistics for specified language */
            static void lang(std::string lang, uint files, uint code);
    };
}

#endif
