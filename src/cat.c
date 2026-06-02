/*!
 * Basic cat program
 */

#include <stdio.h>
#include <unistd.h>

int display(FILE* fp);
FILE* findfile(char* name[]);
int main(int argc, char* argv[]);

/**
 * A function to display the text of a file.
 *
 * @param display A file pointer to the file to print to stdout.
 * @returns an int representing if successful in opening file (0 is success).
 */
int display(FILE* fp)
{
    char line[1000];

    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }

    while(fgets(line, 1000, fp) != NULL) {
        fputs(line, stdout);
    }

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
 * Cat program.
 *
 * @param argc The number of arguments.
 * @param argv The array of arguments passed into the program.
 * @returns an int representing successful execution (0 is success).
 */
int main(int argc, char* argv[])
{
    int i;

    if (argc == 1 && !isatty(fileno(stdin))) {
        display(stdin);
    }

    for (i = 1; i < argc; ++i) {
        FILE* fp = findfile(argv + i);
        if (fp != NULL) {
            display(fp);
            fclose(fp);
        }
    }
    return 0;
}
