#ifndef _ROW_H_
#define _ROW_H_

typedef struct _node {
    char value;
    struct _node *next;
} Node;

typedef struct {
    Node *head;
    Node *tail;
} List;

List list_create();
void list_free(List *list);

void list_append(List *list, char v);
void list_insert(List *list, char v);
void list_getin(List* list,char v,int i);

void list_set(List *list, int index, char v);
int list_get(List *list, int index);

int list_size(List *list);

Node* list_find(List *list, int v);
void list_remove(List *list, int v);
void list_print(List* list);

#endif
