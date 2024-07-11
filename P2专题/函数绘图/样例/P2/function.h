#ifndef _FUNCTION_H_
#define _FUNCTION_H_

typedef struct node Node;

Node* ReadFunc();

double Value(double x, Node* f);

void DotLine(double left,double right,int i,int j,Node* head);

void Axis(int i,int j);


#endif
