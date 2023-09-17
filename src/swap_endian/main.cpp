#include <cstdint>
#include <cstdio>

uint32_t swap_endian(uint32_t val) {
  return (((uint32_t)(val) & 0xff000000) >> 24) | (((uint32_t)(val) & 0x00ff0000) >> 8) | 
          (((uint32_t)(val) & 0x0000ff00) << 8) | (((uint32_t)(val) & 0x000000ff) << 24);
}

int main() {
  uint32_t val = 0x12345678;
  printf("%#x\n", val);
  printf("%#x\n", swap_endian(val));
  // 如何判断大小端存储
  union {
    int i;
    char ch;
  } u;
  u.i = 1;
  if (u.ch == 1) printf("小端存储\n");
  else printf("大端存储\n");
  return 0;
}