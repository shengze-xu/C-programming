#include <stdio.h>
#include <stdlib.h>
#include "linkedlist.h"

typedef struct _node{
	int value;
	struct _node *next;
}Node;

//typedef struct {
//    Node *head;
//    Node *tail;
//} List;

List list_create(){
    List list;
	list.head=NULL;
	list.tail=NULL;
	return list;
}

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

void list_append(List *list, int v){
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

void list_insert(List *list, int v){
	Node *p=(Node*)malloc(sizeof(Node));
	p->value=v;
	p->next=list->head;
	list->head=p;
}

void list_set(List *list, int index, int v){
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

int list_find(List *list, int v){
	int ret=-1,i=0;
	Node *p=list->head;
	for(p=list->head;p;p=p->next,i++){
		if(p->value==v){
			ret=i;
			break;
		}
	}
	return ret;
}


void list_remove(List *list, int v){
    Node *p=list->head,*q=NULL;
    for(p=list->head,q=NULL;p;q=p,p=p->next){
        if(p->value==v){
            if(q){
                if(p==list->tail){
                    list->tail=q;
                    list->tail->next=NULL;
                    p=NULL;
                    free(p);
                    break;
                }
				else if(p==list->head){
                    list->head=p->next;
                    p=NULL;
					free(p);
					break;
                }
                else{
                    q->next=p->next;
                    p=q->next;
                    free(p);
                    break;
                }
            }
			else{
                list->head=p->next;
                free(p);
                p=NULL;
                break;
            }
        }
    }
}


void list_iterate(List *list, void (*func)(int v)){
	Node *p=list->head;
	for(p=list->head;p;p=p->next){
		(func)(p->value);
	}
}


