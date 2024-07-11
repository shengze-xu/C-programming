#include<stdio.h>
#include<stdlib.h>
#include"acllib.h"
#define TEXTSIZE 40
#define CARETWIDTH 25
#define CARETHEIGHT 40
#define HEIGHT 100
#define WIDTH 1000
#define MAX 1000

typedef struct _node{
	char s[2];
	struct _node*prev;
	struct _node*next;
}Node;
typedef struct {
	Node*head;
	Node*tail;
}List;
List list = {NULL,NULL};
Node*ptr = NULL;

void AppendTail(List*list,char a);
void InsertNode(List*list,char a);
void PrintText(int x,int y,Node*ptr);
int FollowingSize(Node*ptr);
int ischar(int key);
char convert(int key);
void keyListener(int key,int event);
void timerListener(int id);

int Setup()
{
	initConsole();
    initWindow("TextEditor",DEFAULT,DEFAULT,WIDTH,HEIGHT);
    registerKeyboardEvent(keyListener);
        setCaretSize(1,CARETHEIGHT);
        setCaretPos(0,0);
    registerTimerEvent(timerListener);
        startTimer(0,500);
    return 0;
}

void AppendTail(List*list,char a)
{
	Node*n = (Node*)malloc(sizeof(Node));
	n->s[0] = a;
	n->s[1] = '\0';
	n->next = NULL;
	ptr = n;
	n->prev = list->tail;
	if(list->head==NULL){
		list->head = list->tail = n;
	}
	else{
		list->tail->next = n;
		list->tail = n;
	}
}
void InsertNode(List*list,char a)
{
	Node*n = (Node*)malloc(sizeof(Node));
	n->s[0] = a;
	n->s[1] = '\0';
	n->next = ptr;
	n->prev = ptr->prev;
	if(ptr->prev==NULL);
	else ptr->prev->next = n;
	ptr->prev = n;
}

void PrintText(int x,int y,Node*ptr)//打印出光标后面的所有字符
{
	Node*p;
	int k=0;
	beginPaint();
	for(p=ptr; p; p=p->next){
		paintText(x+k*CARETWIDTH,y,p->s);
		k++;
	}
	endPaint();
}

int FollowingSize(Node*ptr)
{
	Node*p;
	int count=0;
	for(p=ptr; p; p=p->next){
		count++;
	}
	return count;
}

int ischar(int key)
{
	int check = 0;
	if(key>='A' && key<='Z')check=1;
	else if(key>='0' && key<='9')check=3;
	else{
		switch(key){
			case 32:check=3;break;
			case 187:check=2;break;
			case 189:check=2;break;
			case 219:check=2;break;
			case 220:check=2;break;
			case 221:check=2;break;
			case 186:check=2;break;
			case 222:check=2;break;
			case 188:check=2;break;
			case 190:check=2;break;
			case 191:check=2;break;
			case 192:check=2;break;
			default:break;
		}
	}
	return check;
}

char convert(int key)
{
	int ret=0;
	switch(key){
		case 187:ret=61;break;
		case 189:ret=45;break;
		case 219:ret=91;break;
		case 220:ret=92;break;
		case 221:ret=93;break;
		case 186:ret=59;break;
		case 222:ret=39;break;
		case 188:ret=44;break;
		case 190:ret=46;break;
		case 191:ret=47;break;
		case 192:ret=96;break;
		default:break;
	}
	return ret;
}

void keyListener(int key,int event)
{
    static int x=0,y=0;
    char c[2];
    static int middle = 0;
    static int shift = 0;
    static int Caps = 32;//Capslock
    static int Caret = 1;//Width of the Caret
    	printf("key = %d,  event = %d.\n",key,event);//debug usage.
	int k = ischar(key);
    if(k && event==0){
		c[1]='\0';
		if(k==2)key = convert(key);
        else if(k==1)key += Caps;//大小写状态.
        if(shift){
        	if(k==3){
        		if(key==32);
        		else{
        			switch(key){
        				case 48:key=41;break;
        				case 49:key=33;break;
        				case 50:key=64;break;
        				case 51:key=35;break;
        				case 52:key=36;break;
        				case 53:key=37;break;
        				case 54:key=94;break;
        				case 55:key=38;break;
        				case 56:key=42;break;
        				case 57:key=40;break;
					}
				}
			}
			else if(k==1){
				if(Caps==32)key-=Caps;
				else key+=32;
			}
			else{
        	switch(key){
				case 61:key=43;break;
				case 45:key=95;break;
				case 91:key=123;break;
				case 92:key=124;break;
				case 93:key=125;break;
				case 59:key=58;break;
				case 39:key=34;break;
				case 44:key=60;break;
				case 46:key=62;break;
				case 47:key=63;break;
				case 96:key=126;break;
				default:break;
			}
			}
		}
        c[0]=key;
        
        if(middle==1 && Caret==CARETWIDTH){//光标插入状态 
        	beginPaint();
        	setTextSize(TEXTSIZE);
        	paintText(x,y,c);
        	endPaint();
        	(ptr->s)[0] = c[0];
        	ptr=ptr->next;
        	if(ptr==NULL)middle=0;
		}
        else{
        	if(ptr==NULL);
        	else PrintText(x+CARETWIDTH,y,ptr);
        
      		if(middle==0)AppendTail(&list,c[0]);
        	else InsertNode(&list,c[0]);
        
        	beginPaint();
        	setTextSize(TEXTSIZE);
        	paintText(x,y,c);
        	endPaint();
        	if(middle==0&&ptr)ptr = ptr->next;
    	}
        	x+=CARETWIDTH;
        	setCaretPos(x,y);//x has changed.
    }
    else if(key==16){
    	if(event==0)shift=1;
    	else shift = 0;
	}
    else if(key==8 && event==0 && x!=0){//Backspace 
    	if(x==0);
    	else{
    		if(ptr==NULL){
    			list.tail = list.tail->prev;
    			if(list.tail)list.tail->next = NULL;
    			else list.head = NULL;
			}
    		else{
				if(ptr->prev->prev==NULL){
    			ptr->prev = NULL;
    			list.head = ptr;
				}
    			else{
    				ptr->prev->prev->next = ptr;
		    		ptr->prev = ptr->prev->prev;	
				}
			}
			x-=CARETWIDTH;
			setCaretPos(x,y);
			beginPaint();
			setPenColor(WHITE);
			setBrushColor(WHITE);
			rectangle(x,0,x+CARETWIDTH*(FollowingSize(ptr)+1),CARETHEIGHT);
			endPaint();
			PrintText(x,y,ptr);	
		}
	}
	else if(key==20 && event==0){//Capslock
		if(Caps==32)Caps=0;
		else Caps=32;
	}
	else if(key==46 && event==0){//Delete
		beginPaint();
		setPenColor(WHITE);
		setBrushColor(WHITE);
		rectangle(x,0,x+CARETWIDTH*(FollowingSize(ptr)+1),CARETHEIGHT);
		// paintText(x,y,++p);
		endPaint();
		if(ptr==NULL);
		else{
			ptr = ptr->next;//change ptr!!! 
			PrintText(x,y,ptr);
			if(ptr==NULL){
				middle = 0;
				list.tail = list.tail->prev;
    			if(list.tail)list.tail->next = NULL;
    			else list.head = NULL;
			}
			else{
				if(ptr->prev->prev==NULL){
    			ptr->prev = NULL;
    			list.head = ptr;
				}
    			else{
    				ptr->prev->prev->next = ptr;
		    		ptr->prev = ptr->prev->prev;	
				}
			}
		}
	}
	else if(key==45 && event==0){//Insert 
		if(Caret==1){
			setCaretSize(CARETWIDTH,CARETHEIGHT);
			Caret = CARETWIDTH;
			 showCaret();
		}
		else {
			setCaretSize(1,TEXTSIZE);
			Caret = 1;
			 showCaret();
		}
	}
	else if(key==37 && event==0){//left
		if(x==0);
		else{
			middle = 1;
			x-=CARETWIDTH;
			if(ptr==NULL)ptr = list.tail;
			else ptr = ptr->prev;
			setCaretPos(x,y);
		}
	}
	else if(key==39 && event==0){//right
		if(ptr==NULL)middle = 0;
		else{
			x+=CARETWIDTH;
			ptr = ptr->next;
			if(ptr==NULL)middle = 0;
			setCaretPos(x,y);
		}
	}
}

void timerListener(int id) //做光标闪烁
{
    static int count = 1;
    beginPaint();
    if(count%2)showCaret();
    else hideCaret();
    endPaint();
    count++;
}
