//Michael Shen
//mjshen
//cs12b
//pa5

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Dictionary.h"
#include "Dictionary.c"

#define MAX_LEN 180
int main(int argc, char* argv[]){
	Dictionary F = newDictionary();
	char* A[] = {"1","2","3","4","5","6","7"};
	char* B[] = {"one","two","three","four","five","six","seven"};
	char* x;
	char* y;

	int i;
	for(i=0; i<7; i++){
		insert(F, A[i], B[i]);
	}
	printDictionary(stdout, F);

	for(i = 0; i<7; i++){
		x = A[i];
		y = lookup(F, x);
		printf("key=\"%s\" %s\"%s\"\n", x, (y==NULL?"not found ":"value="), y);	
	}

	//insert(F, "5", "eight");

	delete(F, "1");
	delete(F, "2");
	delete(F, "3");

	printDictionary(stdout, F);

	for(i = 0; i<7; i++){
		x = A[i];
		y = lookup(F,x);
		printf("key=\"%s\" %s\"%s\"\n", x, (y==NULL?"not found ":"value="), y);	
	}
	//delete(A, "1");
	printf("%d\n", size(F));
	printf("%s\n", (isEmpty(F)?"true":"false") );
	makeEmpty(F);
	printf("%s\n", (isEmpty(F)?"true":"false"));

	freeDictionary(&F);
	return(EXIT_SUCCESS);
}
