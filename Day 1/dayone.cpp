#include "bits/stdc++.h"
using namespace std;

int main() {
    FILE* fp;
    char line[200]; // Assuming a maximum line length of 150 characters

    // Open the file in read mode
    fp = fopen("input.txt", "r");

    if (fp == NULL) {
        printf("Could not open file.");
        return 1;
    }

    int sum = 0;
    int val = 0;
    int lines = 0;

    // Read file line by line and print each line
    while (fgets(line, sizeof(line), fp) != NULL) {
        // printf("%s", line);
        lines++;
        val = 0;
        int i = 0;
        for (i = 0; line[i] != '\0'; i++) {
            if ('0' <= line[i] && line[i] <= '9') { // Check if the character is a digit
                val = val + line[i] - '0';
                break; // Stop after finding the first digit
            }
        }
        while(line[i] != '\0' && i < 200) i++; // move i to last index
        val = val * 10; // times 10 to make it the tenth-digit
        i--;
        for (; i >= 0; i--) {
            if ('0' <= line[i] && line[i] <= '9') { // Check if the character is a digit
                val = val + line[i] - '0';
                break; // Stop after finding the first digit
            }
        }

        // printf("%d\n", val);
        // if(val < 10 || val > 99) printf("help! %d\n", val);
        sum = sum + val;
    }

    printf("%d\n", sum);
    printf("totalling %d lines\n", lines);

    // Close the file
    fclose(fp);

    return 0;
}