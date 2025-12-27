#ifndef CLIST_H_
#define CLIST_H_

typedef struct intrusive_node
{
  struct intrusive_node *next;
  struct intrusive_node *prev;
} intrusive_node_t;

typedef struct
{
  intrusive_node_t *head;
} intrusive_list_t;

void init_list(intrusive_list_t *head);
void add_node(intrusive_list_t *head, intrusive_node_t *node);
void remove_node(intrusive_list_t *head, intrusive_node_t *node);
int get_length(intrusive_list_t *head);
void apply(intrusive_list_t *list, void (*op)(intrusive_node_t *node, void *data), void *data);
#endif // CLIST_H_
