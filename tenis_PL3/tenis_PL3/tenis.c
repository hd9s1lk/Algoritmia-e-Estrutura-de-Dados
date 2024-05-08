#define _CRT_SECURE_NO_WARNINGS
#include <conio.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_NAME 20
#define STAGES 15

typedef struct _PLAYER
{
	char name[MAX_NAME];
	int sets;
}PLAYER;

typedef struct _BTREE_NODE
{
	PLAYER* pData;
	struct _BTREE_NODE* pL;
	struct _BTREE_NODE* pR;
} BTREE_NODE;


typedef BTREE_NODE* BTREE;
typedef enum _BOOLEAN { FALSE = 0, TRUE = 1 } BOOLEAN;
typedef enum _STATUS { ERROR = 0, OK = 1 } STATUS;

#define DATA(node) ((node)->pData)
#define LEFT(node) ((node)->pL)
#define RIGHT(node) ((node)->pR)

BTREE_NODE* NewBtreeNode(PLAYER* data);
BTREE_NODE* InitNode(PLAYER*, BTREE_NODE*, BTREE_NODE*);
BTREE_NODE* CreateBtree(PLAYER**, int, int);
STATUS ReadPlayersFromFile(PLAYER**, char*);
BOOLEAN BtreeLeaf(BTREE_NODE* node);
int CountLeafs(BTREE);
void PrintLeaf(BTREE);
int CountTotalSets(BTREE btree);
void PrintGame(BTREE);
void PrintALLGames(BTREE);
int PlayerSetsGanhos(BTREE, char*);
int PlayerSetsJogados(BTREE, char*);
void PrintPlayerGames(BTREE, char*);
int BtreeDeep(BTREE);
BOOLEAN ChangePlayerName(BTREE, char*, char*);
void BtreeFree(BTREE*);
void MaisDireita(BTREE);
BOOLEAN RemoverPlayer(BTREE, char*);

int main()
{
	BTREE Btree;

	PLAYER* players[STAGES];
	char file_name[MAX_NAME];
	char nome[MAX_NAME];
	char Novonome[MAX_NAME];

	if (ReadPlayersFromFile(players, "torneio.txt"))
	{
		Btree = CreateBtree(players, 0, STAGES);  //começa em 0 a ler
		printf("\nNúmero de participantes: %d\n", CountLeafs(Btree)); //nr de participantes são as folhas
		printf("\nLista de Participantes:\n");
		PrintLeaf(Btree);
		printf("\nNumero de sets: %d", CountTotalSets(Btree));
		printf("\nVencedor do torneio: %s", DATA(Btree)->name);
		printf("\n Jogo da Final: ");
		PrintGame(Btree);
		printf("\n Lista de jogos: \n");
		PrintALLGames(Btree);
		printf("Qual o nome do jogador?");
		gets(nome);
		printf("\n Sets ganhos por um player %s: %d\n",nome, PlayerSetsGanhos(Btree,nome));
		printf("\n Sets jogados por um player %s: %d\n",nome, PlayerSetsJogados(Btree, nome));
		printf("\n A arvore tem %d de altura\n", BtreeDeep(Btree));
		printf("\n O nome do jogador a mudar: ");
		gets(nome);
		printf("\n O novo nome do jogador: ");
		gets(Novonome);
		ChangePlayerName(Btree, nome, Novonome);
		printf("Jogador mais a direita: ");
		MaisDireita(Btree);
		BtreeFree(&Btree);
		RemoverPlayer(Btree, "Player6");
		PrintLeaf(Btree);
	}
	else
		printf("ERRO na leitura do ficheiro\n");

	return 0;
}

BTREE_NODE* NewBtreeNode(PLAYER* data)
{
	BTREE_NODE* tmp_pt;

	if ((tmp_pt = (BTREE_NODE*)malloc(sizeof(BTREE_NODE))) != NULL)  //criar novo nó ou seja alocar memória
	{
		DATA(tmp_pt) = data;  //colocar data
		LEFT(tmp_pt) = RIGHT(tmp_pt) = NULL; //filhos em null
	}
	return tmp_pt;
}

BTREE_NODE* InitNode(PLAYER* ptr_data, BTREE_NODE* node1, BTREE_NODE* node2) //já temos dois filhos queremos é adicionar pai
{
	BTREE_NODE* tmp_pt = NULL;
	tmp_pt = NewBtreeNode(ptr_data);
	LEFT(tmp_pt) = node1;
	RIGHT(tmp_pt) = node2;
	return(tmp_pt);
}

BTREE_NODE* CreateBtree(PLAYER** v, int i, int size)
{
	if (i >= size)
		return(NULL);
	else
		return(InitNode(*(v + i), CreateBtree(v, 2 * i + 1, size), CreateBtree(v, 2 * i + 2, size))); //vai adicionar nó
	//ou seja, pai e dois filhos, pai com init node, e nó da direita e da esquerda com CreateBtree
	//+1 pois primeiro o da esquerda e +2 para depois o da direita
}

STATUS ReadPlayersFromFile(PLAYER** players, char* file_name)
{
	FILE* fp;
	int j, i = 0;

	PLAYER* ptr_data;

	if ((fp = fopen(file_name, "r")) != NULL)
	{
		while (!feof(fp))
		{
			if ((ptr_data = (PLAYER*)malloc(sizeof(PLAYER))) != NULL)  //se existir
			{
				fscanf(fp, "%[^;];", ptr_data->name); //nome
				fscanf(fp, "%d\n", &ptr_data->sets); //sets
				players[i] = ptr_data; //colocar num vetor de players
				i++;  //número dos jogadores a incrementar
			}
			else
			{
				for (j = i; j >= 0; j--)  //se der erro, volta atrás libertando a memória
					free(players[j]);
				return(ERROR);
			}
		}
		fclose(fp);
		return(OK);
	}
	else
		return(ERROR);
}

BOOLEAN BtreeLeaf(BTREE_NODE* btree)
{
	return ((LEFT(btree) == NULL) && (RIGHT(btree) == NULL)) ? TRUE : FALSE; //é folha se o ponteiro da direira e da esquerda apontar para null
}

int CountLeafs(BTREE btree) {
	if (BtreeLeaf(btree))
		return 1;
	return CountLeafs(LEFT(btree)) + CountLeafs(RIGHT(btree)); //somar folhas da esquerda e folhas da direta
}

void PrintLeaf(BTREE btree) {
	if (btree == NULL)
		return;
	if (BtreeLeaf(btree))
		printf("\n%s", DATA(btree)->name);
	else {
		PrintLeaf(LEFT(btree));
		PrintLeaf(RIGHT(btree)); //preorder
	}
}

int CountTotalSets(BTREE btree) {
	int i = 0;
	if (btree != NULL) {
		i = DATA(btree)->sets + CountTotalSets(LEFT(btree)) + CountTotalSets(RIGHT(btree));
	}
	return i;
}


void PrintGame(BTREE btree) {
	if (btree != NULL && !BtreeLeaf(btree)) {
		printf("\t %s (%d)  <----> (%d) %s\n",
			DATA(LEFT(btree))->name,
			DATA(LEFT(btree))->sets,
			DATA(RIGHT(btree))->sets,
			DATA(RIGHT(btree))->name
		);
	}
}

void PrintALLGames(BTREE btree) {
	if (btree != NULL && !BtreeLeaf(btree)) {
		PrintALLGames(LEFT(btree));
		PrintALLGames(RIGHT(btree));
		PrintGame(btree);
	}
}

int PlayerSetsGanhos(BTREE btree, char* nome)
{
	int i = 0;
	if (btree != NULL) {
		if (strcmp(nome, DATA(btree)->name) == 0) { //procurar por um jogador na arvore toda
			i += DATA(btree)->sets; //na raiz
		}
		i += PlayerSetsGanhos(LEFT(btree), nome) + PlayerSetsGanhos(RIGHT(btree), nome); //ver do lado esquerdo e do lado direito
	}

	return i;
}

int PlayerSetsJogados(BTREE btree, char* nome)
{
	int soma = 0;
	if (btree != NULL && !BtreeLeaf(btree)) {
		if ((strcmp(nome, (DATA(LEFT(btree))->name) == 0) || (strcmp(DATA(RIGHT(btree))->name, nome) ==0 )) { //vê jogos na raiz
			soma += DATA(LEFT(btree))->sets + DATA(RIGHT(btree))->sets;
		}
		soma += PlayerSetsGanhos(LEFT(btree), nome); //vê do lado esquerdo
		soma += PlayerSetsGanhos(RIGHT(btree), nome); //vê do lado direito
	}
	
	return soma;
}

void PrintPlayerGames(BTREE btree, char* nome)
{
	if (btree != NULL && !BtreeLeaf(btree)) {
		if ((strcmp(nome, (DATA(LEFT(btree))->name) == 0) || (strcmp(DATA(RIGHT(btree))->name, nome) == 0)) { //se tiver na raiz imprime
			PrintGame(btree);
		}
		PrintPlayerGames(LEFT(btree),nome); // se não vê do lado esquerdo
		PrintPlayerGames(RIGHT(btree),nome); //vê do lado direito
	}

	return;
}

int BtreeDeep(BTREE btree) {
	int deep = 0, left, right;

	if (btree != NULL) {
		left = BtreeDeep(LEFT(btree)); //guardar o deep do lado esquerdo
		right = BtreeDeep(RIGHT(btree)); //guardar o deep do lado direito
		deep = 1 + ((left > right) ? left : right); // : é se não ...  o maior deles mais um, ou seja, mais a raiz
	}
	return deep;
}

BOOLEAN ChangePlayerName(BTREE btree, char*nome1, char*nome2)
{
	BOOLEAN find = FALSE;
	if (btree != NULL) {
		if (strcmp(DATA(btree)->name, nome1) == 0)  //vê na raiz o nome, se for igual troca
			strcpy(DATA(btree)->name, nome2);
		find = TRUE;
		ChangePlayerName(LEFT(btree), nome1, nome2); // se não for a raiz vê do lado esquerdo
		ChangePlayerName(RIGHT(btree), nome1, nome2); //vê do lado direito
	}
}

void BtreeFree(BTREE *btree)
{
	if (*btree != NULL) {
		BtreeFree(&LEFT(*btree));
		BtreeFree(&RIGHT(*btree));
		free(DATA(*btree));
		free(*btree);
		*btree = NULL;
	}
}

void MaisDireita(BTREE bt) {
	while (RIGHT(bt) != NULL) {
		bt = RIGHT(bt);
	}

	printf("%s", DATA(bt)->name);
		
}

BOOLEAN RemoverPlayer(BTREE bt, char* name) {
	BOOLEAN find = FALSE;
	if (bt != NULL && !BtreeLeaf(bt)) {
		if (strcmp(DATA(LEFT(bt))->name, name) == 0) {
			find = TRUE;
			BtreeFree(&LEFT(bt));
			return TRUE;
		}
		if (strcmp(DATA(RIGHT(bt))->name, name) == 0) {
			find = TRUE;
			BtreeFree(&RIGHT(bt));
			return TRUE;

		}

		return find;
	}

}


