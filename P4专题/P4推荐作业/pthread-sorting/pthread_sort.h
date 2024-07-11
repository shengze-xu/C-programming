#ifndef _PTHREAD_SORT_
#define _PTHREAD_SORT_

typedef struct {
	int *num;
	int start, end;
}sort_data;

typedef struct {
	int *num;
	int start, end;
	void(*sort_func)(int*, int, int);
}sort_data_with_sort_func;

typedef struct _sort_data_queue{
	sort_data array;
	struct _sort_data_queue* next;
}sort_data_queue;

sort_data_queue* sort_data_queue_create(void);
void sort_data_queue_push(sort_data_queue *queue, sort_data array);
sort_data sort_data_queue_pop(sort_data_queue *queue);

int set_max_thread_number(int num);
void cur_thread_number_inc(void);
void cur_thread_number_dec(void);

int partition(int *a, int start, int end);
void merge(int *a, int begin, int mid, int end);
void* linear_single_thread_sort(sort_data_with_sort_func *arg);
void linear_thread_sort(int *a, int start, int end, void(*sort_func)(int*, int, int));

void bottom_up_merge_sort(int *a, int start, int end);
void* single_thread_merge_sort(void *arg);
void thread_merge_sort(int *a, int start, int end);
void linear_thread_bottom_up_merge_sort(int *a, int start, int end);

void quick_sort(int *a, int start, int end);
void* single_thread_quick_sort(void *arg);
void thread_quick_sort(int *a, int start, int end);
void linear_thread_quick_sort(int *a, int start, int end);

#endif
