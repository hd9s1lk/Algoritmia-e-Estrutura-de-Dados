#include"LinkedList.h"
#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

STATUS newLinkedList(LINKED_LIST* list){
    *list = NULL;
    return OK;
}

STATUS newListNode(LIST_NODE** list, int pN){
    LIST_NODE* listTemp;

    if ((listTemp = (LIST_NODE*)malloc(sizeof(LIST_NODE))) == NULL){
        printf("Erro");
        return ERROR;
    }

    *list = listTemp;
    DATA(listTemp) = pN;
    NEXT(listTemp) = NULL;

    return OK;
}

STATUS destroyLinkedList(LINKED_LIST* list){
    int *pX = NULL;

    if(emptyLinkedList(*list)){
        return ERROR;
    }

    while(*list != NULL){
        removeHeadLinkedList(list, pX);
        return OK;
    }
}


STATUS putHeadLinkedList(LINKED_LIST* list, int x){
    LIST_NODE* node;

    if(newListNode(&node,x) == ERROR){
        return ERROR;
    }

    NEXT(node) = *list;
    *list = node;
    return OK;
}

STATUS removeHeadLinkedList(LINKED_LIST* list, int* x){
    LIST_NODE* node;

    if(emptyLinkedList(*list)){
        return ERROR;
    }

    node = *list;
    *list = NEXT(*list);

    if(x != NULL){
        *x = DATA(node);
    }

    free(node);
    return OK;
}

BOOLEAN emptyLinkedList(LINKED_LIST list){
    if(list==NULL){
        return TRUE;
    } else {
        return FALSE;
    }
}

int lengthLinkedList(LINKED_LIST* list){
    int size=0;

    LIST_NODE* node = NULL;
    for(node=list; node!=NULL; node=NEXT(node)){
        size++;
        return size;
    }
}

LIST_NODE* getHeadLinkedList(LINKED_LIST list){
    if(!emptyLinkedList(list)){
        return list;
    } else {
        return NULL;
    }
}

LIST_NODE* getTailLinkedList(LINKED_LIST list){
    if(emptyLinkedList(list)){
        return NULL;
    }

    LIST_NODE* node;
    while(NEXT(node)!=NULL){
        node = NEXT(node);
    }

    return node;
}

STATUS printLinkedList(LINKED_LIST list){
    if(emptyLinkedList(list)){
        return ERROR;
    }

    int i=0;
    LIST_NODE* node=NULL;

    for(node=list; node!=NULL; node=NEXT(node), i++){
        printf("[%d] -> %d", i, DATA(node));
        return OK;
    }
}

int lengthLinkedList(LINKED_LIST L){
    int size=0;
    LIST_NODE* node;
    while(node!=NULL){
        node = NEXT(node);
        size++;
    }

    return size;
}