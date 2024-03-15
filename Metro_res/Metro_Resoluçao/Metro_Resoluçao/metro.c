// Lixo.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <stdlib.h>
#include<conio.h>
#include<string.h>

// Header file for LINKED_LIST
#ifndef _LINKED_LIST_DEFINITIONS
#define _LINKED_LIST_DEFINITIONS

//-------------------------------------------------------
#ifndef _LOGICAL
#define _LOGICAL
typedef enum { ERROR = 0, OK = 1 } STATUS;
typedef enum { FALSE = 0, TRUE = 1 } BOOLEAN;
#endif // !_LOGICAL

#define MAX_CHARS 20

//-------------------------------------------------------
// linked node and list definitions

typedef struct {
    char nome[MAX_CHARS];
    float custo;
    BOOLEAN estado;
    int liga;
}STATION;


typedef struct _LIST_NODE {
    STATION* data;
    struct _LIST_NODE* pNext;
}LIST_NODE;

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
STATUS newLinkedList(LINKED_LIST*);
STATUS newListNode(LIST_NODE**, STATION*);
STATUS destroyLinkedList(LINKED_LIST*);

// Input and Output -------------------------------------
STATUS putHeadLinkedList(LINKED_LIST*, STATION*);
STATUS removeHeadLinkedList(LINKED_LIST*, STATION**);

// Query ------------------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST);
int lengthLinkedList(LINKED_LIST);
LIST_NODE* getHeadLinkedList(LINKED_LIST);
LIST_NODE* getTailLinkedList(LINKED_LIST);
STATUS printLinkedList(LINKED_LIST);
#endif // !_LINKED_LIST_DEFINITIONS

STATUS startMetroLines(LINKED_LIST*, int);
STATUS addStation(LINKED_LIST*);
void printMetroLine(LINKED_LIST);
void destroyMetroNetwork(LINKED_LIST*);
STATUS ReadLine(LINKED_LIST*, const char*);
float custoLinha(LINKED_LIST);
BOOLEAN stationExist(LINKED_LIST, const char*);
STATUS changeStationStatus(LINKED_LIST);

int main()
{
    LINKED_LIST metroNetwork = NULL;
    int c, nLine;
    BOOLEAN out = FALSE;
    char nome[50];
    printf("Metro network number of lines: ");
    scanf("%d", &nLine);
    //flush the input buffer
    while ((c = getchar()) != '\n');
    system("cls");
    if (startMetroLines(&metroNetwork, nLine) == ERROR)    //passar a lista e o número de linhas
        return ERROR;
    do {
        fprintf(stdout, "\n\n");
        fprintf(stdout, "0 -- Exit\n");
        fprintf(stdout, "1 -- Add station (enter Line, Station and Position)\n");
        fprintf(stdout, "2 -- Delete Station (enter Line and Station)\n");
        fprintf(stdout, "3 -- On/Off Station (enter Station)\n");
        fprintf(stdout, "4 -- Journey Fare (enter Origin and Destination)\n");
        fprintf(stdout, "5 -- Print line (enter Line)\n");
        fprintf(stdout, "6 -- Line Cost (enter Line)\n");
        fprintf(stdout, "7 -- Save lines data\n");
        fprintf(stdout, "8 -- Line Name\n");
        fprintf(stdout, "\nOption: ");
        scanf("%d", &c);
        //flush the input buffer
        while (getchar() != '\n');

        switch (c) {
        case 0: out = TRUE;
            break;
        case 1: if (addStation(&metroNetwork) == OK)
            printf("Estação adicionada com sucesso!\n");
              else
            printf("ERRO!\n");
            break;
            /*        case 2: deleteStation(&metroNetwork, NULL);
                        break;
                    case 3: changeLineStatus(&metroNetwork, getLineNumber(metroNetwork));
                        break;
                    case 4: ticketFares(metroNetwork, nLines);
                        break;
            */
        case 3: changeStationStatus(&metroNetwork);
            break;
        case 5: printMetroLine(metroNetwork);
            break;
        case 6: custoLinha(metroNetwork);
            break;
        case 7: saveMetroLines(metroNetwork, nLine);
            break;
        default:fprintf(stdout, "Invalid option\n\n");
        case 8:
            printf("Insira o nome da estação: ");
            gets(nome);
            if (stationExist(metroNetwork, nome)) {
                printf("Existe");
            }
            else {
                printf("Não exite");
            }
        }
        break;
    } while (out != TRUE);

    destroyMetroNetwork(&metroNetwork);

    return OK;


}
STATUS startMetroLines(LINKED_LIST* list, int nlines)       
{
    char nomeArquivo[20];

    sprintf(nomeArquivo, "line%d.txt", nlines);  //ler o arquivo em específico
    if (ReadLine(list, nomeArquivo))
        return OK;
    return ERROR;
}

STATUS ReadLine(LINKED_LIST* list, const char* filename)   //função para ler ficheiros
{
    FILE* fp;
    STATION* pt;
    int ativa;

    if ((fp = fopen(filename, "r")) != NULL)
    {
        while (!feof(fp))
        {
            if ((pt = (STATION*)malloc(sizeof(STATION))) != NULL && (putHeadLinkedList(list, pt) != ERROR))  //aloca memória para cada estação e depois
            {                                                                                               //chama a putHeadLinkedList e coloca no início
                fscanf(fp, "%[^;];%f;%d;%d\n", pt->nome, &(pt->custo), &ativa, &(pt->liga)); //lê tudo até ; nome não tem & pois é um array de chars
                pt->estado = FALSE;
                if (ativa)
                    pt->estado = TRUE;
            }
            else
            {
                destroyMetroNetwork(list);  //se der erro elimina lista
                return ERROR;
            }
        }
        fclose(fp);
        return OK;
    }
    else
        return ERROR;
}

STATUS saveMetroLines(LINKED_LIST list, int nline) {
    FILE* fp;
    char nomeArquivo[20];  // Defina o tamanho adequado para o nome do arquivo

    sprintf(nomeArquivo, "line%d_Copia.txt", nline);

    if ((fp = fopen(nomeArquivo, "w")) != NULL) {
        while (list != NULL) {
            fprintf(fp, "%s;%.2f;%d;%d;\n",
                ((STATION*)DATA(list))->nome,
                ((STATION*)DATA(list))->custo,
                ((STATION*)DATA(list))->estado,
                ((STATION*)DATA(list))->liga);
            list = NEXT(list);
        }
        fclose(fp);
        return OK;

    }
    else
        return ERROR;
}
STATUS addStation(LINKED_LIST* L)
{

    return OK;
}

void printMetroLine(LINKED_LIST list)  //imprimir a linha completa, ou seja, enquanto ponteiro não for null , imprime data
{
    while (list != NULL)
    {
        printf("%s - %.2f\n", DATA(list)->nome, list->data->custo);
        list = NEXT(list);
    }
}

void destroyMetroNetwork(LINKED_LIST* L)
{

}



// Source file for LINKED_LIST
//-------------------------------------------------------
// Constructor functions --------------------------------
STATUS newLinkedList(LINKED_LIST* pL)
{
    *pL = NULL;
    return OK;
}

//-------------------------------------------------------
STATUS newListNode(LIST_NODE** pN, STATION* X)    //cria novo nó
{
    LIST_NODE* pTempN;
    // node allocation
    if ((pTempN = (LIST_NODE*)malloc(sizeof(LIST_NODE))) == NULL) {
        printf("\nLinkedList node: memory allocation error");
        return ERROR;
    }
    // list node update
    *pN = pTempN;
    DATA(pTempN) = X;
    //pTempN->data = X;
    NEXT(pTempN) = NULL;
    return OK;
}
//-------------------------------------------------------
// Destructor functions ---------------------------------
STATUS destroyLinkedList(LINKED_LIST* pL)
{
    STATION* pX = NULL;
    // underflow
    if (emptyLinkedList(*pL))
        return ERROR;
    // if pX = NULL - don't want to use the deleted data
    while (*pL != NULL)
        removeHeadLinkedList(pL, &pX);
    return OK;
}
//-------------------------------------------------------
// Input functions --------------------------------------
STATUS putHeadLinkedList(LINKED_LIST* pL, STATION* X)
{
    LIST_NODE* pTempN;
    // node creation
    if (newListNode(&pTempN, X) == ERROR)  //se não conseguir criar novo nó, dá erro
        return ERROR;
    // list update
    NEXT(pTempN) = *pL;
    *pL = pTempN;
    return OK;
}
//-------------------------------------------------------
// Output functions -------------------------------------
STATUS removeHeadLinkedList(LINKED_LIST* pL, STATION** pX)
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
    else
        free(pAuxN);
    return OK;
}
//-------------------------------------------------------
// Query functions --------------------------------------
BOOLEAN emptyLinkedList(LINKED_LIST L)
{
    return ((L == NULL) ? TRUE : FALSE);
}
//-------------------------------------------------------
int lengthLinkedList(LINKED_LIST L)
{
    int size = 0;
    LIST_NODE* pAuxL = NULL;
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL))
        size++;
    return size;
}
//-------------------------------------------------------
LIST_NODE* getHeadLinkedList(LINKED_LIST L)
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
    while (NEXT(pTempL) != NULL)
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
    for (pAuxL = L; pAuxL != NULL; pAuxL = NEXT(pAuxL), i++)
        printf("\nList element [%d]: %d", i, DATA(pAuxL));
    return OK;
}

float custoLinha(LINKED_LIST L) {
    float final = 0;

    while (L!=NULL) {
        final += DATA(L)->custo;
        L = NEXT(L);
        printf("Custo: %f", DATA(L)->custo);
    }
}

BOOLEAN stationExist(LINKED_LIST L, const char* name) { //percorre a lista e diz se existe ou não
    while (L != NULL) {
        if (strcmp(name, DATA(L)->nome) == 0) {
            return TRUE;
        }
        L = NEXT(L);
    }
    return FALSE;
}

STATUS changeStationStatus(LINKED_LIST L) {
    char nome[50];
    printf("Qual o nome da Estação?");
    gets(nome);
    while (L != NULL) {
        if (strcmp(nome, DATA(L)->nome) == 0) {
            if (DATA(L)->estado == 0) 
                DATA(L)->estado = 1;
            else
                DATA(L)->estado = 0;
            return OK;

        }
        L = NEXT(L);

    }

    return ERROR;

}
//-------------------------------------------------------


// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
