#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "acllib.h"
#include "function.h"
#include "callback.h" 

#define width 1500
#define height 600
#define theight 60
#define twidth 30


void Left(int *px){
	if(*px>0)(*px)--;
} 

void Right(int *px,List *list){
	int len=list_size(list);
	if(*px<len)(*px)++;
}

void Backspace(int *px,List *list){
	if(*px>0){
		list_remove(list,*px);
		(*px)--;
	}
	showtext(list);
}

void Delete(int *px,List *list){
	int len=list_size(list);
	if(*px<len){
		list_remove(list,*px+1);
	}
	showtext(list);
}

void Insert(int *flag){
	if(*flag==1)*flag=0;
	else *flag=1;
}

void Enter(int *px,List *list){
	static int i=1;
	printf("µÚ%dÐÐ:",i++);
	Node *p=list->head;
	for(p=list->head;p;p=p->next){
		printf("%c",p->value);
	}
	printf("\n");
	list_free(list);
	*px=0;
	showtext(list);	
}

void showtext(List *list){
	beginPaint();
	setPenColor(WHITE);
	setBrushColor(WHITE);
	rectangle(0,0,width,height);	
	Node *p=list->head;
	int i=0;
	for(p=list->head;p;p=p->next,i++){
		char str[2];
	    setTextSize(theight);
		sprintf(str,"%c",p->value);
		paintText(i*twidth,0,str);
	}
	endPaint();
}

void paintCaret(int x,int flag){
	int caretwidth;
	if(flag) caretwidth=2;
	else caretwidth=twidth;
	setCaretSize(caretwidth,theight);
	setCaretPos(x*twidth,0);
	showCaret();
}


/*-------------list-------------*/


void list_free(List *list){
	Node*p=list->head;
	Node*q=NULL;
	for(p=list->head;p;p=q){
		q=p->next;
		free(p);
	}
	list->tail=NULL;
	list->head=NULL;
}

void list_append(List *list, char v){
	Node *p=(Node*)malloc(sizeof(Node));
	p->value=v;
	p->next=NULL;
	if(list->head){
		list->tail->next=p;
		list->tail=p;
	}
	else{
		list->head=list->tail=p;
	}
}

void list_insert(List *list, char v){
	Node *p=(Node*)malloc(sizeof(Node));
	p->value=v;
	p->next=list->head;
	list->head=p;
	if(list->tail==NULL)list->tail=p;
}

void list_set(List *list, int index, char v){
	int i=0;
	Node*p;
	for(p=list->head;p;p=p->next,i++){
		if(index==i){
			p->value=v;
		}
	}
}

int list_get(List *list, int index){
	Node *p;
	int i=0;
	for(p=list->head;p;p=p->next,i++){
		if(index==i){
		    return p->value; 
		}
	}
}

int list_size(List *list){
	int len=0;
	Node *p=list->head;
	while(p){
		len++;
		p=p->next;
	}
	return len;
}

Node* list_find(List *list, int index){
    int i=1;
    Node* p=list->head;
    for(i=1;i<index;i++){
    	p=p->next;
	}
    return p;
}

void list_remove(List *list, int index){
    Node* p=list_find(list,index);
    if(p==list->head){
        list->head=p->next;
    }
    else{
        Node* q=list->head;
        while(q->next!=p){
            q=q->next;
        }
        if(p==list->tail){
            list->tail=q;
		    q->next=NULL;
        }
        else{
            q->next=p->next;
        }
    }
	free(p);
}








