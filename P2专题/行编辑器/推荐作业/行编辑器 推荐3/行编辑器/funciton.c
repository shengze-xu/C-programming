#include "function.h"
#include <stdio.h>
#include "acllib.h"
#include <string.h>

static char str[1000];
static int x=3;
static char* p=str;
static int ins=0;
static int s=1;

void KeyListener(int key,int event){
	char* p1;
    if(key==13&&event==1){
        printf("��%d�У�%s\n",s,str);s++;
		beginPaint();
		rectangle(0,0,600,20);
	    setCaretPos(0,0);
	    showCaret();
		endPaint();	
		x=3;
		memset( str,0,sizeof(str) );p=str;
	}
	if(key==8&&event==1){
		p1=p-1;
		while(*p1!=0){
			*p1=*(p1+1);
			p1++;
		}
		beginPaint();
		rectangle(x-11,0,600,20);
	    setCaretPos(x-11,0);
	    showCaret();
	    paintText(x-11,0,str+(x/11-1));
		endPaint();	
		x-=11;
		p-=1;
	}
	if(key==46&&event==1){
		p1=p;
		while(*p1!=0){
			*p1=*(p1+1);
			p1++;
		}
		beginPaint();
		rectangle(x,0,600,20);
	    setCaretPos(x,0);
	    showCaret();
	    paintText(x,0,str+(x/11));
		endPaint();
	}
	if(key==45&&event==1){
		ins=!ins;
		if(ins){
			setCaretSize(5,20);
		}else{
			setCaretSize(2,20);
		}
		showCaret();
	}
	if(key==37&&event==1&&(*(p-1))!=0){
		x-=11;
		beginPaint();
	    setCaretPos(x,0);
	    showCaret();
		endPaint();	
		p--;
	}
	if(key==39&&event==1&&(*(p))!=0){
		x+=11;
		beginPaint();
	    setCaretPos(x,0);
	    showCaret();
		endPaint();	
		p++;
	}
}

void CharListener(char c){
	int i=0;char* p0=str;char a;
	char ch[5];
	if(c!='\b'&&c!='\r'&&(!ins)){
		if(*(p+1)==0){
			ch[0]=*p=c;
	        beginPaint();
	        paintText(x,0,ch);
	        setCaretPos(x+11,0);
	        showCaret();
	        endPaint();
	        x+=11;
	        p++;
		}else{
			while((*p0)!=0){
				p0++;
			}
			while(p0!=p){
				*p0=*(p0-1);
				p0--;
			}
			ch[0]=*p=c;
			beginPaint();
		    rectangle(x,0,600,20);
		    paintText(x,0,str+(x/11));
	        setCaretPos(x+11,0);
	        showCaret();
	        endPaint();
	        x+=11;
	        p++;
		}
	} 
	if(c!='\b'&&c!='\r'&&ins){
		*p=c;
		beginPaint();
		rectangle(x,0,600,20);
		paintText(x,0,str+(x/11));
	    setCaretPos(x+11,0);
	    showCaret();
	    endPaint();
	    x+=11;
	    p++;
	}
	
}

void Mouselistener(int a,int y,int button,int event){
	int len=0,x0=0;char *p2=str;
	if(y<24&&event==0){
		while(*p2!=0){
			len++;
			p2++;
		}
		x0=3+len*11;
		if(a<=x0){
			x=((a-3)/11)*11+3;
	        p=str+(x/11);
	        setCaretPos(x,0);
	        showCaret();
		}else{
			x=x0;
			p=str+(x/11);
	        setCaretPos(x,0);
	        showCaret();
		}
	    
	}
}
