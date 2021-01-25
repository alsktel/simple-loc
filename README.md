# Simple-loc 
Simple code lines counter for Linux.

[![CodeFactor](https://www.codefactor.io/repository/github/eastev/simple-loc/badge)](https://www.codefactor.io/repository/github/eastev/simple-loc)

## Installation
To install simple-loc you need these tools to be installed:
* g++
* ld
* make
* git

Follow these steps to install simple-loc:
1. Clone this repo: `git clone https://github.com/eastev/simple-loc.git`
2. Enter the directory: `cd simple-loc`
3. Build it: `make`
4. Install it: `sudo make install`

If you want to uninstall simple-loc use: `sudo make uninstall`  
You can see all make commands with: `make help`

## Usage
All information about usage and simple-loc parameters can be seen by: `loc -h`  
For example to count all code lines of all languages in current directory and 
subdirectories use: `loc`.  
If you want to specify directory use: `loc -d <dir>`

## Config
Simple-loc has its own language config `/etc/simple-loc/langs.conf`  
It can be modified (Instructions are in a head of file). Basic config has some properties for C, C++, C#, Python, Makefile and etc.

### Copyright © eastev <<eastevrud31@gmail.com>>    
All rights reserved.
