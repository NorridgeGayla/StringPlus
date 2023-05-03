#include "../headers/my_string.h"

void *my_to_make_char(const char *str, int a) {
  char *new_string = my_NULL;
  if (str != my_NULL) {
    my_size_t size = 0;
    char *ptr = (char *)str;
    while (*(ptr + size) != '\0') size++;
    new_string = (char *)calloc(size + 1, sizeof(char));
    my_strcpy(new_string, str);
    my_size_t i = 0;
    size = 0;
    ptr = new_string;
    while (*(ptr + size) != '\0') size++;
    for (; i < size; i++) {
      if (a) {
        if (new_string[i] >= 65 && new_string[i] <= 90) {
          new_string[i] = new_string[i] + 32;
        }
      } else {
        if (new_string[i] >= 97 && new_string[i] <= 122) {
          new_string[i] = new_string[i] - 32;
        }
      }
    }
    new_string[i] = '\0';
  }
  return new_string;
}

void *my_to_upper(const char *str) { return my_to_make_char(str, 0); }
void *my_to_lower(const char *str) { return my_to_make_char(str, 1); }

/*Function "my_insert" allocates memory (malloc), and adds substring starts
with "start_index" byte. User needs to free the allocated memory to avoid leaks.
*/
void *my_insert(const char *src, const char *str, my_size_t start_index) {
  char *new_string = my_NULL;
  if (src != my_NULL && str != my_NULL) {
    char *source_ptr = (char *)src;
    char *string_ptr = (char *)str;
    my_size_t size = my_strlen(source_ptr) + my_strlen(string_ptr) + 1;
    new_string = (char *)malloc((size + 1) * sizeof(char));
    if (start_index > my_strlen(source_ptr)) {
      free(new_string);
      new_string = my_NULL;
    }
    if (new_string != my_NULL) {
      for (my_size_t i = 0, j = 0; i < size; i++, j++) {
        if (i < start_index || i >= start_index + my_strlen(string_ptr)) {
          new_string[i] = source_ptr[j];
        } else {
          while (*string_ptr != '\0') {
            new_string[i] = *string_ptr;
            string_ptr++;
            i++;
          }
          i--;
          j--;
        }
      }
    }
  }
  return new_string;
}

void *my_trim(const char *src, const char *trim_chars) {
  char *new_string = my_NULL;
  if (src != my_NULL) {
    my_size_t size = 0;
    char *ptr = (char *)src;
    while (*(ptr + size) != '\0') size++;
    new_string = (char *)calloc(size + 1, sizeof(char));
    my_strcpy(new_string, src);
    if (trim_chars != my_NULL) {
      for (int i = size; i >= 0 && my_strchr(trim_chars, new_string[i]) != 0;
           i--) {
        new_string[i] = '\0';
      }
      while (new_string[0] != '\0' &&
             my_strchr(trim_chars, new_string[0]) != 0) {
        my_memmove(&new_string[0], &new_string[1], my_strlen(new_string));
      }
    }
  }
  return new_string;
}
