/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc code parsing functions
 */

#include <limits>
#include <algorithm>

#include <parser.hpp>

#define UNSUPPORTED "NONE"

void skip_comments(std::ifstream& file)
{
    char c;

    while(true)
    {
        c = file.get();

        if(c == '#')
        {
            file.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
        }
        else
        {
            break;
        }
    }
}

loc::parser::parser(std::string& config)
{
    config_reader.open(config);
    
    skip_comments(config_reader);

    langs = std::vector<loc::lang>();
}

loc::parser::~parser()
{
    config_reader.close();
    langs.clear();
}

loc::lang loc::parser::get_lang(std::string& ext)
{
    std::string name;
    std::string token;
    std::string _ext;
    std::string comment;
    std::string b_comment_open;
    std::string b_comment_close;
    std::string arr_token;

    while(!config_reader.eof())
    {
        config_reader >> token;

        if(token == "LANG")
        {
            config_reader >> token;
            config_reader >> name;
            config_reader >> token;
            
        }
        else if(token == "EXT")
        {
            config_reader >> token;
            config_reader >> _ext;

            if(ext != _ext)
            {
                while(token != "{" && !config_reader.eof())
                {
                    config_reader >> token;
                }
            }
        }
        else if(token == "COMMENT")
        {
            config_reader >> token;
            config_reader >> comment;
        }
        else if(token == "COMMENT_BLOCK")
        {
            config_reader >> token;

            std::getline(config_reader, arr_token);

            arr_token = arr_token.substr(arr_token.find('[') + 1);
            arr_token.pop_back();
            b_comment_close = arr_token.substr(arr_token.find(',') + 2);
            b_comment_open = arr_token.substr(0, arr_token.find(','));
        }
        else if(token == "}")
        {
            config_reader.clear();
            config_reader.seekg(0);

            return lang(name, comment, b_comment_open, b_comment_close);
        }
    }

    fprintf(stderr, "\033[0;33mWARNING\033[0m: Unsupported language ");
    fprintf(stderr, "with file extension '.%s'\n", ext.c_str());

    config_reader.clear();
    config_reader.seekg(0);

    return lang(name = UNSUPPORTED, comment, b_comment_open, b_comment_close);
}

bool is_ugly_code_line(std::string& line, loc::lang& lang)
{
    if(line.size() == 0 || line.find(lang.get_comment()) == 0)
        return false;

    if(line.find(lang.get_comment_block_open()) == 0)
    {
        if(line.find(lang.get_comment_block_close()) == std::string::npos)
            return false;

        line = line.substr(line.find(lang.get_comment_block_close()) + 1);

        return is_ugly_code_line(line, lang);
    }
    else
    {
        return true;
    }
}

uint count_code(std::string& file_name, loc::lang& lang)
{
    bool cf = true;
    uint code = 0;
    std::string line;
    std::ifstream reader(file_name);

    while(!reader.eof())
    {
        std::getline(reader, line);
        line.erase(std::remove_if(line.begin(), line.end(), isspace), 
                    line.end());

        if(line.size() == 0)
            continue;

        if(line.find(lang.get_comment()) != 0 && 
            line.find(lang.get_comment_block_open()) != 0 && cf)
        {
            code++;
            continue;
        }
        else if(line.find(lang.get_comment_block_open()) == 0)
        {
            if(line.find(lang.get_comment_block_close()) == std::string::npos)
                cf = false;
        }
        else if(line.find(lang.get_comment_block_close()) == 0)
        {
            cf = true;
        }
        else if(line.find(lang.get_comment()) == 0)
        {
            continue;
        }
        else if(!cf && line.find(lang.get_comment_block_close()) ==     
                std::string::npos)
        {
            continue;
        }

        if(line.find(lang.get_comment_block_close()) != std::string::npos)
        {
            line = line.substr(line.find(lang.get_comment_block_close()) + 
                                lang.get_comment_block_close().size());

            if(is_ugly_code_line(line, lang))
            {
            cf = true;
            code++;
            }
        }
    }

    return code;
}

void loc::parser::file(std::string& name)
{
    std::string ext = name.substr(name.rfind('.') + 1);
    lang language = get_lang(ext);

    if(language.get_name() == UNSUPPORTED)
    {
        return;
    }

    if(langs.size() == 0)
    {
        langs.push_back(language);
    }

    for(size_t i = 0; i < langs.size(); i++)
    {
        if(langs[i].get_name() == language.get_name())
        {
            langs[i].add_code(count_code(name, langs[i]));
            langs[i].add_file();
        }
    }
}
