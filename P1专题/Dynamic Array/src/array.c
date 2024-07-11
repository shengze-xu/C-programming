#include <stdio.h>
#include <stdlib.h>
#include "array.h"

Array array_create(){
	Array array;
    array.size=BLOCK_SIZE;
	array.content=(int*)malloc(sizeof(int)*array.size);
	return array;
}
void array_free(Array* array){
	free(array->content);
	array->content=NULL;
	array->size=0;
}

int array_size(const Array *array){
	return array->size;
}

void array_inflate(Array *array){
	int *p=(int*)malloc(sizeof(int)*(array->size+BLOCK_SIZE));
	int i;
	for(i=0;i<array->size;i++){
		p[i]=array->content[i];
	}
	free(array->content);
	array->content=p;
	array->size+=BLOCK_SIZE;
}

int array_get(const Array *array, int index){
	return array->content[index];
}

void array_set(Array *array, int index, int value){
	array->content[index]=value;
}

Array array_clone(const Array *array){
	Array a;
	int index=0;
	a.size=array->size;
	a.content=(int*)malloc(a.size*sizeof(int));
	for(index=0;index<(array->size);index++){
		a.content[index]=array->content[index];
	}
	return a;
}
