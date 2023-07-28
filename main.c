You are given two strings word1 and word2. Merge the strings by adding letters in alternating order,
starting with word1. If a string is longer than the other, append the additional letters onto the end of the merged string.
Return the merged string.

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *mergeAlternately(char const *word1, char const *word2);

int main() {
    char word1[] = "abc";
    char word2[] = "pqr";
    char *merge = mergeAlternately(word1, word2);
    printf("%s", merge);
    free(merge);
    return 0;
}

char *mergeAlternately(char const *word1, char const *word2) {
    char const *ptr = (char *)calloc((strlen(word1) + strlen(word2) + 1), sizeof(char));
    char *p = ptr;

    while (*word1 && *word2) {
        *(p++) = *(word1++);
        *(p++) = *(word2++);
    }

    if (*word1) {
        strcpy(p, word1);
    } else if (*word2) {
        strcpy(p, word2);
    }
    return ptr;
}
