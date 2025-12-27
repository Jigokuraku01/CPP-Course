#include "point_list.h"
#include "clist.h"

const int SIZE_OF_INT_IN_LIST = 3;
const int COUNT_OF_BYTS_IN_BYTE = 8;
int Max_Input_Numb = 1;
int main(int argc, char** argv)
{
	int x;
	int y;
	for (int i = 0; i < SIZE_OF_INT_IN_LIST * COUNT_OF_BYTS_IN_BYTE; ++i)
		Max_Input_Numb *= 2;
	intrusive_list_t l;
	init_list(&l);
	FILE* fin;
	if (strcmp((const char*)argv[1], (const char*)"loadtext") == 0)
	{
		fin = fopen(argv[2], "r");
		while (!feof(fin))
		{
			if(fscanf(fin, "%d %d\n", &x, &y) != 2)
				break;
			add_point(&l, x, y);
			if(ferror(fin))
				break;
			if(feof(fin))
				break;
		}
	}
	else if (strcmp((const char*)argv[1], (const char*)"loadbin") == 0)
	{
		fin = fopen(argv[2], "rb");
		while (!feof(fin))
		{
			x = 0;
			y = 0;
			fread(&x, SIZE_OF_INT_IN_LIST, 1, fin);
			fread(&y, SIZE_OF_INT_IN_LIST, 1, fin);
			if(x >= Max_Input_Numb / 2)
				x -= (Max_Input_Numb);
			if(y >= Max_Input_Numb / 2)
				y -= (Max_Input_Numb);
			if(ferror(fin))
				break;
			if(feof(fin))
				break;
			add_point(&l, x, y);
		}
	}
	fclose(fin);
	char* action = argv[3];
	if (strcmp(action, "count") == 0)
		printf("%d\n", count_list(&l));
	else if (strcmp(action, "print") == 0)
	{
		int MAX_SIZE_FOR_STR = 500;
		char* final_str = malloc(sizeof(char) * MAX_SIZE_FOR_STR);
		for (int  i = 0; i < MAX_SIZE_FOR_STR; ++i)
			final_str[i] = 0;
		int CNT_FOR_ADD_STR = argc - 4;
		for (int i = 0; i < CNT_FOR_ADD_STR; ++i)
		{
			final_str = strcat(final_str, argv[i + 4]);
			if (i + 1 != CNT_FOR_ADD_STR)
				final_str = strcat(final_str, " ");
		}
		print_list(&l, final_str);
		free(final_str);
		printf("\n");
	}
	else if (strcmp(action, "savetext") == 0)
	{
		FILE* fout = fopen(argv[4], "w");
		Save_Txt_List(&l, fout);
		fclose(fout);
	}
	else if (strcmp(action, "savebin") == 0)
	{
		FILE* fout = fopen(argv[4], "wb");
		Save_Bin_List(&l, fout);
		fclose(fout);
	}
	remove_all_points(&l);
	return 0;
}
