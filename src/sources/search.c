#include "../headers/my_string.h"

void *my_memchr(const void *str, int c, my_size_t n) {
  char *result = my_NULL;
  for (my_size_t i = 0; i < n; i++) {
    if (((char *)str)[i] == c) {
      result = ((char *)str + i);
      break;
    }
  }
  return result;
}

char *my_strchr(const char *str, int c) {
  my_size_t i = 0;
  while (str[i] && str[i] != c) ++i;
  return c == str[i] ? (char *)str + i : my_NULL;
}

char *my_strstr(const char *haystack, const char *needle) {
  char *ptr = (char *)haystack;
  char *result = my_NULL;
  my_size_t i_for_str = 0;
  my_size_t i = 0;
  int flag = 0;
  while (*(ptr + i) != '\0') {
    if (*(ptr + i) == *needle) {
      result = ptr + i;
      i_for_str = 0;
      char *needle_ptr = (char *)needle;
      while ((*(needle_ptr + i_for_str) != '\0') &&
             (*(ptr + i + i_for_str) != '\0')) {
        if (*(ptr + i + i_for_str) != *(needle_ptr + i_for_str)) {
          result = my_NULL;
          i_for_str = 0;
          break;
        }
        if (*(needle_ptr + 1 + i_for_str) == '\0') {
          flag = 1;
        }
        i_for_str++;
      }
      if (*(ptr + i + i_for_str) == '\0' &&
          (*(needle_ptr + i_for_str) != '\0')) {
        result = my_NULL;
      }
    }
    if (flag) break;
    i++;
  }
  return *((char *)needle) == '\0' ? (char *)haystack : result;
}

char *my_strrchr(const char *str, int c) {
  char *ptr = (char *)str;
  char *result = my_NULL;
  my_size_t i = 0;
  my_size_t ans = 0;
  while (*(ptr + i) != '\0') {
    if (*(ptr + i) == c) ans = i;
    i++;
  }
  if (c == '\0' && *(ptr + i) == '\0') {
    ans = i;
  }
  if (*str == '\0' && c == '\0') {
    result = (char *)str;
  } else if ((*str == '\0' && c != '\0') || ans == 0) {
    result = my_NULL;
  } else {
    result = ptr + ans;
  }
  return result;
}

char *my_strpbrk(const char *str1, const char *str2) {
  char *ptr = (char *)str1;
  char *ptr_str2 = my_NULL;
  my_size_t i = 0;
  my_size_t i_for_str;
  char *result = my_NULL;
  while (*(ptr + i) != '\0') {
    i_for_str = 0;
    ptr_str2 = (char *)str2;
    while (*(str2 + i_for_str) != '\0') {
      if (*(ptr + i) == *(ptr_str2 + i_for_str)) {
        result = ptr + i;
        break;
      }
      i_for_str++;
    }
    if (result != my_NULL) break;
    i++;
  }
  return result;
}
