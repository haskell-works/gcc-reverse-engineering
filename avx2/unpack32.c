#include <mmintrin.h>
#include <unistd.h>
#include <immintrin.h>

typedef struct parts {
  uint32_t a;
  uint32_t b;
  uint32_t c;
  uint32_t d;
  uint32_t e;
  uint32_t f;
  uint32_t g;
  uint32_t h;
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

int moo () {
  vector_t v = { { 1, 2, 4, 8 } };

  parts_t x = example(v.v);
  
  return x.a | x.b | x.c;
}

int main() {
  return moo();
}
