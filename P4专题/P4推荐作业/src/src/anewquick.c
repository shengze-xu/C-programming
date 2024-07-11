#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "pthread.h"
#include "anewquick.h" 
 
int count=0;    
int maxcount=8;
int flag_quick=0;
int count_sum=0;

void commenQuickSort(int *arr,int left,int right){
	
	
	int t,i,j,temp;
	if(left > right){
		return ;
	}
	temp=arr[left];
	i=left;
	j=right;
	while(i!=j){
		while(arr[j] >= temp&&i<j)j--;
		while(arr[j]<=temp&&i<j)i++;
		if(i<j){
			t=arr[i];arr[i]=arr[j];arr[j]=t;
		}
	}
	arr[left]=arr[i];
	arr[i]=temp;
	commenQuickSort(arr,left,i-1);
	commenQuickSort(arr,i+1,right);

}
 
void* ThreadQuickSort(void* lpParam)   
{
    int i=((ThreadSortData *)lpParam)->i;    
    int j=((ThreadSortData *)lpParam)->j;
    int *num=((ThreadSortData *)lpParam)->p;

     
    int start=i;   
    int end=j;  
    int tp=rand()%(end-start);
    int key=num[i+tp]; 
   
     
    while(i<j)   
    {
        while(i<j && num[j]>=key)
        {
            j--;
        }
        num[i]=num[j];
         
        while(i<j && num[i]<=key)
        {
            i++;
        }
        num[j]=num[i];
    }
    num[i]=key;
     
    pthread_t hThread1;
    pthread_t hThread2;
    
    if (count == maxcount) {
        flag_quick = 1;
    }
     	ThreadSortData * pData1 = malloc(sizeof(ThreadSortData));
        pData1->i=start;
        pData1->j=i-1;
        pData1->p=num;
    if (count < maxcount) {
        count++; 
       	//count_sum++;
        pthread_create(&hThread1,NULL,ThreadQuickSort,pData1);
        pthread_join(hThread1, NULL); 
        pthread_exit(NULL);
        count--;
    }
    else {
    	
        commenQuickSort(num,start,i-1);
    }
    //2
     	ThreadSortData * pData2 = malloc(sizeof(ThreadSortData));
        pData2->i=i+1;
        pData2->j=end;
        pData2->p=num;
    if (count < maxcount) {
        count++; 
       //count_sum++;
        pthread_create(&hThread2,NULL,ThreadQuickSort,pData2);
        pthread_join(hThread2, NULL); 
        pthread_exit(NULL);
        count--;
    }
    else {
        commenQuickSort(num,i+1,end);
    }
    
    return NULL;
}


void pthread_quickmain()
{
    int *pqarr=malloc(sizeof(int)*NUM);
    srand(2) ;
    int temp=0;
    for(int i=0;i<NUM;i++)
    {
        pqarr[i]=rand();  
    }
    printf("\n"); 
    
    
    
    
//   for(int i=0;i<1000;i++){
//   	printf("%d ",pqarr[i]);
//   }
//     printf("HEREs\n"); 
     
    ThreadSortData *pData=malloc(sizeof(ThreadSortData));   
    pData->p=pqarr;
    pData->i=0;
    pData->j=NUM-1;
     
    pthread_mutex_init(&lock,NULL);
     
    pthread_t thread0;
    
    struct timeval tbegin, tend;
    gettimeofday(&tbegin, NULL);
    
    
	pthread_create(&thread0,NULL,ThreadQuickSort,pData);
    
    pthread_join(thread0, NULL); 

	gettimeofday(&tend, NULL);
    if (flag_quick == 1) {
       //printf("The number of thread that I use : %d\n", maxcount);     
    }
    //printf("[quick]The REAL number of thread that I use : %d\n",count);   
    if(check_result(pqarr)); 
    printf("Finish the thread_merge_sort successfully!\n");
//	printf("[quick]The summary number of thread that I use : %d\n",count_sum);  
	printf("[quick]The running time is %d microsecond\n",(tend.tv_usec - tbegin.tv_usec)); 
 
    free(pqarr) ;
}

