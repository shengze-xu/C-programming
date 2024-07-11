#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct _func func;

func* getFunction();//get the function expression;
double ValueofFunc(func* f, double x);//get the value of f(x) at x

double sup(func* f,double left,double right);//get the max of f
double inf(func* f,double left,double right);//get the min of f

double changex(double x,double left,double right);
double changey(double y,double max,double min);

void putcoordinate(double x0,double y0,double left,double right,double max,double min);
void putCell(double x0,double y0,double left,double right,double max,double min);
void DrawImage(func* f,double left,double right,double max,double min);
#endif
