#include "clist.h"
#include "point_list.h"
void add_node(intrusive_list_t *head, intrusive_node_t *node)
{
  if (head->head == NULL)
    head->head = node;
  else
  {
    int sz = count_list(head);
    intrusive_node_t* tmp_node = head->head;
    for(int i = 0; i < sz - 1; ++i)
      tmp_node = tmp_node->next;
    tmp_node->next = node;
    node->prev = tmp_node;  
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

void init_list(intrusive_list_t *head)
{
  head->head = NULL;
}

void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data)
{
  intrusive_node_t* tmp = list->head;
  while (tmp != NULL)
  {
    op(tmp, data);
    tmp = tmp->next;
  }
}