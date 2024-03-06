// Header file for LINKED_LIST
#ifndef _LINKED_LIST_DEFINITIONS
#define _LINKED_LIST_DEFINITIONS
//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
    typedef enum { ERROR = 0, OK = 1 } STATUS;
    typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL
//-------------------------------------------------------
// linked node and list definitions
struct LIST_NODE {
    int data;
    LIST_NODE* pNext;
};


typedef LIST_NODE* LINKED_LIST;

//-------------------------------------------------------
#ifndef _DATA_MACRO
#define _DATA_MACRO
// macro definition for easy access to single node data field
#define DATA(X) ((X)->data)
#endif // !_DATA_MACRO
//-------------------------------------------------------
#ifndef _LINK_LIST_MACRO
#define _LINK_LIST_MACRO
// macro definition for easy access to single LIST_NODE link field
#define NEXT(X) ((X)->pNext)
#endif // !_LINK_LIST_MACRO
//-------------------------------------------------------
// Functions Declaration --------------------------------
//-------------------------------------------------------
// Constructors and Destructors -------------------------
STATUS newLinkedList(LINKED_LIST*);  //inicializar lista
STATUS newListNode(LIST_NODE**, int); //criar novo nó
STATUS destroyLinkedList(LINKED_LIST*); //destroi a lista
// Input and Output -------------------------------------
STATUS putHeadLinkedList(LINKED_LIST*, int);  //novo nó no início da lista
STATUS removeHeadLinkedList(LINKED_LIST*, int*); //remove nó no início da lista
// Query ------------------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST); //se vazia retorna TRUE
int lengthLinkedList(LINKED_LIST); //devolve tamanho da lista
LIST_NODE* getHeadLinkedList(LINKED_LIST); //retorna o primeiro nó da lista
LIST_NODE* getTailLinkedList(LINKED_LIST); // retorna último nó da lista
STATUS printLinkedList(LINKED_LIST); //imprime a lista toda
#endif // !_LINKED_LIST_DEFINITIONS