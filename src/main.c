/*!
 * Transcat - A cat program which colours stdin with the transgender flag.
 */

#include <getopt.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

#include "flags.h"

int display(FILE* fp, uint32_t colours[], int colour_len);
FILE* findfile(char* name[]);
int main(int argc, char* argv[]);

/**
 * A function to display the text of a file.
 *
 * @param display A file pointer to the file to print to stdout.
 * @param colours An array of 32-bit colours (where alpha discarded) which are
 *                used to colour each line.
 * @param colour_len The length of the colour array.
 * @returns an int representing if successful in opening file (0 is success).
 */
int display(FILE* fp, uint32_t colours[], int colour_len)
{
    char line[1000];
    int colour_index = 0;

    if (fp == NULL) {
        return 1;
    }

    while (fgets(line, 1000, fp) != NULL) {

        if (colour_len != 0) {
            uint32_t colour;
            uint8_t red;
            uint8_t blue;
            uint8_t green;
            colour_index = colour_index % colour_len;
            colour = colours[colour_index++];
            red = (colour >> 24) & 0xFF;
            blue = (colour >> 16) & 0xFF;
            green = (colour >> 8) & 0xFF;
            fprintf(stdout, "\033[38;2;%d;%d;%dm", red, blue, green);
        }

        fputs(line, stdout);
    }

    fputs("\033[0m", stdout);

    return 0;
}

/**
 * A function to find a given file point based on the file name.
 *
 * @param name A string representing the name of the file to find.
 * @returns a file pointer
 */
FILE* findfile(char* name[])
{
    FILE* fp;
    if (access(*name, R_OK) != 0) {
        return NULL;
    }
    fp = fopen(*name, "r");
    if (fp == NULL) {
        return NULL;
    }
    return fp;
}

/**
 * Cat program that prints with a trans flag.
 *
 * @param argc The number of arguments.
 * @param argv The array of arguments passed into the program.
 * @returns an int representing successful execution (0 is success).
 */
int main(int argc, char* argv[])
{
    int i;
    int remaining_elements;
    char ch;
    uint32_t arr[5];
    FLAG flag;

    uint8_t invalid_option = 0;
    char flag_name = 't';
    int option_index = 0;

    static struct option long_options[] = {
        {"trans",        no_argument,       0, 't'},
        {"transgender",  no_argument,       0, 't'},
        {"lesbian",  no_argument,           0, 'l'},
        {0,              0,                 0,  0 }
    };

    while ((ch = getopt_long(argc, argv, "tl", long_options, NULL)) != -1) {
        switch (ch) {
        case 't':
        case 'l':
            flag_name = ch;
            break;
        case '?':
            invalid_option = 1;
            break;
        }
    }

    if (invalid_option) {
        printf("Error: Unrecognised Option. Quit.");
        exit(3);
    }

    flag = get_flag(flag_name);

    memcpy(arr, flag.colours, 5 * sizeof(uint32_t));

    if (remaining_elements == 0 && !isatty(fileno(stdin))) {
        int success;
        success = display(stdin, arr, 5);
        if (success == 1) {
            perror("Error opening file");
            return 1;
        }
    }

    for (i = optind; i < argc; ++i) {
        FILE* fp = findfile(argv + i);
        if (fp != NULL) {
            display(fp, arr, 5);
            fclose(fp);
        } else {
            perror("Cannot open file");
            return 1;
        }
    }
    return 0;
}
