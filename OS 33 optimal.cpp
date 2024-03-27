#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 4  // Number of frames in memory

int main() {
    int pages[] = {0, 1, 2, 3, 2, 4, 5, 3, 4};  // Reference string
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    int frames[FRAME_SIZE];
    int frame_count = 0;
    int page_faults = 0;
    int next_occurrence[FRAME_SIZE];

    printf("Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;  // Initialize frames to -1, indicating an empty frame
        next_occurrence[i] = -1;  // Initialize next occurrences to -1
    }

    printf("\nOptimal Page Replacement:\n");

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if page is already in frame
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                page_found = 1;
                break;
            }
        }

        if (!page_found) {
            // Find the optimal frame to replace
            int replace_index = -1;
            int max_distance = -1;

            for (int j = 0; j < FRAME_SIZE; j++) {
                int current_distance = 0;
                int k;

                for (k = i + 1; k < num_pages; k++) {
                    current_distance++;

                    if (frames[j] == pages[k]) {
                        break;
                    }
                }

                if (k == num_pages) {
                    replace_index = j;
                    break;
                }

                if (current_distance > max_distance) {
                    max_distance = current_distance;
                    replace_index = j;
                }
            }

            printf("Page %d -> ", page);

            frames[replace_index] = page;
            next_occurrence[replace_index] = i;

            for (int j = 0; j < FRAME_SIZE; j++) {
                printf("%d ", frames[j]);
            }
            printf("  (Page Fault)\n");

            page_faults++;
        } else {
            printf("Page %d -> ", page);
            for (int j = 0; j < FRAME_SIZE; j++) {
                printf("%d ", frames[j]);
            }
            printf("\n");
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}


