/*
 * SPDX-License-Identifier: GPL-3.0
 * Copyright © eastev <eastevrud31@gmail.com>
 */ 

/*
 * Simple-loc code parsing functions
 */

#include <limits>
#include <algorithm>
#include <filesystem>

#include <parser.hpp>

#define UNSUPPORTED "NONE"

loc::parser::parser(std::string& config)
{
    config_reader.open(config);

    if(!config_reader.is_open())
    {
        fprintf(stderr, "\033[0;31mError\033[0m: Config not found\n\n\n");

        std::exit(-1);
    }

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

            if(ext == _ext)
            {
                continue;
            }
            else
            {
                while(token != "}" && !config_reader.eof())
                {
                    config_reader >> token;
                    continue;
                }

                continue;
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
        else if(token == "}" && !config_reader.eof())
        {
            config_reader.clear();
            config_reader.seekg(0);

            return lang(name, comment, b_comment_open, b_comment_close);
        }
    }

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
            if(line.find(lang.get_comment_block_close()) == 
                std::string::npos || lang.get_comment_block_open() ==
                lang.get_comment_block_close())
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
    ext.erase(std::remove(ext.begin(), ext.end(), '/'), ext.end());
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

            return;
        }
    }

    langs.push_back(language);
    langs[langs.size() - 1].add_code(count_code(name, language));
    langs[langs.size() - 1].add_file();
}

void loc::parser::dir(std::string& dir)
{
    for(auto & file : std::filesystem::directory_iterator(dir))
    {
        std::string name = file.path();

        if(file.is_directory())
            this->dir(name);
        else
            this->file(name);
    }
}

void loc::parser::files_only()
{
    for(auto & file : std::filesystem::directory_iterator("."))
    {
        std::string name = file.path();

        if(file.is_directory())
            continue;
        else
            this->file(name);
    }
}

void loc::parser::files_only(std::string& dir)
{
    for(auto & file : std::filesystem::directory_iterator(dir))
    {
        std::string name = file.path();

        if(file.is_directory())
            continue;
        else
            this->file(name);
    }
}

std::string loc::parser::get_lang_ext(std::string& lang)
{
    std::string lang_token;
    std::string ext;
    std::string token;

    while(!config_reader.eof())
    {
        config_reader >> token;

        if(token == "LANG")
        {
            config_reader >> token;
            config_reader >> lang_token;

            if(lang_token == lang)
            {
                config_reader >> token;
                config_reader >> token;

                if(token == "EXT")
                {
                    config_reader >> token;
                    config_reader >> ext;
                }
                else
                {
                    break;
                }

                config_reader.clear();
                config_reader.seekg(0);

                return ext;
            }
        }
    }

    config_reader.clear();
    config_reader.seekg(0);

    return std::string(UNSUPPORTED);
}

void loc::parser::parse_lang(std::string& lang, std::string& file)
{
    if(lang == "C")
    {
        std::string _ext = "c";
        std::string name = file;
        std::string ext = name.substr(name.rfind('.') + 1);
        ext.erase(std::remove(ext.begin(), ext.end(), '/'), ext.end());

        if(ext == _ext)
        {
            this->file(file);
        }

        _ext = "h";

        if(ext == _ext)
        {
            this->file(file);
        }

        if(ext != "c" && ext != "h")
            return;
    }
    else if(lang == "C++")
    {
        std::string _ext = "cpp";
        std::string name = file;
        std::string ext = name.substr(name.rfind('.') + 1);
        ext.erase(std::remove(ext.begin(), ext.end(), '/'), ext.end());

        if(ext == _ext)
        {
            this->file(file);
        }

        _ext = "hpp";

        if(ext == _ext)
        {
            this->file(file);
        }

        if(ext != "cpp" && ext != "hpp")
            return;
    }
    else
    {
        std::string _ext = this->get_lang_ext(lang);
        std::string name = file;
        std::string ext = name.substr(name.rfind('.') + 1);
        ext.erase(std::remove(ext.begin(), ext.end(), '/'), ext.end());

        if(ext == _ext)
        {
            this->file(file);
        }
    }
}

void loc::parser::language(std::string& lang)
{
    for(auto & file : std::filesystem::directory_iterator("."))
    {
        std::string name = file.path();

        if(file.is_directory())
            continue;
        else
            this->parse_lang(lang, name);
    }
}

void loc::parser::language(std::string& lang, std::string& directory)
{
    for(auto & file : std::filesystem::directory_iterator(directory))
    {
        std::string name = file.path();

        if(file.is_directory())
            continue;
        else
            this->parse_lang(lang, name);
    }
}
