#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef enum {ERROR=0, OK=1} STATUS;
typedef enum {FALSE=0, TRUE=1} BOOLEAN;

typedef struct Node {   //inicializar a estrutura de uma lista ligada
    int data;
    struct Node* next;
}NODE;

void printList(NODE* list);   //imprimir lista
void deleteList(NODE** list); //eliminar lista
int tamanhoList(NODE*);  //diz o número de nós, ou seja, o tamanho da lista
STATUS putHeadLinkedList(NODE** pL, int X); //
STATUS newListNode(NODE** pN, int X); //
NODE* getHeadLinkedList(NODE list);
BOOLEAN emptyLinkedList(NODE list);


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
    //tamanhoList(primeiro);
    //deleteList(&primeiro);
    //printList(primeiro);
    //printList(primeiro);

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


STATUS putHeadLinkedList(NODE** pL, int X){
    NODE* TempNODE;
    // node creation
    if (newListNode(&TempNODE, X) == ERROR){
         return ERROR;
    }
    // list update
    TempNODE->next = *pL;
    *pL = TempNODE;
    return OK;
}

NODE* getHeadLinkedList(NODE list){  //vai ler a cabeça de lista
    if(!emptyLinkedList(list)){
        return (&list);
    } else {
        return NULL;
    }
}

BOOLEAN emptyLinkedList(NODE list){   //vê se está vazio ou não
    if(&list == NULL){
        return TRUE;
    } else {
        return FALSE;
    }
}

STATUS newListNode(NODE** pN, int X){  //criar um novo nó
    NODE* TempNODE;
    // node allocation
    if ((TempNODE = (NODE*)malloc(sizeof(NODE))) == NULL) {
        printf("\nLinkedList node: memory allocation error");
        return ERROR;
    }
    // list node update
    *pN = TempNODE;
    TempNODE->data = X;
    TempNODE->next = NULL;
    return OK;
}


