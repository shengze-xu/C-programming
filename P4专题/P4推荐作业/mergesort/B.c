#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include <time.h>
int a[15000000];
int tmp[15000000];
#define array_length 150000//00
int num_thread[2];
int limit=2;
int flag=0;
void create_array(){
	srand((int)time(NULL));
	int i;
    for (i=0;i<array_length;i++) {
    	a[i] = rand();
	}
}
void merge_sort(int value[]);
void merge(int a[],int s,int f,int m,int tmp[]);
int main(){
	create_array();
	struct timeval tbegin, tend;
    gettimeofday(&tbegin, NULL);
	int range_1[2];
	int range_2[2];
	range_1[0]=0;
	range_1[1]=(array_length-1)/2;
	range_2[0]=(array_length-1)/2+1;
	range_2[1]=(array_length-1);
	puts("now its func merge sort!\n");
	pthread_t tid;
    int rc;
    rc=pthread_create(&tid, NULL, merge_sort, range_1);
    if(rc)printf("failed to create a new thread");
    rc=pthread_create(&tid, NULL, merge_sort, range_2);
    if(rc)printf("failed to create a new thread");
    pthread_join(tid, NULL);
   merge(a,0,array_length-1,(array_length-1)/2,tmp);
   gettimeofday(&tend, NULL);
   int i=array_length;
	printf("the number of the index is %d\n",i);
	printf("The running time is %d millisecond\n",(tend.tv_sec-tbegin.tv_sec)*1000+(tend.tv_usec - tbegin.tv_usec)/1000);
	return 0;
}
void merge_sort(int value[]){
	int s=value[0];
 	int f=value[1];
 	int m=s+(f-s)/2;
	if(f>s){//exit of the recurrsion
	int range_1[2];
	int range_2[2];
		range_1[0]=s;
		range_1[1]=m;
		range_2[0]=m+1;
		range_2[1]=f;//set the argues needed to recurrsion
    	merge_sort(range_1);
    	merge_sort(range_2);
	merge(a,s,f,m,tmp);
	}
}
void merge(int a[],int s,int f,int m,int tmp[])
 {
 	int cnt=0;
 	int p1=s,p2=m+1;
 	while(p1<=m&&p2<=f)
 	{
 		if(a[p1]<a[p2])
 		tmp[cnt++]=a[p1++];
 		else
 		tmp[cnt++]=a[p2++];
	 }
	 while(p1<=m)
	 {
	 	tmp[cnt++]=a[p1++];
	 }
	 while(p2<=f)
	 {
	 	tmp[cnt++]=a[p2++];
	 }
	 int i;
	 for(i=0;i<f-s+1;i++)
	 {
	 	a[s+i]=tmp[i];
	 }
 }
