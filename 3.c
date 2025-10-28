#include "lib/timing.c"
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

enum ParseState {
    RIGHT,
    LEFT,
    MUL,
    DO_DONT,
};

int main() {
    start_timing();

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

    int sum = 0;
    bool enabled = true;
    for (int i = 0; i < filesize; i++) {
        if (content[i] == ')') {

            // Start seeking backwards
            int j = i - 1;

            // flags
            int parse_state = RIGHT;
            int left_num = 0;
            int right_num = 0;
            int *current_num = &right_num;

            int idx = 0;
            char prev_char = ')';
            bool new_enabled;

            while (j >= 0) {
                char current = content[j];

                switch (current) {
                case '0':
                case '1':
                case '2':
                case '3':
                case '4':
                case '5':
                case '6':
                case '7':
                case '8':
                case '9':
                    if (parse_state != LEFT && parse_state != RIGHT)
                        goto badpattern;

                    *current_num += (current - '0') * (int)pow(10, idx++);
                    break;

                case ',':
                    if (parse_state != RIGHT)
                        goto badpattern;

                    current_num = &left_num;
                    idx = 0;
                    parse_state = LEFT;
                    break;

                case '(':
                    if (prev_char == ')') {
                        parse_state = DO_DONT;
                        break;
                    }
                    if (parse_state != LEFT)
                        goto badpattern;

                    parse_state = MUL;
                    break;

                case 'l':
                    if (parse_state != MUL)
                        goto badpattern;
                    if (prev_char != '(')
                        goto badpattern;
                    break;
                case 'u':
                    if (parse_state != MUL)
                        goto badpattern;
                    if (prev_char != 'l')
                        goto badpattern;
                    break;
                case 'm':
                    if (parse_state != MUL)
                        goto badpattern;
                    if (prev_char != 'u')
                        goto badpattern;

                    // Parsed successfully
                    goto goodpattern;
                    break;

                    // don't
                case 't':
                    if (parse_state != DO_DONT)
                        goto badpattern;
                    if (prev_char != '(')
                        goto badpattern;
                    break;
                case '\'':
                    if (parse_state != DO_DONT)
                        goto badpattern;
                    if (prev_char != 't')
                        goto badpattern;
                    break;
                case 'n':
                    if (parse_state != DO_DONT)
                        goto badpattern;
                    if (prev_char != '\'')
                        goto badpattern;
                    break;

                    // either middle or first
                case 'o':
                    if (parse_state != DO_DONT)
                        goto badpattern;
                    if (prev_char == 'n') {
                        new_enabled = false;
                        break;
                    }
                    if (prev_char == '(') {
                        new_enabled = true;
                        break;
                    }
                    goto badpattern;
                    break;

                    // always last
                case 'd':
                    if (parse_state != DO_DONT)
                        goto badpattern;
                    if (prev_char != 'o')
                        goto badpattern;
                    enabled = new_enabled;
                    break;

                default:
                    goto badpattern;
                }

                prev_char = current;
                j--;
            } // end of parse loop

        goodpattern: {
            if (!enabled)
                continue;

            sum += left_num * right_num;
            continue;
        }

        badpattern:;
        }
    }

    printf("%d\n", sum);

    free(content);

    end_timing();
    return 0;
}
