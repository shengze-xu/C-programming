#include <math.h>
#include<stdlib.h>
#include <stdio.h>
#include <string.h>
#include "acllib.h"
#include "function.h"

int Setup(){
	initConsole();
	printf("�����뺯�����ʽ������3x^2+2x-1)");
	Node *f=NULL;
	f=ReadFunc();
	
	printf("�����뺯�������򣺣���-1.4 1.4��");
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
	//ȷ��x����ֵ 
	double x=left,value;
	while(x<=right){
		
		value=Value(x,f);
		if(fabs(value)>ymax)  ymax=fabs(value);
		x+=0.001;
	}
	ymax*=1.5;
	for(j=0;j<=ymax;j++){
	}
	//ȷ��y����ֵ 
	 
	initWindow("function image",DEFAULT,DEFAULT,1000,750);
	beginPaint();
	
	DotLine(left,right,i,j,f);
	//������� 

	Axis(i,j);
	
	//�������� �������� 
	endPaint();
	
	return 0;
}
