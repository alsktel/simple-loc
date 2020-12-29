/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc arguments searching functions 
 */

#ifndef __LOC_ARGS_H__
#define __LOC_ARGS_H__

/* Search for argument, return index or 0 if not found */
int arg_search(int argc, const char** argv, const char* arg);

/* Get argument parameter */
const char* get_arg_param(int argc, const char** argv, const char* arg); 

#endif
