#include <stdio.h>
#include <math.h>
#include <string.h>
#include "acllib.h"
#include "function.h"
#define width 800
#define height 800 
#define epsilon 0.000001

int Setup(){
	initConsole();
	printf("在这个程序中，你可以输入函数表达式和自变量区间，本程序会帮助你绘制函数图像\n"); 
	printf("输入函数表达式（如x^2-2x+1):");
	func *f=creatfunc();
	double left,right;
	printf("输入坐标区间（如：-1.5 1.5）:"); 
	scanf("%lf %lf",&left,&right);

	double X=fabs(left);
	if(fabs(right)>fabs(left)){
		X=fabs(right);
	}
	X=X*1.5;//X坐标轴最大范围 
	
	double i,max=funcvalue(f,left),min=funcvalue(f,left);
	double Y=fabs(min);
	double m=left,n=left;
	for(i=left;i<=right;i+=epsilon){
		if(funcvalue(f,i)>max){
			max=funcvalue(f,i);
			m=i;//m是函数取最大值时x的值 
		}
		if(funcvalue(f,i)<min){
			min=funcvalue(f,i);
			n=i;//n是函数取最小值时x的值 
		}
	}
	if(fabs(max)>fabs(min)){
		Y=fabs(max); 
	}
	Y=Y*1.5;//Y坐标轴最大范围 

	initWindow("paint",DEFAULT,DEFAULT,width,height);
	
	beginPaint();
	
	funcimage(f,left,right,X,Y);
    paintaxis(X,Y); 
    paintvalue(f,m,n,X,Y);
	endPaint();
	
	return 0;
}
