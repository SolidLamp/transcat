#include <stdio.h>
#include <unistd.h>

int display(FILE* fp);
FILE* findfile(char* name[]);
int main(int argc, char* argv[]);

int display(FILE* fp)
{
    int ch;
    if (fp == NULL) {
        perror("Error opening file");
        return 1;
    }
    while ((ch = getc(fp)) != EOF) {
        putchar(ch);
    }
    return 0;
}

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
