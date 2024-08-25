#include "hash.h"

int main(void){
  int value = hash("firoz");
  printf("%u\n", value);

  return 0;
}



unsigned int hash(const char* key, ht_t *hash_table){
  if(key == NULL){
    printf("Error: hash.c(5:31) -> key can'nt be NULL!");
    exit(EXIT_FAILURE);
  }

  unsigned long int value = 0;
  size_t key_len = strlen(key);

  for(int i = 0; i < key_len; i++){
    value = (value * 37) + key[i];
  }

  value %= hash_table->capacity;
  return value;
}

ht_t * ht_create(void){
  ht_t *hash_table;

  hash_table = malloc(sizeof(ht_t) * 1);
  hash_table->capacity = INITIAL_CAPACITY;
  hash_table->size = 0;
  
  hash_table->entrys = malloc(sizeof(ht_entry) * hash_table->capacity)

}
