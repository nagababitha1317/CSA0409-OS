#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void grep(const char *pattern, const char *filename) {
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        perror("fopen");
        exit(EXIT_FAILURE);
    }

    char line[256];
    int line_number = 0;

    while (fgets(line, sizeof(line), file)) {
        line_number++;

        if (strstr(line, pattern) != NULL) {
            printf("%s:%d:%s", filename, line_number, line);
        }
    }

    fclose(file);
}

int main(int argc, char *argv[]) {
    if (argc != 3) {
        printf("Usage: %s <pattern> <filename>\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    const char *pattern = argv[1];
    const char *filename = argv[2];

    grep(pattern, filename);

    return 0;
}

