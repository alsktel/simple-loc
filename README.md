# CodeLinesCounter
My own counter of code lines.
This counter ignores comments and empty lines.

## Get CodeLinesCounter
To get it follow:

Clone this repo: `git clone https://github.com/eastev/CodeLinesCounter.git`

Enter CodeLinesCounter directory: `cd CodeLinesCounter`

Make it executable: `chmod +x loc`

Run loc by the ways described in [Usage](#usage) or [Integrate](#make-loc-a-command) or [Command](#usage-as-command)

## Supported languages:
* Shell
* C
* C++
* C#
* Assembly

You can add or edit language setting in `./clc/loc.conf` or if you've used `./loc -i` in `/etc/clc/loc.cong` 

**Notice!**

C headers must be *.h and C++ headers must be *.hpp

## Usage
To run counter: `./loc [directory]` or `./loc -f [file]`

For more options use: `./loc -h` or `./loc --help`

## Make loc a command
For integration of loc to your terminal commands use: `./loc -i`

For deleting loc terminal command use: `./loc -r`

## Usage as command
It is possible after [Integration](#make-loc-a-command)

Use CodeLinesCounter as common terminal command `loc ...` instead of `./loc ...` from everywhere.

## Development 
You can use and develop this project within the GNU GPL v3.0 licence.
