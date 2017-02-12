#include "option.hpp"
#include <cstdlib>
#include <iostream>
#include <string>

using namespace std;

bool parse_command_line(int argc, char *argv[], Option *option) {
    string default_message =
        R"(Fast Sudoku Solver by Gaurav Singh
    Usage: sudoku [options]
           sudoku [options] sourcefile
        Options: -h     Show this message
                 -l     List solutions
                 -c     Count solutions
                 -m     Maximum solutions to be searched
)";

    for (int i = 1; i < argc; ++i) {
        string arg = argv[i];

        if (arg == "-h") {
            cerr << default_message;
            option->help = true;
            return true;
        } else if (arg == "-l") {
            option->list_sol = true;
        } else if (arg == "-c") {
            option->count_sol = true;
        } else if (arg == "-m") {
            if (i + 1 < argc) {
                option->max_sol = atoi(argv[++i]);
                if (option->max_sol < 2) {
                    cerr << "Maximum solutins can not be less than 2.";
                    return false;
                }
            } else {
                cerr << "No argument for -m found.";
                return false;
            }
        } else {
            if (i + 1 == argc) {
                option->fd = fopen(argv[i], "r");
                if (!(option->fd)) {
                    cerr << "Error while reading: " << arg;
                    return false;
                }
            } else {
                cerr << "Error while parsing command line" << endl;
                cerr << default_message;
                return false;
            }
        }
    }

    return true;
}
