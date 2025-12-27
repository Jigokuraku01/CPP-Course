#include "clist.h"
typedef struct point
{
  int x;
  int y;
  intrusive_node_t node;
} point_t;

void add_point(intrusive_list_t *head, int x, int y)
{
  point_t *tmp = malloc(sizeof(point_t));
  (*tmp).node.next = NULL;
  (*tmp).node.prev = NULL;
  tmp->x = x;
  tmp->y = y;
  add_node(head, &((*tmp).node));
}

void remove_point(intrusive_list_t *head, int x, int y) // removes all (x, y) pairs
{
  int sz = get_length(head);
  intrusive_node_t *tmp_node = head->head;
  for (int i = 0; i < sz; ++i)
  {
    point_t *tmp = container_of(tmp_node, point_t, node);
    tmp_node = tmp_node->next;
    if (tmp->x == x && tmp->y == y)
    {
      remove_node(head, &((*tmp).node));
      free(tmp);
    }
  }
}

void show_all_points(intrusive_list_t *head)
{
  int sz = get_length(head);
  point_t *tmp_point;
  intrusive_node_t *tmp_node = head->head;
  for (int i = 0; i < sz; ++i)
  {

    tmp_point = container_of(tmp_node, point_t, node);
    printf("(%d %d)", tmp_point->x, tmp_point->y);
    if (i + 1 != sz)
      printf(" ");
    tmp_node = tmp_node->next;
  }
  printf("\n");
}

void remove_all_points(intrusive_list_t *head)
{
  int sz = get_length(head);
  for (int i = 0; i < sz; ++i)
  {
    point_t *tmp = container_of(head->head, point_t, node);
    remove_node(head, head->head);
    free(tmp);
  }
}

int main()
{
  intrusive_list_t l;
  init_list(&l);
  char c[] = "input";
  int x, y;
  while (1)
  {
    scanf("%300s", c);
    if (strcmp(c, "add") == 0)
    {
      scanf("%d %d", &x, &y);
      add_point(&l, x, y);
    }
    else if (strcmp(c, "rm") == 0)
    {
      scanf("%d %d", &x, &y);
      remove_point(&l, x, y);
    }
    else if (strcmp(c, "print") == 0)
      show_all_points(&l);
    else if(strcmp(c, "rma") == 0)
      remove_all_points(&l);
    else if(strcmp(c, "len") == 0)
      printf("%d\n", get_length(&l));
    else if(strcmp(c, "exit") == 0)
    {
      remove_all_points(&l);
      return 0;
    }
    else
      printf("Unknown command\n");
  }

  return 0;
}