#ifndef _ARRAY_H_
#define _ARRAY_H_ 

typedef struct {
    int *content;
    int size;
} Array;

Array array_create();
void array_free(Array* array);

int array_size(const Array *array);
void array_inflate(Array *array);

int array_get(const Array *array, int index);
void array_set(Array *array, int index, int value);

Array array_clone(const Array *array);

#endif
