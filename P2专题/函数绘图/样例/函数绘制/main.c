/*This program is written by Zhao Hongjue. 
First version: 04/07/2020
this program can get the image of the pow function.*/

#include <stdio.h>
#include <string.h>
#include <math.h>
#include "acllib.h"
#include "function.h"
#define WinWidth 1000
#define WinHeight 750
#define epsilon 0.00001

int Setup()
{
	initConsole();
	printf("this project can help you get the image of power function. please follow the guidance.\n\
please make sure that what you enter is right, because this project can't find your wrong.\n\
hope this project can help you :)\n");

	printf("Please enter the function expression(e.g:2x^3-x^2+x+1):	");
	func* f=getFunction();//get the function expression
	
	double left, right;
hr:
	
	printf("Please enter the interval(e.g: -1.4 1.4):");
	scanf("%lf %lf",&left,&right);
	
	if(left>=right){
		printf("wrong!");
		goto hr;
	}

	double max=sup(f,left,right);
	double min=inf(f,left,right);
	
	double x0=changex(0,left,right);
	double y0=changey(0,max,min);
	
	initWindow("function image",DEFAULT,DEFAULT,WinWidth,WinHeight);
	
	beginPaint();
	
	putCell(x0,y0,left,right,max,min);
	putcoordinate(x0,y0,left,right,max,min);
	DrawImage(f,left,right,max,min);
	
	endPaint();
	return 0;
}
