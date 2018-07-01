#include <stdio.h>
#include <fcntl.h>
#include <mmintrin.h>
#include <unistd.h>
#include <immintrin.h>

#define BUFFER_SIZE 512

int main(int argc, char **argv)
{
  if (argc < 2) {
    printf("Error: Insufficient arguments\n");
    printf("\n");
    printf("%s <src-file>\n", argv[0]);
    return 1;
  }

  char *filename = argv[1];

  FILE *file = fopen(filename, "r");

  if (!file) {
    printf("Error opening file\n");
    return 1;
  }

  char buffer[BUFFER_SIZE];

  size_t total_bytes_read = 0;

  size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, file);

  while (bytes_read > 0) {
    total_bytes_read += bytes_read;

    bytes_read = fread(buffer, 1, BUFFER_SIZE, file);
  }

  printf("Total bytes read %zu\n", total_bytes_read);


  return 0;
}
