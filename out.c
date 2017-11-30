#include <stdio.h>

int main()
{

  /*char input[100];
  printf("WElcome enter some string here: ");
  //scanf("%s", input);
  fgets(input, sizeof(input), stdin);
  printf("You entered:");
  puts(input);
  //printf("%s\n", input);*/

  int choice;

  printf("Enter your choice: ");
  scanf("%d",&choice);
  printf("You entered: %d\n",choice);
  int ans=1;
  while (ans!=0) {
  /* code */
  switch(choice)
  {
    case 1:
      printf("ONe");
      printf("Choice: ");
      scanf("%d", &ans);
      break;
    case 2:
      printf("TWo");
      printf("Choice: ");
      scanf("%d", &ans);
      break;
    case 3:
      printf("Three");
      printf("Choice: ");
      scanf("%d", &ans);
      break;

  }
}



  return 0;
}
