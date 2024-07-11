#ifndef __ANEWMERGE_H__
#define __ANEWMERGE_H__


#include <stdio.h>
#include "pthread.h"
#include <stdlib.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include "anewquick.h"
#include "all.h"



#ifndef __NUM__X
#define __NUM__X
int a[NUM+5];
 
#endif
void merge(int left, int right);
void* ThreadMergeSort(void* arg);
void createData(int Garray[]);
int pthread_mergemain();

#endif
