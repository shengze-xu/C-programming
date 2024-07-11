#include <stdio.h>
#include "row.h"
#include <stdlib.h>

List list_create(){
    List list;
    list.head=list.tail=NULL;
    return list;
}

void list_free(List *list){
    Node *p, *q;
    for(p=list->head;p;p=q){
        q=p->next;
        free(p);
    }
    list->head=NULL;
    list->tail=NULL;
}

void list_append(List *list, char v){
    Node* p=(Node*)malloc(sizeof(Node));
	p->value=v;
    p->next=NULL;
	if(list->head==NULL){
    	list->head=list->tail=p;
	}
    else{
		list->tail->next=p;
		list->tail=p;
    }
}

void list_insert(List *list, char v){
    Node* p=(Node*)malloc(sizeof(Node));
    p->value=v;
    p->next=list->head;
    list->head=p;
    if(list->tail==NULL)list->tail=p;
}

void list_getin(List* list,char v,int i){
    if(i==0)list_insert(list,v);
    else if(i==list_size(list))list_append(list,v);
    else{
        Node* r=list_find(list,i);
        Node* p=(Node*)malloc(sizeof(Node));
        p->value=v;
        p->next=r->next;
        r->next=p;
    }
}


void list_set(List *list, int index, char v){
    int i=0;
    Node *p=list->head;
    while(i!=index){
        i++;
        p=p->next;
    }
    p->value=v;
}

int list_get(List *list, int index){
    int i=0;
    Node *p=list->head;
    while(i!=index){
        i++;
        p=p->next;
    }
    return p->value;
}

int list_size(List *list){
    int cnt=0;
    Node* p=list->head;
 	for(p=list->head;p;p=p->next){
		cnt++;
	}
    return cnt;
}

Node* list_find(List *list, int index){
    int i=1;
    Node* p=list->head;
    while(i<index){
        i++;
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

void list_print(List* list){
    Node* p=list->head;
    for(;p;p=p->next){
        printf("%c",p->value);
    }
    printf("\n");
}
