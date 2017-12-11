#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <arpa/inet.h>
#define PORT 8888
#define O_SIZE 20
//#define O_QUANTITY 1
void order(int orderArray[O_SIZE]) //function that takes the order from the client
{
  int choice=0, i=0, quantity = 0, ans=1;
  //printf("You entered: %d\n",choice);
  //int orderArray[O_SIZE]= {0};

while (choice!=8){

     printf("Enter your choice: ");
     scanf("%d",&choice);
    orderArray[i] = choice;
    i++;
  if (choice<9)
  {
      if(choice == 8) break;
/* now take the quantity of the product*/
    printf("Enter the quantity: ");
    scanf("%d",&quantity);
    orderArray[i] = quantity;
    i++;
  }
  else{
    printf("Wrong input\n");
  }
}
printf("Thank you for your order. Good bye!\n");

  for(int j = 0; j<O_SIZE; j++)
  {
    printf("%d\n", orderArray[j]);
  }
}

int main(int argc, char const *argv[])
{
  struct sockaddr_in address;
  int sock = 0, valread;
  struct sockaddr_in serv_addr;
  char *hello = "Hello from client";
  char buffer[1024] = {0}, cchat[1024];
  char *bye = "bye";
  int orderArray[O_SIZE]= {0};

  //printf("CREATING CLIENT SOCKET .....\n");
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
  {
    printf("\n Socket creation error \n");
    return -1;
  }
  //printf("DEFINING SOCKET FAMILY, ADDRESS & PORT .....\n");
  memset(&serv_addr, '0', sizeof(serv_addr)); // initialize serv_addr array with the value 0
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);
  // Convert IPv4 and IPv6 addresses from text to binary form
  if(inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr)<=0) //convert string '127.0.0.1' to the network address and copy the the sin_addr
  {
  printf("\nInvalid address/ Address not supported \n");
  return -1;
  }
  //printf("CONNECTING ON PORT 8888 TO COMMUNICATE WITH SERVER..\n");
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
  {
    printf("\nConnection Failed \n");
  return -1;
  }

  valread = read( sock , buffer, 1024);
  printf("%s\n",buffer );

  order(orderArray); // function takes the order from the client
  send(sock , orderArray , O_SIZE , 0 );//
  while(1)
  {
  memset(buffer, 0, sizeof(buffer));
  memset(cchat, 0, sizeof(cchat));

  //fgets (cchat, sizeof(cchat), stdin); // take the message from the terminal
  //send(sock , cchat , strlen(cchat) , 0 );

  valread = read( sock , buffer, 1024);
  printf("Server: ");
  printf("%s\n",buffer );
  cchat[strlen(cchat)] = '\0';
  if(strncmp(cchat, bye, strlen(bye))==0)
  break;
}
  return 0;
  }
