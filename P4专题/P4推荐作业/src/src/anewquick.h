#ifndef __ANEWQUICK_H__
#define __ANEWQUICK_H__



#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pthread.h"
#include <sys/time.h>
#include "all.h"




void* ThreadQuickSort(void* lpParam);
void pthread_quickmain(void);
void commenQuickSort(int *arr,int left,int right); 
void createData(int Garray[]);



typedef struct{
    int *p; 
    int i;  
    int j;  
}ThreadSortData;
pthread_mutex_t lock;

#endif

