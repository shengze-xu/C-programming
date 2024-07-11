#include "anewmerge.h"
#include<time.h>

 int num_thread  = 0;
 int max_threadnum = 8;
 int flag = 0;
 int allthread=0;
// clock_t start,stop;
 
void merge(int left, int right){
    int mid = (left + right)/2;
    int size1 = mid - left + 1;
    int size2 = right - mid;
    int t1[size1];
    int t2[size2];

    memcpy(t1, a+left, sizeof(int) * (mid-left+1));
    memcpy(t2, a+mid+1, sizeof(int) * (right-mid));

    int i = 0, j = 0;
    int k = left;
    while (i < size1 && j < size2) {
        if (t1[i] <= t2[j]) {
            a[k] = t1[i];
            i++;
        }
        else {
            a[k] = t2[j];
            j++;
        }
        k++;
    }
    while (i < size1) {
        a[k] = t1[i];
        k++;
        i++;
    }
    while (j < size2) {
        a[k] = t2[j];
        j++;
        k++;
    }
}

void commenMergeSort(int * array,int start,int end){
	if(start==end-1)return;
	int mid=(end+start)/2;
	commenMergeSort(array,start,mid);
	commenMergeSort(array,mid,end);
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

void* ThreadMergeSort(void* arg){
	allthread++;
	//printf("thread:%d\n",allthread);

    int *argu = (int*)arg;
    int left = argu[0];
    int right = argu[1];

    int mid = (left + right)/2;
    int arg1[2];
    int arg2[2];

    arg1[0] = left;
    arg1[1] = mid;

    arg2[0] = mid + 1;
    arg2[1] = right;

    if (left >= right) {
        return NULL;
    }

    pthread_t t2;
    pthread_t t1;

    if (num_thread  == max_threadnum) {
        flag = 1;
    }
    
    if (num_thread  <= max_threadnum) {
        num_thread  += 1; 
        pthread_create(&t1, NULL, ThreadMergeSort, arg1);
        pthread_join(t1, NULL); 
        pthread_exit(NULL);
        num_thread  -= 1;
    }
    else {
    	commenMergeSort(a,arg1[0],arg1[1]);
    }
    
    if (num_thread  <= max_threadnum) {
        num_thread  += 1;
        pthread_create(&t2, NULL, ThreadMergeSort, arg2); 
        pthread_join(t2, NULL);
        pthread_exit(NULL);
        num_thread  -= 1;
    }
    else {
    	commenMergeSort(a,arg2[0],arg2[1]);
    }

//	pthread_create(&t1, NULL, ThreadMergeSort, arg1);
//    pthread_create(&t2, NULL, ThreadMergeSort, arg2);
//	pthread_join(t1, NULL);
//    pthread_join(t2, NULL);

    merge(left, right);
    pthread_exit(0);
    return NULL;
}



int pthread_mergemain(){
    createData(a);
    
    
//    struct timeval mtbegin, mtend;
//    gettimeofday(&mtbegin, NULL);
//	printf("%d\n",mtbegin.tv_usec) ;
//	time_t then=time(0);
//	start=clock();
    int arg[2];
    arg[0] = 0;
    arg[1] =NUM;

    pthread_t  thread_0;
    num_thread = 1;
    
    struct timeval mtbegin, mtend;
    gettimeofday(&mtbegin, NULL);
//	printf("%d\n",mtbegin.tv_usec) ;
    pthread_create(&thread_0, NULL, ThreadMergeSort, arg);
    pthread_join(thread_0, NULL);
    
    
//    stop=clock();
//    printf("%f\n",(double)(stop-start)*1000);
//    for(int iu=0;iu<1000;iu++)printf("%d ",iu);
    gettimeofday(&mtend, NULL);
//    	printf("%d\n",mtend.tv_usec) ;

	commenMergeSort(a,arg[0],arg[1]);
	if(check_result(a)){
		printf("Finish the thread_merge_sort successfully!\n");
	}else printf("WRONG\n");
	
    if (flag == 1) {
       printf("The number of thread that I use : %d\n", max_threadnum);     
    }
    
//    printf("[merge]The REAL number of thread that I use : %d\n", num_thread );
	int mytemp=(mtend.tv_usec - mtbegin.tv_usec);
    printf("[merge]The running time is %d microsecond\n",(mytemp));
//	printf("%llu\n",time(0)-then);

    return 0;
}

