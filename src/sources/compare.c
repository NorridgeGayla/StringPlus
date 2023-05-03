#include "../headers/my_string.h"

#define SIZE 256

int my_memcmp(const void *str1, const void *str2, my_size_t n) {
  my_size_t i = 0;
  int result = 0;
  if (*((char *)str1 + i) == '\0' && *((char *)str2 + i) == '\0') {
    result = 0;
  } else {
    while (i < n && !result) {
      result = (*((char *)str1 + i) - *((char *)str2 + i));
      i++;
    }
  }
  return result;
}

int my_strcmp(const char *str1, const char *str2) {
  int result = 0;
  my_size_t i = 0;
  if (str1[i] == '\0' && str2[i] == '\0') {
    result = 0;
  } else {
    while (!result) {
      result = str1[i] - str2[i];
      if (str1[i] == '\0' && str2[i] == '\0') {
        break;
      }
      i++;
    }
  }
  return result;
}

int my_strncmp(const char *str1, const char *str2, my_size_t n) {
  int result = 0;
  my_size_t i = 0;
  while (i < n && !result) {
    result = str1[i] - str2[i];
    if (str1[i] == '\0' && str2[i] == '\0') {
      break;
    }
    i++;
  }
  return result;
}
