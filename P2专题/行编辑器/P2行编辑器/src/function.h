#ifndef _FUNCTION_H_
#define _FUNCTION_h_

typedef struct _node{
	char value;
	struct _node *next;
}Node;

typedef struct {
    Node *head;
    Node *tail;
} List;


void Left(int *px);
void Right(int *px,List *list);
void Backspace(int *px,List *list);
void Delete(int *px,List *list);
void Enter(int *px,List *list);
void showtext(List *list);
void Insert(int *flag);
void paintCaret(int x,int flag);

/*-----------linkedlist-------------*/


void list_free(List *list);
void list_append(List *list, char c);
void list_insert(List *list, char c);
void list_set(List *list, int index, char c);
int list_get(List *list, int index);
int list_size(List *list);
Node* list_find(List *list, int index);
void list_remove(List *list, int index);


#endif
