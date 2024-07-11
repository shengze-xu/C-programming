#include <stdio.h>
#include <math.h>
#include<stdlib.h>
#include "acllib.h"
#include "function.h"
#include <string.h>
typedef struct node{
	double coef;
	double exp;
	struct node *next;
}Node;

Node* ReadFunc(){
	Node *head=NULL; 
	Node *q=head;
	char ch='+';
	char c;
	double a;int flag;
	int cnt=0;
	while(ch!='\n'){
		Node *n=malloc(sizeof(Node));
		if(ch=='+'){
			n->coef=1.0;
		}else{
			n->coef=-1.0;
		}
		
		n->exp=1.0;
		n->next=NULL;
		
		flag=scanf("%lf",&a);
		if(flag==1){
			n->coef*=a;
		}
		/*if(cnt==0&&flag==0&&(c=getchar())=='-'){
			n->coef=-1.0;
			flag=scanf("%lf",&a);
			if(flag==1){
				n->coef*=a;
			}
		} */
		if((c=getchar())=='x'){
			if((c=getchar())=='^'){
				scanf("%lf",&(n->exp));
				c=getchar();
			}  
		}else{
			n->exp=0.0;
		}
		ch=c;
		
		if(head){
			q->next=n;
			q=q->next;
		}else{
			head=n;
			q=n;
		}
		cnt++; 
	}
	
	return head;
}

double Value(double x, Node* f){
	Node *p=f;
	double result=0.0;
	for(;p;p=p->next){
		result=result+p->coef*pow(x,p->exp);
	}
	return result;
}

void DotLine(double left,double right,int i,int j, Node* head){
	double x=left;
	double value,x1,y1,x2,y2;
	value=Value(x,head);
	x1=x*500/i+500;
	y1=375-value*375/j;
	putPixel(x1,y1,RED);
	while(x<=right){
		x+=0.001;
		value=Value(x,head);
		x2=x*500/i+500;
		y2=375-value*375/j;
		putPixel(x2,y2,RED);
		setPenColor(BLACK);
		line(x1,y1,x2,y2);
		x1=x2;
		y1=y2;
	}
}


void Axis(int i,int j){
	double k;
	char str[100];
	for(k=25.0;k<1000;k+=25){
		setPenColor(RGB(135,206,255));
		line(k,0,k,750);
		setTextSize(8);
		setPenColor(BLACK);
		sprintf(str,"%.1f",(k-500.0)*i/500);
		paintText(k,375,str);
	}
	for(k=25.0;k<750;k+=25){
		setPenColor(RGB(135,206,255));
		line(0,k,1000,k);
		setTextSize(8);
		setPenColor(BLACK);
		sprintf(str,"%.1f",(375.0-k)*j/375);
		paintText(500,k,str);
	}
	setPenColor(BLACK);
	line(0,375,1000,375);
	line(500,0,500,750);
	setTextSize(20);
	paintText(500,375,"O");
	paintText(500,0,"y");
	paintText(980,375,"x");
}




