#include<stdio.h>
#include<stdlib.h>
#include<conio.h>

typedef struct _data{
    int dia;
    int mes;
    int ano;
}DATA;

typedef struct _aluno{
    int numero;
    char nome[50];
    DATA dataNascimento;
}ALUNO;

typedef struct {
    int numero;
    char nome[50];
    DATA* dataNascimento;
}ALUNOP;

typedef struct _pessoa{
    char nome[50];
    int idade;
    struct _pessoa* pai;
}PESSOA;

int main(int argc, char*argv[]){

    ALUNO a;
    ALUNO* b;

    a.numero=12345;
    strcpy(a.nome,"Joao");
    a.dataNascimento.dia=20;
    a.dataNascimento.ano=2000;
    a.dataNascimento.mes=5;

    printf("\nNome: $s \nNumero: %d \nDia: %d \nMes %d \nAno: %d ",
            a.nome, a.numero, a.dataNascimento.dia, a.dataNascimento.mes, a.dataNascimento.ano);

    
    b=(ALUNO*)malloc(sizeof(ALUNO));
    b->numero=1236;
    strcpy(b->nome, "Henrique");
    b->dataNascimento.dia=12;
    b->dataNascimento.mes=1;
    b->dataNascimento.ano=1999;

    printf("\nNome: $s \nNumero: %d \nDia: %d \nMes %d \nAno: %d ",
            b->nome, b->numero, b->dataNascimento.dia, b->dataNascimento.mes, b->dataNascimento.ano);


    ALUNOP x;
    ALUNOP *y;
    DATA d;
    d.dia = 12;
    d.mes = 3;
    d.ano = 2020;

    x.numero=1234;
    strcpy(x.nome, "Antonio");
    x.dataNascimento = &d;

    printf("\nNome: $s \nNumero: %d \nDia: %d \nMes %d \nAno: %d ",
            x.nome, x.numero, x.dataNascimento->dia, x.dataNascimento->mes, x.dataNascimento->ano);


    y=(ALUNOP*)malloc(sizeof(ALUNOP));
    y->dataNascimento=(DATA*)malloc(sizeof(DATA));

    printf("\nIntroduza os dados do aluno: ");
    printf("\tNome: ");
    gets(y->nome);
    printf("\tNumero:");
    scanf("%d", &(y->numero));
    printf("\tDia:");
    scanf("%d", &(y->dataNascimento->dia));
    printf("\tMes:");
    scanf("%d", &(y->dataNascimento->mes));
    printf("\tAno:");
    scanf("%d", &(y->dataNascimento->ano));

    printf("\nNome: $s \nNumero: %d \nDia: %d \nMes %d \nAno: %d ",
            y->nome, y->numero, y->dataNascimento->dia, y->dataNascimento->mes, y->dataNascimento->ano);

    

    PESSOA r;
    PESSOA* t;

    r.idade = 23;
    strcpy(r.nome, "Silva");
    r.pai = NULL;
    t=(PESSOA*)malloc(sizeof(PESSOA));
    t->idade = 45;
    strcpy(t->nome, "Pedro Silva");
    t->pai = NULL;

    r.pai = t;

    printf("\nNome: %s \nIdade: %d \nNome do Pai %s \nIdade do Pai: %d ",
            r.nome, r.idade, r.pai->nome, r.pai->idade);

    
    return 0;
}