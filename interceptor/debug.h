#include <stdio.h>

void print_hex(const void *data, size_t len) {
  const unsigned char *p = data;
  for (size_t i = 0; i < len; i++) {
    printf("%02X ", p[i]);
  }
  printf("\n");
}

void print_hexdump(const void *data, size_t len) {
  const unsigned char *p = data;
  for (size_t i = 0; i < len; i += 16) {
    printf("%08zx  ", i);

    // hex
    for (size_t j = 0; j < 16; j++) {
      if (i + j < len)
        printf("%02x ", p[i + j]);
      else
        printf("   ");
      if (j == 7)
        printf(" ");
    }

    printf(" |");
    // ascii
    for (size_t j = 0; j < 16 && i + j < len; j++) {
      unsigned char c = p[i + j];
      printf("%c", (c >= 32 && c < 127) ? c : '.');
    }
    printf("|\n");
  }
}
