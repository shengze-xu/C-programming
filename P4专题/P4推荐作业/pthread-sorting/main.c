#include <stdio.h>
#include <stdlib.h>
#include <windows.h> 
#include <pthread.h>
#include "pthread_sort.h" 

#pragma comment(lib,"x86/pthreadVC2.lib")

#define POW (20)
#define MAXNUM (1 << POW) 
#define TESTGROUP (6)
#define TESTNUM (200000)
#define ORDERLY 0

int main(int argc, char *argv[])  
{ 
	int time = GetTickCount();
	srand(time);
	set_max_thread_number(6);
	
	///////////////////////测试数据 
	
	int *num[2];
	for(int i = 0; i < 2; i++) num[i] = (int*)malloc(MAXNUM * sizeof(int));
#if ORDERLY
	for(int i = 0; i < MAXNUM; i++) num[1][i] = i;
#else
	for(int i = 0; i < MAXNUM; i++) num[1][i] = rand() * 1000 + rand();
#endif
	
	///////////////////////测试用例 
	
    int *test_point = (int*)malloc(TESTNUM * sizeof(int));//内容是待检验的数组位置 
    test_point[0] = 1; test_point[1] = MAXNUM - 2;//头和尾 
    for(int i = 2; i < TESTNUM; i++) {
    	test_point[i] = 0;
    	for(int j = 0; j < POW; j++) test_point[i] |= (rand()%2) * (1 << j);//0 ~ 2^POW之间的数字
    	test_point[i] = test_point[i] % (MAXNUM - 5) + 2;//防止越界
	}
	
	///////////////////////函数测试 
	
	void(*sort_func[])(int*, int, int) = {bottom_up_merge_sort, thread_merge_sort, linear_thread_bottom_up_merge_sort, quick_sort, thread_quick_sort, linear_thread_quick_sort};
	const char *sort_func_name[] = {"bottom_up_merge_sort", "thread_merge_sort", "linear_thread_bottom_up_merge_sort", "quick_sort", "thread_quick_sort", "linear_thread_quick_sort"};
	if (sizeof(sort_func)/sizeof(sort_func[0]) < TESTGROUP) return -1;
	
	for(int i = 0; i < TESTGROUP; i++){
		int mark = 0;
		for(int j = 0; j < MAXNUM; j++) num[0][j] = num[1][j];//恢复数据
		
		time = GetTickCount();
    	sort_func[i](num[0], 0, MAXNUM - 1);
    	time = GetTickCount() - time;
    	
    	for(int j = 0; j < TESTNUM; j++){
	    	int ind = test_point[j];
	    	if(num[0][ind] >= num[0][ind - 1] && num[0][ind] <= num[0][ind + 1]) mark++;
	    	//else printf("%d wrong\n", ind);
		}
	    printf("%s:\nmark = %d/%d, time = %dms\n", sort_func_name[i], mark, TESTNUM, time);
	}
    
    for(int i = 0; i < 2; i++) free(num[i]);
    free(test_point);
    return 0;
}  
