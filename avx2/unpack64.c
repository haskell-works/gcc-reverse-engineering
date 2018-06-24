#include <mmintrin.h>
#include <unistd.h>
#include <immintrin.h>

typedef struct parts {
  uint64_t a;
  uint64_t b;
  uint64_t c;
  uint64_t d;
} parts_t;

typedef union vector {
  parts_t p;
  __m256i v;
} vector_t;

parts_t example(__m256i ii) {
  vector_t v;

  v.v = ii;

  return v.p;
}

int main() {
  vector_t v;

  parts_t x = example(v.v);
  
  return x.a;
}
