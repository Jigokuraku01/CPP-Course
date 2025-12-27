#include "clist.h"

void add_node(intrusive_list_t *head, intrusive_node_t *node)
{
  if (get_length(head) == 0)
    head->head = node;
  else
  {
    head->head->prev = node;
    node->next = head->head;
    head->head = node;
  }
}
void remove_node(intrusive_list_t *head, intrusive_node_t *node)
{
  if (head->head == node)
  {
    intrusive_node_t *next = node->next;
    head->head = next;
    return;
  }
  intrusive_node_t *next = node->next;
  intrusive_node_t *prev = node->prev;
  if (next != NULL)
    next->prev = prev;
  if (prev != NULL)
    prev->next = next;
}

int get_length(intrusive_list_t *head)
{
  int len = 0;
  intrusive_node_t *tmp_node = head->head;
  while (tmp_node != NULL)
  {
    len++;
    tmp_node = tmp_node->next;
  }

  return len;
}

void init_list(intrusive_list_t *head)
{
  head->head = NULL;
}