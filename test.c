//#define _GNU_SOURCE
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 8
int main(void)
{
  /*int NUMB = 8;
    FILE * fp;
    char * line = NULL;
    size_t len = 0;
    ssize_t read;
   char messageArray[SIZE][50] = {""};

    fp = fopen("menu", "r");
    if (fp == NULL)
        exit(EXIT_FAILURE);

    int i=0;

    while ((read = getline(&line, &len, fp)) != -1) {
      strcpy(messageArray[i],line);
      i++;
    }

    int n = i;
    for (int j = 0; j < n; j++) /* output each word read


    {
            printf ("%s", messageArray[j]);
    }
    fclose(fp);
    if (line)
        free(line);
    exit(EXIT_SUCCESS);*/

    char a[4]="0";
    char b[4]="0";
  //  char b = "6";
    int c=0;

    strcat(a,"5");
    strcat(b,"55");

    int i,j;
    sscanf(a, "%d", &i);
    sscanf(b, "%d", &j);

    printf("%d\n", i + j);
}
