#include <stdio.h>
#include <fcntl.h>
#include <mmintrin.h>
#include <unistd.h>
#include <immintrin.h>
#include <string.h>

#define BUFFER_SIZE 8192

// __m256i _mm256_broadcastb_epi8 (__m128i a)
// __m256i _mm256_cmpeq_epi64 (__m256i a, __m256i b)

void process_data(char *text, size_t bytes_read, uint64_t *bits_w64, __m256i ws_newlines)
{
  char *bytes_end = text + bytes_read;
  uint32_t *bits_w32 = (uint32_t *)bits_w64;

  if ((bytes_read & 0x1f) == 0) {
    for (; text != bytes_end; text += 32) {
      __m256i matches_bytes = _mm256_cmpeq_epi8(*(__m256i*)text, ws_newlines);

      int matches_bits = _mm256_movemask_epi8(matches_bytes);

      *(bits_w32++) = (uint32_t)matches_bits;
    }
  } else {
    for (size_t i = 0; i < bytes_read; i += 32) {
      size_t bytes_read_iter = bytes_read - i;

      if (bytes_read_iter > 32) {
        bytes_read_iter = 32;
      }

      __m256i matches_bytes = _mm256_cmpeq_epi8(*(__m256i*)(text + i), ws_newlines);

      int matches_bits = _mm256_movemask_epi8(matches_bytes);

      *(bits_w32 + i / 32) = (0xffffffff >> (32 - bytes_read_iter)) & (uint32_t)matches_bits;
    }
  }
}

__m256i broadcast_u8(uint8_t w)
{
  __m128i w128 = {w};

  return _mm256_broadcastb_epi8(w128);
}

int main(int argc, char **argv)
{
  if (argc < 3) {
    return 1;
  }

  char *in_filename  = argv[1];
  char *out_filename = argv[2];

  FILE *in_file   = fopen(in_filename,  "r");
  FILE *out_file  = fopen(out_filename, "w");

  if (!in_file) {
    return 1;
  }

  char buffer[BUFFER_SIZE];
  uint64_t bits[BUFFER_SIZE / 64];

  __m256i ws_newline = broadcast_u8((uint8_t)'\n');

  memset(bits, 0, BUFFER_SIZE / 64);

  size_t total_bytes_read = 0;

  size_t bytes_read = fread(buffer, 1, BUFFER_SIZE, in_file);

  while (bytes_read > 0) {
    total_bytes_read += bytes_read;

    process_data(buffer, bytes_read, bits, ws_newline);

    fwrite((char*)bits, 1, (bytes_read + 7) / 8, out_file);

    bytes_read = fread(buffer, 1, BUFFER_SIZE, in_file);
  }

  fflush(out_file);

  fclose(in_file);
  fclose(out_file);

  return 0;
}
