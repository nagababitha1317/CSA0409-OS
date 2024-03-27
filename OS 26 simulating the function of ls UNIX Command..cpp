#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>

void list_directory(const char *path) {
  DIR *dir;
  struct dirent *entry;

  dir = opendir(path);
  if (!dir) {
    perror("opendir");
    return;
  }

  while ((entry = readdir(dir)) != NULL) {
    // Skip special entries "." and ".."
    if (strcmp(entry->d_name, ".") == 0 || strcmp(entry->d_name, "..") == 0) {
      continue;
    }
    printf("%s\n", entry->d_name);
  }

  closedir(dir);
}

int main(int argc, char *argv[]) {
  // Use current directory if no argument provided
  const char *path = (argc == 1) ? "." : argv[1];

  list_directory(path);

  return 0;
}

