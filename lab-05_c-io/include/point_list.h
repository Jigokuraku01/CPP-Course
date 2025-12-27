#ifndef POINT_LIST_H_
#define POINT_LIST_H_
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "clist.h"
extern const int SIZE_OF_INT_IN_LIST;
extern const int COUNT_OF_BYTS_IN_BYTE;
extern int Max_Input_Numb;
#define container_of(ptr, type, member) (type *)((char *)(ptr) - offsetof(type, member))

void add_point(intrusive_list_t *head, int x, int y);
void remove_point(intrusive_list_t *head, int x, int y);
void show_all_points(intrusive_list_t *head);
void remove_all_points(intrusive_list_t *head);
int count_list(intrusive_list_t *head);
void print_list(intrusive_list_t *head, char*str);
void Save_Txt_List(intrusive_list_t* head, FILE* fout);
void Save_Bin_List(intrusive_list_t* head, FILE* fout);
#endif // POINT_LIST_H_