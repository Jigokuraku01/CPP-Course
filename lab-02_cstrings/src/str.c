#include"str.h"

char *my_strcpy(char *s1, const char *s2)
{
	char* st = s1;
	while (*s2 != '\0') *s1++ = *s2++;
	*s1 = '\0';
	return st;
}

size_t my_strlen(char *s)
{
	size_t ans = 0;
	while (*(s++)) ans++;
	return ans;
}

int my_strcmp(char *s1, char *s2)
{
	while ((*s1) == (*s2) && *s1 != '\0' && *s2 != '\0') {s1++;s2++;}
	if (*s1 == '\0' && *s2 == '\0')
		return 0;
	if (*s1 > *s2)
		return 1;
	return -1;
}

char *my_strcat(char *s1, const char *s2)
{
	char* st = s1;
	while (*s1 != '\0') s1++;
	my_strcpy(s1, s2);
	return st;
}