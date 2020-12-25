/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc terminal output functions
 */

#ifndef __LOC_OUTPUT_H__
#define __LOC_OUTPUT_H__

/* Print logo and copyright notice */
void print_logo();

/* Print tool info and help */
void print_help();

/* Print table header */
void print_header();

/* Print info about one language */
void print_lang(const char* lang, int code, int files);

/* Print bottom separator blank space */
void print_sep();

#endif
