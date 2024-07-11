#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "acllib.h"
#include "function.h"
#include "callback.h" 

#define width 1500
#define height 300
#define theight 60
#define twidth 30

static int x;
static List list={NULL,NULL};
static int flag=1;


void KeyListener(int key,int event){
	if(event){
		switch(key){
			case 37:Left(&x);break;
			case 39:Right(&x,&list);break;
			case 8: Backspace(&x,&list);break;
			case 45:Insert(&flag);break;
			case 46:Delete(&x,&list);break;
			case 13:Enter(&x,&list);break;
	    }
	}
	paintCaret(x,flag);
}

void CharListener(char key){
	if(key!=8&&key!=13){
		int len=list_size(&list);
	    if(flag==1){
	    	if(x==0) list_insert(&list,key);
		    else if(0<x&&x<len){
		    	Node* p=(Node*)malloc(sizeof(Node));
		        Node* q=list_find(&list,x);
		        p->value=key;
		        p->next=q->next;
		        q->next=p;
			}
		    else list_append(&list,key);	
		}
		else{
			if(x==len) list_append(&list,key);
			else list_set(&list,x,key);
		}
	    showtext(&list); 
	    x++;
	}
	paintCaret(x,flag);
}

void MouseListener(int mx,int my,int button,int event){
	if(button==1&&event==0&&my<=theight){
		int len=list_size(&list);
		int i=mx/twidth;
		if(i<len){
			x=i;
		}
		else x=len;
	}
	paintCaret(x,flag);
}
