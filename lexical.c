#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <string.h>



const char* TokenType[] = {
  "KEYWORD",
  "IDENTIFIER",
  "VARIABLE",
  "SEPARATOR",
  "OPERATOR",
  "LITERAL",
};

typedef struct Token{
  int type;
  char *value;
}Token;

typedef struct TokensList{
  Token *token;
  int size;
  int capacity;
}TokensList;


char * input_buffer(FILE *,size_t *);
TokensList * token_generate(char* buffer, size_t len);
void substr(char *destination, const char *source, int start, int end);
void set_token(Token *token, const char *value);
int is_digit(const char *);



int main(void){

  FILE* ftp;

  ftp = fopen("main.fi", "r");
  if(ftp == NULL){
    perror("FILE Not Open");
    exit(EXIT_FAILURE);
  }

  size_t len;

  char *buffer = input_buffer(ftp,&len);
  
  for(int i = 0; i < strlen(buffer); i++){
    printf("%c",buffer[i]);
  }
  printf("\n");
  fclose(ftp);
  size_t token_len;
  TokensList *list = token_generate(buffer,len);
  for(int i = 0; i < list->size; i++){
    printf("(%s, %s)\n", TokenType[list->token[i].type],list->token[i].value);
  }
  free(buffer);
  for(int i = 0; i < list->size; i++){
    free(list->token[i].value);
  }
  free(list->token);
  free(list);
  return 0;

}

char* input_buffer(FILE *ftp, size_t *len){
  char *buffer;
  size_t buffer_size = 2;
  size_t index = 0;

  buffer = malloc(sizeof(char) * buffer_size);

  char ch;
  while((ch = fgetc(ftp)) != EOF){
    if(index == buffer_size){
      buffer_size *= 2;
      buffer = realloc(buffer,sizeof(char) * buffer_size);
    }

    buffer[index] = ch;
    index++;
  }
  buffer[index] = '\0';
  *len = index;
  printf("1\n");
  return buffer;
}

TokensList * token_generate(char* buffer, size_t len){
  TokensList *list = malloc(sizeof(TokensList));
  list->capacity = 2;
  list->size = 0;
  list->token = malloc(sizeof(Token)*list->capacity);
  int start = 0;
  int end = 0;
  int i = 0;
  int token_len;

  while(i < len){
    if(list->size == list->capacity){
      list->capacity *= 2;
      list->token = realloc(list->token, sizeof(Token) * list->capacity);
    }

    if(buffer[end] == ' ' || buffer[end] == '\n'){
      token_len = end - start + 1;
      char *token = malloc(sizeof(char) * token_len);
      substr(token,buffer,start,end);
      start = end + 1;
      set_token(&list->token[list->size],token);
      list->size++;
    }else if(buffer[end] == ';'){
      token_len = end - start;
      char *token = malloc(sizeof(char) * token_len);
      substr(token,buffer,start,end);
      start = end + 1;
      set_token(&list->token[list->size],token);
      list->size++;
    }
    i++;
    end++;
  }
  return list;
}

void substr(char *destination, const char *source, int start, int end){
  int index = 0;
  for(int i = start; i < end; i++){
    destination[index++] = source[i];
  }
  destination[index] = '\0';
}

void set_token(Token *token, const char *value){
  int len = strlen(value)+1;
  if(strcmp(value,"int") == 0){
    token->type = 0;
  }else if(strcmp(value,"void") == 0 || strcmp(value,"return") == 0){
    token->type = 0;
  }else if(is_digit(value)){
    token->type = 5;
  }else if(strcmp(value,"=") == 0 || strcmp(value,"+") == 0){
    token->type = 4;
  }else{
    token->type = 1;
  }
  token->value = malloc(sizeof(char) * len);
  strcpy(token->value,value);

}

int is_digit(const char *value){
  for(int i = 0; i < strlen(value); i++){
    if(!isdigit(value[i])){
      return 0;
    }
  }
  return 1;
}
