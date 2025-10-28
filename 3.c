#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum ParseState {
    RIGHT,
    LEFT,
    MUL,
};

int main() {
    FILE *fp;
    fp = fopen("input-3.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file");
        return 1;
    }

    // Get filesize
    fseek(fp, 0, SEEK_END);
    long filesize = ftell(fp);
    fseek(fp, 0, SEEK_SET);

    // Create buffer with exactly enough space
    char *content = (char *)malloc(filesize + 1);
    if (content == NULL) {
        perror("Failed to allocate memory");
        fclose(fp);
        return 1;
    }

    // Read file
    size_t bytes_read = fread(content, sizeof(char), filesize, fp);
    if (bytes_read != filesize) {
        perror("Error reading file contents");
        fclose(fp);
        free(content);
        return 1;
    }
    content[filesize] = '\0';

    // Close file now
    fclose(fp);

    int i = 0;
    while (i < filesize) {
        if (content[i] == ')') {
            // Start seeking backwards
            char prev = '\0';
            int j = i;

            // flags
            int parse_state = RIGHT;
            int left_num = 0;
            int right_num = 0;
            int *current_num = &right_num;
            int idx = 0;

            while (j >= 0) {
                switch (content[j]) {
                case '0' ... '9':
                    *current_num += (content[i] - '0') * pow(10, idx++);
                    break;
                case ',':
                    if (current_num == &right_num) {
                        current_num = &left_num;
                        idx = 0;
                    } else {
                        goto badpattern;
                    }
                    break;
                default:
                    goto badpattern;
                }
            }

        goodpattern:
            continue;

            // Generic exit point for all failed parse attempts
        badpattern:
            NULL;
        }
    }

    free(content);
    return 0;
}
