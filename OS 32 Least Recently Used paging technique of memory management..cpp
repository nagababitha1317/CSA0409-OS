#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 4  // Number of frames in memory

int main() {
    int pages[] = {0, 1, 2, 3, 2, 4, 5, 3, 4};  // Reference string
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    int frames[FRAME_SIZE];
    int frame_count = 0;
    int page_faults = 0;
    int recent_index[FRAME_SIZE];
    int recent_count = 0;

    printf("Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;  // Initialize frames to -1, indicating an empty frame
        recent_index[i] = -1;  // Initialize recent indexes to -1
    }

    printf("\nLRU Page Replacement:\n");

    for (int i = 0; i < num_pages; i++) {
        int page = pages[i];
        int page_found = 0;

        // Check if page is already in frame
        for (int j = 0; j < FRAME_SIZE; j++) {
            if (frames[j] == page) {
                page_found = 1;

                // Update recent index of the page
                for (int k = 0; k < recent_count; k++) {
                    if (recent_index[k] == j) {
                        for (int l = k; l < recent_count - 1; l++) {
                            recent_index[l] = recent_index[l + 1];
                        }
                        recent_index[recent_count - 1] = j;
                        break;
                    }
                }

                break;
            }
        }

        if (!page_found) {
            // Find the least recently used frame
            int replace_index = recent_index[0];

            printf("Page %d -> ", page);

            frames[replace_index] = page;

            // Update recent index
            for (int j = 0; j < recent_count - 1; j++) {
                recent_index[j] = recent_index[j + 1];
            }
            recent_index[recent_count - 1] = replace_index;

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

        // Update recent count
        if (page_found) {
            for (int j = 0; j < recent_count; j++) {
                if (recent_index[j] == -1) {
                    recent_index[j] = j;
                    recent_count++;
                    break;
                }
            }
        } else {
            recent_index[recent_count] = recent_count;
            recent_count++;
        }
    }

    printf("\nTotal Page Faults: %d\n", page_faults);

    return 0;
}

