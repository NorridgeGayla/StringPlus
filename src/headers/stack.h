#ifndef STRINGPLUS_SRC_HEADERS_STACK_H_
#define STRINGPLUS_SRC_HEADERS_STACK_H_

#include "my_string.h"

typedef struct StackForNumber {
  struct StackForNumber *prev_number;
  my_size_t number;
} StackForNumber;

StackForNumber *InitStack(char symbol);
StackForNumber *Push(StackForNumber *head, char symbol);
my_size_t Pop(StackForNumber **head);
void Clear(StackForNumber *head);

#endif  // STRINGPLUS_SRC_HEADERS_STACK_H_
