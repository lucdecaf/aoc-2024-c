#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int cmp(const void *a, const void *b);

int main(int argc, char *argv[]) {
    FILE *fptr;

    fptr = fopen("input-1.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    char line[15];
    char num[6];
    num[5] = 0;

    int keys[1000];
    int counts[100000] = {0};
    for (int i = 0; i < 1000; i++) {
        fgets(line, 15, fptr);
        strncpy(num, line, 5);
        keys[i] = atoi(num);
        strncpy(num, line + 8, 5);
        counts[atoi(num)]++;
    }

    fclose(fptr);

    int sum = 0;
    for (int i = 0; i < 1000; i++) {
        int key = keys[i];
        int count = counts[key];
        sum += key * count;
    }

    printf("%d\n", sum);

    return 0;
}

int cmp(const void *a, const void *b) {
    int aInt = *(const int *)a;
    int bInt = *(const int *)b;
    if (aInt < bInt)
        return -1;
    if (aInt > bInt)
        return 1;
    return 0;
}
