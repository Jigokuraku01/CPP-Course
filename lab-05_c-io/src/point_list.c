#include "clist.h"
#include "point_list.h" 

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

void remove_all_points(intrusive_list_t *head)
{
  int sz = count_list(head);
  for (int i = 0; i < sz; ++i)
  {
    point_t *tmp = container_of(head->head, point_t, node);
    remove_node(head, head->head);
    free(tmp);
  }
}

void Func_For_Count(intrusive_node_t * node, void *n)
{
  node = node;
  (*(int*)n)++;
}

void Func_For_Save_Txt(intrusive_node_t * tmp_node, void *file)
{
  file = (FILE*)file;
  point_t* tmp_point = container_of(tmp_node, point_t, node);
  fprintf(file, "%d %d\n", tmp_point->x, tmp_point->y);
}

void Func_For_Save_Bin(intrusive_node_t * tmp_node, void *file)
{
  file = (FILE*)file;
  point_t* tmp_point = container_of(tmp_node, point_t, node);
  int tmp_x = tmp_point->x;
  int tmp_y = tmp_point->y;
  if(tmp_x < 0)
    tmp_x = Max_Input_Numb + tmp_x;
  fwrite(&tmp_x, SIZE_OF_INT_IN_LIST, 1, file);
  if(tmp_y < 0)
    tmp_y = Max_Input_Numb + tmp_y;
  fwrite(&tmp_y, SIZE_OF_INT_IN_LIST, 1, file);
}

void Func_For_Print(intrusive_node_t * tmp_node, void *str)
{
  point_t* tmp_point = container_of(tmp_node, point_t, node);
  printf((char*)str, tmp_point->x, tmp_point->y);
}

int count_list(intrusive_list_t *head)
{
  int ans = 0;
  apply(head, &Func_For_Count, &ans);
  return ans;
}

void print_list(intrusive_list_t *head, char*str)
{
  apply(head, &Func_For_Print, str);
}

void Save_Txt_List(intrusive_list_t* head, FILE* fout)
{
  apply(head, Func_For_Save_Txt, fout);
}

void Save_Bin_List(intrusive_list_t* head, FILE* fout)
{
  apply(head, Func_For_Save_Bin, fout);
}