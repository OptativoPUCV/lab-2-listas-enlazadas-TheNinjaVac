#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include "list.h"

typedef struct Node Node;

struct Node {
    void * data;
    Node * next;
    Node * prev;
};

struct List {
    Node * head;
    Node * tail;
    Node * current;
};

typedef List List;

Node * createNode(void * data) {
    Node * new = (Node *)malloc(sizeof(Node));
    assert(new != NULL);
    new->data = data;
    new->prev = NULL;
    new->next = NULL;
    return new;
}

List * createList() {
    List*lista = (List *) malloc(sizeof(List));
    lista->head = NULL;
    lista->tail = NULL;
    lista->current = NULL;
     return lista;
}

void * firstList(List * list) {
    if (list->head == NULL) return NULL;
    list->current = list->head;
    return list->current->data;
}

void * nextList(List * list) {
    if (list->current == NULL) return NULL;
    list->current = list->current->next;
    return (list->current) ? list->current->data : NULL;
}

void * lastList(List * list) {
    if (list->tail == NULL ) return NULL;
    list->current = list->tail;
    return list->current->data;
}

void * prevList(List * list) {
    if(list->current == NULL) return NULL;
    list->current = list->current->prev;
    return (list->current) ? list->current->data : NULL;;
}

void pushFront(List * list, void * data) {
    Node *nuevoNodo =(Node *) malloc (sizeof(Node));
    nuevoNodo->prev = NULL;
    nuevoNodo->data = data;
    nuevoNodo->next = list->head;
    if (list->head) list->head->prev = nuevoNodo;
    if (list->tail == NULL)list->tail =nuevoNodo;
    list->head = nuevoNodo;
}

void pushBack(List * list, void * data) {
    list->current = list->tail;
    pushCurrent(list,data);
}

void pushCurrent(List * list, void * data) {
    Node *nuevoNodo = createNode(data);
    if(list == NULL) {
        list->head = nuevoNodo;
        list->current = nuevoNodo;
        list->tail = nuevoNodo;
        return;
    }
    if (list->tail == list->current){
        list->current->next = nuevoNodo;
        nuevoNodo->prev = list->current;
        list->tail = nuevoNodo;
        list->current = nuevoNodo;
        return;
    }
    list->current->next = nuevoNodo;
    nuevoNodo->prev = list->current;
    nextList(list);
    list->current->prev = nuevoNodo;
    nuevoNodo->next = list->current;

}

void * popFront(List * list) {
    list->current = list->head;
    return popCurrent(list);
}

void * popBack(List * list) {
    list->current = list->tail;
    return popCurrent(list);
}

void* popCurrent(List * list) {
    if (list == NULL || list->current == NULL) return NULL; 
    Node * nodoAEliminar = list->current;
    void * dato = nodoAEliminar->data;

    if (list->head == list->tail) {
        list->head = NULL;
        list->tail = NULL;
        list->current = NULL;
    }
    else if (list->current == list->head) {
        list->head = list->current->next;
        list->head->prev = NULL;
        list->current = list->head;
    }
    else if (list->current == list->tail) {
        list->tail = list->current->prev;
        list->tail->next = NULL;
        list->current = NULL;
    }
    else {
        list->current->prev->next = list->current->next;
        list->current->next->prev = list->current->prev;
        list->current = list->current->next;
    }
    free(nodoAEliminar);
    return dato;
}

void cleanList(List * list) {
    while (list->head != NULL) {
        popFront(list);
    }
}