#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
int a[15000000];
int tmp[15000000];
#define array_length 2000000
int num_thread[2];
int limit=2;
int flag=0;
void create_array(){
	srand((int)time(NULL));
    for (int i=0;i<array_length;i++) {
    	a[i] = rand();
	}

}
void quick_sort(int value[]);
int partition(int value[]);
int main(){
	create_array();
	struct timeval tbegin, tend;
    int range[2];
	int range_1[2];
	int range_2[2];
	range[0]=0;
	range[1]=(array_length-1);
	puts("now its func quick sort!\n");
	 gettimeofday(&tbegin, NULL);
	int p=partition(range);
	range_1[0]=0;
	range_1[1]=p;
	range_2[0]=p+1;
	range_2[1]=array_length-1;
	pthread_t tid;
    int rc;
    rc=pthread_create(&tid, NULL, quick_sort, range_1);
    if(rc)printf("failed to create a new thread");
    rc=pthread_create(&tid, NULL, quick_sort, range_2);
    if(rc)printf("failed to create a new thread");
    pthread_join(tid, NULL);

   gettimeofday(&tend, NULL);
   int i=array_length;
	printf("the number of the index is %d\n",i);
	printf("The running time is %d millisecond\n",(tend.tv_sec-tbegin.tv_sec)*1000+(tend.tv_usec - tbegin.tv_usec)/1000);
	return 0;
}
void quick_sort(int value[]){
	int s=value[0];
 	int f=value[1];
	if(f>s){//exit of the recurrsion
	int p=partition(value);
	int range_1[2];
	int range_2[2];
		range_1[0]=s;
		range_1[1]=p;
		range_2[0]=p+1;
		range_2[1]=f;//set the argues needed to recurrsion
    	quick_sort(range_1);
    	quick_sort(range_2);
	}
}
int partition(int value[]){
	int left=value[0];
 	int right=value[1];
	int pivot=a[left+(right-left)/2];
	int cnt;
	int i=left-1;
	int j=right+1;
	while(i!=j){
		do{
			i++;
		} while(a[i]<pivot);
		do{
			j--;
		}while(a[j]>pivot);
		if(i>=j)return j;
		int temp=a[i];
		a[i]=a[j];
		a[j]=temp;
	}
	return -1;
}
