#ifndef _EDIT_H_
#define _EDIT_H_

void LEFT(int *pi);
void RIGHT(List* list,int *pi);
void ENTER(List* list,int* pi);
void BACKSPACE(List* list,int *pi);
void INSERT(int* pcaretwid,int i);
void deletekey(List* list,int *pi);
void HOME(int *pi);
void END(List* list,int *pi);

void print(List* list);
void putCaret(int i);

#endif
