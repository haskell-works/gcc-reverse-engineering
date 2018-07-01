#include <stdio.h>
#include <fcntl.h>
#include <mmintrin.h>
#include <unistd.h>
#include <immintrin.h>
#include <string.h>

#define BUFFER_SIZE 512

// __m256i _mm256_broadcastb_epi8 (__m128i a)
// __m256i _mm256_cmpeq_epi64 (__m256i a, __m256i b)
// __m256i _mm256_shuffle_epi8 (__m256i a, __m256i b)
// __m256i _mm256_maskload_epi32 (int const* mem_addr, __m256i mask)

#define MAX_STATES 2
#define MAX_LANES 32
#define MAX_BYTES 256
#define STATE_0 0
#define STATE_1 1

uint8_t g_transitions[MAX_STATES][MAX_BYTES];

void make_transitions()
{
  for (size_t state = 0; state < MAX_STATES; ++state) {
    for (size_t byte = 0; byte < MAX_BYTES; ++byte) {
      if (0) {
      } else if (state == STATE_0 && byte == '"') {
        g_transitions[state][byte] = STATE_1;
      } else if (state == STATE_1 && byte == '"') {
        g_transitions[state][byte] = STATE_0;
      } else {
        g_transitions[state][byte] = state;
      }
    }
  }
}

void process_data(char *text, size_t bytes_read, uint64_t *bits)
{
  

  // // __declspec(align(8)) const float num = 20;
  // const __m128i x = _mm_set_epi32(1,2,3,4);

  // __m128i mask = 1; // (__m128i)(int)',';

}

int main(int argc, char **argv)
{
  if (argc < 3) {
    printf("Error: Insufficient arguments\n");
    printf("\n");
    printf("%s <src-file> <target-file>\n", argv[0]);
    return 1;
  }

  char *in_filename  = argv[1];
  char *out_filename = argv[2];

  FILE *in_file   = fopen(in_filename,  "r");
  FILE *out_file  = fopen(out_filename, "w");

  if (!in_file) {
    printf("Error opening file\n");
    return 1;
  }

  char buffer[BUFFER_SIZE];
  uint64_t bits[BUFFER_SIZE];

  memset(bits, 0, BUFFER_SIZE);

  size_t total_bytes_read = 0;

  size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, in_file);

  while (bytes_read > 0) {
    total_bytes_read += bytes_read;

    process_data(buffer, bytes_read, bits);

    fwrite((char*)bits, 1, (bytes_read + 7) / 8, out_file);

    bytes_read = fread(buffer, 1, BUFFER_SIZE, in_file);
  }

  fclose(in_file);
  fclose(out_file);

  return 0;
}
