#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define INITIAL_CAPACITY 10

typedef struct ht_entry {
  char *type;
  char *value;
}ht_entry;


typedef struct ht_t{
  ht_entry *entrys;
  int capacity;
  int size;
}ht_t;



unsigned int hash(const char*);
