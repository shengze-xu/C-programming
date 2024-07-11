#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>

#define array_length 10000000	

int a[20000000]; 

typedef struct{
	int first;
	int last;
} MY_ARRAY;

void Create_array(){
	srand((int)time(NULL));
	int i;
    for(i=0;i<array_length;i++) {
    	a[i]=rand();
    	//printf("%d ",a[i]);
	}
	//printf("\n");
}

void mySort(MY_ARRAY *array);
int partition( int a[], int left, int right );
void quicksort( int a[], int left, int right );

int main(){
	int i;
	Create_array();
	
	struct timeval T1,T2;
	int deltaT;
	gettimeofday(&T1,NULL);
	
	int pivot = partition(a,0,array_length-1);
	int pivot1 = partition(a,0,pivot-1);
	int pivot2 = partition(a,pivot,array_length-1);
	
//	MY_ARRAY arr1,arr2;
//	arr1.first=0;
//	arr1.last=pivot;
//	arr2.first=pivot+1;
//	arr2.last=array_length-1;
	
	MY_ARRAY arr1,arr2,arr3,arr4;
	arr1.first=0;
	arr1.last=pivot1;
	arr2.first=pivot1+1;
	arr2.last=pivot;
	arr3.first=pivot+1;
	arr3.last=pivot2;
	arr4.first=pivot2+1;
	arr4.last=array_length-1;
	
/*	MY_ARRAY arr;
	arr.first=0;
	arr.last=array_length-1;
*/	
	pthread_t tid;
	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr1);
	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr2);
	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr3);
	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr4);
//	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr);	
//	
	pthread_join(tid, NULL);

//	quicksort(a,0,array_length); 
	gettimeofday(&T2,NULL);
	deltaT=(T2.tv_sec-T1.tv_sec)*1000+(T2.tv_usec - T1.tv_usec)/1000;
	
//	for(i=0;i<array_length;i++){
//		printf("%d\n",a[i]);
//	}
//	printf("\n");

	printf("time is %d millisecond\n",deltaT);
	int uT= (T2.tv_sec-T1.tv_sec)*1000000+(T2.tv_usec - T1.tv_usec);
	printf("time is %d usecond\n",uT);
	return 0;
}

void mySort(MY_ARRAY *array){
	quicksort(a,array->first,array->last);
}

void quicksort( int arr[], int left, int right ){
	if ( left < right ) {
        int p = partition(arr, left, right);
        quicksort(arr, left, p);
        quicksort(arr, p+1, right);
    }
}

int partition( int arr[], int left, int right ){
    int i=left,j=right;
    int p=arr[(left+right)/2];
    while(i<=j){
        while(arr[i]<p){
            i++;
        }
        while(arr[j]>p){
            j--;
        }
        if(i<=j){
            int t=arr[i];
            arr[i]=arr[j];
            arr[j]=t;
            i++;
            j--;
        }
    }
    return i-1;
}
