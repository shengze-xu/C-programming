#include "oldmerge.h"
#include "anewquick.h"
void mergesort(int * array,int start,int end){
	if(start==end-1)return;
	int mid=(end+start)/2;
	mergesort(array,start,mid);
	mergesort(array,mid,end);
	int * temp=malloc(sizeof(int)*(end-start));
	int left_idx=start,right_idx=mid,i=0;
	while(left_idx<mid&&right_idx<end){
		if(array[left_idx]<array[right_idx]){
			temp[i++]=array[left_idx++];
		}else{
			temp[i++]=array[right_idx++];
		}
	}
	while(left_idx<mid){
		temp[i++]=array[left_idx++];
	}
	while(right_idx<end){
		temp[i++]=array[right_idx++];
	}
	for(int ii=0,idx=start;ii<end-start;idx++,ii++){
		array[idx]=temp[ii];
	}
	free(temp) ;
}
void ordinary_mergemain(void){
	int* omarr=(int*)malloc(sizeof(int)*NUM);
	createData(omarr);
	
	struct timeval omtbegin, omtend;
    gettimeofday(&omtbegin, NULL);
	mergesort(omarr,0,NUM-1);
	gettimeofday(&omtend, NULL);
	printf("[ordinary-merge]The running time is %d microsecond\n",(omtend.tv_usec - omtbegin.tv_usec)); 
	
	
	
}
