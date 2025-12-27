#include"test_str.h"
int main()
{
	char mas11[4] = {'a', 'b', 'c', '\0'};
	test_my_strlen(mas11);
	printf("%s\n", "strlen done");
	char mas12[4] = {'a', 'b', 'c', '\0'};
	char mas22[3] = {'t', 'k', '\0'};
	test_my_strcmp(mas12, mas22);
	printf("%s\n", "strcmp done");
	char mas13[4] = {'a', 'b', 'c', '\0'};
	const char mas23[1] = {'\0'};
	test_my_strcpy(mas13, mas23);
	printf("%s\n", "strcpy done");
	 char mas14[100] = {'a', 'b', 'c', '\0'};
	const char mas24[3] = {'t', 'k', '\0'};
	char nul[1000] = {0};
	test_my_strcat(nul, mas14, mas24);
	printf("%s\n", "strcat done");
}