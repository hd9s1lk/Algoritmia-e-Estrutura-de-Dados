#include<stdlib.h>
#include<stdio.h>
#include<conio.h>

typedef enum _BOOLEAN {FALSE=0, TRUE=1} BOOLEAN;

int *MemoryAlloc(int dim); //* (ponteiro) é o endereço de memória da variável
void ReadArray(int *w, int dim);

void main(void) 
{ 
 int dim,i, *v = NULL; 
 
 printf("Dimensão do vector: "); 
 scanf("%d",&dim);               // o & comercial vai alterar o valor a partir do endereço de memória da variável, ou seja,
                                // vai alterar o valor de onde está a variável, independente de qual variável seja
 
 if((v = MemoryAlloc(dim)) == NULL) 
  printf("ERRO na alocação de memória"); 
 else 
 { 
  ReadArray(v,dim); 
  for (i=0; i<dim; i++) 
    printf("V[%d] = %d\n",i,*(v+i)); //*(v+i)==v[i] 
  free(v);                           // liberta a memória
 }

 printf("Endereco da variavel dim = %p", &dim);
 printf("Endereco da variavel dim = %p", &dim+1);
} 


int * MemoryAlloc(int dim)   //devolve o endereço da memória de w, já que a função é do tipo int*
{ 
 int *w = NULL; 
 
 w = (int *) malloc(dim*sizeof(int)); 
 return(w); 
}

void ReadArray(int *w, int dim) //como é int, ao incrementar ele soma 4 bytes, se fosse double ele somava 8 bytes
{ 
 int i; 
 
 for (i=0; i<dim; i++) 
 { 
  printf("\tV[%d]= ",i); 
  scanf("%d",w+i); 
 } 
} 

