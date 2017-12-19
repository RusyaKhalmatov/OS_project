#include <stdio.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>
#include <math.h>
#include <arpa/inet.h>
#define PORT 32568
#define O_SIZE 10

char* parse(int number) {


    int digits = 0;
    int temp = number;

    while (temp != 0) {

        temp /= 10;
        digits++;
    }
    temp = number;
    char str[digits + 1];
    for (int i = 0; i < digits; i++) {

        str[i] = (char)(temp % 10) + 48;
        temp /= 10;
    }

    str[digits] = '\0';

    char* result = malloc(sizeof(char) * digits + 1);
    int j = digits - 1;
    for (int i = 0; i < digits; i++) {

        result[i] = str[j];
        j--;
    }
    result[digits] = '\0';

    return result;
}

int cast(char* str) {

    int result = 0;
    int digits = strlen(str);
    int power = digits;

    for (int i = 0; i < digits; i++) {

        result += ((int)str[i] - 48) * ((int)pow(10, power - 1));
        power--;
    }

    return result;

}

void order(char orderArray[O_SIZE]); //function that takes the order from the client
int connection();
void send_order(char array, int size, int sock);
int main(int argc, char const *argv[])
{
  int sock = connection();
  char orderArray[O_SIZE]= {0};
  char buffer[1024] = {0}, cchat[1024];
  char *hello = "Hello from client";
  char *bye = "bye";

  int valread = read( sock , buffer, 1024);
  printf("%s\n",buffer);

  order(orderArray); // function takes the order from the client
  send(sock, orderArray, strlen(orderArray), 0); // send order array to the client


  //send_order(orderArray,O_SIZE,sock);
  while(1)
  {
    memset(buffer, 0, sizeof(buffer));
    memset(cchat, 0, sizeof(cchat));
    fgets (cchat, sizeof(cchat), stdin); // take the message from the terminal
    send(sock , cchat , strlen(cchat) , 0 );
    valread = read( sock , buffer, 1024);
    printf("Server: ");
    printf("%s\n",buffer );
    cchat[strlen(cchat)] = '\0';
    if(strncmp(cchat, bye, strlen(bye))==0) break;
  }


  return 0;
}

void order(char items[O_SIZE]) //function that takes the order from the client
{
  int  choice=0, ans=1;
  //printf("You entered: %d\n",choice);
  //int orderArray[O_SIZE]= {0};

        int meal_counter = 0;

        int amount = 0;

        char client_address[40];
        char client_phone[40];

        do {

            //printMenu(items, num_rows);
            printf("Enter: ");
            scanf("%d", &choice);

            if (choice == 0)
                break;

            printf("Enter amount: ");
            scanf("%d", &amount);

            char* temp1 = parse(choice);

            strcat(items, temp1);
            strcat(items, "?");

            char* temp2 = parse(amount);

            strcat(items, temp2);
            strcat(items, "!");

            ++meal_counter;

        } while(choice != 0);

        // printf("Enter Address: ");
        // scanf("%s", client_address);
        //int t = send(sock, client_address, strlen(client_address), 0);
        //printf("%d\n", t);
        // printf("Enter Phone: ");
        // scanf("%s", client_phone);
        //int y = send(sock, client_phone, strlen(client_address), 0);
        //printf("%d\n", y);

        printf("%s\n", items);
      //  char* x = parse(meal_counter);
      //  strcat(items, x);
      //  printf("%s\n", items);


}
int connection()
{
    int sock = 0;
    struct sockaddr_in serv_addr;

    //printf("CREATING CLIENT SOCKET .....\n");
    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
      printf("\n Socket creation error \n");
      return -1;
    }
    //printf("DEFINING SOCKET FAMILY, ADDRESS & PORT .....\n");
    memset(&serv_addr, '0', sizeof(serv_addr)); // initialize serv_addr array with the value 0
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    //serv_addr.sin_addr.s_addr = inet_addr("192.168.43.169");
    serv_addr.sin_port = htons(PORT);
    //printf("CONNECTING ON PORT 8888 TO COMMUNICATE WITH SERVER..\n");
    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0)
    {
      printf("\nConnection Failed \n");
    return -1;
    }
    return sock;
  }

void send_order(char array, int size, int sock)  // function that sends the order array to the server
{
//  send(sock, )
  //write(sock, &size, sizeof(size));
 //write(sock, &array, sizeof(array));
}
