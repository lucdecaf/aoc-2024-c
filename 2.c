#include "lib/timing.c"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

bool is_safe(int nums[], int nums_count);
bool is_safe_without_correction(int nums[], int nums_count);

int main(int argc, char *argv[]) {
    start_timing();

    FILE *fptr;

    fptr = fopen("input-2.txt", "r");
    if (fptr == NULL) {
        printf("Failed to open file\n");
        return 1;
    }

    int safe_reports = 0;
    char buf[64];
    while (fgets(buf, 63, fptr)) {
        int offset = 0;
        int direction = 0;
        bool safe = true;

        // Read numbers
        int nums[10];
        int nums_count = 0;
        while (buf[offset] != '\n' && buf[offset] != '\0') {
            int num = atoi(buf + offset);
            offset += num >= 10 ? 3 : 2;
            nums[nums_count++] = num;
        }

        if (is_safe(nums, nums_count))
            safe_reports++;
    }

    fclose(fptr);

    printf("%d\n", safe_reports);

    end_timing();
    return 0;
}

bool is_safe(int nums[], int nums_count) {
    if (is_safe_without_correction(nums, nums_count))
        return true;

    int new_nums[nums_count - 1];
    for (int skip = 0; skip < nums_count; skip++) {
        for (int i = 0; i < nums_count - 1; i++) {
            new_nums[i] = i >= skip ? nums[i + 1] : nums[i];
        }

        if (is_safe_without_correction(new_nums, nums_count - 1))
            return true;
    }

    return false;
}

bool is_safe_without_correction(int nums[], int nums_count) {
    int direction = 0;

    for (int i = 1; i < nums_count; i++) {
        int num = nums[i];
        int prev = nums[i - 1];

        int diff = num - prev;
        if (diff == 0 || abs(diff) > 3) {
            return false;
        }

        if (direction == 0) {
            direction = diff > 0 ? -1 : 1;
        }

        int current_direction = diff > 0 ? -1 : 1;
        if (current_direction != direction) {
            return false;
        }

        prev = num;
    }

    return true;
}
