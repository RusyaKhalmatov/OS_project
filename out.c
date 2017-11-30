#include <stdio.h>

int main()
{

char input[100];
  printf("WElcome enter some string here: ");
  //scanf("%s", input);
  fgets(input, sizeof(input), stdin);
  printf("You entered:");
  puts(input);
  //printf("%s\n", input);


  return 0;
}
