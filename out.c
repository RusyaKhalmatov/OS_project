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
  while (choice!=0) {
  /* code */
  switch(choice)
  {
    case 1:
      printf("ONe\n");
      printf("Choice: ");
      scanf("%d", &choice);
      break;
    case 2:
      printf("TWo\n");
      printf("Choice: ");
      scanf("%d", &choice);
      break;
    case 3:
      printf("Three\n");
      printf("Choice: ");
      scanf("%d", &choice);
      break;

  }
}



  return 0;
}
