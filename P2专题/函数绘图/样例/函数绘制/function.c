#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "function.h"
#include "acllib.h"
#define WinWidth 1000
#define WinHeight 750
#define epsilon 0.00001
#define delta 20
#define maxn 20

typedef struct _func{
	struct _func* prev;
	double coef;
	double exp;
	struct _func* next;
} func;

func* getFunction(){
	func *head=NULL, *tail=NULL;
	char op='+';
	
	while(op!='\n'){		
		func* p=(func*)malloc(sizeof(func));
		if(op=='+')p->coef=1.0;
		else p->coef=-1.0;
		p->exp=1.0;
		p->prev=NULL;
		p->next=NULL;
		
		double value;
		int flag;
		flag=scanf("%lf",&value);
		if(flag==1) p->coef*=value;
		
		char ch;
		if((ch=getchar())=='x'){
			if((ch=getchar())=='^'){
				flag=scanf("%lf",&value);
				if(flag==1) p->exp*=value;
				ch=getchar();
			}
		}
		else p->exp=0.0;
		
		if(head==NULL)head=tail=p;
		else{
			p->prev=tail;
			tail->next=p;
			tail=p;
		}
		
		op=ch;
	}
	return head;
}

double ValueofFunc(func* f, double x){
	func* p;
	double sum=0.0;
	
	for(p=f;p;p=p->next){
		sum+=p->coef*pow(x,p->exp);
	}
	
	return sum;
}

double sup(func* f,double left,double right){
	double i, max=ValueofFunc(f,left);
	for(i=left;i<=right;i+=epsilon){
		if(ValueofFunc(f,i)>max)max=ValueofFunc(f,i);
	}
	return max;
}

double inf(func* f,double left,double right){
	double i, min=ValueofFunc(f,left);
	for(i=left;i<=right;i+=epsilon){
		if(ValueofFunc(f,i)<min)min=ValueofFunc(f,i);
	}
	return min;
}

double changex(double x,double left,double right){
	double x1;
	
	if(left>=0)left=0;
	if(right<=0)right=0;
	
	double A=(WinWidth-2*delta)/(right-left);
	double B=delta-A*left;
	
	x1=A*x+B;
	
	return x1;
}

double changey(double y,double max,double min){
	double y1;
	
	if(min>=0)min=0;
	if(max<=0)max=0;
	
	double A=(WinHeight-2*delta)/(min-max);
	double B=delta-A*max;
	
	y1=A*y+B;
	
	return y1;
}

void putcoordinate(double x0,double y0,double left,double right,double max,double min){
	setPenColor(BLACK);

	line(x0,0,x0,WinHeight);
	line(0,y0,WinWidth,y0);
	
	line(x0-delta/2,delta,x0,0);
	line(x0+delta/2,delta,x0,0);
	line(WinWidth-delta,y0+delta/2,WinWidth,y0);
	line(WinWidth-delta,y0-delta/2,WinWidth,y0);
	
	setTextSize(delta*3.0/4);
		
 	paintText(x0-delta/2,y0+delta*1/5.0,"O");
 	paintText(WinWidth-delta/2,y0+delta,"x");
 	paintText(x0+delta/2,delta,"y");
 	
	line(changex(left,left,right),y0-delta/2,changex(left,left,right),y0);
	line(changex(right,left,right),y0-delta/2,changex(right,left,right),y0);
	line(x0+delta/2,changey(max,max,min),x0,changey(max,max,min));
	line(x0+delta/2,changey(min,max,min),x0,changey(min,max,min));
	
	setTextSize(delta/2);
	
	char leftstr[maxn],rightstr[maxn],maxstr[maxn],minstr[maxn];
	sprintf(leftstr,"%.1lf",left);
	sprintf(rightstr,"%.1lf",right);
	sprintf(maxstr,"%.1lf",max);
	sprintf(minstr,"%.1lf",min);
	
	paintText(changex(left,left,right)-delta/2,y0+delta/2,leftstr);
	paintText(changex(right,left,right)-delta/2,y0+delta/2,rightstr);
	paintText(x0-delta/2,changey(max,max,min),maxstr);
	paintText(x0-delta/2,changey(min,max,min),minstr);
}

void putCell(double x0,double y0,double left,double right,double max,double min){
	if(left>=0)left=0;
	if(right<=0)right=0;
	if(max<=0)max=0;
	if(min>=0)min=0;
	
	setPenColor(RGB(0,240,255));
	setTextSize(delta/2);
	
	char temp[maxn];
	double xeta=(right-left)/10, i, j;
	for(i=0,j=0;i<=right||j>=left;i+=xeta,j-=xeta){
		sprintf(temp,"%.1lf",i);
		line(changex(i,left,right),0,changex(i,left,right),WinHeight);
		if(i)paintText(changex(i,left,right)-delta/2,y0+delta/2,temp);	

		sprintf(temp,"%.1lf",j);
		line(changex(j,left,right),0,changex(j,left,right),WinHeight);
		if(j)paintText(changex(j,left,right)-delta/2,y0+delta/2,temp);
	}
	
	double yeta=(max-min)/10;
	for(i=0,j=0;i<=max||j>=min;i+=yeta,j-=yeta){
		sprintf(temp,"%.1lf",i);
		line(0,changey(i,max,min),WinWidth,changey(i,max,min));
		if(i)paintText(x0-delta/2,changey(i,max,min),temp);
		
		sprintf(temp,"%.1lf",j);
		line(0,changey(j,max,min),WinWidth,changey(j,max,min));
		if(j)paintText(x0-delta/2,changey(j,max,min),temp);
	}
}

void DrawImage(func* f,double left,double right,double max,double min){
	double x;
	for(x=left;x<=right;x+=epsilon){
		double x1=changex(x,left,right);
		double y1=changey(ValueofFunc(f,x),max,min);
		putPixel(x1,y1,RED);
	}
}

