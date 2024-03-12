#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct Node{
    int data;
    struct Node* next;
}NODE;

void printList(NODE* list);
void deletelist(NODE** list);
void tamanhoList(NODE* list);

int main(int argc, char*argv[]){

    NODE* primeiro = NULL;
    NODE* segundo = NULL;
    NODE* terceiro = NULL;

    primeiro=(NODE*)malloc(sizeof(NODE));
    segundo=(NODE*)malloc(sizeof(NODE));
    terceiro=(NODE*)malloc(sizeof(NODE));

    primeiro->data = 5;
    primeiro->next = segundo;

    segundo->data = 27;
    segundo->next = terceiro;

    terceiro->data = 13;
    terceiro->next = NULL;

    printList(primeiro);
    tamanhoList(primeiro);
    deleteList(primeiro);
    printList(primeiro);


    system("pause");
    return 0;
}


void printList(NODE* list){
    if(list==NULL){
        printf("Lista vazia");
        return;
    }

    while(list!=NULL){
        printf("%d \n", list->data);
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

void tamanhoList(NODE* list){
    if(list==NULL){
        printf("Nao tem nos\n");
        return;
    }
    int i=0;
    while(list!=NULL){
        list = list->next;
        i++;
    }
    printf("Tamanho da lista: %d", i);
}

