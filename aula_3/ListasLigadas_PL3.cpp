#include"LinkedList.h"
#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

int main(int argc, char*argv[]){


    LINKED_LIST a;   //lista ligada 
    LINKED_LIST b;
    int num[10];
    newLinkedList(&a);  // & comercial para dar a morada para o ponteiro chamado pela função
    newLinkedList(&b);

    putHeadLinkedList(&b, 10);
    putHeadLinkedList(&b, 5);
    putHeadLinkedList(&b, 17);

    putHeadLinkedList(&a, 5);
    putHeadLinkedList(&a, 10);
    printLinkedList(a);

    printf("\n O tamanho da lista = %d", lengthLinkedList(a));

    int x;
    removeHeadLinkedList(&a, &x);

    printLinkedList(a);
    printf("\n A lista %s vazia", emptyLinkedList(a) ? "está" : "Não está");
    removeHeadLinkedList(&a, &x);

    printf("\n A lista %s vazia", emptyLinkedList(a) ? "está" : "Não está");

    putHeadLinkedList(&a, -10);
    putHeadLinkedList(&a, 27);
    putHeadLinkedList(&a, 5);

    printf("\n O valor do primeiro nó = %d", DATA(getHeadLinkedList(a)));
    printf("\n O valor do último nó = %d", DATA(getTailLinkedList(a)));


    LIST_NODE * pTemp = a;
    while(pTemp != NULL){
        putHeadLinkedList(&b, DATA(pTemp));
        pTemp = NEXT(pTemp);
    }   

    printLinkedList(a);
    printLinkedList(b);


}