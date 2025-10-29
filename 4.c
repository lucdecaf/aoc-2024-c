#include "lib/timing.c"
#include <stdio.h>
#include <stdlib.h>

const size_t LINE_LENGTH = 140;

int main(int argc, char *argv[]) {
    start_timing();

    FILE *fp;
    fp = fopen("input-4.txt", "r");
    if (fp == NULL) {
        perror("Failed to open file\n");
        return 1;
    }

    char board[LINE_LENGTH][LINE_LENGTH];
    for (int i = 0; i < LINE_LENGTH; i++) {
        fread(board[i], 1, LINE_LENGTH, fp);
        fseek(fp, 1, SEEK_CUR);
    }

    fclose(fp);

    int count = 0;
    for (int i = 1; i < LINE_LENGTH - 1; i++) {
        for (int j = 1; j < LINE_LENGTH - 1; j++) {
            char ch = board[i][j];
            if (ch != 'A')
                continue;

            count +=
                ((board[i - 1][j - 1] == 'M' && board[i + 1][j + 1] == 'S') ||
                 (board[i + 1][j + 1] == 'M' && board[i - 1][j - 1] == 'S')) &&
                ((board[i - 1][j + 1] == 'M' && board[i + 1][j - 1] == 'S') ||
                 (board[i + 1][j - 1] == 'M' && board[i - 1][j + 1] == 'S'));
        }
    }

    printf("%d\n", count);

    end_timing();
    return 0;
}
