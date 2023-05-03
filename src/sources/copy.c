#include "../headers/my_string.h"

void *my_memcpy(void *dest, const void *src, my_size_t n) {
  for (my_size_t i = 0; i < n; i++) {
    *((char *)dest + i) = *((char *)src + i);
  }
  return dest;
}

void *my_memmove(void *dest, const void *src, my_size_t n) {
  char *buff = (char *)calloc(n, sizeof(char));
  for (my_size_t i = 0; i < n; i++) {
    *((char *)buff + i) = *((char *)src + i);
  }
  for (my_size_t i = 0; i < n; i++) {
    *((char *)dest + i) = *((char *)buff + i);
  }
  free(buff);
  return dest;
}

void *my_memset(void *str, int c, my_size_t n) {
  for (my_size_t i = 0; i < n; i++) {
    *((char *)str + i) = c;
  }
  return str;
}

char *my_strcpy(char *dest, const char *src) {
  char *r = dest;
  while ((*dest++ = *src++)) {
  }
  return r;
}

char *my_strncpy(char *dest, const char *src, my_size_t n) {
  char *ptr = dest;
  while (*src && n-- && (dest != my_NULL)) {
    *dest++ = *src++;
  }
  *dest = '\0';
  return ptr;
}
