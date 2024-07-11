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
	printf("����������У���������뺯�����ʽ���Ա������䣬��������������ƺ���ͼ��\n"); 
	printf("���뺯�����ʽ����x^2-2x+1):");
	func *f=creatfunc();
	double left,right;
	printf("�����������䣨�磺-1.5 1.5��:"); 
	scanf("%lf %lf",&left,&right);

	double X=fabs(left);
	if(fabs(right)>fabs(left)){
		X=fabs(right);
	}
	X=X*1.5;//X���������Χ 
	
	double i,max=funcvalue(f,left),min=funcvalue(f,left);
	double Y=fabs(min);
	double m=left,n=left;
	for(i=left;i<=right;i+=epsilon){
		if(funcvalue(f,i)>max){
			max=funcvalue(f,i);
			m=i;//m�Ǻ���ȡ���ֵʱx��ֵ 
		}
		if(funcvalue(f,i)<min){
			min=funcvalue(f,i);
			n=i;//n�Ǻ���ȡ��Сֵʱx��ֵ 
		}
	}
	if(fabs(max)>fabs(min)){
		Y=fabs(max); 
	}
	Y=Y*1.5;//Y���������Χ 

	initWindow("paint",DEFAULT,DEFAULT,width,height);
	
	beginPaint();
	
	funcimage(f,left,right,X,Y);
    paintaxis(X,Y); 
    paintvalue(f,m,n,X,Y);
	endPaint();
	
	return 0;
}
