#include "../headers/stack.h"

StackForNumber *InitStack(char symbol) {
  StackForNumber *head = (StackForNumber *)malloc(sizeof(StackForNumber));
  if (head != my_NULL) {
    head->number = (my_size_t)(symbol - 48);
    head->prev_number = my_NULL;
  }
  return head;
}

StackForNumber *Push(StackForNumber *head, char symbol) {
  StackForNumber *new_element = InitStack(symbol);
  if (new_element != my_NULL) {
    new_element->prev_number = head;
  }
  return new_element;
}

my_size_t Pop(StackForNumber **head) {
  my_size_t res = (*head)->number;
  StackForNumber *tmp = *head;
  (*head) = (*head)->prev_number;
  free(tmp);
  return res;
}

void Clear(StackForNumber *head) {
  while (head->prev_number != my_NULL) {
    Pop(&head);
  }
  free(head);
}
