#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct _func func;
	
func* creatfunc();

double funcvalue(func *f,double x);

void funcimage(func *f,double left,double right,double X,double Y);
void paintaxis(double X,double Y);
void paintvalue(func*f,double m,double n,double X,double Y);

#endif
