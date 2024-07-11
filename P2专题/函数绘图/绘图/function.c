#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include "acllib.h"
#include "function.h"

#define epsilon 0.000001
#define width 800
#define height 800 

typedef struct _func{
	double coef;
	double exp;
	struct _func *next;
} func;

/*func* creatfunc(){
	func *head=NULL;
	func *n=head;
	char op='+';
	char ch;	
	int flag;
	double value;
	while(op!='\n'){		
		func *p=(func*)malloc(sizeof(func));
		if(op=='+'){
			p->coef=1.0;
		}
		else{
			p->coef=-1.0;
		}
		p->exp=1.0;
		p->next=NULL;		
	
		flag=scanf("%lf",&value);
		if(flag==1) p->coef*=value;
	
		if((ch=getchar())=='x'){
			if((ch=getchar())=='^'){
				flag=scanf("%lf",&value);
				if(flag==1) p->exp*=value;
				ch=getchar();
			} 
		}
		else{
			p->exp=0.0;
		}
		op=ch;
		
		if(head){
			n->next=p;
			n=n->next;
		}
		else{
			head=p;
			n=p;
		}
	}
	return head;
} */


func* creatfunc(){
	func *head=NULL;
	func *n=head;
	char ch;	
	double value;
	do{		
		func *p=(func*)malloc(sizeof(func));	
	
		if(scanf("%lf",&value)) p->coef=value;//省略上个写法中的op 
		else p->coef=1.0;
	
		if((ch=getchar())=='x'){
			if((ch=getchar())=='^'){
				if(scanf("%lf",&value)) p->exp=value;
				ch=getchar();
			}else p->exp=1.0; 
		}
		else p->exp=0.0;
		p->next=NULL;
		
		if(head){
			n->next=p;
			n=n->next;
		}
		else{
			head=p;
			n=p;
		}
	}while(ch!='\n');
	
	return head;
} 

double funcvalue(func *f,double x){
	func* p;
	double sum=0.0;
	for(p=f;p;p=p->next){
		sum+=p->coef*pow(x,p->exp);
	}
	return sum;
}

void funcimage(func *f,double left,double right,double X,double Y){
	double x,y,x1,y1;
	double k1,b1,k2,b2;
	for(x=left;x<=right;x+=epsilon){
		y=funcvalue(f,x);
		k1=width/(2*X);
	    b1=width/2;
		k2=-height/(2*Y);
	    b2=height/2;
		x1=k1*x+b1;
		y1=k2*y+b2;
		putPixel(x1,y1,RED);
	}
}

void paintvalue(func*f,double m,double n,double X,double Y){
	double x1,x2,y1,y2;
	char str1[100];
	char str2[100];
	x1=width/(2*X)*m+width/2;
	y1=-height/(2*Y)*funcvalue(f,m)+height/2;
	x2=width/(2*X)*n+width/2;
	y2=-height/(2*Y)*funcvalue(f,n)+height/2;
	sprintf(str1,"%s%.2f%s%.2f","当x=",m,"时 fmax=",funcvalue(f,m));
	sprintf(str2,"%s%.2f%s%.2f","当x=",n,"时 fmin=",funcvalue(f,n));
	setTextSize(10);
	setTextColor(RGB(172,176,234));
	paintText(x1,y1,str1);
	paintText(x2,y2,str2);
}

void paintaxis(double X,double Y){
	int i,w=width/40;
	char str1[100]; 
	for(i=w;i<width;i+=w){
		if(i%(width/8)!=0&&i!=width/2){
			setPenColor(RGB(179,179,183));
			line(i,0,i,height);
		}
		if(i%(width/8)==0&&i!=width/2){
			setPenColor(RGB(102,103,105));
			line(i,0,i,height);
		}
		sprintf(str1,"%.2f",(2*X/width)*i-X);
		if(i%(width/20)==0&&i!=width/2){
			setTextSize(10);
			paintText(i-10,height/2,str1);
		}
	}
	int j,h=height/40;
	char str2[100];
	for(j=h;j<height;j+=h){
		if(j%(height/8)!=0&&j!=height/2){
			setPenColor(RGB(179,179,183));
			line(0,j,width,j);
		}
		if(j%(height/8)==0&&j!=height/2){
			setPenColor(RGB(102,103,105));
			line(0,j,width,j);
		}
		sprintf(str2,"%.2f",(-2*Y/height)*j+Y);
		if(j%(height/20)==0&&j!=height/2){
			setTextSize(10);
			paintText(width/2-20,j-5,str2);
		}
	}
	setPenColor(RGB(0,0,0));
	setPenWidth(2);
	line(0,height/2,width,height/2);
	line(width,height/2,width-10,height/2-5);
	line(width,height/2,width-10,height/2+5);
	line(width/2,0,width/2,height); 
	line(width/2,0,width/2-5,10);
	line(width/2,0,width/2+5,10);
    setTextSize(20);
	paintText(width/2+5,height/2+2,"O");
	paintText(width-15,height/2+6,"x");
	paintText(width/2+10,0,"y");
	setTextSize(20);
	paintText(10,10,"函数图像"); 
}







