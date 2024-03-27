#include <stdio.h>
#include <stdlib.h>

#define FRAME_SIZE 4  // Number of frames in memory

int main() {
    int pages[] = {0, 1, 2, 3, 2, 4, 5, 3, 4};  // Reference string
    int num_pages = sizeof(pages) / sizeof(pages[0]);

    int frames[FRAME_SIZE];
    int frame_count = 0;
    int page_faults = 0;
    int next_frame_index = 0;

    printf("Reference String: ");
    for (int i = 0; i < num_pages; i++) {
        printf("%d ", pages[i]);
    }
    printf("\n");

    for (int i = 0; i < FRAME_SIZE; i++) {
        frames[i] = -1;  // Initialize frames to -1, indicating an empty frame
    }

    printf("\nFIFO Page Replacement:\n");

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
            frames[next_frame_index] = page;
            next_frame_index = (next_frame_index + 1) % FRAME_SIZE;  // Circular increment
            page_faults++;

            printf("Page %d -> ", page);
            for (int j = 0; j < FRAME_SIZE; j++) {
                printf("%d ", frames[j]);
            }
            printf("  (Page Fault)\n");
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

