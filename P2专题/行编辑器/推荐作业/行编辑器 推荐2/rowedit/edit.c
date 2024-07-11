#include <stdio.h>
#include <stdlib.h>
#include "acllib.h"
#include "row.h"
#include "edit.h"

#define WinWidth 1200 
#define WinHeight 100 
#define charsize 100 
#define maxn 15
#define delta 51

void LEFT(int *pi){
	if(*pi>0)(*pi)--;
}

void RIGHT(List *list,int *pi){
	if(*pi<list_size(list))(*pi)++;
}

void ENTER(List* list,int *pi){
	list_print(list);
	list_free(list);
	*pi=0;
	print(list);	
}

void BACKSPACE(List *list,int *pi){
	if(*pi>0){
		list_remove(list,*pi);
		LEFT(pi);
	}
	if(list->head==NULL)list->tail=NULL;
	print(list);
}

void INSERT(int* pcaretwid,int i){	
	if(*pcaretwid==3){
		*pcaretwid=51;
//		printf("caretwid=%d\n",*pcaretwid);
	}
	else *pcaretwid=3;
}

void deletekey(List* list,int *pi){
	if(*pi<list_size(list))list_remove(list,*pi+1);
	if(list->head==NULL)list->tail=NULL;
	print(list);
}

void HOME(int *pi){
	*pi=0;
}

void END(List* list,int *pi){
	*pi=list_size(list);
}

void print(List* list){	
	beginPaint();
	
	setPenColor(EMPTY);
	setBrushColor(WHITE);
	rectangle(0,0,WinWidth,WinHeight);
	
	Node* p=list->head;
	char str[2];
	int i=0;
	
	for(;p;p=p->next){
		sprintf(str,"%c",p->value);
		paintText(i*delta,0,str);
		i++;
	}
	
	endPaint();
}

void putCaret(int i){
	setCaretPos(i*delta,0);
}






