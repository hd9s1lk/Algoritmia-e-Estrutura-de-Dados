#include"LinkedList.h"
#include<stdlib.h>
#include<stdio.h>

//-------------------------------------------------------
// Constructor functions --------------------------------
STATUS newLinkedList(LINKED_LIST* pL)
{
*pL = NULL;
return OK;
}
//-------------------------------------------------------
STATUS newListNode(LIST_NODE** pN, int X)
{
LIST_NODE* pTempN;
// node allocation
if ((pTempN = (LIST_NODE*)malloc(sizeof(LIST_NODE))) == NULL) {  //vai criar novo nó e vai apontar para novo nó
printf("\nLinkedList node: memory allocation error");
return ERROR;
}
// list node update
*pN = pTempN;    //aponta para novo nó criado
DATA(pTempN) = X;
NEXT(pTempN) = NULL;
return OK;
}
//-------------------------------------------------------
// Destructor functions ---------------------------------
STATUS destroyLinkedList(LINKED_LIST* pL)
{
int *pX = NULL;
// underflow
if (emptyLinkedList(*pL))   //
return ERROR;
// if pX = NULL - don't want to use the deleted data
while (*pL != NULL)
removeHeadLinkedList(pL, pX);
return OK;
}
//-------------------------------------------------------
// Input functions --------------------------------------
STATUS putHeadLinkedList(LINKED_LIST* pL, int X)    //criar nova "cabeça" para a lista ligada
{
LIST_NODE* pTempN;
// node creation
if (newListNode(&pTempN, X) == ERROR)
return ERROR;
// list update
NEXT(pTempN) = *pL;   //temporário(novo) criado aponta para o primeiro
*pL = pTempN;
return OK;
}
//-------------------------------------------------------
// Output functions -------------------------------------
STATUS removeHeadLinkedList(LINKED_LIST* pL, int* pX)
{
LIST_NODE* pAuxN;
//underflow
if (emptyLinkedList(*pL))
    return ERROR;
// node deletion
pAuxN = *pL;
*pL = NEXT(*pL);
// node data and memory handling
if (pX != NULL) // if pX = NULL - don't want to use the returned data
    *pX = DATA(pAuxN);
//else
free(pAuxN);
return OK;
}
//-------------------------------------------------------
// Query functions --------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST L)
{
return ((L == NULL) ? TRUE : FALSE);    //vê se está vazia ou não
}
//-------------------------------------------------------
int lengthLinkedList(LINKED_LIST L)   //tamanho da lista ligada
{
int size = 0;
LIST_NODE* pAuxL = NULL;
for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL)) //pAuxL aponta para o primeiro nó enquanto e vai incrementando até NULL
size++;
return size;
}
//-------------------------------------------------------
LIST_NODE* getHeadLinkedList(LINKED_LIST L) //vê se está vazia ou não para devolver a "cabeça" da lista liagada
{
if (!emptyLinkedList(L))
return (L);
else
return NULL;
}
//-------------------------------------------------------
LIST_NODE* getTailLinkedList(LINKED_LIST L)
{
if (emptyLinkedList(L))
    return NULL;
LIST_NODE* pTempL = L;
while (NEXT(pTempL) != NULL)   //ciclo while para ser diferente de NULL e vai passando de nó a nó
    pTempL = NEXT(pTempL);
return pTempL;
}
//-------------------------------------------------------
STATUS printLinkedList(LINKED_LIST L)
// non-generic - suitable only for int data
{
int i = 0;
LIST_NODE* pAuxL = NULL;  
if (emptyLinkedList(L)) {
printf("\nEmpty List.\n");
return ERROR;
}
for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL), i++)   //vai passando de nó a nó e impriminto a data desse nó
printf("\nList element [%d]: %d", i, DATA(pAuxL));
return OK;
}
//-------------------------------------------------------

int lengthLinkedListWHILE(LINKED_LIST L)   //tamanho da lista ligada
{
int size = 0;
LIST_NODE* pAuxL = L;
while(pAuxL != NULL){
    size++;
}
return size;
}
