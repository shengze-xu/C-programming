#include <stdio.h>
#include <stdlib.h>
#include "pthread.h"
#include "anewquick.h"
#include "anewmerge.h"
#include "oldquick.h"
#include "oldmerge.h"

//RAND_MAX 0x7fff

void createData(int Garray[]){
    srand(2) ;
    int temp=0;
    for(int i=0;i<NUM;i++)
    {	
    	Garray[i]=rand(); 
    }
     printf("\n");  
}

int check_result(int array[]){
	int fg=1;
	for(int i=0;i<NUM-1;i++){
		if(array[i]>array[i+1]){
			fg=0;
		}
	}
	return fg;
}

int main(){
	
	printf("NUM=%d\n",NUM);
	printf("Environment:Intel i5-8265u\nNumber of cores: 4\nNumber of threads: 8\n");
	
	ordinary_mergemain();
	ordinary_quickmain();
	pthread_mergemain();
	pthread_quickmain();
	
    return 0;
    
}
