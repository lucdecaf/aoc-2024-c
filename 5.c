#include "lib/timing.c"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    start_timing();

    FILE *fp;
    fp = fopen("input-5.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file\n");
        return 1;
    }

    int sum;

    int orderings[100][100];

    for (int i = 0; i < 100; i++) {
        for (int j = 0; j < 100; j++) {
            orderings[i][j] = 0;
        }
    }

    int left, right;
    char buf[100];
    while (fgets(buf, sizeof(buf), fp)) {
        if (buf[0] == '\n')
            break;

        left = atoi(buf);
        right = atoi(buf + 3);

        orderings[left][right] = 1;
    }

    int pages[30];
    int pages_len;
    int num;
    while (fgets(buf, sizeof(buf), fp)) {
        pages_len = 0;

        int valid = 0;
        int ever_valid = 1;

        int i = 0;
        do {
            num = atoi(buf + (i * 3));
            pages[i] = num;
            pages_len++;
        } while (buf[(++i * 3) - 1] == ',');

        while (!valid) {
            valid = 1;

            for (int i = pages_len - 1; i > 0; i--) {
                int *ordering = orderings[pages[i]];

                for (int j = i - 1; j >= 0; j--) {
                    if (ordering[pages[j]]) {
                        ever_valid = 0;
                        valid = 0;

                        // Perform swap
                        int temp = pages[i];
                        pages[i] = pages[j];
                        pages[j] = temp;

                        break;
                    }
                }

                if (!valid)
                    break;
            }
        }

        if (!ever_valid)
            sum += pages[(pages_len - 1) / 2];
    }

    fclose(fp);

    printf("%d\n", sum);

    end_timing();
    return 0;
}
