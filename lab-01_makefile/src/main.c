#include"header.h"
/*
#include"header.h"
Правды ради, тут возникли непонятки. Если раскомиттить 2 include, то по логике дожен быть multiple definition. Но всё компилится
*/

/*
если раскомиттить этот код, получится multiple definition
int max(int a, int b) 
{
  logDebug('m');
  if(a > b)
    return a;
  return b;
}
*/

int main() {
  int a = doComputation(5, 7.0);
  int b = 5;
  max(a, b);
/*min(a, b); - если раскомиттить этот код, получится undefined reference*/
  logDebug('!');

  return 0;
}
