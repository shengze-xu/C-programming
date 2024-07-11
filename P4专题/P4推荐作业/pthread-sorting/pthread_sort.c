#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include "pthread_sort.h"

#define THREAD_NUMBER_GATE 256
#define QUICK_SORT_GATE 80000
#define MERGE_SORT_GATE 20000

#define min(x,y) ((x)<(y)?(x):(y))

static int cur_thread_number = 0;//�������е��߳��� 
static int max_thread_number = 7;//����߳��� 
static pthread_mutex_t cur_thread_number_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t quick_sort_mutex = PTHREAD_MUTEX_INITIALIZER;
static pthread_mutex_t merge_sort_mutex = PTHREAD_MUTEX_INITIALIZER;

sort_data_queue* sort_data_queue_create(void){
	sort_data_queue *queue = (sort_data_queue*)malloc(sizeof(sort_data_queue));
    queue->array.num = NULL; queue->array.start = 0; queue->array.end = 0;
    queue->next = NULL;
    return queue;
}

void sort_data_queue_push(sort_data_queue *queue, sort_data array){
	sort_data_queue *node = (sort_data_queue*)malloc(sizeof(sort_data_queue));
	node->array = array;
	node->next = queue->next;
	queue->next = node;
}

sort_data sort_data_queue_pop(sort_data_queue *queue){
	if(queue->next==NULL){
		sort_data err = {NULL, 0, 0};
		return err;
	}
	sort_data_queue *cur = queue;
	while(cur->next->next) cur = cur->next;
	sort_data copy = cur->next->array;
	free(cur->next);
	cur->next = NULL;
	return copy;
}

int set_max_thread_number(int num){
	if (num > 0 && num < THREAD_NUMBER_GATE){
		max_thread_number = num;
		return num;
	} else return -1;
}

void cur_thread_number_inc(){
	pthread_mutex_lock(&cur_thread_number_mutex);
	cur_thread_number++;
	pthread_mutex_unlock(&cur_thread_number_mutex);
}

void cur_thread_number_dec(){
	pthread_mutex_lock(&cur_thread_number_mutex);
	cur_thread_number--;
	pthread_mutex_unlock(&cur_thread_number_mutex);
}

/////////////////////////////////////////

int partition(int *a, int start, int end){
	int first = start, last = end;
	//printf("%d %d\n", first, last);
	if(first >= last) return -1;
	int key = a[first];
	while(first < last){
		while(first < last && a[last] >= key) last--;
		a[first] = a[last];
		while(first < last && a[first] <= key) first++;
		a[last] = a[first];
	}
	a[first] = key;
	return first;
}

void merge(int *a, int begin, int mid, int end){//mid��end��һ�ߣ�����end 
	int p1 = begin, p2 = mid;
    int *temp = (int*)malloc(sizeof(int) * (end - begin));
	for(int i = 0; i < end - begin; i++){
		if(p1 < mid && (p2 >= end || a[p1] < a[p2])){
			temp[i] = a[p1];
			p1++;
		} else {
			temp[i] = a[p2];
			p2++;
		}
	}
    for(int i = begin; i < end; i++) a[i] = temp[i - begin];
    free(temp); 
}

void* linear_single_thread_sort(void *arg){
	sort_data_with_sort_func *data = (sort_data_with_sort_func*)arg;
	data->sort_func(data->num, data->start, data->end);
	pthread_exit(NULL);
}

void linear_thread_sort(int *a, int start, int end, void(*sort_func)(int*, int, int)){
	pthread_t *thrnum = (pthread_t*)malloc(sizeof(pthread_t) * max_thread_number);
	sort_data_with_sort_func *data_part = (sort_data_with_sort_func*)malloc(sizeof(sort_data_with_sort_func) * max_thread_number);
	
	//������������ 
	int length = end - start + 1;//�ܳ��� 
	int part_length = length / max_thread_number + 1;//ÿ�ݵĳ��� 
	for(int i = 0; i < max_thread_number; i++){
		//�ָ�����
		data_part[i].num = a;
		data_part[i].start = min(start + i * part_length, end);
		if (i == max_thread_number) data_part[i].end = end;
		else data_part[i].end = min(start + (i+1) * part_length - 1, end);
		data_part[i].sort_func = sort_func;
		//�����߳� 
		pthread_create(&thrnum[i], NULL, linear_single_thread_sort, &data_part[i]);
	}
	
	//�ȴ������߳̽������ϲ� 
	for(int i = 0; i < max_thread_number; i++) pthread_join(thrnum[i], NULL);
	for(int i = 0; i < max_thread_number; i++){
		int _mid = min(start + i * part_length, end);
		int _end = min(start + (i+1) * part_length, end + 1);
		merge(a, start, _mid, _end); 
	}
	
	free(thrnum); free(data_part);
}

/////////////////////////////////////////

void bottom_up_merge_sort(int *a, int start, int end){//С������
	for(int i = 1; i < end - start + 1; i *= 2){
		for(int j = start; j <= end; j += i*2){
			merge(a, j, min(j + i, end + 1), min(j + i*2, end + 1));
		}
	}
}

void* single_thread_merge_sort(void *arg){
	//ȡ���������� 
	sort_data_queue *task_list = *(sort_data_queue**)arg;
	pthread_mutex_lock(&merge_sort_mutex);
	sort_data data = sort_data_queue_pop(task_list);
	pthread_mutex_unlock(&merge_sort_mutex);
	
	//ִ������������̫Сʱת���߳� 
	if(data.start <= MERGE_SORT_GATE){
		bottom_up_merge_sort(data.num, 0, data.end - 1);
	} else {
		merge(data.num, 0, data.start, data.end);
	}
	
	//�˳� 
	cur_thread_number_dec();
	pthread_exit(NULL);
}

void thread_merge_sort(int *a, int start, int end){
	int thread_count = 0;
	pthread_t thrnum;
	sort_data_queue *task_list = sort_data_queue_create();//����������� 
    
    for(int i = min(MERGE_SORT_GATE, (end - start) / 2 + 1); i < end - start + 1; i *= 2){
    	//д���������� 
    	for(int j = start; j <= end; j += i*2){
    		sort_data data = {a + j, min(j + i, end + 1) - j, min(j + i*2, end + 1) - j};
    		sort_data_queue_push(task_list, data);
		}
		//ѭ��ֱ����������������� 
		while(task_list->next || cur_thread_number){//������в��ջ������߳������� 
    		if(cur_thread_number < max_thread_number && task_list->next){
    			pthread_create( &thrnum, NULL, single_thread_merge_sort, &task_list );
    			cur_thread_number_inc(); 
				thread_count++;
			}
		}
	}
	
	free(task_list);
	printf("(total thread number = %d)\n", thread_count);
}

void linear_thread_bottom_up_merge_sort(int *a, int start, int end){
	linear_thread_sort(a, start, end, bottom_up_merge_sort);
}

/////////////////////////////////////////

void quick_sort(int *a, int start, int end){//С������ 
	int mid = partition(a, start, end);
	if (mid == -1) return;
	quick_sort(a, start, mid - 1);
	quick_sort(a, mid + 1, end);
}

void* single_thread_quick_sort(void *arg){
	//ȡ���������� 
	sort_data_queue *task_list = *(sort_data_queue**)arg;
	pthread_mutex_lock(&quick_sort_mutex);
	sort_data data = sort_data_queue_pop(task_list);
	pthread_mutex_unlock(&quick_sort_mutex);
	
	if(data.end - data.start < QUICK_SORT_GATE){//������̫Сת���߳� 
		quick_sort(data.num, data.start, data.end);
		cur_thread_number_dec();
		pthread_exit(NULL);
	}
	
	int mid = partition(data.num, data.start, data.end);//mid never equals -1
	sort_data left = data, right = data;
	left.end = mid - 1;
	right.start = mid + 1;
	
	//д���������� 
	pthread_mutex_lock(&quick_sort_mutex);
	if(mid > data.start + 1) sort_data_queue_push(task_list, left);
	if(mid < data.end - 1) sort_data_queue_push(task_list, right);
	pthread_mutex_unlock(&quick_sort_mutex);
	
	cur_thread_number_dec();
	pthread_exit(NULL);
}

void thread_quick_sort(int *a, int start, int end){
	int thread_count = 0;
	pthread_t thrnum;
	sort_data_queue *task_list = sort_data_queue_create();//�����������
	
	//д���ʼ���� 
	sort_data data = {a, start, end};
    sort_data_queue_push(task_list, data);
    
    //ѭ��ֱ����������������� 
	while(task_list->next || cur_thread_number){
    	if(cur_thread_number < max_thread_number && task_list->next){
    		pthread_create( &thrnum, NULL, single_thread_quick_sort, &task_list );
    		cur_thread_number_inc(); 
			thread_count++;
		}
	}
	
	free(task_list);
	printf("(total thread number = %d)\n", thread_count);
}

void linear_thread_quick_sort(int *a, int start, int end){
	linear_thread_sort(a, start, end, quick_sort);
}
