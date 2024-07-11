#include <math.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acllib.h"
#include "function.h"

int Setup(){
	initConsole();
	printf("请输入函数表达式：（如3x^2+2x-1)");
	Node *f=NULL;
	f=ReadFunc();
	
	printf("请输入函数定义域：（如-1.4 1.4）");
	double left,right,xmax,ymax=0.0;
	int i,j;
	scanf("%lf %lf",&left,&right);
	if(fabs(left)>fabs(right)){
		xmax=fabs(left);
	}else{
		xmax=fabs(right);
	} 
	xmax*=1.5;
	for(i=0;i<=xmax;i++){
	}
	//确定x轴阈值 
	double x=left,value;
	while(x<=right){
		
		value=Value(x,f);
		if(fabs(value)>ymax)  ymax=fabs(value);
		x+=0.001;
	}
	ymax*=1.5;
	for(j=0;j<=ymax;j++){
	}
	//确定y轴阈值 
	 
	initWindow("function image",DEFAULT,DEFAULT,1000,750);
	beginPaint();
	
	DotLine(left,right,i,j,f);
	//描点连线 

	Axis(i,j);
	
	//画坐标轴 画网格线 
	endPaint();
	
	return 0;
}
