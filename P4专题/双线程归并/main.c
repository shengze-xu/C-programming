#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
#include <math.h>
 
#define array_length 1000000

int a[20000000]; 

typedef struct{
	int first;
	int last;
	int length;
} MY_ARRAY;

void Create_array(){
	srand((int)time(NULL));
	int i;
    for(i=0;i<array_length;i++){
    	a[i]=rand();
//    	printf("%d  ",a[i]);
	}
//	printf("\n");
//	printf("\n");
}

void mySort(MY_ARRAY *array);
void mergeSort(int a[], int len, int start, int end);
void merge(int a[],int len,int left,int mid,int right);

int main(){
	int i;
	Create_array();
	
	struct timeval T1,T2;
	int deltaT;
	gettimeofday(&T1,NULL);
	
	int N=8;
	MY_ARRAY arr[N];
	for(i=0;i<N;i++){
		if(i==0){
			arr[i].first=array_length*(i)/N;
			arr[i].last=array_length*(i+1)/N-1;
		}else if(i<N-1){
			arr[i].first=arr[i-1].last+1;
			arr[i].last=arr[i].first+array_length/N;
		}else{
			arr[i].first=arr[i-1].last+1;
			arr[i].last=array_length-1;
		}	
		arr[i].length=arr[i].last-arr[i].first+1;
//		printf("%d %d\n",arr[i].first,arr[i].last);
	}
/*	arr1.first=0;
	arr1.last=(array_length-1)/2;
	arr1.length=(array_length-1)/2+1;
	arr2.first=(array_length-1)/2+1;
	arr2.last=(array_length-1);
	arr2.length=(array_length)/2;
	
	MY_ARRAY arr;
	arr.first=0;
	arr.last=array_length-1;
	arr.length=array_length; 
*/
	
	pthread_t tid;
	for(i=0;i<N;i++){
		pthread_create(&tid, NULL, (void *)mySort, (void *)&arr[i]);
	}
//	pthread_create(&tid, NULL, (void *)mySort, (void *)&arr);	
//	
	pthread_join(tid, NULL);
	
	merge(a,arr[1].last-arr[0].first+1,arr[0].first,arr[0].last,arr[1].last);
	merge(a,arr[3].last-arr[2].first+1,arr[2].first,arr[2].last,arr[3].last);
	merge(a,arr[5].last-arr[4].first+1,arr[4].first,arr[4].last,arr[5].last);
	merge(a,arr[7].last-arr[6].first+1,arr[6].first,arr[6].last,arr[7].last);
	
	merge(a,arr[3].last-arr[0].first+1,arr[0].first,arr[1].last,arr[3].last);
	merge(a,arr[7].last-arr[4].first+1,arr[4].first,arr[5].last,arr[7].last);
	merge(a,arr[7].last-arr[0].first+1,arr[0].first,arr[3].last,arr[7].last);
	
	merge(a,array_length,0,(array_length-1)/2,array_length-1);
	
	gettimeofday(&T2,NULL);
	deltaT=(T2.tv_sec-T1.tv_sec)*1000+(T2.tv_usec - T1.tv_usec)/1000;
//	for(i=0;i<array_length;i++){
//		printf("%d\n",a[i]);
//	}
	printf("\n");
	
	printf("数据总量为:%d\n",array_length);
	printf("线程数为:%d\n",N);
	printf("time is %d millisecond\n",deltaT);
	int uT= (T2.tv_sec-T1.tv_sec)*1000000+(T2.tv_usec - T1.tv_usec);
	printf("time is %d usecond\n",uT);
	return 0;
}

void mySort(MY_ARRAY *array){
	mergeSort(a,array->length,array->first,array->last);
}

void mergeSort(int a[], int len, int start, int end){
	if(start<end){
		int mid=(start+end)/2;
		mergeSort(a, mid-start+1, start, mid);
		mergeSort(a, end-mid, mid+1, end);
		merge(a, len, start, mid, end);
	}
}

void merge(int a[], int len, int start, int mid, int end){
	int* p = (int*)malloc(len*sizeof(int));
	int i, j, k = 0;
	i = start;
	j = mid+1;
	while(i<=mid && j<=end){
		p[k++] = a[i] > a[j] ? a[i++] : a[j++];
	}
	while(i<=mid){
		p[k++] = a[i++];
	}
	while(j<=end){
		p[k++] = a[j++];
	}
	for(i= 0; i< k; i++){
		a[start + i] = p[i];
	}
	free(p);
}

