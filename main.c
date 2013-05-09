#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "lib1.h"

void str_input(char *information, char *input_text, int max_number_of_symbols);
void file_output(char *file_name);
int main(int argc, char **argv)
{
    if (argc > 1 && !strcmp(argv[1], "-h")) {
        file_output("README.txt");
        return 0;
    }
    return 0;
}
