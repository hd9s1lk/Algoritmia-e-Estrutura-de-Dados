#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct Node {
    int data;
    struct Node* next;
}NODE;

void printList(NODE* list);
void deleteList(NODE** list);
int tamanhoList(NODE*);


int main(int argc, char*argv[]){

    NODE* primeiro = NULL;
    NODE* segundo = NULL;
    NODE* terceiro = NULL;

    primeiro=(NODE*)malloc(sizeof(NODE));
    segundo=(NODE*)malloc(sizeof(NODE));
    terceiro=(NODE*)malloc(sizeof(NODE));

    primeiro->data = 5;
    primeiro->next = segundo;

    segundo->data=10;
    segundo->next=terceiro;

    terceiro->data=15;
    terceiro->next=NULL;

    printList(primeiro);
    tamanhoList(primeiro);
    deleteList(&primeiro);
    printList(primeiro);


    system("pause");
    return 0;
}

void printList(NODE* list){
    if (list==NULL){
        printf("\n Lista vazia\n");
        return;    //com return já não precisa de else
    }

    while(list!=NULL){
        printf(" %d ", list->data);
        list = list->next;
    }
}

void deleteList(NODE** list){
    NODE* current = *list;
    NODE* seguinte;

    while(current!=NULL){
        seguinte = current->next;
        free(current);
        current = seguinte;
    }

    *list = NULL;
}

int tamanhoList(NODE* list){
    if(list==NULL){
        printf("\nNão tem nós");
    }
    
    int i=0;
    while(list!=NULL){
        list = list->next;
        i++;
    }

    printf("\nNos: %d", i);
}