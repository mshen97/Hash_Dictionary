//-----------------------------------------------------------------------------
// Michael Shen
//mjshen
//cs12b
//pa5
//Dictionary.c
//-----------------------------------------------------------------------------

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "Dictionary.h"

#define MAX_LEN 180

const int tableSize = 101;

//rotate_left()
unsigned int rotate_left(unsigned int value, int shift){
   int sizeInBits = 8 * sizeof(unsigned int);
   shift = shift & (sizeInBits - 1);
   if( shift == 0 )
      return value;
   return (value << shift) | (value >> (sizeInBits - shift));
}

//pre_hash()
unsigned int pre_hash(char* input){
   unsigned int result = 0xBAE86554;
   while(*input){
      result ^= *input++;
      result = rotate_left(result, 5);
   }
   return result;
}

//hash()
int hash(char* key){
   return pre_hash(key)%tableSize;
}

typedef struct NodeObj{
   char* key;
   char* value;
   struct NodeObj* next; 
} NodeObj;

typedef NodeObj* Node;

typedef struct DictionaryObj{
   Node *table;
   Node head, tail;
   int numItems;
} DictionaryObj;

Node newNode(char* k, char* v) {
   Node N = malloc(sizeof(NodeObj));
   assert(N!=NULL);
   N->key = k;
   N->value = v;
   N->next =NULL;
   return(N);
}

void freeNode(Node* pN){
   if( pN!=NULL && *pN!=NULL ){
      free(*pN);
      *pN = NULL;
   }
}

Dictionary newDictionary(void){
   Dictionary D = malloc(sizeof(DictionaryObj));
   assert(D!=NULL);
   D->table = calloc(tableSize, sizeof(Node));
   assert(D->table != NULL);
   D->numItems = 0;
   return D;
}

void freeDictionary(Dictionary* pD){
   if( pD!=NULL && *pD!=NULL ){
      makeEmpty(*pD);
      free((*pD)->table);
      free(*pD);
      *pD = NULL;
   }
}

Node findKey(Dictionary D, char* k){
   Node M;
   M = D->table[hash(k)];
   while(M != NULL){
      if( strcmp(M->key, k) == 0 )
         break;
      M = M->next;
   }
   return M;
}

int isEmpty(Dictionary D){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling isEmpty() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(D->numItems>0) return 0;
   return 1;
}

int size(Dictionary D){
   return (D->numItems);
}

char* lookup(Dictionary D, char* k){
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling lookup() on NULL Dictionary reference\n");
      exit(EXIT_FAILURE);
   }
   if(findKey(D,k) == NULL)
      return NULL;
   else
      return findKey(D,k)->value;
}

void insert(Dictionary D, char* k, char* v){
   Node M;
   int n = hash(k);
   if(D == NULL){
      fprintf(stderr, "cannot call insert on a NULL Dictionary\n");
      exit(EXIT_FAILURE);
   }
   else if( findKey(D,k) != NULL ){
      fprintf(stderr, "pre-existing key already exists. cannot call insert");
      exit(EXIT_FAILURE);
   }
   else if( D->table[n] == NULL ){
      D->table[n] = newNode(k,v);
      D->numItems++;
   }
   else{
      M = newNode(k,v);
      M->next = D->table[n];
      D->table[n] = M;
      D->numItems++;
   }
}

void delete(Dictionary D, char* k){
   Node A;
   Node B;
   if( findKey(D,k) == NULL ){
      fprintf(stderr, "cannot delete non-existent key\n");
      exit(EXIT_FAILURE);
   }
   A = findKey(D,k);
   if(A == D->table[hash(k)] && A->next == NULL){
      A = NULL;
      freeNode(&A);
   }
   else if(A == D->table[hash(k)]){
      D->table[hash(k)] = A->next;
      A = NULL;
      freeNode(&A);
   }
   else{
      B = D->table[hash(k)];
      while(B->next != A)
         B = B->next;
      B->next = A->next;
      freeNode(&A);
   }
   D->numItems--;
}

void makeEmpty(Dictionary D){
   int i = 0;
   while(i < tableSize){
      while(D->table[i] != NULL){
         Node M;
         M = D->table[i];
         D->table[i] = M->next;
         freeNode(&M);
         M = NULL;
      }
      i++;
   }
   D->numItems = 0;
}

void printDictionary(FILE* out, Dictionary D){
   Node N;
   if( D==NULL ){
      fprintf(stderr, 
         "Dictionary Error: calling printDictionary() on NULL Dictionary Reference\n");
      exit(EXIT_FAILURE);
   }
   for( int i = 0; i < tableSize; i++ ){
      N = D->table[i];
      while( N != NULL ){
         fprintf(out, "%s %s \n", N->key, N->value);
         N = N->next;
      }
   }  
}

# Hash_DIctionary
