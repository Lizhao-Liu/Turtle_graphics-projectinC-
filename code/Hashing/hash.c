#include "hash.h"

library* library_init()
{
  library* a = (library*)ncalloc(1, sizeof(library));
  a->capacity = INITPOOLSIZE;
  a->v = (item*)ncalloc(a->capacity, sizeof(item));
  return a;
}


item* insert_item(char* name, double value, library* a)
{
  hash_index index;
  int placed=false;
  if(a==NULL){
    a = library_init();
  }
  index = hashcode(name, a->capacity);

  do{
    if(a->v[index].name==NULL){
      a->v[index].name = (char*)ncalloc(sizeof(char), strlen(name)+1);
      strcpy(a->v[index].name, name);
      a->v[index].value = value;
      a->size++;
      placed = true;
    }
    else if(strcmp(a->v[index].name, name)==0){
      a->v[index].value = value;
      a->size++;
      placed = true;
    }
    index++;
  }while(!placed);
  if(a->size >= WARNINGLINE * a->capacity){
    resize(a);
  }
  return &(a->v[index]);
}

double get_value(library* a, char* name)
{
  hash_index index = hashcode(name, a->capacity);
  int found = false;
  double value;
  if(a==NULL || a->v[index].name==NULL){
    on_error("cannot find the value of the item");
  }

  do{
    if(strcmp(a->v[index].name, name)==0){
      found = true;
      value = a->v[index].value;
    }
    index++;
  }while(!found && a->v[index].name!=NULL);
  if(!found){
    on_error("cannot find the value of the item");
  }
  return value;
}

void resize(library* a)
{
  item* oldpool = a->v;
  unsigned oldcapacity = a->capacity, i;
  a->capacity *= SCALE_FACTOR;
  a->v = (item*)ncalloc(a->capacity, sizeof(item));
  for(i=0; i<oldcapacity; i++){
    if(oldpool[i].name!=NULL){
      insert_item(oldpool[i].name, oldpool[i].value, a);
    }
  }
  free(oldpool);
}

bool free_library(library* a)
{
  if(a==NULL){
    return true;
  }
  free(a->v);
  free(a);
  return true;
}

hash_index hashcode(const void* key, unsigned int capacity)
{
   unsigned long hash = 5381;
   const char* ptr;
   for (ptr = (char*) key; *ptr != '\0'; ptr++){
       hash = ((hash << 5) + hash) + (*ptr);
   }
   return (hash_index) hash % capacity;
}
