#ifndef CLIST_H_
#define CLIST_H_
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct intrusive_node
{
  struct intrusive_node *next;
  struct intrusive_node *prev;
} intrusive_node_t;

#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

typedef struct
{
  intrusive_node_t *head;
} intrusive_list_t;

void init_list(intrusive_list_t *head);
void add_node(intrusive_list_t *head, intrusive_node_t *node);
void remove_node(intrusive_list_t *head, intrusive_node_t *node);

int get_length(intrusive_list_t *head);

#endif // CLIST_H_
