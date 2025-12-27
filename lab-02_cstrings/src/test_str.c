#include"test_str.h"

void test_my_strlen(char* s)
{
	if(strlen(s) != my_strlen(s))
		assert((strlen(s) != my_strlen(s)));
}

void test_my_strcmp(char *s1, char *s2)
{
	if (strcmp(s1, s2) == 0 && (my_strcmp(s1, s2) != 0))
		assert((my_strcmp(s1, s2) != 0));
	if (strcmp(s1, s2) > 0 && (my_strcmp(s1, s2) <= 0))
		assert((my_strcmp(s1, s2) <= 0));
	if(strcmp(s1, s2) < 0 && (my_strcmp(s1, s2) >= 0))
		assert((my_strcmp(s1, s2) >= 0));
}
void test_my_strcpy(char * s1, const char * s2)
{
	my_strcpy(s1, s2);
	if((strcmp(s1, s2) != 0))
		assert((strcmp(s1, s2) != 0));
}
void test_my_strcat( char *posToCat,  char *s1,  const char *s2)
{
	strcat(strcat(posToCat, s1), s2);
	my_strcat(s1, s2);
	if((strcmp(s1, posToCat) != 0))
		assert((strcmp(s1, posToCat) != 0));
}