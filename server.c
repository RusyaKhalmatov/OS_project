#include <stdio.h>
#include <string.h>   //strlen
#include <stdlib.h>
#include <errno.h>
#include <unistd.h>   //close
#include <arpa/inet.h>    //close
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/time.h> //FD_SET, FD_ISSET, FD_ZERO macros
#define SIZE 8
#define TRUE   1
#define FALSE  0
#define PORT 32568

void readingFromFile(char *filename, char messageArray[SIZE][50]);// reads from a file menu, the entire menu
void process_order(char or_array[],int size, int order[50]);
int main(int argc , char *argv[])
{
    int opt = TRUE;
    int master_socket , addr_length , new_socket , client_socket[30] ,
          numb_of_clients = 30 , activity, i , valread , sd;
    int max_sd;
    struct sockaddr_in address;

    char buffer[1025];  //data buffer of 1K
    char mesbuffer[1024]; //message buffer
    char schat[1024];
    char menubuffer[50];
    char *bye = "bye";
    char messageArray[SIZE][50] = {""}; // menu array
    //set of socket descriptors
    fd_set readfds;

    //a message
  //  char *message = "HELLO FROM THE SERVER \r\n";
    char *message = "\t ***Welcome***\n";

    //initialise all client_socket[] to 0 so not checked
    for (i = 0; i < numb_of_clients; i++)
    {
        client_socket[i] = 0;
    }

    //create a master socket
    if( (master_socket = socket(AF_INET , SOCK_STREAM , 0)) == 0)
    {
        perror("Socket creation failed");
        exit(EXIT_FAILURE);
    }

    // allow multiple connections ,
    if( setsockopt(master_socket, SOL_SOCKET, SO_REUSEADDR, (char *)&opt,
          sizeof(opt)) < 0)
    {
        perror("setsockopt");
        exit(EXIT_FAILURE);
    }

    //type of socket created
    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    //address.sin_addr.s_addr = inet_addr("192.168.43.169");
    address.sin_port = htons( PORT );

    //bind the socket to localhost port 8888
    if (bind(master_socket, (struct sockaddr *)&address, sizeof(address))<0)
    {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }
    printf("Listener on port %d \n", PORT);

    //maximum 10 connections
    if (listen(master_socket, 10) < 0)
    {
        perror("listen");
        exit(EXIT_FAILURE);
    }

    //accept the incoming connection
    addr_length = sizeof(address);
    puts("Waiting for connections ...");

    while(TRUE)
    {
        //clear the socket set
        FD_ZERO(&readfds);

        //add master socket to set
        FD_SET(master_socket, &readfds);
        max_sd = master_socket;

        //add child sockets to set
        for ( i = 0 ; i < numb_of_clients ; i++)
        {
            //socket descriptor
            sd = client_socket[i];

            //if valid socket descriptor then add to read list
            if(sd > 0)
                FD_SET( sd , &readfds);

            //highest file descriptor number, need it for the select function
            if(sd > max_sd)
                max_sd = sd;
        }

        //wait for an activity on one of the sockets , timeout is NULL ,
        //so wait indefinitely
        activity = select( max_sd + 1 , &readfds , NULL , NULL , NULL);

        if ((activity < 0) && (errno!=EINTR))
        {
            printf("select error");
        }

        //If something happened on the master socket ,
        //then its an incoming connection
        if (FD_ISSET(master_socket, &readfds))
        {
          if ((new_socket = accept(master_socket, (struct sockaddr *)&address, (socklen_t*)&addr_length))<0)
            {
            perror("accept");
            exit(EXIT_FAILURE);
            }
            //inform user of socket number - used in send and receive commands
            printf("New connection , socket fd is %d , ip is : %s , port : %d \n" , new_socket , inet_ntoa(address.sin_addr) , ntohs
            (address.sin_port));


          /********SENDING MESSAGE TO THE CLIENT*/

          readingFromFile("menu",messageArray);//read from file MENU to the messageArray
          send(new_socket, message, strlen(message), 0) != strlen(message); // send welcome message

          for(int j=0; j< SIZE; j++)
          {
            send(new_socket, messageArray[j], strlen(messageArray[j]),0); // send menu message
          }

            puts("Welcome message sent successfully");


            //add new socket to array of sockets
            for (i = 0; i < numb_of_clients; i++)
            {
                //if position is empty
                if( client_socket[i] == 0 )
                {
                    client_socket[i] = new_socket;
                    printf("Adding to list of sockets as %d\n" , i);

                    break;
                }
            }
        }

        //else its some IO operation on some other socket
        for (i = 0; i < numb_of_clients; i++)
        {
            sd = client_socket[i];

            if (FD_ISSET( sd , &readfds))
            {
                //Check if it was for closing , and also read the
                //incoming message
                //int order_array_size = read( sd , buffer, 1024);

               char order_Array[60] = {0};
               int intOrderArray[10] = {0};
               int order = recv(sd, order_Array, 60, 0);
               process_order(order_Array, 60, intOrderArray);
               printf("%s\n", order_Array);
               printf("See your order: \n");

               /*for(int k = 0; k<10;k++)
               {
                 printf("%d\n", intOrderArray[k]);
               }*/

              // printf("%s\n", order_Array);
              /*printf("%c\n", order_Array[0]);
              printf("%c\n", order_Array[1]);
              printf("%c\n", order_Array[2]);
              printf("%c\n", order_Array[3]);
              printf("%c\n", order_Array[4]);
              printf("%c\n", order_Array[5]);
              printf("%c\n", order_Array[6]);
              printf("%c\n", order_Array[7]);*/

                if ((valread = read( sd , buffer, 1024)) == 0)
                {
                    //Somebody disconnected , get his details and print
                    getpeername(sd , (struct sockaddr*)&address , \
                        (socklen_t*)&addr_length);
                    printf("Host disconnected , ip %s , port %d \n" ,
                          inet_ntoa(address.sin_addr) , ntohs(address.sin_port));

                    //Close the socket and mark as 0 in list for reuse
                    close( sd );
                    client_socket[i] = 0;
                }

                //Echo back the message that came in
                else
                {
                  char *mes = "Got it";
                    //set the string terminating NULL byte on the end
                    //of the data read
                    buffer[valread] = '\0';
                    printf("Message from port(%d): %s\n",ntohs(address.sin_port),buffer);

                    //send(sd , buffer , strlen(buffer) , 0 );
                    send(sd , mes , strlen(mes) , 0 );
                }
            }
        }
    }

    return 0;
}

void readingFromFile(char *filename, char messageArray[SIZE][50])// reads from a file menu, the entire menu
{
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
   //char messageArray[SIZE][50] = {""};

    fp = fopen(filename, "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i=0;

    while ((read = getline(&line, &len, fp)) != -1) {
      strcpy(messageArray[i],line);
      i++;
    }

    fclose(fp);
    if (line)
        free(line);

}

void process_order(char or_array[],int size, int order[50])
{
  int next = 0;
  int inc = 0;
  for(int i=0; i<size; i++)
  {
    char buf1[4] = "0";
    char buf2[4] = {0};
    char buf3[4]={0};
    int ord=0;
    int amo=0;
    next = i+1;

        if(or_array[next]=='?' || or_array[next+1]=='?')
      //  if(strncmp(or_array[next],"?",1)==0 || strncmp((char)or_array[next+1],"?",1)==0 )
      {
          if(or_array[next]=='?')
          {
            buf2[0] = or_array[i];
            strcat(buf1,buf2);
            sscanf(buf1, "%d", &ord);
            order[inc] = ord;
            printf("%d\n", ord);
            printf("case one\n");
            i+=2;
          }

          if(or_array[next+1]=='?')
          {
            buf2[0] = or_array[i];
            buf3[0] = or_array[next];
            strcat(buf1, buf2);
            strcat(buf1,buf3);
            sscanf(buf1, "%d", &ord);
            order[inc] = ord;
            printf("%d\n", ord);
              printf("case two\n");
            i+=3;

            /*strcat(buf1,or_array[i]);
            strcat(buf1,or_array[next]);*/
          }
        }

        if(or_array[next]=='!' || or_array[next+1]=='!')
        {
          if(or_array[next]=='!')
          {
            buf2[0] = or_array[i];
            strcat(buf1,buf2);
            sscanf(buf1, "%d", &amo);
            order[inc] = amo;
            printf("%d\n", amo);
              printf("case three\n");
            i+=2;
          }
          if(or_array[next+1]=='!')
          {
            buf2[0] = or_array[i];
            buf3[0] = or_array[next];
            strcat(buf1,buf2);
            strcat(buf1,buf3);
            sscanf(buf1, "%d", &amo);
            order[inc] = amo;
            printf("%d\n", amo);
              printf("case four\n");
            i+=3;
            /*strcat(buf1,or_array[i]);
            strcat(buf1,or_array[next]);*/
          }


        }
  inc++;
  }

}
