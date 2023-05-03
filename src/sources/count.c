#include "../headers/my_string.h"

#define SIZE 256

my_size_t my_strlen(const char *str) {
  my_size_t result = 0;
  while (str[result] != '\0') {
    result++;
  }
  return result;
}

my_size_t my_strspn(const char *str1, const char *str2) {
  my_size_t result = 0;
  if (!(str1 == my_NULL || str2 == my_NULL)) {
    my_size_t index = 0;
    int equal = 1;
    while (str1[result] != '\0' && equal) {
      index = 0;
      equal = 0;
      while (str2[index] != '\0' && !equal) {
        if (str1[result] == str2[index]) {
          equal = 1;
        }
        index++;
      }
      if (equal) {
        result++;
      }
    }
  }
  return result;
}

my_size_t my_strcspn(const char *str1, const char *str2) {
  my_size_t result = 0;
  if (!(str1 == my_NULL || str2 == my_NULL)) {
    my_size_t index = 0;
    int equal = 0;
    while (str1[result] != '\0' && !equal) {
      index = 0;
      while (str2[index] != '\0' && !equal) {
        if (str1[result] == str2[index]) {
          equal = 1;
        }
        index++;
      }
      if (!equal) {
        result++;
      }
    }
  }
  return result;
}
