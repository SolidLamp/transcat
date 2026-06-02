/*!
 * Transcat - A cat program which colours stdin with the transgender flag.
 */

#include <stdint.h>
#include <stdio.h>
#include <unistd.h>

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
        perror("Error opening file");
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
        printf("TODO");
        return NULL;
    }
    fp = fopen(*name, "r");
    if (fp == NULL) {
        perror("Error opening file");
        fprintf(stderr, "Error opening file.");
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
    /* int arr[] = { 0x70707000, 0xB4707000, 0xB470B400, 0xB4B4B400, 0x7070B400, 0xB4B47000, 0x70B4B400 }; */
    uint32_t arr[] = { 0x5BCEFA00, 0xF5A9B800, 0xffffff00, 0xF5A9B800, 0x5BCEFA00 };

    if (argc == 1 && !isatty(fileno(stdin))) {
        display(stdin, arr, 5);
    }

    for (i = 1; i < argc; ++i) {
        FILE* fp = findfile(argv + i);
        if (fp != NULL) {
            display(fp, arr, 5);
            fclose(fp);
        }
    }
    return 0;
}
