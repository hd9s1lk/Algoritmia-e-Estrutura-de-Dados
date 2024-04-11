// Header file for BTREE
#define _CRT_
#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>
#ifndef _BTREE_DEFINITIONS
#define _BTREE_DEFINITIONS

//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL

typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;

#endif // !_LOGICAL
//-------------------------------------------------------
// dlink node binary tree definition
typedef struct _BTREE_NODE {
	int data;
	struct _BTREE_NODE* pL;
	struct _BTREE_NODE* pR;
}BTREE_NODE;
// binary tree definition
typedef BTREE_NODE* BTREE;
//-------------------------------------------------------
#ifndef _DATA_MACRO
#define _DATA_MACRO
// macro definition for easy access to BTREE_NODE data field
#define DATA(X) ((X)->data)
#endif // !_DATA_MACRO
//-------------------------------------------------------
#ifndef _CHILDREN_BTREE_MACROS
#define _CHILDREN_BTREE_MACROS
// macros definition for easy access to BTREE_NODE children fields
#define LEFT(X) ((X)->pL)
#define RIGHT(X) ((X)->pR)
#endif // !_CHILDREN_BTREE_MACROS
//-------------------------------------------------------
// Functions Declarations -------------------------------
//-------------------------------------------------------
//-------------------------------------------------------
// Constructors and Destructors -------------------------
STATUS newBTree(BTREE*);
STATUS newBTNode(BTREE_NODE**, int);
STATUS createSubBTree(BTREE_NODE**, int, BTREE_NODE*, BTREE_NODE*);
STATUS destroyBTree(BTREE*);
STATUS insertBST(BTREE , int);
//-------------------------------------------------------
// Query - General --------------------------------------
BOOLEAN emptyBTree(BTREE);  //se está vazia ou não
BOOLEAN isLeaf(BTREE_NODE*); //se o left & right é null
int numberNodesBTree(BTREE); //número de nós da árvore
int somaNos(BTREE);
int valorMaximo(BTREE); //FAZER EM CASA
//-------------------------------------------------------
// Query - Printing Tree Values -------------------------
STATUS printInOrderBTree(BTREE);  //imprimir valores
//-------------------------------------------------------
// Query - Traversing -----------------------------------
STATUS traverseBTreeInOrder(BTREE); //
#endif // !_BTREE_DEFINITIONS

STATUS newBTree(BTREE* pBT)
{
	*pBT = NULL;
	return OK;
}
//-------------------------------------------------
STATUS newBTNode(BTREE_NODE** pN, int X)
{
	BTREE_NODE* pTempN;
	// node allocation
	if ((pTempN = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) == NULL)  //alocar memória
		return ERROR;
	// btree node update
	DATA(pTempN) = X;     //data de valor X
	LEFT(pTempN) = NULL;  //e ambos os lado a null
	RIGHT(pTempN) = NULL; //a null
	*pN = pTempN;
	return OK;
}
//-------------------------------------------------
STATUS createSubBTree(BTREE_NODE** pN, int X, BTREE_NODE* pL, BTREE_NODE* pR)
{
	BTREE_NODE* pTempN;
	// node creation
	if (newBTNode(&pTempN, X) == ERROR) {
		 //vê se existe nó ou memória alocada
		return ERROR;
	}
	// update btree with left and right subtrees
	LEFT(pTempN) = pL;
	RIGHT(pTempN) = pR;
	*pN = pTempN;
	return OK;
}
//-------------------------------------------------
STATUS destroyBTree(BTREE* pBT)
{
	// underflow
	if (*pBT == NULL)
		return ERROR;
	// destroy recursively
	destroyBTree(&LEFT(*pBT));
	destroyBTree(&RIGHT(*pBT));
	free(DATA(*pBT));
	DATA(*pBT) = NULL;
	free(*pBT);
	*pBT = NULL;
	return OK;
}
//-------------------------------------------------
// Query Functions --------------------------------
BOOLEAN emptyBTree(BTREE BT)
{
	return (BT == NULL) ? TRUE : FALSE; //devolve boolean a ver se está vazia ou não
}
//-------------------------------------------------
BOOLEAN isLeaf(BTREE_NODE* pBT)
{
	return ((LEFT(pBT) == NULL) && (RIGHT(pBT) == NULL)) ? TRUE : FALSE; //folha é nó sem filhos, ou seja verifica o node da direita e da esquerda
}
//-------------------------------------------------
int numberNodesBTree(BTREE BT) 
{
	//int cnt = 0;
	//BTREE tempBT = BT;
	//if (emptyBTree(tempBT) == TRUE)  //verifica se estã vazio
	//	return cnt;
	//int cntL = numberNodesBTree(LEFT(tempBT)); 
	//int cntR = numberNodesBTree(RIGHT(tempBT));
	//return (1 + cntL + cntR);

	return BT == NULL ? 0 : (1 + numberNodesBTree(LEFT(BT)) + numberNodesBTree(RIGHT(BT)));
}
//-------------------------------------------------
// Query Functions - Traversing -------------------
STATUS traverseBTreeInOrder(BTREE BT)
// non-generic - suitable only for int data
{
	BTREE tempBT = BT;
	if (emptyBTree(tempBT) == TRUE)
		return ERROR;
	traverseBTreeInOrder(LEFT(tempBT), pPrintNode);
	// here is printing the node value; but any other action is admissible
	printf("%s, ", DATA(tempBT));
	traverseBTreeInOrder(RIGHT(tempBT), pPrintNode);
	return OK;
}
//-------------------------------------------------
// Query Functions - Printing ---------------------
STATUS printInOrderBTree(BTREE BT)
// non-generic - suitable only for int data
{
	BTREE tempBT = BT;
	if (emptyBTree(tempBT) == TRUE)
		return ERROR;
	// print recursively
	printInOrderBTree(LEFT(tempBT));  //para preorder o print DATA vai para cima ou seja primeiro a ser lido
	printf("%d, ", DATA(tempBT));
	printInOrderBTree(RIGHT(tempBT)); //para postorder o print DATA vai para baixo ou seja último a ser lido
	return OK;
}

STATUS insertBST(BTREE* bt, int x)
{
	if (emptyBTree(*bt)) {
		BTREE_NODE* pNew;
		if (newBTNode(&pNew, x) == ERROR) {
			return ERROR;

			*bt = pNew;
			return OK;
		}
		if (x > DATA(*bt))
			insertBST(&RIGHT(*bt), x);
		else
			insertBST(&LEFT(*bt), x);
		return OK;
	}
}

int somaNos(BTREE bt) {
	
	return bt == NULL ? 0 : (somaNos(RIGHT(bt)) + somaNos(LEFT(bt)) + DATA(bt));
	
}

int valorMaximo(BTREE bt) {  //valor máximo numa BST é o valor mais à direita

	BTREE_NODE* temp;
	if (emptyBTree(bt)) {
		printf("Erro");
		exit(0);
	}
	while (RIGHT(temp) != NULL) {
		temp = RIGHT(temp);
	}
	return DATA(temp);
	
}

main() {
	BTREE ba;

	newBTree(&ba); //endereço da a
	//emptyBTree(ba) ? printf("Arvore Vazia: %d") : printf("\n Arvore não vazia");
	//newBTNode(&ba, 10); 
	

	insertBST(&ba, 10);
	insertBST(&ba, 7);
	insertBST(&ba, 15);
	insertBST(&ba, 9);
	insertBST(&ba, 11);
	insertBST(&ba, 17);
	insertBST(&ba, 8); //imprimir em InOrder uma BST fica sempre em ordem crescente
	somaNos(ba);

	printf("\n A arvore tem: %d", numberNodesBTree(ba));
	printf("\nTotal da arvore = %d", somaNos(ba));







}