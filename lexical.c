#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void input_buffer(FILE *, char**);

int main(void){
  FILE* ftp;

  ftp = fopen("main.fi", "r");
  if(ftp == NULL){
    perror("FILE Not Open");
    exit(EXIT_FAILURE);
  }

  char *buffer;
  input_buffer(ftp,&buffer);
  
  for(int i = 0; i < strlen(buffer); i++){
    printf("%c",buffer[i]);
  }
  printf("\n");
  return 0;

}

void input_buffer(FILE *ftp, char **buffer){
  size_t buffer_size = 2;
  size_t index = 0;

  *buffer = malloc(sizeof(char) * buffer_size);
  
  char ch;
  while((ch = fgetc(ftp)) != EOF){
    if(index == buffer_size){
      buffer_size *= 2;
      *buffer = realloc(*buffer,sizeof(char) * buffer_size);
    }

    (*buffer)[index] = ch;
    index++;
  }
  (*buffer)[index] = '\0';
}
