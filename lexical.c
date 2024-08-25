#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Defining all magic number
#define QUOTE_SINGLE 39
#define QUOTE_DOUBLE 34

char * input_buffer(FILE *);


 int main(void){
  FILE *ftp;
  
  ftp = fopen("main.fi","r");

  if(ftp == NULL){
    printf("File open Error!\n");
    exit(EXIT_FAILURE);
  }
  char *buffer = input_buffer(ftp);

  printf("%s\n", buffer);
  return 0;
}

char* input_buffer(FILE *ftp){
  char *buffer;
  size_t buffer_cpacity = 4;
  size_t buffer_size = 0;

  buffer = malloc(sizeof(char) * buffer_cpacity);

  int ch;

  while((ch = fgetc(ftp)) != EOF){
    if(buffer_cpacity <= buffer_size){
      buffer_cpacity *= 2;
      buffer = realloc(buffer, sizeof(char) * buffer_cpacity);
    }

    if(ch == '\n') continue;

    if(ch == ';' || ch == ','|| ch == '(' || ch == ')' || ch == '{' || ch == '}' || ch == QUOTE_DOUBLE || ch == QUOTE_SINGLE || ch == '[' || ch == ']'){
      buffer[buffer_size++] = ' ';
      buffer[buffer_size++] = ch;
      buffer[buffer_size++] = ' ';
    }else{
      buffer[buffer_size++] = ch;
    }
  }

  buffer[buffer_size] = '\0';

  return buffer;
}


