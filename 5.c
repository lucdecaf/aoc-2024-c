#include "lib/timing.c"
#include <stdio.h>

int main(int argc, char *argv[]) {
    start_timing();
    FILE *fp;
    fp = fopen("input-4.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file\n");
        return 1;
    }

    // readfile

    fclose(fp);

    // calculations

    end_timing();
    return 0;
}
