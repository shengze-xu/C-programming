#include "oldquick.h"
#include "anewquick.h"



void ordinary_quickmain(void){
	int *oqarr=(int*)malloc(sizeof(int)*NUM);
	createData(oqarr);
	struct timeval oqtbegin, oqtend;
    gettimeofday(&oqtbegin, NULL);
	commenQuickSort(oqarr,0,NUM-1);
	gettimeofday(&oqtend, NULL);
	printf("[ordinary-quick]The running time is %d microsecond\n",(oqtend.tv_usec - oqtbegin.tv_usec)); 
	
}







