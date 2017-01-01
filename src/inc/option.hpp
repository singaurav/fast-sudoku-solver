#ifndef OPTION_INCLUDED
#define OPTION_INCLUDED

#include <stdio.h>

struct Option {
    FILE *fd;
    int max_sol;
    bool list_sol;
    bool count_sol;
    bool help;

    Option() {
        fd = stdin;
        max_sol = 2;
        list_sol = false;
        count_sol = false;
        help = false;
    }
};

bool parse_command_line(int argc, char *argv[], Option *option);

#endif // #ifndef OPTION_INCLUDED
