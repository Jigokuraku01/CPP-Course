#include"mergesort.h"


int comp(const void* a, const void* b)
{
	return strcmp((char*)a, (const char*)b);
}

int comp_int(const void* a, const void* b)
{
	int mul = 1;
	if(*(char*)a == '-' && *(char*)b != '-')
		return -1;
	if(*(char*)a != '-' && *(char*)b == '-')
		return 1;
	if(*(char*)a == '-' && *(char*)b == '-')
		mul = -1;
	if(strlen((char*)a) != strlen((char*)b))
		return (strlen((char*)a) - strlen((char*)b)) * mul;
	return mul * strcmp((char*)a, (char*)b);
}

int main(int argc, char** argv)
{
	int n = argc - 2;
	int el_size = -1;
	char **ans = malloc(sizeof(char*) * (n));
	if(ans == NULL)
	{
		printf("Error: memory allocation failed");
		return 1;
	}
	for (int i = 0; i < n; ++i)
		*(ans + i) = *(argv + i + 2);

	if(strcmp(*(argv + 1), "int") != 0)
	{
		if(mergesort(ans, n, el_size, &comp) == -1)
		{
			free(ans);
			printf("Error: memory allocation failed");
			return 1;
		}
	}
	else
	{
		if(mergesort(ans, n, el_size, &comp_int) == -1)
		{
			free(ans);
			printf("Error: memory allocation failed");
			return 1;
		}
	}

	for (int i = 0; i < n; ++i)
	{
		printf("%s", *(ans + i));
		if(i != n - 1)
			printf(" ");
	}
	printf("\n");
	free(ans);
	return 0;
}